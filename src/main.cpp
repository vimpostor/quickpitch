#include <QApplication>
#include <QQmlApplicationEngine>
#include <QDir>
#include <QQuickStyle>
#include <QQmlContext>

#include "pitchdetector.h"
#include "settings.h"

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QQuickStyle::setStyle(QLatin1String("Material"));
	QApplication app(argc, argv);

	qmlRegisterType<PitchDetector>("PitchDetector", 1, 0, "PitchDetector");

	QQmlApplicationEngine engine;

	// context properties
	engine.rootContext()->setContextProperty("c_settings", &Settings::get());

	engine.addImportPath(QCoreApplication::applicationDirPath() + QDir::separator() + QLatin1String("..") + \
						 QDir::separator() + QLatin1String("fluid") + QDir::separator() + QLatin1String("qml"));
	engine.addImportPath(QCoreApplication::applicationDirPath() + QDir::separator() + QLatin1String("qml"));
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

	return app.exec();
}
