#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConnectionSettingDialog/connectionsettingdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "Clients/clientslistdialog.h"
#include "Clients/firmsdialog.h"
#include "DynamicButton/dynamiicbutton.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QBuffer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea(this);  // инициализируем QMdiArea
    // Настраиваем скроллбары
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    // Устанавливаем Mdi Area в качестве центрального виджета
    setCentralWidget(mdiArea);

    setToolBarClients();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnSettings_triggered()
{
    ConnectionSettingDialog *connDlg = new ConnectionSettingDialog(this);
    connDlg->exec();
}

void MainWindow::on_actionClientsList_triggered()
{
    ClientsListDialog *clDlg = new ClientsListDialog(this);
    clDlg->exec();
}


void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("О Программе Hotline Desktop"),
             tr("Программа <b>Hotline Desktop</b> создана для облегчения работы сотрудников Горячей Линиии."));
}

void MainWindow::on_action_Qt_triggered()
{
    QApplication::aboutQt();
}



void MainWindow::on_actionFirms_triggered()
{
    FirmsDialog *firmsDlg = new FirmsDialog(this);
    firmsDlg->exec();
}

void MainWindow::slotGetNumberButton()
{
    DynamiicButton *button = (DynamiicButton*)sender();
    int clientID=button->getButtonID();
    qInfo(logInfo()) << "Client ID" << clientID;
}

void MainWindow::setToolBarClients()
{
    QSqlQuery q;

    q.prepare("SELECT CLIENT_ID, NAME, LOGO, COMMENTS FROM clients ORDER BY CLIENT_ID");
    if(!q.exec()){
        qCritical(logCritical()) << "Не возможно получить список клиентов" << q.lastError().text();
        return;
    }
    while(q.next()){
         DynamiicButton *button = new DynamiicButton(q.value(0).toInt(),this);
         button->setText(q.value(1).toString());

         QPixmap outPixmap;
         outPixmap.loadFromData(q.value(2).toByteArray());
         outPixmap = outPixmap.scaledToWidth(100);
         QByteArray byteArray;
         QBuffer buffer (&byteArray);
         outPixmap.save(&buffer, "PNG");
         QString html = QString("<img src='data:image/png;base64, %0'>").arg(QString(byteArray.toBase64()));
         button->setToolTip(html);
         button->setToolTipDuration(1000);
         ui->toolBarClients->addWidget(button);
         connect(button,&QAbstractButton::clicked,this,&MainWindow::slotGetNumberButton);
    }
    q.finish();

}
