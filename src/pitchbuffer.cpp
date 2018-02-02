#include "pitchbuffer.h"
#include <QDebug>

PitchBuffer::PitchBuffer(QObject *parent) : QIODevice(parent)
{
}

bool PitchBuffer::getSamples(fvec_t *samplesDest)
{
	if (m_buf.size() < HOP_SIZE) {
		return false;
	}
	for (int i = 0; i < HOP_SIZE; ++i) {
		fvec_set_sample(samplesDest, m_buf.front(), i);
		m_buf.pop();
	}
	return true;
}

qint64 PitchBuffer::readData(char *data, qint64 maxlen)
{
	Q_UNUSED(data)
	Q_UNUSED(maxlen)
	return -1;
}

qint64 PitchBuffer::writeData(const char *data, qint64 len)
{
	const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
	const int numberNewSamples = len / sizeof(float);
	for (int i = 0; i < numberNewSamples; ++i) {
		const float sample = *reinterpret_cast<const float*>(ptr);
		m_buf.push(sample);
		ptr += sizeof(float);
	}
	if (m_buf.size() >= HOP_SIZE) {
		emit samplesReady();
	}
	return len;
}
