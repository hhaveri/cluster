#ifndef CLIENT_H
#define CLIENT_H

#include <ipc_global.h>
#include <QLocalSocket>
#include <QObject>

/**
 * @brief The Client class
 */
class IPC_SHARED_EXPORT Client final
    : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject* parent = nullptr);

    bool connectTo(const QString& name);
    bool isConnected() const;

    void send(const QByteArray& message);

signals:
    void connected();
    void disconnected();
    void receive(const QByteArray& message);

private:
    QLocalSocket mClient;
    qint64 mMessageSize;
};

#endif // CLIENT_H

