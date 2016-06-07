#include "apimetnolocation.h"


ApiMetNoLocation::ApiMetNoLocation()
{
    manager = NULL;
    xmlReader = NULL;
}

ApiMetNoLocation::~ApiMetNoLocation()
{
    delete manager;
    delete xmlReader;
}

void ApiMetNoLocation::getForecastSLOT()
{
    float lat = 50.6019;
    float lon = 15.3355;
    float msl = 321;
    QString url = QString("http://api.met.no/weatherapi/locationforecast/1.9/?lat=")+QString::number(lat)+";lon="+QString::number(lon)+";msl="+QString::number(msl);

    QNetworkRequest request;
    request.setUrl(QUrl(url));

    delete manager;
    manager = new QNetworkAccessManager(this); // Instance variable
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finishedSLOT(QNetworkReply *)));

    manager->get(request);
}
void ApiMetNoLocation::getForecast(ForecastModel *model)
{
    this->model = model;
    getForecastSLOT();

}
void ApiMetNoLocation::finishedSLOT( QNetworkReply * reply)
{
    QString lastDate = "";
    QList<ForecastDataMet> forecast;
    delete xmlReader;
    xmlReader = new QXmlStreamReader(reply->readAll());
    if (xmlReader->readNextStartElement() && xmlReader->name() == "weatherdata")
    {
        while (xmlReader->readNextStartElement())
        {
            if (xmlReader->name() == "product")
            {
                while (xmlReader->readNextStartElement())
                {
                    if (xmlReader->name() == "time")
                    {
                        ForecastDataMet f;

                        QXmlStreamAttributes attr = xmlReader->attributes();
                        f.from = QDateTime::fromString(attr.value("from").toString(),"yyyy-MM-ddTHH:mm:ssZ");
                        f.to = QDateTime::fromString(attr.value("to").toString(),"yyyy-MM-ddTHH:mm:ssZ");

                        while (xmlReader->readNextStartElement())
                        {
                            if (xmlReader->name() == "location")
                            {
                                while (xmlReader->readNextStartElement())
                                {
                                    QXmlStreamAttributes attr = xmlReader->attributes();
                                    if (xmlReader->name() == "symbol")
                                    {
                                        f.symbolNum = attr.value("number").toInt();
                                        f.symbolName = attr.value("id").toString();
                                    }
                                    else if (xmlReader->name() == "precipitation")
                                    {
                                        f.precipation = attr.value("value").toFloat();
                                        f.precipationUnit = attr.value("unit").toString();
                                    }
                                    else if (xmlReader->name() == "windDirection")
                                    {
                                        f.windDir = attr.value("deg").toFloat();
                                        f.windDirCode = attr.value("code").toString();
                                    }
                                    else if (xmlReader->name() == "windSpeed")
                                    {
                                        f.windSpeed = attr.value("mps").toFloat();
                                        f.windSpeedBeaufort = attr.value("beaufort").toInt();
                                        f.windSpeedName = attr.value("name").toString();
                                    }
                                    else if (xmlReader->name() == "temperature")
                                    {
                                        f.temperature = attr.value("value").toFloat();
                                        f.temperatureUnit = attr.value("unit").toString();
                                    }
                                    else if (xmlReader->name() == "humidity")
                                    {
                                        f.humidity = attr.value("value").toFloat();
                                        f.humidityUnit = attr.value("unit").toString();
                                    }
                                    else if (xmlReader->name() == "pressure")
                                    {
                                        f.pressure = attr.value("value").toFloat();
                                        f.pressureUnit = attr.value("unit").toString();
                                    }
                                    else if (xmlReader->name() == "cloudiness")
                                    {
                                        f.cloudiness = attr.value("percent").toFloat();
                                    }
                                    else if (xmlReader->name() == "fog")
                                    {
                                        f.fog = attr.value("percent").toFloat();
                                    }
                                    else if (xmlReader->name() == "lowClouds")
                                    {
                                        f.lowClouds = attr.value("percent").toFloat();
                                    }
                                    else if (xmlReader->name() == "mediumClouds")
                                    {
                                        f.mediumClouds = attr.value("percent").toFloat();
                                    }
                                    else if (xmlReader->name() == "highClouds")
                                    {
                                        f.highClouds = attr.value("percent").toFloat();
                                    }
                                    else if (xmlReader->name() == "minTemperature")
                                    {
                                        f.minTemperature = attr.value("value").toFloat();
                                        f.minTemperatureUnit = attr.value("unit").toString();
                                    }
                                    else if (xmlReader->name() == "maxTemperature")
                                    {
                                        f.maxTemperature = attr.value("value").toFloat();
                                        f.maxTemperatureUnit = attr.value("unit").toString();
                                    }
                                    else if (xmlReader->name() == "dewpointTemperature")
                                    {
                                        f.dewpointTemperature = attr.value("value").toFloat();
                                        f.dewpointTemperatureUnit = attr.value("unit").toString();
                                    }
                                    xmlReader->skipCurrentElement();
                                }


                                QString date = f.to.toString("d.M.");
                                if(date != lastDate)
                                {
                                    lastDate = date;
                                    model->addForecast(ForecastItem(date));
                                }

                                int range = f.from.secsTo(f.to);
                                if(range == 3*60*60)
                                {
                                    ForecastDataMet previous = forecast.at(forecast.size()-1);
                                    QString time = f.from.toString("H:mm")+"-"+f.to.toString("H:mm");
                                    QString cloudImage = "/images/clouds/"+QString::number(f.symbolNum)+".png";
                                    QString cloudText = f.symbolName;
                                    QString windImage = "/images/wind/"+QString().sprintf("%04d",(int)(previous.windSpeed*10/25)*25)+"."+QString().sprintf("%03d",(int)(previous.windDir/5)*5)+".png";
                                    QString windText = QString::number(previous.windSpeed) + " m/s "+ previous.windSpeedName+" "+previous.windDirCode;
                                    QString temperature = QString::number(previous.temperature)+"°";
                                    QString precipation = QString::number(f.precipation)+" mm";
                                    model->addForecast(ForecastItem(time,cloudImage,cloudText,windImage,windText,precipation,temperature));
                                }
                                forecast.push_back(f);
                            }
                        }
                    }
                }
            }
            else
                xmlReader->skipCurrentElement();
        }
    }
    model->removeEndSections();
    if (xmlReader->tokenType() == QXmlStreamReader::Invalid)
        xmlReader->readNext();
}
