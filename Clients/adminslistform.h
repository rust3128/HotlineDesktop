#ifndef ADMINSLISTFORM_H
#define ADMINSLISTFORM_H

#include "TreeModel/treemodel.h"
#include <QWidget>


namespace Ui {
class AdminsListForm;
}

class AdminsListForm : public QWidget
{
    Q_OBJECT

public:
    explicit AdminsListForm(QWidget *parent = nullptr);
    ~AdminsListForm();

public slots:
    void slotGetClientID(int id);

protected:
    void changeEvent(QEvent *e);

private:
    void createUI();
private:
    Ui::AdminsListForm *ui;
    TreeModel *model;
    int clientID;
};

#endif // ADMINSLISTFORM_H
