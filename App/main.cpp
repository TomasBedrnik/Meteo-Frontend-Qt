#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <QProcess>
#include <QTimer>

#include "yrno.h"
#include "apimetnolocation.h"
#include "forecastdatamodel.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //PARAMETERS
    int screenWidth = 1366;
    int screenHeight = 788;
    //QString imagesPath = "/mnt/zbytek/tmp/Meteo-Backend";
    QString imagesPath = "/tmp/Meteo-Backend";

    QProcess p;
    QStringList params;

    //params << "../../Meteo-Backend/preloadImages.py";
    params << "./Meteo-Backend/preloadImages.py";
    params << " -first";
    p.start("python", params);
    p.waitForFinished(20000);

    QString p_stdout = p.readAll();
    int nImages = p_stdout.toInt();
    std::cout << p_stdout.toUtf8().constData() << std::endl;
    std::cout << "___" << std::endl;
    std::cout << nImages << std::endl;
    //nImages = 10;

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

    bool ret = app.exec();
    delete no;
    delete metNo;
    delete timer;
    return ret;
}
