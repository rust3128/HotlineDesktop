#include "mainwindow.h"
#include "ui_mainwindow.h"
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


void MainWindow::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("О Программе Hotline Desctop"),
             tr("Программа <b>Hotline Desctop</b> создана для облегчения работы сотрудников Горячей Линиии."));
}

void MainWindow::on_action_Qt_triggered()
{
    QApplication::aboutQt();
}
