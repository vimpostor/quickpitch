#include "pitch.h"
#include <QDebug>

const QString Pitch::noteNames[12] = {
	"a", "b", "h", "c", "cis", "d", "dis", "e", "f", "fis", "g", "gis"
};


Pitch::Pitch() : Pitch(0)
{
}

Pitch::Pitch(float frequency, float confidence)
{
	setPitch(frequency, confidence);
}

void Pitch::setFrequency(const float f)
{
	m_frequency = f;
}

float Pitch::getFrequency() const
{
	return m_frequency;
}

void Pitch::setConfidence(const float c)
{
	m_confidence = c;
}

float Pitch::getConfidence() const
{
	return m_confidence;
}

void Pitch::setPitch(const float frequency, const float confidence)
{
	setFrequency(frequency);
	setConfidence(confidence);
}

int Pitch::getOffset() const
{
	return frequencyToOffset(getFrequency());
}

QString Pitch::getNoteLong() const
{
	return getNote() + QString::number(getOctave());
}

QString Pitch::getNote() const
{
	if (getFrequency() <= 0) {
		return "No Pitch";
	}
	return offsetToNote(getOffset());
}

float Pitch::getAccuracy() const
{
	return pitchToAccuracy(getFrequency(), getOffset());
}

int Pitch::getOctave() const
{
	return offsetToOctave(getOffset());
}

float Pitch::offsetToFrequency(int aOffset)
{
	return A_PITCH * std::pow(halfNoteDiff, aOffset);
}

// y = 440*s^x
// y/440 = s^x
// log_s(y/440) = x
int Pitch::frequencyToOffset(float f)
{
	if (f <= 0) {
		return 0;
	}
	const float arg = f / 440;
	return std::round(std::log2(arg) / logHalfNoteDiff);
}

QString Pitch::offsetToNote(int o)
{
	return noteNames[(o + 120) % 12];
}

float Pitch::pitchToAccuracy(const float frequency, const int offset)
{
	const float perfectPitch = offsetToFrequency(offset);
	if (frequency >= perfectPitch) {
		return (frequency - perfectPitch) / (offsetToFrequency(offset + 1) - frequency);
	} else {
		return -1 * (frequency - perfectPitch) / (offsetToFrequency(offset - 1) - frequency);
	}
}

int Pitch::offsetToOctave(int aOffset)
{
	return A_OCTAVE + std::floor((aOffset + 9) / 12.f);
}

bool operator ==(const Pitch &l, const Pitch &r)
{
	return (l.getFrequency() == r.getFrequency()) && (l.getConfidence() == r.getConfidence());
}

bool operator !=(const Pitch &l, const Pitch &r)
{
	return !(l == r);
}
