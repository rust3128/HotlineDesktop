#ifndef PAYTYPEFORM_H
#define PAYTYPEFORM_H

#include <QGroupBox>
#include "modelpaytypes.h"



namespace Ui {
class PaytypeForm;
}

class PaytypeForm : public QGroupBox
{
    Q_OBJECT

public:
    explicit PaytypeForm(QWidget *parent = nullptr);
    ~PaytypeForm();

public slots:
    void slotGetClientID(int id);
protected:
    void changeEvent(QEvent *e);

private slots:
    void on_toolButtonAddPaytype_clicked();

    void on_tableView_doubleClicked(const QModelIndex &idx);

private:
    void createModel();
    void createUI();
    void showPaytypeDialog(int id);
private:
    Ui::PaytypeForm *ui;
    int clientID;
    ModelPaytypes *model;

};

#endif // PAYTYPEFORM_H
