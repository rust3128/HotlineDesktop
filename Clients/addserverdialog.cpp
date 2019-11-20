#include "addserverdialog.h"
#include "ui_addserverdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>

AddServerDialog::AddServerDialog(QSqlRecord *r, int clID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddServerDialog),
    clientID(clID),
    recordServer(r)
{
    ui->setupUi(this);
    qInfo(logInfo()) << "currentType" << recordServer->value(2).toInt();
    createModels();
    createUI();
}

AddServerDialog::~AddServerDialog()
{
    delete ui;
}

void AddServerDialog::createUI()
{
    ui->comboBoxServerType->setModel(modelServersType);
    ui->comboBoxServerType->setModelColumn(1);
    if(recordServer->isEmpty()){
        ui->comboBoxServerType->setCurrentIndex(-1);
        ui->comboBoxServerType->setEditable(true);
        ui->comboBoxServerType->setCurrentText("Укажите тип сервера...");
        ui->checkBoxIsActive->setChecked(true);
        ui->buttonBox->button(QDialogButtonBox::Save)->setDisabled(true);
    } else {
        ui->lineEditServerName->setText(recordServer->value(3).toString());
        currentType = recordServer->value(2).toInt();
            qInfo(logInfo()) << "currentType" << currentType;
        ui->comboBoxServerType->setCurrentIndex(currentType);
        ui->checkBoxIsActive->setChecked(recordServer->value(1).toBool());
    }
}

void AddServerDialog::createModels()
{
    modelServersType = new QSqlQueryModel(this);
    modelServersType->setQuery("SELECT servertype_id, servertypename FROM hd2.serverstype "
                               "ORDER BY servertype_id");
}

void AddServerDialog::on_comboBoxServerType_activated(int idx)
{
    currentType = modelServersType->data(modelServersType->index(idx,0)).toInt();
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(true);
}

void AddServerDialog::on_buttonBox_rejected()
{
    this->reject();
}

void AddServerDialog::on_buttonBox_accepted()
{
    if(ui->lineEditServerName->text().size()<=4){
        int result = QMessageBox::question(this, "Вопрос",
                     QString("Вы действете хотите добавить сервер с адресом %1?").arg(ui->lineEditServerName->text().trimmed()));
        if(result == QMessageBox::No) return;
    }
    QSqlQuery *q = new QSqlQuery();
    if(recordServer->isEmpty()){
        q->prepare("INSERT INTO servers (`client_id`, `servertype_id`, `connections`, `isactive`) VALUES (:clientID, :serverTypeID, :connections, :isActive)");
        q->bindValue(":clientID", clientID);
    } else {
        q->prepare("UPDATE servers SET `servertype_id`= :serverTypeID, `connections` = :connections, `isactive` = :isActive WHERE server_id = :serverID" );
        q->bindValue(":serverID", recordServer->value(0).toInt());
    }
    qInfo(logInfo()) << "currentType" << currentType;
    q->bindValue(":serverTypeID", currentType);
    q->bindValue(":connections", ui->lineEditServerName->text().trimmed());
    q->bindValue(":isActive", QVariant(ui->checkBoxIsActive->isChecked()).toString());

    if(!q->exec()) {
        qCritical(logCritical()) << "Не возможно обновить информацию о серверах!" << q->lastError().text();
        return;
    } else {
        qInfo(logInfo()) << "Информация о сервере" << ui->lineEditServerName->text().trimmed() << "успешно обновлена";
        this->accept();
    }


}

void AddServerDialog::on_toolButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Новый тип сервера"),
                                         tr("Укажите новый адрес сервера:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()){
        QSqlQuery q;
        q.prepare("INSERT INTO serverstype (servertypename) VALUES (:typename)");
        q.bindValue(":typename", text.trimmed());
        if(!q.exec()){
            qCritical(logCritical()) << "Не удалось добавить новый тип сервера." << q.lastError().text();
            return;
        }
        modelServersType->setQuery(modelServersType->query().lastQuery());
        ui->comboBoxServerType->setCurrentIndex(-1);

    }

}
