#ifndef FBSERVERFORM_H
#define FBSERVERFORM_H

#include <QGroupBox>



namespace Ui {
class FBServerForm;
}

enum TypeSql {
    SELECT,
    INSERT,
    UPDATE
};

class FBServerForm : public QGroupBox
{
    Q_OBJECT

public:
    explicit FBServerForm(QWidget *parent = nullptr);
    ~FBServerForm();


protected:
    void changeEvent(QEvent *e);

public slots:
    void slotGetClientID(int ID);
private slots:
    void slotIsTextChanged();
private:
    void createUI();
    void setEditable();
    void executeSQL(int type);

private:
    Ui::FBServerForm *ui;
    QPalette mEditable;
    QPalette  mNonEditable;
    bool bEditable;
    bool bTextChanged;
    int mClientID;
    int mConnectID;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // FBSERVERFORM_H
