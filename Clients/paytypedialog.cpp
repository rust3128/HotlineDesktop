#include "paytypedialog.h"
#include "ui_paytypedialog.h"

PaytypeDialog::PaytypeDialog(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaytypeDialog),
    paytypeID(id)
{
    ui->setupUi(this);
}

PaytypeDialog::~PaytypeDialog()
{
    delete ui;
}
