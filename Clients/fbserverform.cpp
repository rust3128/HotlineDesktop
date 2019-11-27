#include "fbserverform.h"
#include "ui_fbserverform.h"
#include "LoggingCategories/loggingcategories.h"

FBServerForm::FBServerForm(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FBServerForm)
{
    ui->setupUi(this);
}

FBServerForm::~FBServerForm()
{
    delete ui;
}

void FBServerForm::changeEvent(QEvent *e)
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

void FBServerForm::on_FBServerForm_clicked()
{
    qInfo(logInfo()) << "Clicked FB server" ;
}


void FBServerForm::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    qInfo(logInfo()) << "Doble clicked mouse!!!";
}
