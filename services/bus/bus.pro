TEMPLATE = app
TARGET = $${PROJECT_NAME}$${TARGET}
DESTDIR = ../../out/bin

QT += core network
QT -= gui
CONFIG += console

INCLUDEPATH += $$PWD $$PWD/../../libs/ipc/src
DEPENDPATH += $$PWD $$PWD/../../libs/ipc/src
LIBS += -L$$OUT_PWD/../../out/lib -l$${PROJECT_NAME}ipc

HEADERS += \
    src/bus.h

SOURCES += \
    src/bus.cpp \
    src/main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${PROJECT_NAME}/bin
else: unix:!android: target.path = /opt/$${PROJECT_NAME}/bin
!isEmpty(target.path): INSTALLS += target

