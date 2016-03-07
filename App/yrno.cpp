#include "yrno.h"
#include <QTemporaryFile>


YrNo::YrNo()
{
}

void YrNo::GetForecast()
{
    float lat = 50.6019;
    float lon = 15.3355;
    float msl = 321;
    QString url = QString("http://api.met.no/weatherapi/locationforecast/1.9/?lat=")+QString::number(lat)+";lon="+QString::number(lon)+";msl="+QString::number(msl);

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.yr.no/place/Czech_Republic/Liberec/Semily/forecast.xml"));

    manager = new QNetworkAccessManager(this); // Instance variable
    connect(manager, SIGNAL(finished(QNetworkReply*)),
    this, SLOT(finished(QNetworkReply *)));

    manager->get(request);

//QUrl url("http://kauritree.tumblr.com/api/read/");
//QUrl url("http://api.met.no/weatherapi/locationforecast/1.9/?lat=60.10;lon=9.58;msl=70");

}
void YrNo::finished( QNetworkReply * reply)
{
  xmlReader = new QXmlStreamReader(reply->readAll());
  xmlReader->readNext();
  //Reading from the file
  while (!xmlReader->atEnd())
  {
      QString name = xmlReader->name().toString();
      if (xmlReader->isStartElement())
      {
          QString name = xmlReader->name().toString();
      }
      else if (xmlReader->isEndElement())
      {
          xmlReader->readNext();
      }
      xmlReader->readNext();
  }
  if (xmlReader->hasError())
  {
      //std::cout << "XML error: " << xmlReader->errorString().data() << std::endl;
  }
}
