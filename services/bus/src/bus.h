#ifndef BUS_H
#define BUS_H

#include <server.h>
#include <QObject>

/**
 * @brief The Bus class
 */
class Bus
    : public QObject
{
    Q_OBJECT
public:
    explicit Bus(QObject* parent = nullptr);

    bool start();

private slots:
    void messageReceived(const QByteArray& message, QLocalSocket& client);

private:
    Server mServer;
    QMap<QString, QLocalSocket*> mServices;
};

#endif // BUS_H

