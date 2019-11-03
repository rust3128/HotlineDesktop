#ifndef CLIENTSLISTDIALOG_H
#define CLIENTSLISTDIALOG_H

#include <QDialog>
#include <QSqlTableModel>


namespace Ui {
class ClientsListDialog;
}

class ClientsListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientsListDialog(QWidget *parent = nullptr);
    ~ClientsListDialog();

private slots:
    void on_buttonBox_accepted();
    void slotCurrentPic(QModelIndex idx);

private:
    void createUI();
    void createModel();
private:
    Ui::ClientsListDialog *ui;
    QSqlTableModel *modelClients;
};

#endif // CLIENTSLISTDIALOG_H
