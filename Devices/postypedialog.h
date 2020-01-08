#ifndef POSTYPEDIALOG_H
#define POSTYPEDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class PosTypeDialog;
}

class PosTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PosTypeDialog(QWidget *parent = nullptr);
    ~PosTypeDialog();

protected:
    void changeEvent(QEvent *e);
private slots:
    void on_toolButtonAdd_clicked();

    void on_buttonBox_rejected();

private:
    void createUI();
private:
    Ui::PosTypeDialog *ui;
    QSqlTableModel *model;
};

#endif // POSTYPEDIALOG_H
