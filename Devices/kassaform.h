#ifndef KASSAFORM_H
#define KASSAFORM_H

#include <QWidget>

namespace Ui {
class KassaForm;
}

class KassaForm : public QWidget
{
    Q_OBJECT

public:
    explicit KassaForm(QWidget *parent = nullptr);
    ~KassaForm();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::KassaForm *ui;
};

#endif // KASSAFORM_H
