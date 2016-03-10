#ifndef FORECASTDATAMODEL_H
#define FORECASTDATAMODEL_H
#include <QAbstractListModel>
#include <QStringList>

class ForecastItem
{
public:
    ForecastItem(const QString &type, const QString &size);

    QString type() const;
    QString size() const;

private:
    QString m_type;
    QString m_size;
};

class ForecastModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ForecastRoles {
        //TypeRole = Qt::UserRole + 1,
        TypeRole,
        SizeRole
    };

    ForecastModel(QObject *parent = 0);

    void addForecast(const ForecastItem &animal);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<ForecastItem> m_animals;
};

#endif // FORECASTDATAMODEL_H
