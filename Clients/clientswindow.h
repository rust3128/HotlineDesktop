#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

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

private:
    void createUI();
    void createModels();
    void createServerLists();
private:
    Ui::ClientsWindow *ui;
    int clientID;
    QSqlQueryModel *modelServers;
};

#endif // CLIENTSWINDOW_H
