#include "devicetypesdialog.h"
#include "ui_devicetypesdialog.h"

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
