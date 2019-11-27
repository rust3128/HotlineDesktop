#ifndef FBSERVERFORM_H
#define FBSERVERFORM_H

#include <QGroupBox>

namespace Ui {
class FBServerForm;
}

class FBServerForm : public QGroupBox
{
    Q_OBJECT

public:
    explicit FBServerForm(QWidget *parent = nullptr);
    ~FBServerForm();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_FBServerForm_clicked();

private:
    Ui::FBServerForm *ui;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // FBSERVERFORM_H
