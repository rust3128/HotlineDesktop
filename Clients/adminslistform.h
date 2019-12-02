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

private slots:
    void on_treeView_doubleClicked(const QModelIndex &idx);
    void on_toolButtonAddContact_clicked();

private:
    void createUI();
    void changeContactInfo(int id);
private:
    Ui::AdminsListForm *ui;
    TreeModel *model;
    int clientID;
};

#endif // ADMINSLISTFORM_H
