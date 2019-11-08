#ifndef CLIENTSWINDOW_H
#define CLIENTSWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class ClientsWindow;
}

class ClientsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientsWindow(int clID, QWidget *parent = nullptr);
    ~ClientsWindow();

private:
    void createUI();
private:
    Ui::ClientsWindow *ui;
    int clientID;
};

#endif // CLIENTSWINDOW_H
