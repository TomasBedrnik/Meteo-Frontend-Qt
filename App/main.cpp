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

    //PARAMETERS
    int screenWidth = 1366;
    int screenHeight = 788;
    QString imagesPath = "/tmp/Meteo-Backend";

// NOT WORKING
//    QByteArray width;
//    QByteArray height;
//    width.setNum(screenWidth);
//    height.setNum(screenHeight);
//    qputenv("QT_QPA_EGLFS_PHYSICAL_WIDTH",width);
//    qputenv("QT_QPA_EGLFS_PHYSICAL_HEIGHT",height);

    QProcess p;
    QStringList params;

    params << "./Meteo-Backend/preloadImages.py";
    p.start("python", params);
    p.waitForFinished(20000);

    QString p_stdout = p.readAll();
    int nImages = p_stdout.toInt();



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
    engine.rootContext()->setContextProperty("screenWidth", screenWidth);
    engine.rootContext()->setContextProperty("screenHeight", screenHeight);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
