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

private:
    void createModel();
    void createUI();
private:
    Ui::PaytypeForm *ui;
    int clientID;
    ModelPaytypes *model;
};

#endif // PAYTYPEFORM_H
