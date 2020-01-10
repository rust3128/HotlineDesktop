#include "clientswindow.h"
#include "ui_clientswindow.h"
#include "Clients/firmsdialog.h"
#include "Clients/addserverdialog.h"
#include "LoggingCategories/loggingcategories.h"
#include "Devices/kassaform.h"
#include <QListWidgetItem>
#include <QKeyEvent>
#include "pingoutdialog.h"
#include "Clients/fbserverform.h"
#include "objectcontactdialog.h"


ClientsWindow::ClientsWindow(int clID, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientsWindow),
    clientID(clID)
{
    ui->setupUi(this);
    ui->toolBoxMain->setStyleSheet("QToolBox::tab#toolBoxMain {"
                            "   background: #009deb;"
                                "border-radius: 5px;"
                                "font-size: 15px;"
                                "icon-size: 48px;"
                                "color: black;"
                            "}"
                            "QToolBox::tab:first#toolBoxMain {"
                                "background: #4ade00;"
                                "border-radius: 5px;"
                                "font-size: 15px;"
                                "color: black;"
                            "}"
                            "QToolBox::tab:last#toolBoxMain {"
                                "background: #f95300;"
                                "border-radius: 5px;"
                                "font-size: 15px;"
                                "color: black;"
                            "}"
                            "QToolBox::tab:selected#toolBoxMain {" /* italicize selected tabs */
                                "font: italic bold;"
                                "font-size: 15px;"
                                "color: white;"
                            "}");

    createConnections();
    emit signalSendClientID(clientID);
    createModels();
    createUI();
    connect(ui->tableViewTerminals->selectionModel(),&QItemSelectionModel::selectionChanged,this,&ClientsWindow::slotSelectionTerminals);
}

ClientsWindow::~ClientsWindow()
{
    delete ui;
}

int ClientsWindow::sentClientID()
{
    return clientID;
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
    if(!outPixmap.isNull()){
        ui->labelLogo->setPixmap(  (outPixmap.size().width() > 90) ? outPixmap.scaledToWidth(90) : outPixmap  );
    }
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

    ui->tableViewTerminals->setModel(modelTerminals);
    ui->tableViewTerminals->verticalHeader()->hide();
    ui->tableViewTerminals->hideColumn(0);
    ui->tableViewTerminals->hideColumn(1);
    ui->tableViewTerminals->hideColumn(3);
    ui->tableViewTerminals->resizeColumnsToContents();
    ui->tableViewTerminals->horizontalHeader()->stretchLastSection();
    ui->tableViewTerminals->verticalHeader()->setDefaultSectionSize(ui->tableViewTerminals->verticalHeader()->minimumSectionSize());

//    qInfo(logInfo()) << "Selection Model" << ui ->tableViewTerminals->selectionModel()->setModel(modelTerminals);
//    ui ->tableViewTerminals->selectionModel()->setModel(modelTerminals);
    ui->tabWidgetComp->addTab(new KassaForm(), "Касса 1");


}

void ClientsWindow::createConnections()
{
    connect(this,&ClientsWindow::signalSendClientID,ui->widgetFBServer,&FBServerForm::slotGetClientID,Qt::DirectConnection);
    connect(this,&ClientsWindow::signalSendClientID,ui->widgetAdmins,&AdminsListForm::slotGetClientID);
    connect(this,&ClientsWindow::signalSendClientID,ui->widgetPaytypes,&PaytypeForm::slotGetClientID);



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
    //Model Terminals
    modelTerminals = new ModelTerminals(this);
    modelTerminals->setTable("objects");
    modelTerminals->setHeaderData(2, Qt::Horizontal, "АЗС");
    modelTerminals->setHeaderData(4, Qt::Horizontal, "Наименование");
    modelTerminals->setHeaderData(6, Qt::Horizontal, "Примечание");
    modelTerminals->setHeaderData(5, Qt::Horizontal, "В работе");
    QString strFilter = QString("client_id = %1 order by terminal_id").arg(clientID);
    modelTerminals->setFilter(strFilter);
    modelTerminals->select();

   //Model Contacts

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
      ui->tableWidgetServers->verticalHeader()->setDefaultSectionSize(ui->tableWidgetServers->verticalHeader()->minimumSectionSize());
      ui->tableWidgetServers->selectRow(0);
      ui->tableWidgetServers->setFocus();
      // Имитируем нажатие кнопки Tab, чтобы выделить строку
      QKeyEvent* pe = new QKeyEvent(QEvent::KeyPress,
              Qt::Key_Tab,Qt::NoModifier, "Tab");
      QApplication::sendEvent(ui->tableWidgetServers, pe) ;
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

void ClientsWindow::on_toolButtonPing_clicked()
{
    QString connectServer;
    QList<QTableWidgetItem*>itemList = ui->tableWidgetServers->selectedItems();
    if(itemList.isEmpty()) return;
    connectServer = itemList.at(2)->text();
    PingOutDialog *pingDlg = new PingOutDialog(&connectServer,this);
    pingDlg->exec();
}

void ClientsWindow::slotSelectionTerminals(const QItemSelection &, const QItemSelection &)
{
    QModelIndexList selection = ui->tableViewTerminals->selectionModel()->selectedIndexes();
    objectID = modelTerminals->data(modelTerminals->index(selection.at(0).row(),0),Qt::DisplayRole).toInt();
    QString filterStr = QString("object_id=%1").arg(objectID);

    QString infoText = " "+modelTerminals->data(modelTerminals->index(selection.at(0).row(),2),Qt::DisplayRole).toString()+"\n"
            + modelTerminals->data(modelTerminals->index(selection.at(0).row(),4),Qt::DisplayRole).toString();
    ui->toolBoxInfo->setItemText(0, "Контакты"+infoText);
    ui->toolBoxInfo->setItemText(1, "Рабочие места"+infoText);
    ui->toolBoxInfo->setItemText(2, "База данных"+infoText);

    modelObjContacts = new QSqlTableModel(this);
    modelObjContacts->setTable("objectcontacts");
    modelObjContacts->setFilter(filterStr);
    modelObjContacts->select();

    ui->tableViewObjectCont->setModel(modelObjContacts);
    ui->tableViewObjectCont->hideColumn(0);
    ui->tableViewObjectCont->hideColumn(1);
    ui->tableViewObjectCont->resizeColumnsToContents();
}

void ClientsWindow::on_toolButtonAddObjectContact_clicked()
{
    ObjectContactDialog *objConn = new ObjectContactDialog(objectID, new QSqlRecord(), this);
    objConn->exec();
    modelObjContacts->select();
}

void ClientsWindow::on_tableViewObjectCont_doubleClicked(const QModelIndex &idx)
{
    QSqlRecord r = modelObjContacts->record(idx.row());
    ObjectContactDialog *objConn = new ObjectContactDialog(objectID, &r, this);
    objConn->exec();
    modelObjContacts->select();
}
