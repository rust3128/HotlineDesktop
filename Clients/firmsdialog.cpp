#include "firmsdialog.h"
#include "ui_firmsdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QPushButton>
#include <QMessageBox>
#include <QInputDialog>
#include <QDir>

FirmsDialog::FirmsDialog(int clientID, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirmsDialog),
    currentClientID(clientID)
{
    ui->setupUi(this);

    createModels();
    createUI();
}

FirmsDialog::~FirmsDialog()
{
    delete ui;
}

void FirmsDialog::createUI()
{
    ui->frameInfo->hide();
    ui->frameInfo->setEnabled(false);
    ui->pushButtonAdd->hide();

    ui->buttonBox->button(QDialogButtonBox::Save)->hide();
    ui->comboBoxClients->setModel(modelClients);
    ui->comboBoxClients->setModelColumn(1);
    ui->comboBoxClients->setCurrentIndex(currentClientID);
    ui->comboBoxClients->setCurrentText("Выберите клиента...");

    if(currentClientID !=-1){
        ui->comboBoxClients->hide();
        setFilterClients();
        QModelIndex k = modelFirms->index(0,0);
        ui->listViewClients->setCurrentIndex(k);
        showFirmInfo(k);
        ui->frameInfo->show();
    }
    ui->listViewClients->setModel(modelFirms);
    ui->listViewClients->setModelColumn(2);

    connect(ui->listViewClients->selectionModel(),&QItemSelectionModel::selectionChanged,this,&FirmsDialog::slotFirmChanged);
}

void FirmsDialog::createModels()
{
    modelClients = new QSqlQueryModel();
    modelClients->setQuery("SELECT c.client_id, c.name FROM clients c");

    modelFirms = new QSqlTableModel();
    modelFirms->setTable("firms");
    setFilterClients();
}



void FirmsDialog::on_buttonBox_accepted()
{
    QSqlQuery q;
    QString strSQL = QString("UPDATE firms SET "
            "address = '%1', "
            "okpo = '%2', "
            "inn = '%3', "
            "dogovornum = '%4', "
            "dogovordate = '%5' "
        "WHERE (firm_id = %6)")
            .arg(ui->plainTextEditAdress->toPlainText().trimmed())
            .arg(ui->lineEditOKPO->text().trimmed())
            .arg(ui->lineEditINN->text().trimmed())
            .arg(ui->lineEditNumDog->text().trimmed())
            .arg(ui->dateEdit->date().toString("yyyy-MM-dd"))
            .arg(currentFirmID);
    if(!q.exec(strSQL)){
        qCritical(logCritical()) << "Не возможно обновить данные о юр.лице." << q.lastError().text();
        return;
    }
    ui->frameInfo->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Save)->hide();
    setFilterClients();
    ui->listViewClients->setEnabled(true);
}

void FirmsDialog::on_buttonBox_rejected()
{
    this->reject();
}

void FirmsDialog::on_listViewClients_doubleClicked(const QModelIndex &idx)
{
    ui->frameInfo->setEnabled(true);
    ui->pushButtonAdd->hide();
    ui->listViewClients->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Save)->show();
    currentFirmID = modelFirms->data(modelFirms->index(idx.row(),0)).toInt();
    showFirmInfo(idx);

}

void FirmsDialog::on_comboBoxClients_activated(int idx)
{
    currentClientID = modelClients->data(modelClients->index(idx,0)).toInt();
    setFilterClients();
    if(modelFirms->rowCount() == 0) {
        int result = QMessageBox::question(this, "Вопрос", "Добавить юридическое лицо для этого клиента?");
        if(result == QMessageBox::Yes){
            addFirms();

        }
    }
    ui->frameInfo->show();
    QModelIndex k = modelFirms->index(0,0);
    ui->listViewClients->setCurrentIndex(k);
    showFirmInfo(k);
    ui->pushButtonAdd->show();

}

void FirmsDialog::addFirms()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                 QString::fromUtf8("Новое юр.лицо"),
                                 QString::fromUtf8("Наименование юридического лица"),
                                 QLineEdit::Normal,
                                 "", &ok);
    if (ok && !name.isEmpty()){
        QSqlQuery q;
        q.prepare("INSERT INTO firms (client_id, name) "
                  "VALUES (:clientID, :name)");
        q.bindValue(":clientID", currentClientID);
        q.bindValue(":name", name.trimmed());
        if(!q.exec()) {
            qCritical(logCritical()) << "Не удалось добавить юр.лицо" << q.lastError().text();
            return;
        }
        setFilterClients();
    }
}

void FirmsDialog::setFilterClients()
{
    strFilter = QString("client_id = %1").arg(currentClientID);
    modelFirms->setFilter(strFilter);
    modelFirms->select();
}

void FirmsDialog::showFirmInfo(QModelIndex idx)
{
    ui->plainTextEditAdress->setPlainText(modelFirms->data(modelFirms->index(idx.row(),3)).toString());
    ui->lineEditOKPO->setText(modelFirms->data(modelFirms->index(idx.row(),4)).toString());
    ui->lineEditINN->setText(modelFirms->data(modelFirms->index(idx.row(),5)).toString());
    ui->lineEditNumDog->setText(modelFirms->data(modelFirms->index(idx.row(),6)).toString());
    ui->dateEdit->setDate(modelFirms->data(modelFirms->index(idx.row(),7)).toDate());
}

void FirmsDialog::on_pushButtonAdd_clicked()
{
    addFirms();
}

void FirmsDialog::slotFirmChanged(QItemSelection selection)
{
    showFirmInfo(selection.indexes().first());
}
