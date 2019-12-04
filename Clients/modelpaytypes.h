#ifndef MODELPAYTYPES_H
#define MODELPAYTYPES_H

#include <QObject>
#include <QSqlQueryModel>

class ModelPaytypes : public QSqlQueryModel
{
public:
    explicit ModelPaytypes(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MODELPAYTYPES_H
