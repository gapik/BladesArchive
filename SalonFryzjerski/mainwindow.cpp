#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_editclient.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QString>
#include <QMessageBox>

#include "clientlistreader.h"
#include "servicelistreader.h"
#include "productlistreader.h"
#include "clientfilter.h"
#include "client.h"
#include "visit.h"
#include "service.h"
#include "product.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->logoBlades->setPixmap(QPixmap(logoPath));
    setWindowIcon(QIcon(icoPath));
    setWindowTitle("Salon Fryzjerski BLADES - baza klientów");

    QStandardItemModel *def_model = new QStandardItemModel(this);
    def_model->setColumnCount(4);
    def_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Imię i Nazwisko (numer telefonu) [UWAGI]")));
    def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Sygnatura")));
    def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Ilość")));
    def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Cena")));
    ui->treeView->setModel(def_model);
    ui->treeView->setColumnWidth(0,300);
    ui->treeView->setColumnWidth(1,100);
    ui->treeView->setColumnWidth(2,75);
    ui->treeView->setColumnWidth(3,75);

    ui->ClientList->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(&defineVisitDialogObj,&DefineVisitDialog::newVisitDefined,this,&MainWindow::on_newVisitDefined);
    connect(&defineVisitDialogObj,&DefineVisitDialog::editModeIsDone,this,&MainWindow::updateTreeView);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::on_Search_textChanged(const QString &arg1)
{
    QRegExp regExp(arg1,Qt::CaseInsensitive, QRegExp::Wildcard);
    ui->ClientList->clear();
    for(int i=0;i<clientsReader->getClientsList().count();i++)
        {
             if(QString(clientsReader->getClientsList().at(i)->getFirstName() + " " + clientsReader->getClientsList().at(i)->getLastName()).contains(regExp))
             {
                 ui->ClientList->addItem(clientsReader->getClientsList().at(i)->getFirstName() + ' ' + clientsReader->getClientsList().at(i)->getLastName());
             }
        }
    ui->ClientList->sortItems();
    ui->Filter->setText(QString("Filtruj Klientów (%1)").arg(ui->ClientList->count()));
}

ClientListReader *MainWindow::getClientsReader() const
{
    return clientsReader;
}

void MainWindow::setClientsReader(ClientListReader *reader)
{
    clientsReader = reader;
}

ServiceListReader *MainWindow::getServiceReader() const
{
    return servicesReader;
}

void MainWindow::setServiceReader(ServiceListReader *reader)
{
    servicesReader = reader;
}

ProductListReader *MainWindow::getProductReader() const
{
    return productsReader;
}

void MainWindow::setProductReader(ProductListReader *reader)
{
    productsReader = reader;
}

void MainWindow::on_ClientList_itemSelectionChanged()
{
    updateTreeView();
}
void MainWindow::on_addClient_clicked()
{
    addNewClientDialog.setWindowFlags(Qt::WindowCloseButtonHint);
    addNewClientDialog.setWindowIcon(QIcon(icoPath));
    addNewClientDialog.setWindowTitle("Salon Fryzjerski BLADES - nowy Klient");
    addNewClientDialog.setWindowFlags(Qt::WindowStaysOnTopHint);
    addNewClientDialog.setModal(true);
    addNewClientDialog.show();
}

void MainWindow::on_ClientEdit_clicked()
{
    if(ui->ClientList->selectedItems().size()==0){
        QMessageBox::information(this,"Wskaż Klienta","Żaden Klient nie został wybrany");
    }else{
        QStringList clientToEditName= ui->ClientList->selectedItems().at(0)->text().split(' ');
        QList<Client*> clients=getClientsReader()->getClientsList();

        for (int i=0;i<clients.count();i++){
            if (clients.at(i)->getFirstName() == clientToEditName.at(0)
                    && clients.at(i)->getLastName() == clientToEditName.at(1)){
                editClientDialog.setClientToEdit(clients.at(i));
                editClientDialog.setWindowFlags(Qt::WindowCloseButtonHint);
                editClientDialog.setWindowIcon(QIcon(icoPath));
                editClientDialog.setWindowTitle("Salon Fryzjerski BLADES - edycja danych Klienta");
                editClientDialog.setWindowFlags(Qt::WindowStaysOnTopHint);
                editClientDialog.setModal(true);
                editClientDialog.show();
                editClientDialog.getUi()->NameField->setText(editClientDialog.getClientToEdit()->getFirstName());
                editClientDialog.getUi()->LastnameField->setText(editClientDialog.getClientToEdit()->getLastName());
                editClientDialog.getUi()->PhoneField->setText(editClientDialog.getClientToEdit()->getPhoneNumber());
                editClientDialog.getUi()->CommentField->setText(editClientDialog.getClientToEdit()->getComment());
                editClientDialog.setClientToEditIndex(clients.at(i)->getClientID());
                break;
            }
        }
    }
}

void MainWindow::on_deleteClient_clicked()
{
    if(ui->ClientList->selectedItems().size()==0){
        QMessageBox::information(this,"Wskaż Klienta","Żaden Klient nie został wybrany");
    }else{
        //Save XML file with services
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Potwierdzenie zmian.", "Czy na pewno chcesz usunąć Klienta?",
                                        QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QStringList clientToEditName= ui->ClientList->selectedItems().at(0)->text().split(' ');
            QList<Client*> clients=getClientsReader()->getClientsList();

            for (int i=0;i<clients.count();i++){
                if (clients.at(i)->getFirstName() == clientToEditName.at(0)
                        && clients.at(i)->getLastName() == clientToEditName.at(1)){

                    clientsReader->removeClientFromList(clients.at(i));

                    ui->ClientList->clear();
                    for(int j=0;j<clientsReader->getClientsList().size();j++){
                        ui->ClientList->addItem(clientsReader->getClientsList().at(j)->getFirstName() + ' ' + clientsReader->getClientsList().at(j)->getLastName());
                    }
                    ui->ClientList->sortItems();
                    ui->Filter->setText(QString("Filtruj Klientów (%1)").arg(ui->ClientList->count()));

                    ui->Search->clear();

                    QStandardItemModel *def_model = new QStandardItemModel(this);
                    def_model->setColumnCount(4);
                    def_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Imię i Nazwisko (numer telefonu) [UWAGI]")));
                    def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Sygnatura")));
                    def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Ilość")));
                    def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Cena")));
                    ui->treeView->setModel(def_model);
                    ui->treeView->setColumnWidth(0,300);
                    ui->treeView->setColumnWidth(1,100);
                    ui->treeView->setColumnWidth(2,75);
                    ui->treeView->setColumnWidth(3,75);

                    //save xml
                    clientsReader->updateXML();
                    break;
                }
            }
        }
    }
}

void MainWindow::on_manageServices_clicked()
{
    manageServicesDialogObj.setServicesReader(getServiceReader());
    manageServicesDialogObj.loadServiceList();
    manageServicesDialogObj.setWindowFlags(Qt::WindowCloseButtonHint);
    manageServicesDialogObj.setWindowIcon(QIcon(icoPath));
    manageServicesDialogObj.setWindowTitle("Salon Fryzjerski BLADES - zarządzaj usługami");
    manageServicesDialogObj.setWindowFlags(Qt::WindowStaysOnTopHint);
    manageServicesDialogObj.setModal(true);
    manageServicesDialogObj.show();
    //add new service with QMessageBox confirmation + save xml
    //remove service with QMessageBox confirmation + save xml
}

void MainWindow::on_manageProducts_clicked()
{
    manageProductsDialog.setProductReader(getProductReader());
    manageProductsDialog.loadProductList();
    manageProductsDialog.setWindowFlags(Qt::WindowCloseButtonHint);
    manageProductsDialog.setWindowIcon(QIcon(icoPath));
    manageProductsDialog.setWindowTitle("Salon Fryzjerski BLADES - zarządzaj produktami");
    manageProductsDialog.setWindowFlags(Qt::WindowStaysOnTopHint);
    manageProductsDialog.setModal(true);
    manageProductsDialog.show();
    //add new service with QMessageBox confirmation + save xml
    //remove service with QMessageBox confirmation + save xml
}

void MainWindow::on_addVisit_clicked()
{
    if (ui->ClientList->selectedItems().size() == 0){
        QMessageBox::information(this,"Wskaż Klienta","Żaden Klient nie został wybrany");
    }else{
        QStringList clientToEditName= ui->ClientList->selectedItems().at(0)->text().split(' ');
        QList<Client*> clients=getClientsReader()->getClientsList();

        bool ifDateExists = false;
        for (int i=0;i<clients.count();i++){
            if (clients.at(i)->getFirstName() == clientToEditName.at(0)
                    && clients.at(i)->getLastName() == clientToEditName.at(1)){
                for (int j=0;j<clients.at(i)->getVisitList().size();j++){
                    if (clients.at(i)->getVisitList().at(j)->getVisitDateString() == ui->calendarWidget->selectedDate().toString("d MMMM yyyy")){
                        ifDateExists=true;
                    }
                }
                break;
            }
        }

        if(ifDateExists){
            QMessageBox::warning(this,"Istnieje już wizyta z tego dnia!","Istnieje już wizyta z tego dnia.");
            return;
        }

        defineVisitDialogObj.setServicesReader(getServiceReader());
        defineVisitDialogObj.setProductsReader(getProductReader());
        defineVisitDialogObj.loadServiceList();
        defineVisitDialogObj.setDateLabel(ui->calendarWidget->selectedDate().toString("d MMMM yyyy"));
        defineVisitDialogObj.setClientLabel(ui->ClientList->currentItem()->text());
        defineVisitDialogObj.setWindowFlags(Qt::WindowCloseButtonHint);
        defineVisitDialogObj.setWindowIcon(QIcon(icoPath));
        defineVisitDialogObj.setWindowTitle("Salon Fryzjerski BLADES - dodaj wizytę");
        defineVisitDialogObj.setWindowFlags(Qt::WindowStaysOnTopHint);
        defineVisitDialogObj.setModal(true);
        defineVisitDialogObj.setIconPath(getIcoPath());
        defineVisitDialogObj.show();
    }
}

void MainWindow::on_editVisit_clicked()
{
    if (ui->ClientList->selectedItems().size() == 0){
        QMessageBox::information(this,"Wskaż Klienta","Żaden Klient nie został wybrany");
    }else{
        if (ui->treeView->selectionModel()->hasSelection() && ui->treeView->selectionModel()->selectedIndexes().at(0).parent().data().toString() == QString("")){
            defineVisitDialogObj.setServicesReader(getServiceReader());
            defineVisitDialogObj.setProductsReader(getProductReader());
            defineVisitDialogObj.loadServiceList();
            defineVisitDialogObj.setDateLabel(ui->calendarWidget->selectedDate().toString("d MMMM yyyy"));
            defineVisitDialogObj.setClientLabel(ui->ClientList->currentItem()->text());
            defineVisitDialogObj.setWindowFlags(Qt::WindowCloseButtonHint);
            defineVisitDialogObj.setWindowIcon(QIcon(icoPath));
            defineVisitDialogObj.setWindowTitle("Salon Fryzjerski BLADES - edytuj wizytę");
            defineVisitDialogObj.setWindowFlags(Qt::WindowStaysOnTopHint);
            defineVisitDialogObj.setModal(true);
            defineVisitDialogObj.setIconPath(getIcoPath());

            QStringList clientToEditName= ui->ClientList->selectedItems().at(0)->text().split(' ');
            QList<Client*> clients=getClientsReader()->getClientsList();

            for (int i=0;i<clients.count();i++){
                if (clients.at(i)->getFirstName() == clientToEditName.at(0)
                        && clients.at(i)->getLastName() == clientToEditName.at(1)){
                    for (int j=0;j<clients.at(i)->getVisitList().size();j++){
                        if (clients.at(i)->getVisitList().at(j)->getVisitDateString() == ui->treeView->selectionModel()->selectedIndexes().at(0).data().toString()){
                            defineVisitDialogObj.loadVisitToEdit(clients.at(i)->getVisitList().at(j));
                        }
                    }
                    break;
                }
            }

            defineVisitDialogObj.show();
        }else{
            QMessageBox::information(this,"Wskaż Wizytę!","Żadna Wizyta nie została wybrana");
        }
    }
}

void MainWindow::on_expandCollapse_clicked()
{
    if (treeExpanded){
        ui->treeView->collapseAll();
        treeExpanded=false;
        ui->expandCollapse->setText("Rozwiń Wizyty");
    }else{
        ui->treeView->expandAll();
        treeExpanded=true;
        ui->expandCollapse->setText("Zwiń Wizyty");
    }
}

void MainWindow::on_deleteVisit_clicked()
{
    if (ui->treeView->selectionModel()->hasSelection() && ui->treeView->selectionModel()->selectedIndexes().at(0).parent().data().toString() == QString("")){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Potwierdzenie zmian.", "Czy na pewno chcesz usunąć Wizytę?",
                                        QMessageBox::Yes|QMessageBox::No);

        if (reply == QMessageBox::Yes) {
            QStringList clientToEditName= ui->ClientList->selectedItems().at(0)->text().split(' ');
            QList<Client*> clients=getClientsReader()->getClientsList();

            for (int i=0;i<clients.count();i++){
                if (clients.at(i)->getFirstName() == clientToEditName.at(0)
                        && clients.at(i)->getLastName() == clientToEditName.at(1)){
                    for (int j=0;j<clients.at(i)->getVisitList().size();j++){
                        if (clients.at(i)->getVisitList().at(j)->getVisitDateString() == ui->treeView->selectionModel()->selectedIndexes().at(0).data().toString()){
                            clients.at(i)->removeVisit(clients.at(i)->getVisitList().at(j));
                        }
                    }
                    //save xml
                    clientsReader->updateXML();
                    break;
                }
            }
            updateTreeView();
        }
    }else{
        QMessageBox::warning(this,"Nie wybrałeś wizyty!","Nie wybrałeś wizyty.");
    }
}

void MainWindow::on_newVisitDefined()
{
    QStringList clientToEditName= ui->ClientList->selectedItems().at(0)->text().split(' ');
    QList<Client*> clients=getClientsReader()->getClientsList();

    for (int i=0;i<clients.count();i++){
        if (clients.at(i)->getFirstName() == clientToEditName.at(0)
                && clients.at(i)->getLastName() == clientToEditName.at(1)){
            clients.at(i)->addVisit(defineVisitDialogObj.getNewVisit());
            clients.at(i)->sortVisitsByDate();
        }
    }

    updateTreeView();
}

QString MainWindow::getIcoPath() const
{
    return icoPath;
}

void MainWindow::updateTreeView()
{
    QString choosenClient = ui->ClientList->currentItem()->text();
    QStringList ClientID = choosenClient.split(' ');

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Sygnatura")));
    model->setHorizontalHeaderItem(2, new QStandardItem(tr("Ilość")));
    model->setHorizontalHeaderItem(3, new QStandardItem(tr("Cena")));

    QList<Client*> clients=getClientsReader()->getClientsList();
    for (int i=0;i<clients.count();i++){
        if (clients.at(i)->getFirstName() == ClientID.at(0) && clients.at(i)->getLastName() == ClientID.at(1)){
            QString label = clients.at(i)->getFirstName().append(" " + clients.at(i)->getLastName());
            if (!clients.at(i)->getPhoneNumber().isEmpty()){
                label = label.append(" (" + clients.at(i)->getPhoneNumber() + ")");
            }
            if (!clients.at(i)->getComment().isEmpty()){
                label = label.append(" [" + clients.at(i)->getComment() + "]");
            }
            model->setHorizontalHeaderItem(0, new QStandardItem(label));

            QList<Visit*> visits = clients.at(i)->getVisitList();
            model->setRowCount(visits.count());
            for(int j=0;j<visits.count();j++){

                QString priceException;
                QStandardItem *visitsItem = new QStandardItem( visits.at(j)->getVisitDateString() );
                if (visits.at(j)->getPrice() != 0){
                    priceException=QString::number(visits.at(j)->getPrice());
                }else{
                    priceException="brak danych";
                }
                QStandardItem *priceItem = new QStandardItem( priceException );
                visitsItem->setEditable(false);
                priceItem->setEditable(false);

                QList<Service*> services = visits.at(j)->getServiceList();
                for(int p=0;p<services.count();p++){
                    QStandardItem *serviceNameItem = new QStandardItem( services.at(p)->getName() );
                    serviceNameItem->setEditable(false);

                    visitsItem->appendRow( serviceNameItem );
                    QList<Product*> products = services.at(p)->getProductList();
                    for(int k=0;k<products.count();k++){
                        QStandardItem *productNameItem = new QStandardItem( products.at(k)->getName() );
                        QStandardItem *productSignatureItem = new QStandardItem( products.at(k)->getSignature() );
                        QStandardItem *productAmountItem = new QStandardItem( QString::number(products.at(k)->getAmount()) );
                        productNameItem->setEditable(false);
                        productSignatureItem->setEditable(false);
                        productAmountItem->setEditable(false);
                        serviceNameItem->appendRow(QList<QStandardItem *>() << productNameItem << productSignatureItem << productAmountItem );
                    }
                }
                model->setItem(j, 0, visitsItem);
                model->setItem(j, 3, priceItem);
            }
            i=clients.count();
        }
    }
    ui->treeView->setModel(model);
    if (treeExpanded){
        ui->treeView->expandAll();
    }else{
        ui->treeView->collapseAll();
    }
    clientsReader->updateXML();
}

QString MainWindow::getWorkDirectory() const
{
    return workDirectory;
}

void MainWindow::setWorkDirectory(const QString &value)
{
    workDirectory = value;

    ClientListReader *reader = new ClientListReader(workDirectory);
    setClientsReader(reader);
    clientFilter *filter = new clientFilter;
    filter->loadClientsToFilter(reader->getClientsList(),ui);

    ServiceListReader *serviceReader = new ServiceListReader(workDirectory);
    setServiceReader(serviceReader);

    ProductListReader *productReader = new ProductListReader(workDirectory);
    setProductReader(productReader);

    addNewClientDialog.setMainUi(ui);
    addNewClientDialog.setReader(getClientsReader());
    addNewClientDialog.setFilter(filter);

    editClientDialog.setMainUi(ui);
    editClientDialog.setReader(getClientsReader());
    editClientDialog.setFilter(filter);

}
