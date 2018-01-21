#include "client.h"
#include <QDataStream>
#include <QDebug>

Client::Client(QObject* parent)
    : QObject(parent)
    , mMessageSize(-1)
{
    connect(&mClient, &QLocalSocket::connected, this, &Client::connected);
    connect(&mClient, &QLocalSocket::disconnected, this, &Client::disconnected);
    connect(&mClient, &QLocalSocket::readyRead, this, [this] {
        bool messageReceived(true);
        while (!mClient.atEnd() && messageReceived) {
            // Read incoming message size
            if (mMessageSize == -1 && mClient.bytesAvailable() >= static_cast<qint64>(sizeof(mMessageSize))) {
                mClient.read(reinterpret_cast<char*>(&mMessageSize), static_cast<qint64>(sizeof(mMessageSize)));
            }

            // Read & handle message if it is fully available
            messageReceived = (mClient.bytesAvailable() >= mMessageSize);
            if (messageReceived) {
                const QByteArray message(mClient.read(mMessageSize));
                mMessageSize = -1;

                emit receive(message);
            }
        }
    });
}

bool Client::connectTo(const QString& name)
{
    bool result(false);
    if (!mClient.isOpen()) {
        mClient.connectToServer(name);
        result = mClient.waitForConnected(1000);
    }

    return result;
}

bool Client::isConnected() const
{
    return mClient.isOpen();
}

void Client::send(const QByteArray& message)
{
    const qint64 messageSize(message.size());

    mClient.write(reinterpret_cast<const char*>(&messageSize), static_cast<qint64>(sizeof(messageSize)));
    mClient.write(message);
    mClient.flush();
}

