TEMPLATE = lib
TARGET = $${PROJECT_NAME}$${TARGET}
DESTDIR = ../../out/lib

QT += core network
QT -= gui
CONFIG += plugin

DEFINES += \
    BUSCLIENT_LIBRARY

HEADERS += \
    src/busclient.h \
    src/busclient_global.h

SOURCES += \
    src/busclient.cpp

INCLUDEPATH += $$PWD/src $$PWD/../../libs/ipc/src
DEPENDPATH += $$PWD/src $$PWD/../../libs/ipc/src
LIBS += -L$$OUT_PWD/../../out/lib -l$${PROJECT_NAME}ipc

# Default rules for deployment.
qnx: target.path = /tmp/$${PROJECT_NAME}/lib
else: unix:!android: target.path = /opt/$${PROJECT_NAME}/lib
!isEmpty(target.path): INSTALLS += target

