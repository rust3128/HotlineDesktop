#include "fbserverform.h"
#include "ui_fbserverform.h"
#include "LoggingCategories/loggingcategories.h"
#include <QSqlQuery>
#include <QSqlError>

FBServerForm::FBServerForm(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FBServerForm)
{
    ui->setupUi(this);
    bTextChanged=false;
    connect(ui->lineEditServer,&QLineEdit::textChanged,this,&FBServerForm::slotIsTextChanged);
    connect(ui->lineEditDatabase,&QLineEdit::textChanged,this,&FBServerForm::slotIsTextChanged);
    connect(ui->lineEditUser,&QLineEdit::textChanged,this,&FBServerForm::slotIsTextChanged);
    connect(ui->lineEditPassword,&QLineEdit::textChanged,this,&FBServerForm::slotIsTextChanged);

}

FBServerForm::~FBServerForm()
{
    delete ui;
}

void FBServerForm::changeEvent(QEvent *e)
{
    QGroupBox::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FBServerForm::slotGetClientID(int ID)
{
    mClientID = ID;
    qInfo(logInfo()) << "Client ID" << mClientID;
    createUI();
}

void FBServerForm::slotIsTextChanged()
{
    bTextChanged=true;
}

void FBServerForm::createUI()
{
    mEditable = ui->lineEditServer->palette();  // Default colors
    mNonEditable = ui->lineEditServer->palette();
    QColor col = mNonEditable.color(QPalette::Button);
    mNonEditable.setColor(QPalette::Base, col);
    mNonEditable.setColor(QPalette::Text, Qt::black);
    bEditable = false;
    setEditable();
    executeSQL(SELECT);
}

void FBServerForm::setEditable()
{
    ui->lineEditServer->setReadOnly(!bEditable);
    ui->lineEditDatabase->setReadOnly(!bEditable);
    ui->lineEditUser->setReadOnly(!bEditable);
    ui->lineEditPassword->setReadOnly(!bEditable);

    if(bEditable){
        ui->lineEditServer->setPalette(mEditable);
        ui->lineEditDatabase->setPalette(mEditable);
        ui->lineEditUser->setPalette(mEditable);
        ui->lineEditPassword->setPalette(mEditable);
    }
    else{
        ui->lineEditServer->setPalette(mNonEditable);
        ui->lineEditDatabase->setPalette(mNonEditable);
        ui->lineEditUser->setPalette(mNonEditable);
        ui->lineEditPassword->setPalette(mNonEditable);
    }
}

void FBServerForm::executeSQL(int type)
{
    QSqlQuery q;
    switch (type) {
    case SELECT:
        q.prepare("SELECT connect_id, server, `database`, user, password FROM centraldb "
                  "WHERE client_id = :clientID");
        q.bindValue(":clientID", mClientID);
        if(q.exec()){
            q.next();
            mConnectID = q.value(0).toInt();
            if(mConnectID <= 0){
                executeSQL(INSERT);

            } else {
                ui->lineEditServer->setText(q.value(1).toString());
                ui->lineEditDatabase->setText(q.value(2).toString());
                ui->lineEditUser->setText(q.value(3).toString());
                ui->lineEditPassword->setText(q.value(4).toString());
            }
        }
        else{
            qCritical(logCritical()) << "Не удалось получить данные о сервере базы данных" << q.lastError().text();
        }
        break;
    case INSERT:
        q.prepare("INSERT INTO centraldb (client_id) VALUE (:clientID)");
        q.bindValue(":clientID", mClientID);
        q.exec();
        break;
    case UPDATE:
        q.prepare("UPDATE centraldb SET server = :server, `database`=:database, user=:user, password=:pass "
                  "WHERE client_id = :clientID");
        q.bindValue(":server", ui->lineEditServer->text().trimmed());
        q.bindValue(":database", ui->lineEditDatabase->text().trimmed());
        q.bindValue(":user", ui->lineEditUser->text().trimmed());
        q.bindValue(":pass", ui->lineEditPassword->text().trimmed());
        q.bindValue(":clientID", mClientID );
        q.exec();
        break;
    default:
        break;
    }
}


void FBServerForm::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    bEditable = !bEditable;
    setEditable();
    qInfo(logInfo()) << "EDITABLE" << bEditable;
    if(!bEditable && bTextChanged){
        executeSQL(UPDATE);
    }
}
