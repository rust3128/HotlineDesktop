#ifndef FIRMSDIALOG_H
#define FIRMSDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QItemSelection>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class FirmsDialog;
}

class FirmsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FirmsDialog(int clnID, QWidget *parent = nullptr);
    ~FirmsDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_listViewClients_doubleClicked(const QModelIndex &idx);

    void on_comboBoxClients_activated(int idx);

    void on_pushButtonAdd_clicked();
    void slotFirmChanged(QItemSelection selection);

private:
    void createUI();
    void createModels();
    void addFirms();
    void setFilterClients();
    void showFirmInfo(QModelIndex idx);
private:
    Ui::FirmsDialog *ui;
    QSqlQueryModel *modelClients;
    QSqlTableModel *modelFirms;
    int currentClientID;
    int currentFirmID;
    QString strFilter;
};

#endif // FIRMSDIALOG_H
