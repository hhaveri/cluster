#include "telemetry.h"
#include <QVariantMap>

namespace
{
const QString SPEED(QStringLiteral("speed"));
const QString LEFT_SIGNAL(QStringLiteral("left_signal"));
const QString RIGHT_SIGNAL(QStringLiteral("right_signal"));
}

Telemetry::Telemetry(QObject* parent)
    : QObject(parent)
    , mSpeed(0.0)
    , mLeftSignal(false)
    , mRightSignal(false)
{
}

void Telemetry::fromVariantMap(const QVariantMap& map)
{
    setSpeed(map.value(SPEED, mSpeed).toReal());
    setLeftSignal(map.value(LEFT_SIGNAL, mLeftSignal).toBool());
    setRightSignal(map.value(RIGHT_SIGNAL, mRightSignal).toBool());
}

QVariantMap Telemetry::toVariantMap() const
{
    return QVariantMap{
        { SPEED, mSpeed },
        { LEFT_SIGNAL, mLeftSignal },
        { RIGHT_SIGNAL, mRightSignal },
    };
}

qreal Telemetry::speed() const
{
    return mSpeed;
}

void Telemetry::setSpeed(qreal speed)
{
    if (speed != mSpeed) {
        mSpeed = speed;
        emit speedChanged(speed);
    }
}

bool Telemetry::leftSignal() const
{
    return mLeftSignal;
}

void Telemetry::setLeftSignal(bool leftSignal)
{
    if (leftSignal != mLeftSignal) {
        mLeftSignal = leftSignal;
        emit leftSignalChanged(leftSignal);
    }
}

QVariantMap Telemetry::leftSignalToVariantMap() const
{
    return QVariantMap{ { LEFT_SIGNAL, mLeftSignal } };
}

bool Telemetry::rightSignal() const
{
    return mRightSignal;
}

void Telemetry::setRightSignal(bool rightSignal)
{
    if (rightSignal != mRightSignal) {
        mRightSignal = rightSignal;
        emit rightSignalChanged(rightSignal);
    }
}

QVariantMap Telemetry::rightSignalToVariantMap() const
{
    return QVariantMap{ { RIGHT_SIGNAL, mRightSignal } };
}
