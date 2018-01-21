#include "simulator.h"
#include <QCoreApplication>
#include <QDebug>

namespace {
const QString CLUSTER_APP(QStringLiteral("/clusterapplication"));
const QString CLUSTER_BUS(QStringLiteral("/clusterbus"));

const QString TELEMETRY(QStringLiteral("telemetry"));
}

Simulator::Simulator(QObject* parent)
    : QObject(parent)
{
    // Broadcast changes in individual telemetry values
    connect(&mTelemetry, &Telemetry::leftSignalChanged, this, [this](bool /*leftSignal*/) {
        mBusClient.sendMessage(QVariantMap{ { TELEMETRY, mTelemetry.leftSignalToVariantMap() } });
    });
    connect(&mTelemetry, &Telemetry::rightSignalChanged, this, [this](bool /*rightSignal*/) {
        mBusClient.sendMessage(QVariantMap{ { TELEMETRY, mTelemetry.rightSignalToVariantMap() } });
    });

    // 100ms broadcast interval for all telemetry data
    mSpeedBroadcastTimer.setInterval(100);
    mSpeedBroadcastTimer.setTimerType(Qt::PreciseTimer);
    connect(&mSpeedBroadcastTimer, &QTimer::timeout, this, [this] {
        mBusClient.sendMessage(QVariantMap{ { TELEMETRY, mTelemetry.toVariantMap() } });
    });

    // When clusterbus is ready, connect & autostart clusterapplication
    connect(&mClusterBus, &QProcess::readyReadStandardOutput, this, [this] {
        mBusClient.connectTo();
        mSpeedBroadcastTimer.start();

        mClusterApp.setProgram(QCoreApplication::applicationDirPath() + CLUSTER_APP);
        mClusterApp.start();
    });

    // Start clusterbus first
    mClusterBus.setProgram(QCoreApplication::applicationDirPath() + CLUSTER_BUS);
    mClusterBus.start();
}

Simulator::~Simulator()
{
    mClusterApp.kill();
    mClusterBus.kill();
}

Telemetry* Simulator::telemetry()
{
    return &mTelemetry;
}

