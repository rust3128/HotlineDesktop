#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConnectionSettingDialog/connectionsettingdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "Clients/clientslistdialog.h"
#include "Clients/firmsdialog.h"
#include "Clients/clientswindow.h"
#include "DynamicButton/dynamiicbutton.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QBuffer>
#include <QHBoxLayout>
#include <QMdiSubWindow>

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
    ui->toolBarClients->setStyleSheet("background: #38395a;");
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
    FirmsDialog *firmsDlg = new FirmsDialog(-1,this);
    firmsDlg->exec();
}

void MainWindow::slotGetNumberButton()
{
    DynamiicButton *button = static_cast<DynamiicButton*>(sender());
    int clientID=button->getButtonID();
    ClientsWindow *clnWnd = new ClientsWindow(clientID, this);
    clnWnd->setWindowTitle(button->text());
    if(mdiArea->subWindowList().size()>0){
        for(int i=0; i<mdiArea->subWindowList().size();++i) {
            if(mdiArea->subWindowList().at(i)->windowTitle() == button->text()) {
                mdiArea->setActiveSubWindow(mdiArea->subWindowList().at(i));
                return;
            }

        }
    }
    mdiArea->addSubWindow(clnWnd);
    clnWnd->showMaximized();


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
         button->setStyleSheet("color: white;"
                               "background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #444450, stop: 0.49 #444450, stop: 0.5 #3c3c46, stop: 1 #1f1f24);"
                               "border-width: 1px;"
                               "border-color: #141529;"
                               "border-style: solid;"
                               "border-radius:4;"
                               "padding: 3px;"
                               "font-size: 16px;"
                               "font-variant:small-caps;"
                               "font-family: courier;"
                               "padding-left:5px;"
                               "padding-right: 5px;"
                               "min-width: 100px;"
                               "max-width: 100px;"
                               "min-height: 15px;"
                               "max-height: 15px;");
         ui->toolBarClients->addWidget(button);


         connect(button,&QAbstractButton::clicked,this,&MainWindow::slotGetNumberButton);
    }
    q.finish();

}
