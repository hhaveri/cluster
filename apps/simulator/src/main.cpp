#include "simulator.h"
#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

namespace
{
const char* const APP_URI("com.cluster.simulator");
}

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QTranslator translator;
    translator.load(QStringLiteral("clustersimulator_") + QLocale::system().name(), QStringLiteral(":/translations/"));
    app.installTranslator(&translator);

    qmlRegisterUncreatableType<Simulator>(APP_URI, 1, 0, "Simulator", QStringLiteral("Cannot create Simulator."));
    qmlRegisterUncreatableType<Telemetry>(APP_URI, 1, 0, "Telemetry", QStringLiteral("Cannot create Telemetry."));

    Simulator simulator;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("simulator"), &simulator);
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    int result(-1);
    if (!engine.rootObjects().isEmpty()) {
        result = app.exec();
    }

    return result;
}

