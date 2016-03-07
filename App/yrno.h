#ifndef YRNO_H
#define YRNO_H


#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QXmlStreamReader>

class YrNo : public QObject
{
    Q_OBJECT
public:
    YrNo();
    void GetForecast();
private slots:
    void finished( QNetworkReply * reply);
private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QXmlStreamReader *xmlReader;
};

#endif // YRNO_H
