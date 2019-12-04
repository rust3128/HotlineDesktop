#include "modelpaytypes.h"

ModelPaytypes::ModelPaytypes(QObject *parent) : QSqlQueryModel(parent)
{

}


QVariant ModelPaytypes::data(const QModelIndex &idx, int role) const
{
    if(role == Qt::DisplayRole) {
        if(idx.column() == 4){
            if(QSqlQueryModel::data(this->index(idx.row(),4)).toBool())
                return tr("Да");
            else
                return tr("Нет");
        } else {
            return QSqlQueryModel::data(idx);
        }
    }
    return QVariant();
}
