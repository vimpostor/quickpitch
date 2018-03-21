#include "pitchdetector.h"
#include <QDebug>

PitchDetector::PitchDetector(QObject *parent) : QObject(parent)
{
	applyFormat();
	m_rec = std::make_unique<QAudioInput>(m_format);
	connect(&m_dev, SIGNAL(samplesReady()), this, SLOT(analyzeSamples()));
}

void PitchDetector::setActive(bool active)
{
	if (active) {
		if (!m_dev.open(QIODevice::WriteOnly)) {
			qDebug() << "Something went wrong while opening the device";
		}
		m_rec->start(&m_dev);
	} else {
		m_rec->stop();
	}
	m_active = active;
}

void PitchDetector::setAlgorithm(const QString algorithm)
{
	if (algorithm == m_algorithm) {
		return;
	}
	m_algorithm = algorithm;
	m_aubio.setAlgorithm(algorithm);
}

void PitchDetector::setSampleRate(const uint sampleRate)
{
	if (sampleRate == m_sampleRate) {
		return;
	}
	m_sampleRate = sampleRate;
	applyFormat();
	m_rec = std::make_unique<QAudioInput>(m_format);
	setActive(m_active);
	m_aubio.setSampleRate(m_sampleRate);
}

void PitchDetector::setLineSeries(QLineSeries *series)
{
	m_dev.series = series;
}

void PitchDetector::applyFormat()
{
	m_format.setCodec("audio/pcm");
	// mono sound
	m_format.setChannelCount(1);
	m_format.setSampleRate(m_sampleRate);
	// we prefer floats since aubio requires floats
	m_format.setSampleType(QAudioFormat::SampleType::Float);
	// floats have a size of 32 bit
	m_format.setSampleSize(sizeof(float) * 8);
	// test if the format is supported
	QAudioDeviceInfo info = QAudioDeviceInfo::defaultInputDevice();
	if (!info.isFormatSupported(m_format)) {
		qWarning() << "Default format not supported, trying to use 16bit signed integer samples";
		m_format.setSampleType(QAudioFormat::SampleType::SignedInt);
		m_format.setSampleSize(sizeof(int16_t) * 8);
		if (!info.isFormatSupported(m_format)) {
			qWarning() << "No support for 16bit signed integer samples. Trying nearest format, the program will probably not work.";
			m_format = info.nearestFormat(m_format);
		}
	}
	m_dev.setSampleType(m_format.sampleType(), m_format.sampleSize() / 8);
}

void PitchDetector::analyzeSamples()
{
	// while new samples are available
	while (m_dev.getSamples(m_aubio.aubioIn)) {
		aubio_pitch_do(m_aubio.getAubioPitch(), m_aubio.aubioIn, m_aubio.aubioOut);
		float frequency = m_aubio.aubioOut->data[0];
		float confidence = aubio_pitch_get_confidence(m_aubio.getAubioPitch());
		m_currentPitch.setPitch(frequency, confidence);
		if (confidence >= m_confidenceThreshold) {
			m_lastConfidentPitch = m_currentPitch;
		}
		emit samplesAnalyzed();
	}
}
