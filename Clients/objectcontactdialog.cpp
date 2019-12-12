#include "objectcontactdialog.h"
#include "ui_objectcontactdialog.h"

ObjectContactDialog::ObjectContactDialog(int id, QSqlRecord *record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectContactDialog),
    objectID(id)
{
    ui->setupUi(this);

    if(record->isEmpty()){
        this->setWindowTitle("Новый контакт");
    } else {
        this->setWindowTitle("Редактирование контакта");
    }

}

ObjectContactDialog::~ObjectContactDialog()
{
    delete ui;
}

void ObjectContactDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
