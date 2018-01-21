#ifndef SERVER_H
#define SERVER_H

#include <ipc_global.h>
#include <QLocalServer>
#include <QObject>

/**
 * @brief The Server class
 */
class IPC_SHARED_EXPORT Server final
    : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject* parent = nullptr);

    bool listen(const QString& name);
    void send(const QByteArray& message, QLocalSocket& client);

    const QList<QLocalSocket*> clients() const;

signals:
    void connected(QLocalSocket& client);
    void disconnected(QLocalSocket& client);
    void receive(const QByteArray& message, QLocalSocket& client);

private:
    QLocalServer mServer;
    QMap<QLocalSocket*, qint64> mClientSizeMap;
};

#endif // SERVER_H

