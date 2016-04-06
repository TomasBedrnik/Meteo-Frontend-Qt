#ifndef YRNO_H
#define YRNO_H


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include "apiinterface.h"

struct ForecastData
{
public:
    QDateTime from;
    QDateTime to;
    int period = 0;
    int symbolNum = 0;
    int symbolNumEx = 0;
    QString symbolVar;
    QString symbolName;
    float precipation = 0;
    float windDir = 0;
    QString windDirCode;
    QString windDirName;
    float windSpeed = 0;
    QString windSpeedName;
    float temperature = 0;
    QString temperatureUnit;
    float pressure = 0;
    QString pressureUnit;
};

class YrNo : public ApiInterface
{
    Q_OBJECT
public:
    YrNo();
    void getForecast(ForecastModel *model);
public slots:
    void getForecastSLOT();
private slots:
    void finishedSLOT(QNetworkReply * reply);
};

#endif // YRNO_H
