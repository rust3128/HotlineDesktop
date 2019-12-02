#include "contactdialog.h"
#include "ui_contactdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSqlQuery>
#include <QSqlError>

ContactDialog::ContactDialog(int id, int clID,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContactDialog),
    contactID(id),
    clientID(clID)
{
    ui->setupUi(this);
    connect(ui->lineEditFIO,&QLineEdit::textChanged,this,&ContactDialog::slotSetModified);
    connect(ui->lineEditPhone,&QLineEdit::textChanged,this,&ContactDialog::slotSetModified);
    connect(ui->lineEditEmail,&QLineEdit::textChanged,this,&ContactDialog::slotSetModified);
    connect(ui->plainTextEditComments,&QPlainTextEdit::textChanged,this,&ContactDialog::slotSetModified);
    connect(ui->checkBoxIsActive,&QCheckBox::clicked,this,&ContactDialog::slotSetModified);
    createUI();
}

ContactDialog::~ContactDialog()
{
    delete ui;
}

void ContactDialog::changeEvent(QEvent *e)
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

void ContactDialog::createUI()
{
    modified = false;
    if(contactID == -1) return;
    QSqlQuery q;
    q.prepare("SELECT name, phone, email, `comment`, isactive FROM clientcontacts WHERE contact_id =:contactID");
    q.bindValue(":contactID", contactID);
    q.exec();
    q.next();
    ui->lineEditFIO->setText(q.value(0).toString());
    ui->lineEditPhone->setText(q.value(1).toString());
    ui->lineEditEmail->setText(q.value(2).toString());
    ui->plainTextEditComments->setPlainText(q.value(3).toString());
    ui->checkBoxIsActive->setChecked(q.value(4).toBool());

}
void ContactDialog::on_buttonBox_rejected()
{
    this->reject();
}

void ContactDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    if(contactID >=0 ){
        q.prepare("UPDATE clientcontacts SET name=:name,phone=:phone,email=:email,`comment`=:comment,isactive=:isactive "
                  "WHERE contact_id = :contactID");

    } else {
        q.prepare("INSERT INTO clientcontacts (client_id, name, phone, email, `comment`) "
                  "VALUES (:clientID, :name, :phone, :email, :comment)");
    }
    q.bindValue(":contactID", contactID);
    q.bindValue(":clientID", clientID);
    q.bindValue(":name", ui->lineEditFIO->text().trimmed());
    q.bindValue(":phone", ui->lineEditPhone->text().trimmed());
    q.bindValue(":email", ui->lineEditEmail->text().trimmed());
    q.bindValue(":comment", ui->plainTextEditComments->toPlainText().trimmed());
    q.bindValue(":isactive", (ui->checkBoxIsActive->isChecked()) ? "true" : "false");
    if(!q.exec()) {
        qCritical(logCritical()) << tr("Не удалось обновить информацию от контакте.") << q.lastError().text();
        this->reject();
    } else {
        qInfo(logInfo()) << tr("Информация о контакте успешно обновлена.");
        this->accept();
    }

}
