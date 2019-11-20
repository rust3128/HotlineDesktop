#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QSqlRecord>

namespace Ui {
class ClientsWindow;
}

class ClientsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientsWindow(int clID, QWidget *parent = nullptr);
    ~ClientsWindow();

private slots:
    void on_pushButtonFirms_clicked();

    void on_toolButtonAddServer_clicked();

    void on_tableWidgetServers_itemDoubleClicked(QTableWidgetItem *item);

private:
    void createUI();
    void createModels();
    void createServerLists();
    void modifyServerList(QSqlRecord *rec);

private:
    Ui::ClientsWindow *ui;
    int clientID;
    QSqlQueryModel *modelServers;
};

#endif // CLIENTSWINDOW_H
