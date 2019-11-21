#include "clientswindow.h"
#include "ui_clientswindow.h"
#include "Clients/firmsdialog.h"
#include "Clients/addserverdialog.h"
#include "LoggingCategories/loggingcategories.h"


ClientsWindow::ClientsWindow(int clID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientsWindow),
    clientID(clID)
{
    ui->setupUi(this);

    createModels();
    createUI();

}

ClientsWindow::~ClientsWindow()
{
    delete ui;
}

void ClientsWindow::createUI()
{
    QSqlQuery q;
    q.prepare("SELECT NAME, LOGO, COMMENTS FROM clients WHERE CLIENT_ID = :clientID");
    q.bindValue(":clientID", clientID);
    q.exec();
    q.next();
    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(q.value(1).toByteArray());
    if(!outPixmap.isNull())
        ui->labelLogo->setPixmap(outPixmap.scaledToWidth(150));
    else
        ui->labelLogo->clear();
    ui->labelName->setText(q.value(0).toString());
    ui->labelComments->setText(q.value(2).toString());


    ui->tableWidgetServers->setColumnCount(4);
    ui->tableWidgetServers->setHorizontalHeaderLabels(QStringList() << "ID" << "" << "Тип" << "Подключение");
    ui->tableWidgetServers->verticalHeader()->hide();
    ui->tableWidgetServers->hideColumn(0);
    ui->tableWidgetServers->hideColumn(4);
    createServerLists();


}

void ClientsWindow::createModels()
{
    modelServers = new QSqlQueryModel(this);
    QString strSQL = QString("SELECT s.server_id, s.isactive, t.servertypename, s.connections, s.servertype_id FROM servers s "
                             "LEFT JOIN serverstype t ON t.servertype_id = s.servertype_id "
                             "WHERE s.client_id = %1 "
                             "ORDER BY s.server_id").arg(clientID);
    modelServers->setQuery(strSQL);
    if(modelServers->lastError().isValid()) qCritical(logCritical()) << "Не возможно получить список серверов." << modelServers->lastError().text();
}

void ClientsWindow::createServerLists()
{
      const int rowCoun = modelServers->rowCount();
      const int columnCount = modelServers->columnCount();
      for(int row = 0; row<rowCoun; ++row){
          ui->tableWidgetServers->insertRow(row);
          for(int col=0; col<columnCount; ++col) {
              if(col == 1){
                  QIcon icon = (modelServers->data(modelServers->index(row,col)).toBool()) ? QIcon(":/Images/yesicon.png") : QIcon(":/Images/NoIcon.png");
                  ui->tableWidgetServers->setItem(row,col, new QTableWidgetItem(icon,nullptr));
                  continue;
              }
              ui->tableWidgetServers->setItem(row,col, new QTableWidgetItem(modelServers->data(modelServers->index(row,col)).toString()));
          }
      }
      ui->tableWidgetServers->resizeColumnsToContents();
}



void ClientsWindow::on_pushButtonFirms_clicked()
{
    FirmsDialog *firmsDlg = new FirmsDialog(clientID,this);
    firmsDlg->exec();
}

void ClientsWindow::on_toolButtonAddServer_clicked()
{
    static QSqlRecord r;
    r.clear();
    modifyServerList(&r);
}

void ClientsWindow::on_tableWidgetServers_itemDoubleClicked(QTableWidgetItem *item)
{
    const int idServer = ui->tableWidgetServers->item(item->row(),0)->data(Qt::DisplayRole).toInt();
    qInfo(logInfo()) << "Current row" << item->row() << "idServer" << idServer;
    QSqlRecord r = modelServers->record(item->row());
    modifyServerList(&r);
}
void ClientsWindow::modifyServerList(QSqlRecord *rec)
{
    AddServerDialog *addSer = new AddServerDialog(rec, clientID, this);
    addSer->exec();
    if(addSer->result() == QDialog::Accepted){
        ui->tableWidgetServers->clear();
        ui->tableWidgetServers->setRowCount(0);
        modelServers->setQuery(modelServers->query().lastQuery());
        ui->tableWidgetServers->setHorizontalHeaderLabels(QStringList() << "ID" << "" << "Тип" << "Подключение");
        createServerLists();
    }
}
