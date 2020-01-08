#include "postypedialog.h"
#include "ui_postypedialog.h"
#include <QSqlQuery>

PosTypeDialog::PosTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PosTypeDialog)
{
    ui->setupUi(this);
    createUI();
}

PosTypeDialog::~PosTypeDialog()
{
    delete ui;
}

void PosTypeDialog::changeEvent(QEvent *e)
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

void PosTypeDialog::createUI()
{
    model = new QSqlTableModel(this);
    model->setTable("postypes");
    model->select();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
}

void PosTypeDialog::on_toolButtonAdd_clicked()
{
    QSqlQuery q;
    q.exec("INSERT INTO postypes (postypename) VALUE('Новый тип...')");
    model->select();
}

void PosTypeDialog::on_buttonBox_rejected()
{
    this->reject();
}
