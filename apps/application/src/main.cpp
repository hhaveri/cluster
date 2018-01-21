#include "application.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

namespace
{
const char* const APP_URI("com.cluster.application");
}

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QTranslator translator;
    translator.load(QStringLiteral("clusterapplication_") + QLocale::system().name(), QStringLiteral(":/translations/"));
    app.installTranslator(&translator);

    qmlRegisterUncreatableType<Application>(APP_URI, 1, 0, "Application", QStringLiteral("Cannot create Simulator."));
    qmlRegisterUncreatableType<Telemetry>(APP_URI, 1, 0, "Telemetry", QStringLiteral("Cannot create Telemetry."));

    Application application;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("application"), &application);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    int result(-1);
    if (!engine.rootObjects().isEmpty()) {
        result = app.exec();
    }

    return result;
}

