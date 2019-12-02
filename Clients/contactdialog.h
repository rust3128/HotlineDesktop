#ifndef CONTACTDIALOG_H
#define CONTACTDIALOG_H

#include <QDialog>

namespace Ui {
class ContactDialog;
}

class ContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ContactDialog(int id, int clID,  QWidget *parent = nullptr);
    ~ContactDialog();

public slots:
    void slotSetModified()
    {
        modified = true;
    }
protected:
    void changeEvent(QEvent *e);
    void createUI();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::ContactDialog *ui;
    int contactID;
    int clientID;
    bool modified;
};

#endif // CONTACTDIALOG_H
