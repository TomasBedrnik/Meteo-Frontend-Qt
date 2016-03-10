#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "yrno.h"
#include "forecastdatamodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ForecastModel model;


    YrNo *test = new YrNo();
    test->GetForecast(&model);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("myModel", &model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
