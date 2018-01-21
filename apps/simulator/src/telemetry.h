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

public:
    explicit Telemetry(QObject* parent = nullptr);

    void fromVariantMap(const QVariantMap& map);
    QVariantMap toVariantMap() const;

    qreal speed() const;
    void setSpeed(qreal speed);

    bool leftSignal() const;
    void setLeftSignal(bool leftSignal);
    QVariantMap leftSignalToVariantMap() const;

    bool rightSignal() const;
    void setRightSignal(bool rightSignal);
    QVariantMap rightSignalToVariantMap() const;

signals:
    void speedChanged(qreal speed);
    void leftSignalChanged(bool leftSignal);
    void rightSignalChanged(bool rightSignal);

private:
    qreal mSpeed;
    bool mLeftSignal;
    bool mRightSignal;
};

#endif // TELEMETRY_H

