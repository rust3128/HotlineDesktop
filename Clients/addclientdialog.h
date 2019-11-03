#ifndef ADDCLIENTDIALOG_H
#define ADDCLIENTDIALOG_H

#include <QDialog>

namespace Ui {
class AddClientDialog;
}

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientDialog(QWidget *parent = nullptr);
    ~AddClientDialog();

private slots:
    void on_plainTextEdit_textChanged();

    void on_pushButtonLoad_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_lineEditName_textChanged(const QString &name);

private:
    Ui::AddClientDialog *ui;
    QByteArray inByteArray;
};

#endif // ADDCLIENTDIALOG_H
