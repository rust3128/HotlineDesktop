#include "modelpaytypes.h"
#include <QBrush>

ModelPaytypes::ModelPaytypes(QObject *parent) : QSqlQueryModel(parent)
{

}


QVariant ModelPaytypes::data(const QModelIndex &idx, int role) const
{

    switch (role) {
    case Qt::DisplayRole:
        if(idx.column() == 4){
            if(QSqlQueryModel::data(this->index(idx.row(),4)).toBool())
                return tr("Да");
            else
                return tr("Нет");
        } else
            return QSqlQueryModel::data(idx);
    case Qt::BackgroundColorRole:
        if(QSqlQueryModel::data(this->index(idx.row(),4)).toBool()){
            return QBrush(QColor("#2EFE64"));
        } else {
            return QBrush(QColor("#F5A9A9"));
        }
    case Qt::EditRole:
        return  QSqlQueryModel::data(idx);
    case Qt::TextAlignmentRole:
        if(idx.column()==4)
            return Qt::AlignCenter;
        break;
    }
    return QVariant();

}
