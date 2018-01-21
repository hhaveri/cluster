#include <QDebug>
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

int main(int argc, char *argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QTranslator translator;
    translator.load(QStringLiteral("clustergfx_") + QLocale::system().name(), QStringLiteral(":/translations/"));
    app.installTranslator(&translator);

    QDir gfxDir(app.applicationDirPath() + QStringLiteral("/gfx"));
    gfxDir.mkpath(gfxDir.path());

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    int result(-1);
    if (!engine.rootObjects().isEmpty()) {
        result = app.exec();
    }

    return result;
}

