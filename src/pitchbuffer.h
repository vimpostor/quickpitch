#ifndef PITCHBUFFER_H
#define PITCHBUFFER_H

#include <QIODevice>
#include <QBuffer>
#include <queue>

extern "C" {
#include "aubio.h"
}

#define BUF_SIZE 2048
#define HOP_SIZE 512

class PitchBuffer : public QIODevice
{
	Q_OBJECT
public:
	explicit PitchBuffer(QObject *parent = nullptr);

	bool getSamples(fvec_t *samplesDest);
signals:
	void samplesReady();
protected:
	qint64 readData(char *data, qint64 maxlen);
	qint64 writeData(const char *data, qint64 len);
private:
	std::queue<float> m_buf;
};

#endif // PITCHBUFFER_H
