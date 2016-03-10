#include "forecastdatamodel.h"

ForecastItem::ForecastItem(const QString &type, const QString &size)
    : m_type(type), m_size(size)
{
}

QString ForecastItem::type() const
{
    return m_type;
}

QString ForecastItem::size() const
{
    return m_size;
}

ForecastModel::ForecastModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void ForecastModel::addForecast(const ForecastItem &animal)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_animals << animal;
    endInsertRows();
}

int ForecastModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_animals.count();
}

QVariant ForecastModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_animals.count())
        return QVariant();

    const ForecastItem &animal = m_animals[index.row()];
    if (role == TypeRole)
        return animal.type();
    else if (role == SizeRole)
        return animal.size();
    return QVariant();
}

QHash<int, QByteArray> ForecastModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[SizeRole] = "size";
    return roles;
}
