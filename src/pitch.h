#ifndef PITCH_H
#define PITCH_H

#include <math.h>
#include <string>
#include <QObject>

#include "util.h"

#define A_PITCH 440.f
#define A_OCTAVE 4

class Pitch
{
	Q_GADGET
	Q_PROPERTY(float frequency READ getFrequency())
	Q_PROPERTY(float confidence READ getConfidence())
	Q_PROPERTY(int offset READ getOffset())
	Q_PROPERTY(QString noteLong READ getNoteLong())
	Q_PROPERTY(QString note READ getNote())
	Q_PROPERTY(float accuracy READ getAccuracy())
	Q_PROPERTY(int octave READ getOctave())
public:
	Pitch();
	Pitch(float frequency, float confidence = 1.f);

	void setFrequency(const float f);
	float getFrequency() const;
	void setConfidence(const float c);
	float getConfidence() const;
	void setPitch(const float frequency, const float confidence);
	int getOffset() const;
	QString getNoteLong() const;
	QString getNote() const;
	float getAccuracy() const;
	int getOctave() const;

	static float offsetToFrequency(int aOffset);
	static int frequencyToOffset(float f);
	static QString offsetToNote(int o);
	static float pitchToAccuracy(const float frequency, const int offset);
	static int offsetToOctave(int aOffset);

	static const QString noteNames[12];
	static constexpr float halfNoteDiff = std::pow(2.f, 1.f / 12);
	static constexpr float logHalfNoteDiff = Util::log2(halfNoteDiff);
private:
	float m_frequency;
	float m_confidence;
};

Q_DECLARE_METATYPE(Pitch)

bool operator ==(const Pitch &l, const Pitch &r);
bool operator !=(const Pitch &l, const Pitch &r);

#endif // PITCH_H
