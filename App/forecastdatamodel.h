#ifndef FORECASTDATAMODEL_H
#define FORECASTDATAMODEL_H
#include <QAbstractListModel>

class ForecastItem
{
public:
    ForecastItem(const QString &time, const QString &cloudImage, const QString &cloudText, const QString &windImage, const QString &windText, const QString &precipitation, const QString &temperature);
    ForecastItem(const QString &date);

    QString time() const;
    QString cloudImage() const;
    QString cloudText() const;
    QString windImage() const;
    QString windText() const;
    QString precipitation() const;
    QString temperature() const;
    QString date() const;
    bool section() const;

private:
    QString m_time;
    QString m_cloudImage;
    QString m_cloudText;
    QString m_windImage;
    QString m_windText;
    QString m_precipitation;
    QString m_temperature;
    QString m_date;
    bool m_section;
};

class ForecastModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ForecastRoles {
        //TypeRole = Qt::UserRole + 1,
        TimeRole,
        CloudImageRole,
        CloudTextRole,
        WindImageRole,
        WindTextRole,
        PrecipitationRole,
        TemperatureRole,
        DateRole,
        SectionRole
    };

    ForecastModel(QObject *parent = 0);

    void addForecast(const ForecastItem &forecast);
    void removeEndSections();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant get() const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<ForecastItem> m_forecasts;
};

#endif // FORECASTDATAMODEL_H
