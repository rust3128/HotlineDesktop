#ifndef MODELTERMINALS_H
#define MODELTERMINALS_H

#include <QObject>
#include <QSqlTableModel>

class ModelTerminals : public QSqlTableModel
{
public:
    explicit ModelTerminals(QObject *parent = nullptr);

    // QAbstractItemModel interface
public:
    QVariant data(const QModelIndex &idx, int role) const;
};

#endif // MODELTERMINALS_H
