#include "paytypeform.h"
#include "ui_paytypeform.h"
#include "LoggingCategories/loggingcategories.h"

PaytypeForm::PaytypeForm(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::PaytypeForm)
{
    ui->setupUi(this);
}

PaytypeForm::~PaytypeForm()
{
    delete ui;
}

void PaytypeForm::slotGetClientID(int id)
{
    clientID = id;
    createModel();
    createUI();
}

void PaytypeForm::changeEvent(QEvent *e)
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

void PaytypeForm::createModel()
{
    model = new ModelPaytypes();
    QString strSQL = QString("SELECT paytypes.paytype_id, paytypes.mpos_id, paytypes.name, paytypes.dllname, paytypes.isactive FROM paytypes WHERE paytypes.client_id = %1")
            .arg(clientID);
    model->setQuery(strSQL);
    model->setHeaderData(1, Qt::Horizontal,"MPos\nID");
    model->setHeaderData(2, Qt::Horizontal,"Наименование");
    model->setHeaderData(3, Qt::Horizontal,"Плагин");
    model->setHeaderData(4, Qt::Horizontal,"Активен");
}

void PaytypeForm::createUI()
{
    ui->tableView->setModel(model);
    ui->tableView->hideColumn(0);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setMinimumSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());

}
