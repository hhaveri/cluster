#include "application.h"
#include <QDebug>

namespace {
const QString TELEMETRY(QStringLiteral("telemetry"));
}

Application::Application(QObject* parent)
    : QObject(parent)
{
    mBusClient.connectTo();
    mBusClient.moveToThread(&mBusThread);
    mBusThread.start();

    connect(&mBusClient, &BusClient::messageReceived, this, [this](const QVariantMap& message) {
        mTelemetry.fromVariantMap(message.value(TELEMETRY).toMap());
    });
}

Application::~Application() {
    mBusThread.quit();
    mBusThread.wait();
}

Telemetry* Application::telemetry()
{
    return &mTelemetry;
}

