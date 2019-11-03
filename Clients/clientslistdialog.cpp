#include "clientslistdialog.h"
#include "ui_clientslistdialog.h"
#include "Clients/addclientdialog.h"
#include <QPushButton>

ClientsListDialog::ClientsListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsListDialog)
{
    ui->setupUi(this);

    createModel();
    createUI();
}

ClientsListDialog::~ClientsListDialog()
{
    delete ui;
}

void ClientsListDialog::createUI()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Добавить");
    ui->tableViewList->setModel(modelClients);
    ui->tableViewList->setColumnHidden(0,true);
    ui->tableViewList->setColumnHidden(2,true);

    ui->tableViewList->verticalHeader()->hide();
    ui->tableViewList->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableViewList->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
             this, SLOT(slotCurrentPic(QModelIndex)));
    modelClients->select();
    ui->tableViewList->resizeColumnsToContents();
}

void ClientsListDialog::createModel()
{
    modelClients = new QSqlTableModel();
    modelClients->setTable("CLIENTS");
    modelClients->setHeaderData(1,Qt::Horizontal,"Наименование");
    modelClients->setHeaderData(3,Qt::Horizontal,"Коментарии");

}

void ClientsListDialog::on_buttonBox_accepted()
{
    AddClientDialog *addClient = new AddClientDialog(this);
    addClient->exec();
    modelClients->select();
    ui->tableViewList->resizeColumnsToContents();
}

void ClientsListDialog::slotCurrentPic(QModelIndex idx)
{

    QPixmap outPixmap = QPixmap(); // Создаём QPixmap, который будет помещаться в picLabel
    /* Забираем данные об изображении из таблицы в качестве QByteArray
     * и помещаем их в QPixmap
     * */
    outPixmap.loadFromData(modelClients->data(modelClients->index(idx.row(), 2)).toByteArray());
    // Устанавливаем изображение в picLabel
    if(!outPixmap.isNull())
        ui->labelLogo->setPixmap(outPixmap.scaledToWidth(150));
    else
        ui->labelLogo->setText("Логотип отсутствует");
}
