#ifndef PITCHDETECTOR_H
#define PITCHDETECTOR_H

#include <QObject>
#include <QAudioInput>
#include <QUrl>
#include <memory>

#include "pitchbuffer.h"

class PitchDetector : public QObject
{
	Q_OBJECT
	Q_PROPERTY(bool active MEMBER m_active WRITE setActive NOTIFY activeChanged)
	Q_PROPERTY(float lastConfidentPitch MEMBER m_lastConfidentPitch NOTIFY samplesAnalyzed())
	Q_PROPERTY(float lastConfidence MEMBER m_lastConfidence NOTIFY samplesAnalyzed())
	Q_PROPERTY(float confidenceThreshold MEMBER m_confidenceThreshold)
public:
	explicit PitchDetector(QObject *parent = nullptr);
	~PitchDetector();

	void setActive(bool active);
	bool m_active;
signals:
	void activeChanged();
	void samplesAnalyzed();
public slots:
private:
	QAudioInput *m_rec;
	QAudioFormat m_format;
	PitchBuffer m_dev;
	aubio_pitch_t *m_aubioPitch;
	fvec_t *m_aubioIn;
	fvec_t *m_aubioOut;
	float m_lastPitch = 0;
	float m_lastConfidentPitch = 0;
	float m_lastConfidence = 0;
	float m_confidenceThreshold = .75;
private slots:
	void analyzeSamples();
};

#endif // PITCHDETECTOR_H
