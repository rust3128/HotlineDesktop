#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMdiArea>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();
    void on_actionAbout_triggered();
    void on_action_Qt_triggered();
    void on_actionConnSettings_triggered();
    void on_actionClientsList_triggered();
    void on_actionFirms_triggered();
    void slotGetNumberButton();
    void on_actionDevis_triggered();

    void on_actionPoss_triggered();

    void on_actionBanks_triggered();

private:
    void setToolBarClients();
private:
    Ui::MainWindow *ui;
    QMdiArea *mdiArea;
};
#endif // MAINWINDOW_H
