#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "yrno.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    YrNo *test = new YrNo();
    test->GetForecast();


    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
