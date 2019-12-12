#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include "modelterminals.h"
#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTableWidgetItem>
#include <QSqlRecord>
#include <QItemSelectionModel>

namespace Ui {
class ClientsWindow;
}

class ClientsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientsWindow(int clID, QWidget *parent = nullptr);
    ~ClientsWindow();
    int sentClientID();
signals:
    void signalSendClientID(int);
private slots:
    void on_pushButtonFirms_clicked();
    void on_toolButtonAddServer_clicked();
    void on_tableWidgetServers_itemDoubleClicked(QTableWidgetItem *item);
    void on_toolButtonPing_clicked();
    void slotSelectionTerminals(const QItemSelection &, const QItemSelection &);

    void on_toolButtonAddObjectContact_clicked();

    void on_tableViewObjectCont_doubleClicked(const QModelIndex &index);

private:
    void createUI();
    void createConnections();
    void createModels();
    void createServerLists();
    void modifyServerList(QSqlRecord *rec);


private:
    Ui::ClientsWindow *ui;
    int clientID;
    int objectID;
    QSqlQueryModel *modelServers;
    ModelTerminals *modelTerminals;
    QSqlTableModel *modelObjContacts;
};

#endif // CLIENTSWINDOW_H
