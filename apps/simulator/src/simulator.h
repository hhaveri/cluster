#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "telemetry.h"
#include <busclient.h>
#include <QProcess>
#include <QTimer>

/**
 * @brief The Simulator class
 */
class Simulator final
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Telemetry* telemetry READ telemetry CONSTANT)

public:
    explicit Simulator(QObject* parent = nullptr);
    ~Simulator();

    Telemetry* telemetry();

private:
    QProcess mClusterBus;
    QProcess mClusterApp;

    BusClient mBusClient;
    QTimer mSpeedBroadcastTimer;

    Telemetry mTelemetry;
};

#endif // SIMULATOR_H

