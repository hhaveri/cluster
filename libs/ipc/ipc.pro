TEMPLATE = lib
TARGET = $${PROJECT_NAME}$${TARGET}
DESTDIR = ../../out/lib

QT += core network
QT -= gui
CONFIG += plugin

DEFINES += \
    IPC_LIBRARY

HEADERS += \
    src/client.h \
    src/ipc_global.h \
    src/server.h

SOURCES += \
    src/client.cpp \
    src/server.cpp

INCLUDEPATH += $$PWD $$PWD/src
DEPENDPATH += $$PWD $$PWD/src

# Default rules for deployment.
qnx: target.path = /tmp/$${PROJECT_NAME}/lib
else: unix:!android: target.path = /opt/$${PROJECT_NAME}/lib
!isEmpty(target.path): INSTALLS += target

