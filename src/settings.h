#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
	Q_OBJECT
	Q_PROPERTY(uint sampleRate MEMBER m_sampleRate)
	Q_PROPERTY(QString algorithm MEMBER m_algorithm)
public:
	static Settings &get();
	uint m_sampleRate = 48000;
	QString m_algorithm = "default";
};

#endif // SETTINGS_H
