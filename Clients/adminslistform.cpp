#include "adminslistform.h"
#include "ui_adminslistform.h"
#include "LoggingCategories/loggingcategories.h"

AdminsListForm::AdminsListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminsListForm)
{
    ui->setupUi(this);
}

AdminsListForm::~AdminsListForm()
{
    delete ui;
}

void AdminsListForm::slotGetClientID(int id)
{
    clientID = id;
    model = new TreeModel(clientID, this);
    createUI();
}

void AdminsListForm::changeEvent(QEvent *e)
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

void AdminsListForm::createUI()
{
    ui->treeView->setModel(model);
}
