#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConnectionSettingDialog/connectionsettingdialog.h"
#include "Clients/clientslistdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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


