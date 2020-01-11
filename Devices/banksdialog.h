#ifndef BANKSDIALOG_H
#define BANKSDIALOG_H

#include <QDialog>
#include "QSqlTableModel"

namespace Ui {
class BanksDialog;
}

class BanksDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BanksDialog(QWidget *parent = nullptr);
    ~BanksDialog();

protected:
    void changeEvent(QEvent *e);
private slots:
    void on_toolButtonAdd_clicked();

    void on_buttonBox_rejected();

private:
    void createUI();
private:
    Ui::BanksDialog *ui;
    QSqlTableModel *model;
};

#endif // BANKSDIALOG_H
