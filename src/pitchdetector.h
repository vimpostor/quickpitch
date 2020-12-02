#ifndef PITCHDETECTOR_H
#define PITCHDETECTOR_H

#include <QObject>
#include <QUrl>
#include <memory>

#include "pitchbuffer.h"
#include "pitchobj.h"
#include "aubiowrapper.h"

class PitchDetector : public QObject
{
	Q_OBJECT
	Q_PROPERTY(bool active MEMBER m_active WRITE setActive NOTIFY activeChanged)
	Q_PROPERTY(PitchObj currentPitch MEMBER m_currentPitch NOTIFY samplesAnalyzed())
	Q_PROPERTY(PitchObj confidentPitch MEMBER m_lastConfidentPitch NOTIFY samplesAnalyzed())
	Q_PROPERTY(QString algorithm MEMBER m_algorithm WRITE setAlgorithm)
	Q_PROPERTY(uint sampleRate MEMBER m_sampleRate WRITE setSampleRate)
public:
	explicit PitchDetector(QObject *parent = nullptr);

	void setActive(bool active);
	void setAlgorithm(const QString algorithm);
	void setSampleRate(const uint sampleRate);
	Q_INVOKABLE void setLineSeries(QLineSeries *series);
signals:
	void activeChanged();
	void samplesAnalyzed();
public slots:
private:
	void applyFormat();

	bool m_active;
	std::unique_ptr<QAudioInput> m_rec;
	QAudioFormat m_format;
	PitchBuffer m_dev;
	AubioWrapper m_aubio;
	PitchObj m_currentPitch;
	PitchObj m_lastConfidentPitch;
	float m_confidenceThreshold = .0;
	QString m_algorithm = "default";
	uint m_sampleRate = 48000;
private slots:
	void analyzeSamples();
};

#endif // PITCHDETECTOR_H
