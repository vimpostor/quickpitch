#ifndef PITCHBUFFER_H
#define PITCHBUFFER_H

#include <QIODevice>
#include <QBuffer>
#include <queue>
#include <QtCharts>
#include <QAudioInput>

#include "util.h"

extern "C" {
#include "aubio.h"
}

#define BUF_SIZE 8192
#define HOP_SIZE 2048

class PitchBuffer : public QIODevice
{
	Q_OBJECT
public:
	explicit PitchBuffer(QObject *parent = nullptr);

	bool getSamples(fvec_t *samplesDest);
	QLineSeries *series = nullptr;
	void setSampleType(QAudioFormat::SampleType type, int size);
signals:
	void samplesReady();
protected:
	qint64 readData(char *data, qint64 maxlen);
	qint64 writeData(const char *data, qint64 len);
private:
	std::vector<float> getFloatSamples(const char *data, qint64 len);
	std::queue<float> m_buf;
	QAudioFormat::SampleType sampleType = QAudioFormat::SampleType::Float;
	int sampleSize = sizeof(float);
};

#endif // PITCHBUFFER_H
