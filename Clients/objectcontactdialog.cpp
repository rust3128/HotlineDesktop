#include "objectcontactdialog.h"
#include "ui_objectcontactdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

ObjectContactDialog::ObjectContactDialog(int id, QSqlRecord *record, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectContactDialog),
    objectID(id)
{
    ui->setupUi(this);

    if(record->isEmpty()){
        this->setWindowTitle("Новый контакт");
        isNew=true;
    } else {
        this->setWindowTitle("Редактирование контакта");
        ui->lineEditName->setText(record->value(2).toString());
        ui->lineEditContact->setText(record->value(3).toString());
        contactID=record->value(0).toInt();
        isNew = false;
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

void ObjectContactDialog::on_buttonBox_rejected()
{
    this->reject();
}

void ObjectContactDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    if(isNew) {
        q.prepare("INSERT INTO objectcontacts (object_id, namecontact, `data`) VALUES (:objectID, :name, :contact)");
    } else {
        q.prepare("UPDATE objectcontacts SET namecontact=:name, `data`=:contact WHERE contact_id=:contactID");
    }
    q.bindValue(":objectID", objectID);
    q.bindValue(":name",ui->lineEditName->text().trimmed());
    q.bindValue(":contact",ui->lineEditContact->text().trimmed());
    q.bindValue(":contactID", contactID);
    if(!q.exec()) {
        qCritical(logCritical()) << "Не удалось обновить информацию о контаксте" << q.lastError().text();
        QMessageBox::critical(this, "Ошибка","Не удалось обновить информацию о контакте!\n"+q.lastError().text());
    }
    this->accept();
}
