TEMPLATE = app

QT += qml quick core network svg xml
CONFIG += c++11

SOURCES += main.cpp \
    yrno.cpp \
    forecastdatamodel.cpp \
    apimetnolocation.cpp

RESOURCES += qml.qrc \
    resources.qrc

#LIBS += -L/usr/arm-linux-gnueabihf/usr/lib \
#    -lpthread

#INCLUDEPATH +=

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    yrno.h \
    forecastdatamodel.h \
    apimetnolocation.h \
    apiinterface.h
