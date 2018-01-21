#ifndef BUSCLIENT_H
#define BUSCLIENT_H

#include <client.h>
#include <busclient_global.h>
#include <QObject>

namespace {
// Bus server uri
const QString BUS_URI(QStringLiteral("com.cluster.bus"));
}

/**
 * @brief The BusClient class
 */
class BUSCLIENT_SHARED_EXPORT BusClient final
    : public QObject
{
    Q_OBJECT

public:
    explicit BusClient(QObject* parent = nullptr);

    bool connectTo(const QString& name = BUS_URI);
    bool isConnected() const;

    void registerService(const QString& uri);

signals:
    void messageReceived(const QVariantMap& message);

public slots:
    void sendMessage(const QVariantMap& message, const QString& uri = QString());

private:
    Client mClient;
};

#endif // BUSCLIENT_H

