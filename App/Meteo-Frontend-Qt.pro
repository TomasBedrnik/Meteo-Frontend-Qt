TEMPLATE = app

QT += qml quick core network
CONFIG += c++11

SOURCES += main.cpp \
    yrno.cpp \
    forecastdatamodel.cpp

RESOURCES += qml.qrc \
    resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    yrno.h \
    forecastdatamodel.h
