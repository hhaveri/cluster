#include "telemetry.h"
#include <QVariantMap>
#include <math.h>

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
    , mCappedSpeed(0)
    , mMaxSpeed(180)
{
    connect(this, &Telemetry::speedChanged, this, [this](qreal speed) {
        setCappedSpeed(qMin(static_cast<int>(ceil(abs(speed))), mMaxSpeed));
    });
}

void Telemetry::fromVariantMap(const QVariantMap& map)
{
    setSpeed(map.value(SPEED, mSpeed).toReal());
    setLeftSignal(map.value(LEFT_SIGNAL, mLeftSignal).toBool());
    setRightSignal(map.value(RIGHT_SIGNAL, mRightSignal).toBool());
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

int Telemetry::cappedSpeed() const
{
    return mCappedSpeed;
}

void Telemetry::setCappedSpeed(int cappedSpeed)
{
    if (cappedSpeed != mCappedSpeed) {
        mCappedSpeed = cappedSpeed;
        emit cappedSpeedChanged(cappedSpeed);
    }
}

int Telemetry::maxSpeed() const
{
    return mMaxSpeed;
}

