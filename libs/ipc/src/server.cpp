#include "server.h"
#include <QDebug>
#include <QJsonDocument>
#include <QLocalSocket>

Server::Server(QObject* parent)
    : QObject(parent)
{
    connect(&mServer, &QLocalServer::newConnection, this, [this] {
        QLocalSocket* client(mServer.nextPendingConnection());
        if (client) {
            mClientSizeMap.insert(client, -1);

            connect(client, &QLocalSocket::disconnected, this, [this, client] {
                mClientSizeMap.take(client);
                emit disconnected(*client);

                client->deleteLater();
            });
            connect(client, &QLocalSocket::readyRead, this, [this, client] {
                bool messageReceived(true);
                while (!client->atEnd() && messageReceived) {
                    qint64 messageSize(mClientSizeMap.value(client));

                    // Read incoming message size
                    if (messageSize < 0 && client->bytesAvailable() >= static_cast<qint64>(sizeof(messageSize))) {
                        client->read(reinterpret_cast<char*>(&messageSize), static_cast<qint64>(sizeof(messageSize)));
                        mClientSizeMap[client] = messageSize;
                    }

                    // Read & handle message if it is fully available
                    messageReceived = (client->bytesAvailable() >= messageSize);
                    if (messageReceived) {
                        const QByteArray message(client->read(messageSize));
                        mClientSizeMap[client] = -1;

                        emit receive(message, *client);
                    }
                }
            });

            emit connected(*client);
        }
    });
}

bool Server::listen(const QString& name)
{
    bool result(false);
    if (!mServer.isListening()) {
        mServer.removeServer(name);
        result = mServer.listen(name);
    }

    return result;
}

void Server::send(const QByteArray& message, QLocalSocket& client)
{
    const qint64 messageSize(message.size());

    client.write(reinterpret_cast<const char*>(&messageSize), sizeof(messageSize));
    client.write(message);
    client.flush();
}

const QList<QLocalSocket*> Server::clients() const
{
    return mClientSizeMap.keys();
}

