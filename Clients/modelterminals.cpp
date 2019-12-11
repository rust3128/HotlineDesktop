#include "modelterminals.h"
#include <QBrush>

ModelTerminals::ModelTerminals(QObject *parent) :
    QSqlTableModel(parent)
{

}


QVariant ModelTerminals::data(const QModelIndex &idx, int role) const
{
    switch (role) {
    case Qt::DisplayRole:
        if(idx.column() == 5){
            if(QSqlTableModel::data(this->index(idx.row(),5)).toBool())
                return tr("Да");
            else
                return tr("Нет");
        } else
            return QSqlTableModel::data(idx);
    case Qt::BackgroundColorRole:
        if(!QSqlTableModel::data(this->index(idx.row(),5)).toBool()){
            return QBrush(QColor("#F5A9A9"));
        }
        break;
    case Qt::EditRole:
        return  QSqlTableModel::data(idx);
    case Qt::TextAlignmentRole:
        if(idx.column()==5)
            return Qt::AlignCenter;
        break;
    }
    return QVariant();
}
