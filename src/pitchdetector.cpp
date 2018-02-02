#include "pitchdetector.h"
#include <QDebug>

PitchDetector::PitchDetector(QObject *parent) : QObject(parent)
{
	m_format.setSampleRate(8000);
	// mono sound
	m_format.setChannelCount(1);
	// aubio requires float
	m_format.setSampleType(QAudioFormat::SampleType::Float);
	// floats have a size of 32 bit
	m_format.setSampleSize(sizeof(float) * 8);
	m_format.setCodec("audio/pcm");
	m_rec = new QAudioInput(m_format, this);
	connect(&m_dev, SIGNAL(samplesReady()), this, SLOT(analyzeSamples()));

	// aubio init
	m_aubioPitch = new_aubio_pitch("default", BUF_SIZE, HOP_SIZE, 8000);
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
}

void PitchDetector::analyzeSamples()
{
	// load the samples
	if (!m_dev.getSamples(m_aubioIn)) {
		qDebug() << "false update";
		return;
	}
	aubio_pitch_do(m_aubioPitch, m_aubioIn, m_aubioOut);
	m_lastPitch = m_aubioOut->data[0];
	m_lastConfidence = aubio_pitch_get_confidence(m_aubioPitch);
	if (m_lastConfidence >= m_confidenceThreshold) {
		m_lastConfidentPitch = m_lastPitch;
	}
	emit samplesAnalyzed();
}
