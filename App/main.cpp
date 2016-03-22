#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QProcess>

#include "yrno.h"
#include "apimetnolocation.h"
#include "forecastdatamodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QProcess p;
    QStringList params;
    QString imagesPath = "/tmp/Meteo-Backend/images";

    bool test = true;
    int nImages = 11;

    if(!test)
    {
        params << "../../Meteo-Backend/preloadImages.py";
        params << imagesPath;
        p.start("python", params);
        p.waitForFinished(5000);

        QString p_stdout = p.readAll();
        nImages = p_stdout.toInt();
    }


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
    engine.rootContext()->setContextProperty("nImages", nImages);
    engine.rootContext()->setContextProperty("imagesPath", imagesPath);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
