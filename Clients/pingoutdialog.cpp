#include "pingoutdialog.h"
#include "ui_pingoutdialog.h"

#include <QByteArray>
#include <QTextCodec>


PingOutDialog::PingOutDialog(QString *hostAdress, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PingOutDialog)
{
    ui->setupUi(this);

    this->setWindowTitle(QString("ping  %1").arg(*hostAdress));
    modelPing = new PingModel(hostAdress,this);
    connect(modelPing,&PingModel::signalSendOutPing,this,&PingOutDialog::slotGetPingString);
    connect(this,&PingOutDialog::signalStartPing,this,&PingOutDialog::slotStartPing);
    emit signalStartPing();
}

PingOutDialog::~PingOutDialog()
{
    delete ui;
}

void PingOutDialog::slotGetPingString(QByteArray output)
{

    QTextCodec *codec = QTextCodec::codecForName("cp-866");
    QString pStr = codec->toUnicode(output.data());
    ui->plainTextEdit->appendPlainText(pStr.trimmed());
}

void PingOutDialog::slotStartPing()
{
    modelPing->start_command();
}

void PingOutDialog::on_buttonBox_rejected()
{
    this->reject();
}
