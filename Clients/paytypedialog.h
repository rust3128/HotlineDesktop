#ifndef PAYTYPEDIALOG_H
#define PAYTYPEDIALOG_H

#include <QDialog>

namespace Ui {
class PaytypeDialog;
}

class PaytypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PaytypeDialog(int id, QWidget *parent = nullptr);
    ~PaytypeDialog();

private:
    Ui::PaytypeDialog *ui;
    int paytypeID;
};

#endif // PAYTYPEDIALOG_H
