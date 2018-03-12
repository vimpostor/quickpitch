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

// TODO: Replace this with a setting - consistent in QML and C++
#define MAX_SERIES 8000

qint64 PitchBuffer::writeData(const char *data, qint64 len)
{
	const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
	const int numberNewSamples = len / sizeof(float);
	QVector<QPointF> points = series->pointsVector();
	// how much to move old samples to the left
	const int translate = numberNewSamples - MAX_SERIES + points.size();
	// move old samples to the left
	if (translate > 0) {
		for (auto &i : points) {
			i.setX(i.x() - translate);
		}
	}
	// the index of the next sample in the chart
	int chartOffset = points.size();
	if (translate > 0) {
		chartOffset -= translate;
	}
	for (int i = 0; i < numberNewSamples; ++i) {
		const float sample = *reinterpret_cast<const float*>(ptr);
		m_buf.push(sample);
		points.push_back(QPointF(chartOffset + i, sample));
		ptr += sizeof(float);
	}
	if (m_buf.size() >= HOP_SIZE) {
		emit samplesReady();
	}
	// remove excess samples from the chart
	if (points.size() > MAX_SERIES) {
		points.erase(points.begin(), points.begin() + points.size() - MAX_SERIES);
	}
	series->replace(points);
	return len;
}
