#ifndef ADDSERVERDIALOG_H
#define ADDSERVERDIALOG_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class AddServerDialog;
}

class AddServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddServerDialog(int servID, int clID, QWidget *parent = nullptr);
    ~AddServerDialog();
private slots:
    void on_comboBoxServerType_activated(int idx);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void createUI();
    void createModels();
private:
    Ui::AddServerDialog *ui;
    QSqlQueryModel *modelServersType;
    int serverId;
    int currentType;
    int clientID;
};

#endif // ADDSERVERDIALOG_H
