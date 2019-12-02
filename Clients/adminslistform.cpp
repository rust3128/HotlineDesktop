#include "adminslistform.h"
#include "ui_adminslistform.h"
#include "LoggingCategories/loggingcategories.h"
#include "Clients/contactdialog.h"

#include <QSqlQuery>
#include <QSqlError>

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
    ui->treeView->resizeColumnToContents(0);
    ui->treeView->resizeColumnToContents(1);
    ui->treeView->hideColumn(2);
}

void AdminsListForm::changeContactInfo(int id)
{
    ContactDialog *contDlg = new ContactDialog(id,clientID, this);
    if(contDlg->exec() == QDialog::Accepted){
        model->deleteLater();
        model = new TreeModel(clientID, this);
        createUI();
    }
}

void AdminsListForm::on_treeView_doubleClicked(const QModelIndex &idx)
{
    qInfo(logInfo()) << "--------------------";
    qInfo(logInfo()) << "Parrent index Row" << idx.parent().row() << "Col" << idx.parent().column();
    qInfo(logInfo()) << "Current index Row" << idx.row() << "Col" << idx.column();
    qInfo(logInfo()) << "Current DATA:" << idx.data().toString();
    const int row = (idx.parent().row() >= 0) ? idx.parent().row() : idx.row();
    const int contactID = model->data(model->index(row,2),Qt::DisplayRole).toInt();
    qInfo(logInfo()) << "Column 2 data" << model->data(model->index(row,2),Qt::DisplayRole).toString();
    changeContactInfo(contactID);

}

void AdminsListForm::on_toolButtonAddContact_clicked()
{
    changeContactInfo(-1);
}
