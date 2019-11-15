#include "clientswindow.h"
#include "ui_clientswindow.h"
#include "Clients/firmsdialog.h"

ClientsWindow::ClientsWindow(int clID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientsWindow),
    clientID(clID)
{
    ui->setupUi(this);

    createUI();

}

ClientsWindow::~ClientsWindow()
{
    delete ui;
}

void ClientsWindow::createUI()
{
    QSqlQuery q;
    q.prepare("SELECT NAME, LOGO, COMMENTS FROM clients WHERE CLIENT_ID = :clientID");
    q.bindValue(":clientID", clientID);
    q.exec();
    q.next();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(q.value(1).toByteArray());
    if(!outPixmap.isNull())
        ui->labelLogo->setPixmap(outPixmap.scaledToWidth(150));
    else
        ui->labelLogo->clear();
    ui->labelName->setText(q.value(0).toString());
    ui->labelComments->setText(q.value(2).toString());

}

void ClientsWindow::on_pushButtonFirms_clicked()
{
    FirmsDialog *firmsDlg = new FirmsDialog(clientID,this);
    firmsDlg->exec();
}
