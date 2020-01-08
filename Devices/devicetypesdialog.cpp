#include "devicetypesdialog.h"
#include "ui_devicetypesdialog.h"
#include <QSqlQuery>

DeviceTypesDialog::DeviceTypesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceTypesDialog)
{
    ui->setupUi(this);
    createUI();
}

DeviceTypesDialog::~DeviceTypesDialog()
{
    delete ui;
}

void DeviceTypesDialog::changeEvent(QEvent *e)
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

void DeviceTypesDialog::createUI()
{
    model = new QSqlTableModel(this);
    model->setTable("devicetype");
    model->select();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
}

void DeviceTypesDialog::on_toolButtonAdd_clicked()
{
    QSqlQuery q;
    q.exec("INSERT INTO devicetype (devtypename) VALUES ('Новое устройство')");
    model->select();
}

void DeviceTypesDialog::on_buttonBox_rejected()
{
    this->reject();
}
