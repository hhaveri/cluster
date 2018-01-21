#include "busclient.h"
#include <QDebug>
#include <QJsonDocument>

namespace
{
const QString ID(QStringLiteral("id"));

const QString PAYLOAD(QStringLiteral("payload"));
const QString URI(QStringLiteral("uri"));

const QString REGISTER(QStringLiteral("register"));
const QString MESSAGE(QStringLiteral("message"));

QByteArray toJson(const QVariantMap& map)
{
    return QJsonDocument::fromVariant(map).toJson(QJsonDocument::Compact);
}

QVariantMap fromJson(const QByteArray& byteArray)
{
    return QJsonDocument::fromJson(byteArray).toVariant().toMap();
}
} // namespace

BusClient::BusClient(QObject* parent)
    : QObject(parent)
{
    connect(&mClient, &Client::receive, this, [this](const QByteArray& message) {
        const QVariantMap map(fromJson(message));
        emit messageReceived(map.value(PAYLOAD).toMap());
    });
}

bool BusClient::connectTo(const QString& name)
{
    return mClient.connectTo(name);
}

bool BusClient::isConnected() const
{
    return mClient.isConnected();
}

void BusClient::registerService(const QString& uri)
{
    if (isConnected()) {
        const QVariantMap map{
            { ID, REGISTER },
            { URI, uri }
        };

        mClient.send(toJson(map));
    }
}

void BusClient::sendMessage(const QVariantMap& message, const QString& uri)
{
    if (isConnected()) {
        const QVariantMap map{
            { ID, MESSAGE },
            { URI, uri },
            { PAYLOAD, message }
        };

        mClient.send(toJson(map));
    }
}

