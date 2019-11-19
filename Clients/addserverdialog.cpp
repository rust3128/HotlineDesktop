#include "addserverdialog.h"
#include "ui_addserverdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QPushButton>
#include <QMessageBox>

AddServerDialog::AddServerDialog(int servID, int clID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddServerDialog),
    serverId(servID),
    clientID(clID)
{
    ui->setupUi(this);
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
    ui->buttonBox->button(QDialogButtonBox::Save)->setDisabled(true);
    if(serverId>0){
        //Редактирование
    } else {
        ui->comboBoxServerType->setCurrentIndex(-1);
        ui->comboBoxServerType->setEditable(true);
        ui->comboBoxServerType->setCurrentText("Укажите тип сервера...");
        ui->checkBoxIsActive->setChecked(true);
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
    q->prepare("INSERT INTO `hd2`.`servers` (`client_id`, `servertype_id`, `connections`, `isactive`) VALUES (:clientID, :serverTypeID, :connections, :isActive)");
    q->bindValue(":clientID", clientID);
    q->bindValue(":serverTypeID", currentType);
    q->bindValue(":connections", ui->lineEditServerName->text().trimmed());
    q->bindValue(":isActive", ui->checkBoxIsActive->isChecked());
    if(!q->exec()) {
        qCritical(logCritical()) << "Не возможно добавить новый сервер!" << q->lastError().text();
        return;
    } else {
        qInfo(logInfo()) << "Сервер" << ui->lineEditServerName->text().trimmed() << "успешно добавленю";
        this->accept();
    }


}
