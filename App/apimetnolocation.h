#ifndef APIMETNOLOCATION_H
#define APIMETNOLOCATION_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include "apiinterface.h"

struct ForecastDataMet
{
public:
    QDateTime from;
    QDateTime to;
    float precipation = 0;
    QString precipationUnit;
    float humidity = 0;
    QString humidityUnit;
    float windDir = 0;
    QString windDirCode;
    float windSpeed = 0;
    int windSpeedBeaufort = 0;
    QString windSpeedName;
    float temperature = 0;
    QString temperatureUnit;
    float pressure = 0;
    QString pressureUnit;
    float cloudiness = 0;
    float fog = 0;
    float lowClouds = 0;
    float mediumClouds = 0;
    float highClouds = 0;
    float dewpointTemperature = 0;
    QString dewpointTemperatureUnit;
    QString symbolName;
    int symbolNum = 0;
    float minTemperature = 0;
    QString minTemperatureUnit;
    float maxTemperature = 0;
    QString maxTemperatureUnit;
};

class ApiMetNoLocation : public QObject
{
    Q_OBJECT
public:
    ApiMetNoLocation();
    void getForecast(ForecastModel *model);
public slots:
    void getForecastSLOT();
private slots:
    void finishedSLOT( QNetworkReply * reply);
private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QXmlStreamReader *xmlReader;
    ForecastModel *model;
};


#endif // APIMETNOLOCATION_H
