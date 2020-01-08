#ifndef DEVICETYPESDIALOG_H
#define DEVICETYPESDIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class DeviceTypesDialog;
}

class DeviceTypesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceTypesDialog(QWidget *parent = nullptr);
    ~DeviceTypesDialog();

protected:
    void changeEvent(QEvent *e);

private:
    void createUI();
private:
    Ui::DeviceTypesDialog *ui;
    QSqlTableModel *model;
};

#endif // DEVICETYPESDIALOG_H
