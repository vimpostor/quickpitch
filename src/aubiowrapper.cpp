#include "aubiowrapper.h"

AubioWrapper::AubioWrapper()
{
	reloadAubio();
	aubioIn = new_fvec(m_hopSize);
	aubioOut = new_fvec(1);
}

AubioWrapper::~AubioWrapper()
{
	del_fvec(aubioIn);
	del_fvec(aubioOut);
}

void AubioWrapper::reloadAubio()
{
	m_aubioPitch = decltype(m_aubioPitch)(constructAubioPitch(m_algorithm, m_bufSize, m_hopSize, m_sampleRate), AubioPitchDeleter());
}

void AubioWrapper::setAlgorithm(const QString alg)
{
	m_algorithm = alg;
}

void AubioWrapper::setSampleRate(const uint_t s)
{
	m_sampleRate = s;
}

aubio_pitch_t *AubioWrapper::getAubioPitch()
{
	return m_aubioPitch.get();
}

aubio_pitch_t *AubioWrapper::constructAubioPitch(QString method, uint_t buf_size, uint_t hop_size, uint_t samplerate)
{
	return new_aubio_pitch(method.toLatin1().data(), buf_size, hop_size, samplerate);
}
