#ifndef APPLICATION_H
#define APPLICATION_H

#include "telemetry.h"
#include <busclient.h>
#include <QThread>

/**
 * @brief The Application class
 */
class Application final
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Telemetry* telemetry READ telemetry CONSTANT)

public:
    explicit Application(QObject* parent = nullptr);
    ~Application();

    Telemetry* telemetry();

private:
    QThread mBusThread;
    BusClient mBusClient;

    Telemetry mTelemetry;
};

#endif // APPLICATION_H

