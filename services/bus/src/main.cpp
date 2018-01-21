#include "bus.h"
#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Bus bus;

    int result(-1);
    if (bus.start()) {
        result = app.exec();
    }

    return result;
}
