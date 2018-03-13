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

void PitchBuffer::setSampleType(QAudioFormat::SampleType type, int size)
{
	m_sampleType = type;
	m_sampleSize = size;
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
	auto samples = getFloatSamples(data, len);
	const int numberNewSamples = samples.size();
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
		const float sample = samples[i];
		m_buf.push(sample);
		points.push_back(QPointF(chartOffset + i, sample));
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

std::vector<float> PitchBuffer::getFloatSamples(const char *data, qint64 len)
{
	const auto signedInt16ToFloat = [](const int16_t i){ return i / 32768.f; };

	const unsigned char *ptr = reinterpret_cast<const unsigned char *>(data);
	std::vector<float> result;
	const int numberSamples = len / m_sampleSize;
	result.resize(numberSamples);
	for (int i = 0; i < numberSamples; ++i) {
		float sample;
		switch (m_sampleType) {
		case QAudioFormat::SampleType::Float:
			sample = *reinterpret_cast<const float*>(ptr);
			break;
		case QAudioFormat::SampleType::SignedInt: {
			// for the time being just assume, that it is a 16 bit int
			int16_t s = *reinterpret_cast<const int16_t*>(ptr);
			sample = signedInt16ToFloat(s);
			break;
		}
		default:
			sample = 0;
			break;
		}
		result[i] = sample;
		ptr += m_sampleSize;
	}
	return result;
}
