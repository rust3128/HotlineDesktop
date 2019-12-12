#ifndef OBJECTCONTACTDIALOG_H
#define OBJECTCONTACTDIALOG_H

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class ObjectContactDialog;
}

class ObjectContactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ObjectContactDialog(int id, QSqlRecord *record, QWidget *parent = nullptr);
    ~ObjectContactDialog();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::ObjectContactDialog *ui;
    int objectID;
};

#endif // OBJECTCONTACTDIALOG_H
