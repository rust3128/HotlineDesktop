#include "firmsdialog.h"
#include "ui_firmsdialog.h"
#include <QPushButton>

FirmsDialog::FirmsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FirmsDialog)
{
    ui->setupUi(this);

    currentClientID = -1;
    createModels();
    createUI();
}

FirmsDialog::~FirmsDialog()
{
    delete ui;
}

void FirmsDialog::createUI()
{
    ui->buttonBox->button(QDialogButtonBox::Save)->hide();
    ui->comboBoxClients->setModel(modelClients);
    ui->comboBoxClients->setModelColumn(1);
    ui->comboBoxClients->setCurrentIndex(currentClientID);
    ui->comboBoxClients->setCurrentText("Выберите клиента...");
}

void FirmsDialog::createModels()
{
    modelClients = new QSqlQueryModel();
    modelClients->setQuery("SELECT c.client_id, c.name FROM clients c");

    modelFirms = new QSqlTableModel();
    modelFirms->setTable("FIRMS");
    modelFirms->select();
    strFilter = QString("CLIENT_ID = %1").arg(currentClientID);
    modelFirms->setFilter("strFilter");

}

void FirmsDialog::on_buttonBox_accepted()
{

}

void FirmsDialog::on_buttonBox_rejected()
{
    this->reject();
}
