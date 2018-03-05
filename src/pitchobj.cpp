#include "pitchobj.h"
#include <QDebug>

const QString PitchObj::noteNames[12] = {
	"a", "b", "h", "c", "cis", "d", "dis", "e", "f", "fis", "g", "gis"
};


PitchObj::PitchObj() : PitchObj(0)
{
}

PitchObj::PitchObj(float frequency, float confidence)
{
	setPitch(frequency, confidence);
}

void PitchObj::setFrequency(const float f)
{
	m_frequency = f;
}

float PitchObj::getFrequency() const
{
	return m_frequency;
}

void PitchObj::setConfidence(const float c)
{
	m_confidence = c;
}

float PitchObj::getConfidence() const
{
	return m_confidence;
}

void PitchObj::setPitch(const float frequency, const float confidence)
{
	setFrequency(frequency);
	setConfidence(confidence);
}

int PitchObj::getOffset() const
{
	return frequencyToOffset(getFrequency());
}

QString PitchObj::getNoteLong() const
{
	return getNote() + QString::number(getOctave());
}

QString PitchObj::getNote() const
{
	if (getFrequency() <= 0) {
		return "No Pitch";
	}
	return offsetToNote(getOffset());
}

float PitchObj::getAccuracy() const
{
	return pitchToAccuracy(getFrequency(), getOffset());
}

int PitchObj::getOctave() const
{
	return offsetToOctave(getOffset());
}

float PitchObj::offsetToFrequency(int aOffset)
{
	return A_PITCH * std::pow(halfNoteDiff, aOffset);
}

/**
 * @brief Calculates the halftone offset from A4 for a given pitch
 *
 * We know how to calculate a given pitch from an offset, by evaluating a simple exponential term.
 * Let s = 2^(1/12). Then any pitch f can be calculated from an offset o by computing f = 440 * s^o.
 *
 * This function computes the inverse. For any frequency f, we have:
 *
 * f = 440 * s^o
 *
 * <=> f / 440 = s^o
 *
 * <=> log(f / 440) / log(s) = o
 *
 * Evaluating this inverse formula and rounding the result to the next integer yields the nearest offset for frequency f.
 * @param f The frequency of the pitch in Hz
 * @return The halftone offset from A4
 */
int PitchObj::frequencyToOffset(float f)
{
	if (f <= 0) {
		return 0;
	}
	const float arg = f / 440;
	return Util::round(Util::log2(arg) / logHalfNoteDiff);
}

QString PitchObj::offsetToNote(int o)
{
	return noteNames[(o + 120) % 12];
}

float PitchObj::pitchToAccuracy(const float frequency, const int offset)
{
	const float perfectPitch = offsetToFrequency(offset);
	if (frequency >= perfectPitch) {
		return (frequency - perfectPitch) / (offsetToFrequency(offset + 1) - frequency);
	} else {
		return -1 * (frequency - perfectPitch) / (offsetToFrequency(offset - 1) - frequency);
	}
}

int PitchObj::offsetToOctave(int aOffset)
{
	return A_OCTAVE + std::floor((aOffset + 9) / 12.f);
}

bool operator ==(const PitchObj &l, const PitchObj &r)
{
	return (l.getFrequency() == r.getFrequency()) && (l.getConfidence() == r.getConfidence());
}

bool operator !=(const PitchObj &l, const PitchObj &r)
{
	return !(l == r);
}
