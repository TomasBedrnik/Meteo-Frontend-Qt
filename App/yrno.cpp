#include "yrno.h"
#include <QTemporaryFile>

YrNo::YrNo()
{
}

void YrNo::GetForecast(ForecastModel *model)
{
    this->model = model;
//    float lat = 50.6019;
//    float lon = 15.3355;
//    float msl = 321;
//    QString url = QString("http://api.met.no/weatherapi/locationforecast/1.9/?lat=")+QString::number(lat)+";lon="+QString::number(lon)+";msl="+QString::number(msl);

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.yr.no/place/Czech_Republic/Liberec/Semily/forecast.xml"));

    manager = new QNetworkAccessManager(this); // Instance variable
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedCity(QNetworkReply *)));

    manager->get(request);

    //QUrl url("http://kauritree.tumblr.com/api/read/");
    //QUrl url("http://api.met.no/weatherapi/locationforecast/1.9/?lat=60.10;lon=9.58;msl=70");

}
void YrNo::finishedCity( QNetworkReply * reply)
{
    QString city;
    QList<ForecastData> forecast;
//    QString country;
    xmlReader = new QXmlStreamReader(reply->readAll());
    if (xmlReader->readNextStartElement() && xmlReader->name() == "weatherdata")
    {
        while (xmlReader->readNextStartElement())
        {
            if (xmlReader->name() == "location")
            {
                while (xmlReader->readNextStartElement())
                {
                    if (xmlReader->name() == "name")
                    {
                        xmlReader->readNext();
                        city = xmlReader->text().toString();
                    }
//                    else if (xmlReader->name() == "country")
//                    {
//                        xmlReader->readNext();
//                        country = xmlReader->text().toString();
//                    }
                    xmlReader->skipCurrentElement();
                }
            }
            else if (xmlReader->name() == "forecast")
            {
                while (xmlReader->readNextStartElement())
                {
                    if (xmlReader->name() == "tabular")
                    {
                        while (xmlReader->readNextStartElement())
                        {
                            if (xmlReader->name() == "time")
                            {
                                ForecastData f;

                                QXmlStreamAttributes attr = xmlReader->attributes();
                                f.from = QDateTime::fromString(attr.value("from").toString(),"yyyy-MM-ddTHH:mm:ss");
                                f.to = QDateTime::fromString(attr.value("to").toString(),"yyyy-MM-ddTHH:mm:ss");
                                f.period = attr.value("period").toInt();

                                while (xmlReader->readNextStartElement())
                                {
                                    QXmlStreamAttributes attr = xmlReader->attributes();
                                    if (xmlReader->name() == "symbol")
                                    {
                                        f.symbolNum = attr.value("number").toInt();
                                        f.symbolNumEx = attr.value("numberEx").toInt();
                                        f.symbolName = attr.value("name").toString();
                                        f.symbolVar = attr.value("var").toString();
                                    }
                                    else if (xmlReader->name() == "precipitation")
                                    {
                                        f.precipation = attr.value("value").toFloat();
                                    }
                                    else if (xmlReader->name() == "windDirection")
                                    {
                                        f.windDir = attr.value("deg").toFloat();
                                        f.windDirCode = attr.value("code").toString();
                                        f.windDirName = attr.value("name").toString();
                                    }
                                    else if (xmlReader->name() == "windSpeed")
                                    {
                                        f.windSpeed = attr.value("mps").toFloat();
                                        f.windSpeedName = attr.value("name").toString();
                                    }
                                    else if (xmlReader->name() == "temperature")
                                    {
                                        f.temperature = attr.value("value").toFloat();
                                        f.temperatureUnit = attr.value("unit").toString();
                                    }
                                    else if (xmlReader->name() == "pressure")
                                    {
                                        f.pressure = attr.value("value").toFloat();
                                        f.pressureUnit = attr.value("unit").toString();
                                    }
                                    xmlReader->skipCurrentElement();
                                }


                                QString time = f.from.toString("d.M. H:mm")+"–"+f.to.toString("H:mm");
                                QString cloudImage = QString::number(f.symbolNum);
                                QString cloudText = f.symbolName;
                                QString windImage = QString().sprintf("%04d",(int)(f.windSpeed*10/25)*25)+"."+QString().sprintf("%03d",(int)(f.windDir/5)*5);
                                QString windText = f.windSpeedName+" "+f.windDirName;

                                model->addForecast(ForecastItem(time,cloudImage,cloudText,windImage,windText));
                                forecast.push_back(f);
                            }
                        }
                        xmlReader->skipCurrentElement();
                    }
                    xmlReader->skipCurrentElement();
                }
            }
            else
                xmlReader->skipCurrentElement();
        }
    }

    // readNextStartElement() leaves the stream in
    // an invalid state at the end. A single readNext()
    // will advance us to EndDocument.
    if (xmlReader->tokenType() == QXmlStreamReader::Invalid)
        xmlReader->readNext();

    if (xmlReader->hasError()) {

    }
}
