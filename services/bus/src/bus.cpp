#include "bus.h"
#include <QCoreApplication>
#include <QDebug>
#include <QJsonDocument>
#include <QLocalSocket>
#include <QTextStream>

namespace
{
const QString ID(QStringLiteral("id"));

// Bus message ids
const QString MESSAGE(QStringLiteral("message"));
const QString REGISTER(QStringLiteral("register"));

// Bus message fields
const QString URI(QStringLiteral("uri"));

// Bus server uri
const QString BUS_URI(QStringLiteral("com.cluster.bus"));

QVariantMap fromJson(const QByteArray& byteArray)
{
    return QJsonDocument::fromJson(byteArray).toVariant().toMap();
}
} // namespace

Bus::Bus(QObject *parent)
    : QObject(parent)
{
    connect(&mServer, &Server::receive, this, &Bus::messageReceived);

    // Clean up client services
    connect(&mServer, &Server::disconnected, this, [this](QLocalSocket& client) {
        const QStringList uris(mServices.keys(&client));
        for (const QString& uri : uris) {
            mServices.remove(uri);
        }
    });
}

bool Bus::start()
{
    bool started(false);

    // Let's start only one instance of the service
    QLocalSocket socket;
    socket.connectToServer(BUS_URI);
    if (!socket.waitForConnected(100)) {
        started = mServer.listen(BUS_URI);
    }

    if (started) {
        QTextStream textStream(stdout, QIODevice::WriteOnly);
        textStream << "Bus ready!\n";
        textStream.flush();
    }
    else {
        QTextStream textStream(stderr, QIODevice::WriteOnly);
        textStream << "Bus failed to start!\n";
        textStream.flush();
    }

    return started;
}

void Bus::messageReceived(const QByteArray& message, QLocalSocket& client)
{
    const QVariantMap map(fromJson(message));
    const QString id(map.value(ID).toString());

    if (id == QStringLiteral("register")) {
        const QString uri(map.value(URI).toString());
        mServices[uri] = &client;
    }
    else if (id == QStringLiteral("message")) {
        const QString uri(map.value(URI).toString());

        // Empty uri is treated as broadcast
        if (uri.isEmpty()) {
            for (QLocalSocket* receiver : mServer.clients()) {
                if (receiver != &client) {
                    mServer.send(message, *receiver);
                }
            }
        }
        else {
            QLocalSocket* service(mServices.value(uri));
            if (service) {
                mServer.send(message, *service);
            }
        }
    }
}

