#ifndef PINGOUTDIALOG_H
#define PINGOUTDIALOG_H

#include <QDialog>
#include "PingModel/pingmodel.h"

namespace Ui {
class PingOutDialog;
}

class PingOutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PingOutDialog(QString *hostAdress, QWidget *parent = nullptr);
    ~PingOutDialog();

signals:
    void signalStartPing();
private slots:
    void slotGetPingString(QByteArray output);
    void slotStartPing();

    void on_buttonBox_rejected();

private:
    Ui::PingOutDialog *ui;
    QString hostAdress;
    PingModel *modelPing;

};

#endif // PINGOUTDIALOG_H
