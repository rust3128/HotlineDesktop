#include "banksdialog.h"
#include "ui_banksdialog.h"
#include <QSqlQuery>


BanksDialog::BanksDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BanksDialog)
{
    ui->setupUi(this);
    createUI();
}

BanksDialog::~BanksDialog()
{
    delete ui;
}

void BanksDialog::changeEvent(QEvent *e)
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

void BanksDialog::createUI()
{
    model = new QSqlTableModel(this);
    model->setTable("banks");
    model->setHeaderData(0,Qt::Horizontal,"МФО");
    model->setHeaderData(1,Qt::Horizontal,"Наименование");
    model->select();


    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->stretchLastSection();
    ui->tableView->resizeColumnsToContents();


}

void BanksDialog::on_toolButtonAdd_clicked()
{
    QSqlQuery q;
    q.exec("INSERT INTO `banks` (`mfo`, `bankname`) VALUES ('Новый МФО', 'Новое название')");
    model->select();
    ui->tableView->resizeColumnsToContents();
}

void BanksDialog::on_buttonBox_rejected()
{
    this->reject();
}
