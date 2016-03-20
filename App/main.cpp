#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "yrno.h"
#include "apimetnolocation.h"
#include "forecastdatamodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ForecastModel modelLeft;
    ForecastModel modelRight;


    YrNo *no = new YrNo();
    no->GetForecast(&modelLeft);
    ApiMetNoLocation *metNo = new ApiMetNoLocation();
    metNo->GetForecast(&modelRight);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("modelLeft", &modelLeft);
    engine.rootContext()->setContextProperty("modelRight", &modelRight);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
