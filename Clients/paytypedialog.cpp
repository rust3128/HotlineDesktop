#include "paytypedialog.h"
#include "ui_paytypedialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

PaytypeDialog::PaytypeDialog(QSqlRecord *rec, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaytypeDialog),
    recordPaytype(rec)
{
    ui->setupUi(this);
    createUI();
}

PaytypeDialog::~PaytypeDialog()
{
    delete ui;
}

void PaytypeDialog::createUI()
{
    if(recordPaytype->isEmpty()){
        this->setWindowTitle("Новый вид оплаты");
        return;
    }
    this->setWindowTitle("Изменение вида оплаты");
    ui->spinBoxMPosID->setValue(recordPaytype->value(1).toInt());
    ui->lineEditName->setText(recordPaytype->value(2).toString());
    ui->lineEditDLName->setText(recordPaytype->value(3).toString());
    ui->checkBox->setChecked(recordPaytype->value(4).toBool());
}

void PaytypeDialog::on_buttonBox_rejected()
{
    this->reject();
}

void PaytypeDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    if(recordPaytype->isEmpty()){
        q.prepare("INSERT INTO paytypes (client_id, mpos_id, name, dllname) VALUES (:clientID, :mposID, :name, :dllname)");
    } else {
        q.prepare("UPDATE paytypes SET mpos_id=:mposID, name=:name, dllname=:dllname, isactive=:isactive WHERE paytype_id=:paytypeID");
    }
    q.bindValue(":clientID", recordPaytype->value(5).toInt());
    q.bindValue(":mposID", ui->spinBoxMPosID->value());
    q.bindValue(":name", ui->lineEditName->text().trimmed());
    q.bindValue(":dllname", ui->lineEditDLName->text().trimmed());
    q.bindValue(":paytypeID",recordPaytype->value(0).toInt());
    q.bindValue(":isactive", (ui->checkBox->isChecked()) ? "true" : "false");
    if(!q.exec()) {
        qCritical(logCritical()) << tr("Не удалось обновить информацию от контакте.") << q.lastError().text();
        QMessageBox::critical(this,"Ошибка","Не удалось обновить информацию от контакте.\n"+q.lastError().text());
        this->reject();
    } else {
        qInfo(logInfo()) << tr("Информация о контакте успешно обновлена.");
        this->accept();
    }

}
