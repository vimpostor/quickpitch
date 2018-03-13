#include "pitchdetector.h"
#include <QDebug>

PitchDetector::PitchDetector(QObject *parent) : QObject(parent)
{
	m_format.setSampleRate(SAMPLE_RATE);
	m_format.setCodec("audio/pcm");
	// mono sound
	m_format.setChannelCount(1);
	// aubio requires float
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
	m_rec = new QAudioInput(m_format, this);
	connect(&m_dev, SIGNAL(samplesReady()), this, SLOT(analyzeSamples()));

	// aubio init
	m_aubioPitch = new_aubio_pitch(m_algorithm.toLatin1().data(), BUF_SIZE, HOP_SIZE, SAMPLE_RATE);
	m_aubioIn = new_fvec(HOP_SIZE);
	m_aubioOut = new_fvec(1);
}

PitchDetector::~PitchDetector()
{
	del_aubio_pitch(m_aubioPitch);
	del_fvec(m_aubioIn);
	del_fvec(m_aubioOut);
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

void PitchDetector::setAlgorithm(QString algorithm)
{
	if (algorithm == m_algorithm) {
		return;
	}
	m_algorithm = algorithm;
	// create new aubio pitch object
	// CRITICAL section
	del_aubio_pitch(m_aubioPitch);
	m_aubioPitch = new_aubio_pitch(m_algorithm.toLatin1().data(), BUF_SIZE, HOP_SIZE, SAMPLE_RATE);
}

void PitchDetector::setLineSeries(QLineSeries *series)
{
	m_dev.series = series;
}

void PitchDetector::analyzeSamples()
{
	// while new samples are available
	while (m_dev.getSamples(m_aubioIn)) {
		aubio_pitch_do(m_aubioPitch, m_aubioIn, m_aubioOut);
		float frequency = m_aubioOut->data[0];
		float confidence = aubio_pitch_get_confidence(m_aubioPitch);
		m_currentPitch.setPitch(frequency, confidence);
		if (confidence >= m_confidenceThreshold) {
			m_lastConfidentPitch = m_currentPitch;
		}
		emit samplesAnalyzed();
	}
}
