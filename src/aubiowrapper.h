#ifndef AUBIOWRAPPER_H
#define AUBIOWRAPPER_H

#include "pitchbuffer.h"

class AubioWrapper
{
public:
	AubioWrapper();
	~AubioWrapper();

	void reloadAubio();
	void setAlgorithm(const QString alg);
	void setSampleRate(const uint_t s);
	aubio_pitch_t *getAubioPitch();
	fvec_t *aubioIn;
	fvec_t *aubioOut;
private:
	struct AubioPitchDeleter {
		void operator()(aubio_pitch_t *a) { del_aubio_pitch(a); }
	};
	aubio_pitch_t *constructAubioPitch(QString method, uint_t buf_size, uint_t hop_size, uint_t samplerate);
	std::unique_ptr<aubio_pitch_t, AubioPitchDeleter> m_aubioPitch;
	QString m_algorithm = "default";
	uint_t m_bufSize = BUF_SIZE;
	uint_t m_hopSize = HOP_SIZE;
	uint_t m_sampleRate = 48000;
};

#endif // AUBIOWRAPPER_H
