#ifndef FORECASTDATAMODEL_H
#define FORECASTDATAMODEL_H
#include <QAbstractListModel>

class ForecastItem
{
public:
    ForecastItem(const QString &time, const QString &cloudImage, const QString &cloudText, const QString &windImage, const QString &windText);

    QString time() const;
    QString cloudImage() const;
    QString cloudText() const;
    QString windImage() const;
    QString windText() const;

private:
    QString m_time;
    QString m_cloudImage;
    QString m_cloudText;
    QString m_windImage;
    QString m_windText;
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
        WindTextRole
    };

    ForecastModel(QObject *parent = 0);

    void addForecast(const ForecastItem &forecast);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant get() const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<ForecastItem> m_forecasts;
};

#endif // FORECASTDATAMODEL_H
