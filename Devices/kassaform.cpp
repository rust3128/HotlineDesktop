#include "kassaform.h"
#include "ui_kassaform.h"

KassaForm::KassaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KassaForm)
{
    ui->setupUi(this);
}

KassaForm::~KassaForm()
{
    delete ui;
}

void KassaForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
