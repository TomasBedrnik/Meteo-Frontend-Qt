#include "yrno.h"

YrNo::YrNo()
{
    manager = NULL;
    xmlReader = NULL;
}

YrNo::~YrNo()
{
    delete manager;
    delete xmlReader;
}

void YrNo::getForecastSLOT()
{
    QNetworkRequest request;
    request.setUrl(QUrl("http://www.yr.no/place/Czech_Republic/Liberec/Semily/forecast.xml"));

    delete manager;
    manager = new QNetworkAccessManager(this); // Instance variable
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSLOT(QNetworkReply *)));

    manager->get(request);
}
void YrNo::getForecast(ForecastModel *model)
{
    this->model = model;
    getForecastSLOT();
}
void YrNo::finishedSLOT( QNetworkReply * reply)
{
    QString city;
    QString lastDate = "";
    QList<ForecastData> forecast;

    delete xmlReader;
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

                                QString date = f.from.toString("d.M.");
                                if(date != lastDate)
                                {
                                    lastDate = date;
                                    model->addForecast(ForecastItem(date));
                                }
                                QString time = f.to.toString("H:mm");
                                QString cloudImage = "/images/clouds/"+QString::number(f.symbolNum)+".png";
                                QString cloudText = f.symbolName;
                                QString windImage = "/images/wind/"+QString().sprintf("%04d",(int)(f.windSpeed*10/25)*25)+"."+QString().sprintf("%03d",(int)(f.windDir/5)*5)+".png";
                                QString windText = QString::number(f.windSpeed) + " m/s "+ f.windSpeedName+" "+f.windDirName;
                                QString temperature = QString::number(f.temperature)+"°";
                                QString precipation = QString::number(f.precipation)+" mm";

                                model->addForecast(ForecastItem(time,cloudImage,cloudText,windImage,windText,precipation,temperature));
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

    if (xmlReader->tokenType() == QXmlStreamReader::Invalid)
        xmlReader->readNext();
}
