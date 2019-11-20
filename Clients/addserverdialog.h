#ifndef ADDSERVERDIALOG_H
#define ADDSERVERDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>

namespace Ui {
class AddServerDialog;
}

class AddServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddServerDialog(QSqlRecord *r, int clID, QWidget *parent = nullptr);
    ~AddServerDialog();
private slots:
    void on_comboBoxServerType_activated(int idx);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_toolButton_clicked();

private:
    void createUI();
    void createModels();
private:
    Ui::AddServerDialog *ui;
    QSqlQueryModel *modelServersType;
    int serverId;
    int currentType;
    int clientID;
    QSqlRecord *recordServer;
};

#endif // ADDSERVERDIALOG_H
