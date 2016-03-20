#ifndef APIINTERFACE_H
#define APIINTERFACE_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include "forecastdatamodel.h"

class ApiInterface : public QObject
{
    Q_OBJECT
public:
    virtual void GetForecast(ForecastModel *model) = 0;
protected slots:
    virtual void finishedSLOT( QNetworkReply * reply) = 0;
protected:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QXmlStreamReader *xmlReader;
    ForecastModel *model;
};

#endif // APIINTERFACE_H
