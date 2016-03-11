#include "forecastdatamodel.h"

ForecastItem::ForecastItem(const QString &time, const QString &cloudImage, const QString &cloudText, const QString &windImage, const QString &windText)
    : m_time(time), m_cloudImage(cloudImage), m_cloudText(cloudText),m_windImage(windImage),m_windText(windText)
{
}

QString ForecastItem::time() const
{
    return m_time;
}

QString ForecastItem::cloudImage() const
{
    return m_cloudImage;
}

QString ForecastItem::cloudText() const
{
    return m_cloudText;
}

QString ForecastItem::windImage() const
{
    return m_windImage;
}

QString ForecastItem::windText() const
{
    return m_windText;
}
ForecastModel::ForecastModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ForecastModel::addForecast(const ForecastItem &forecast)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_forecasts << forecast;
    endInsertRows();
}

int ForecastModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_forecasts.count();
}

QVariant ForecastModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_forecasts.count())
        return QVariant();

    const ForecastItem &forecast = m_forecasts[index.row()];
    if (role == TimeRole)
        return forecast.time();
    else if (role == CloudImageRole)
        return forecast.cloudImage();
    else if (role == CloudTextRole)
        return forecast.cloudText();
    else if (role == WindImageRole)
        return forecast.windImage();
    else if (role == WindTextRole)
        return forecast.windText();
    return QVariant();
}

QHash<int, QByteArray> ForecastModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TimeRole] = "time";
    roles[CloudImageRole] = "cloudImage";
    roles[CloudTextRole] = "cloudText";
    roles[WindImageRole] = "windImage";
    roles[WindTextRole] = "windText";
    return roles;
}
