#ifndef PAYTYPEDIALOG_H
#define PAYTYPEDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class PaytypeDialog;
}

class PaytypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaytypeDialog(QSqlRecord *rec, QWidget *parent = nullptr);
    ~PaytypeDialog();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void createUI();
private:
    Ui::PaytypeDialog *ui;
    QSqlRecord *recordPaytype;
};

#endif // PAYTYPEDIALOG_H
