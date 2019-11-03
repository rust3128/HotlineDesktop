#include "addclientdialog.h"
#include "ui_addclientdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include <QFileDialog>
#include <QBuffer>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

AddClientDialog::AddClientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClientDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
}

AddClientDialog::~AddClientDialog()
{
    delete ui;
}

void AddClientDialog::on_plainTextEdit_textChanged()
{
    if(ui->plainTextEdit->placeholderText().length() > 100)
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->placeholderText().left(100));
}


void AddClientDialog::on_pushButtonLoad_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть логотип"), "", tr("Изображения (*.png *.jpeg *.jpg)"));
    QPixmap inPixmap(fileName); // Сохраняем его в изображение объекта QPixmap;
    ui->labelLogo->setPixmap(inPixmap);
    QBuffer inBuffer( &inByteArray );                   // Сохранение изображения производим через буффер
    inBuffer.open( QIODevice::WriteOnly );              // Открываем буффер
    inPixmap.save( &inBuffer, "PNG" );                  // Записываем inPixmap в inByteArray
}

void AddClientDialog::on_buttonBox_accepted()
{
    int result = QMessageBox::question(this,tr("Вопрос"),
                                       QString(tr("Вы дейстиветльно хотите добавить клиента %1 в базу данных?"))
                                       .arg(ui->lineEditName->text().trimmed()));
    if(result == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare("INSERT INTO CLIENTS (CLIENT_ID, NAME, LOGO, COMMENTS) "
                  "VALUES (GEN_ID(GEN_CLIENTS_ID,1), :name, :logo, :comments)");
        q.bindValue(":name", ui->lineEditName->text().trimmed());
        q.bindValue(":logo", inByteArray);
        q.bindValue(":comments", ui->plainTextEdit->toPlainText());
        if(!q.exec()) {
            qCritical(logCritical()) << "Не возможно добавить клиента." << endl << q.lastError().text();
            return;
        }
        qInfo(logInfo()) << "Клиент изменен.";
    }
    this->accept();
}

void AddClientDialog::on_buttonBox_rejected()
{
    this->reject();
}

void AddClientDialog::on_lineEditName_textChanged(const QString &name)
{
    bool enabled = (name.length() >2) ? true : false;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(enabled);
}
