#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <QObject>

/**
 * @brief The Telemetry class
 */
class Telemetry final
    : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(bool leftSignal READ leftSignal WRITE setLeftSignal NOTIFY leftSignalChanged)
    Q_PROPERTY(bool rightSignal READ rightSignal WRITE setRightSignal NOTIFY rightSignalChanged)

    Q_PROPERTY(int cappedSpeed READ cappedSpeed NOTIFY cappedSpeedChanged)
    Q_PROPERTY(int maxSpeed READ maxSpeed CONSTANT)

public:
    explicit Telemetry(QObject* parent = nullptr);

    void fromVariantMap(const QVariantMap& map);

    qreal speed() const;
    void setSpeed(qreal speed);

    bool leftSignal() const;
    void setLeftSignal(bool leftSignal);

    bool rightSignal() const;
    void setRightSignal(bool rightSignal);

    int cappedSpeed() const;
    void setCappedSpeed(int cappedSpeed);

    int maxSpeed() const;

signals:
    void speedChanged(qreal speed);
    void leftSignalChanged(bool leftSignal);
    void rightSignalChanged(bool rightSignal);

    void cappedSpeedChanged(int cappedSpeed);

private:
    qreal mSpeed;
    bool mLeftSignal;
    bool mRightSignal;

    int mCappedSpeed;
    int mMaxSpeed;
};

#endif // TELEMETRY_H

