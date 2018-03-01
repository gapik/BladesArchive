#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QString>

#include "clientlistreader.h"
#include "clientfilter.h"
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
    def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Numer Produktu")));
    def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Ilość")));
    def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Cena")));
    ui->treeView->setModel(def_model);
    ui->treeView->setColumnWidth(0,250);
    ui->treeView->setColumnWidth(1,100);
    ui->treeView->setColumnWidth(2,75);
    ui->treeView->setColumnWidth(3,75);

    ClientListReader *reader = new ClientListReader;
    setClientsReader(reader);

    clientFilter filter;
    filter.loadClientsToFilter(reader->getClientsList(),ui);
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

void MainWindow::on_ClientList_itemSelectionChanged()
{
    QString choosenClient = ui->ClientList->currentItem()->text();
    QStringList ClientID = choosenClient.split(' ');

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setColumnCount(4);
    model->setHorizontalHeaderItem(1, new QStandardItem(tr("Numer Produktu")));
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

                QStandardItem *visitsItem = new QStandardItem( visits.at(j)->getVisitDateString() );
                QStandardItem *priceItem = new QStandardItem( QString::number(visits.at(j)->getPrice()) );
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
    ui->treeView->expandAll();
}
