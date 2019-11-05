#ifndef FIRMSDIALOG_H
#define FIRMSDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class FirmsDialog;
}

class FirmsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FirmsDialog(QWidget *parent = nullptr);
    ~FirmsDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void createUI();
    void createModels();
private:
    Ui::FirmsDialog *ui;
    QSqlQueryModel *modelClients;
    QSqlTableModel *modelFirms;
    qint16 currentClientID;
    QString strFilter;
};

#endif // FIRMSDIALOG_H
