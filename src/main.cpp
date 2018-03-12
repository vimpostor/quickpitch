#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QQuickStyle>

#include "pitchdetector.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QQuickStyle::setStyle(QLatin1String("Material"));
	QGuiApplication app(argc, argv);

	qmlRegisterType<PitchDetector>("PitchDetector", 1, 0, "PitchDetector");

	QQmlApplicationEngine engine;
	engine.addImportPath(QCoreApplication::applicationDirPath() + QDir::separator() + QLatin1String("..") + \
						 QDir::separator() + QLatin1String("fluid") + QDir::separator() + QLatin1String("qml"));
	engine.addImportPath(QCoreApplication::applicationDirPath() + QDir::separator() + QLatin1String("qml"));
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
