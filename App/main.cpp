#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QProcess>
#include <QTimer>

#include "yrno.h"
#include "apimetnolocation.h"
#include "forecastdatamodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //PARAMETERS
    int screenWidth = 1366;
    int screenHeight = 788;
    QString imagesPath = "/mnt/zbytek/tmp/Meteo-Backend";

    QProcess p;
    QStringList params;

    params << "../../Meteo-Backend/preloadImages.py";
    p.start("python", params);
    p.waitForFinished(20000);

    QString p_stdout = p.readAll();
    int nImages = p_stdout.toInt();

    ForecastModel modelLeft;
    ForecastModel modelRight;

    YrNo *no = new YrNo();
    no->getForecast(&modelLeft);
    ApiMetNoLocation *metNo = new ApiMetNoLocation();
    metNo->getForecast(&modelRight);

    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), no, SLOT(getForecastSLOT()));
    QObject::connect(timer, SIGNAL(timeout()), metNo, SLOT(getForecastSLOT()));
    timer->start(1000*60*10);//10 min

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    engine.rootContext()->setContextProperty("modelLeft", &modelLeft);
    engine.rootContext()->setContextProperty("modelRight", &modelRight);
    engine.rootContext()->setContextProperty("nImages", nImages);
    engine.rootContext()->setContextProperty("imagesPath", imagesPath);
    engine.rootContext()->setContextProperty("screenWidth", screenWidth);
    engine.rootContext()->setContextProperty("screenHeight", screenHeight);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
