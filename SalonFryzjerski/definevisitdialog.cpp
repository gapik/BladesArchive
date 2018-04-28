#include "definevisitdialog.h"
#include "ui_definevisitdialog.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QTreeView>
#include <QModelIndex>
#include <QMessageBox>
#include "product.h"

DefineVisitDialog::DefineVisitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefineVisitDialog)
{
    ui->setupUi(this);
    QStandardItemModel *def_model = new QStandardItemModel(this);
    def_model->setColumnCount(4);
    def_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Usługa")));
    def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Produkty")));
    def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Sygnatura")));
    def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Ilość")));
    ui->servicesList->setModel(def_model);
    ui->servicesList->setColumnWidth(0,450);
    ui->servicesList->setColumnWidth(1,100);
    ui->servicesList->setColumnWidth(2,75);
    ui->servicesList->setColumnWidth(3,75);

    connect(&assignProduct,&assignProductsToVisit::productsUpdated,this,&DefineVisitDialog::on_productsUpdated);
}

DefineVisitDialog::~DefineVisitDialog()
{
    delete ui;
}

ServiceListReader *DefineVisitDialog::getServicesReader() const
{
    return servicesReader;
}

void DefineVisitDialog::setServicesReader(ServiceListReader *value)
{
    servicesReader = value;
}

ProductListReader *DefineVisitDialog::getProductsReader() const
{
    return productsReader;
}

void DefineVisitDialog::setProductsReader(ProductListReader *value)
{
    productsReader = value;
}

void DefineVisitDialog::loadServiceList()
{
    ui->AvailableServices->clear();
    for (int i=0;i<servicesReader->getServicesList().size();i++){
        ui->AvailableServices->addItem(servicesReader->getServicesList().at(i)->getName());
    }
    ui->AvailableServices->sortItems();
    ui->AvailableServices->setSelectionMode(QAbstractItemView::ExtendedSelection);
}

void DefineVisitDialog::setDateLabel(QString dateString)
{
    ui->dateLabel->clear();
    ui->dateLabel->setAlignment(Qt::AlignCenter);
    ui->dateLabel->setText("Data Wizyty: " + dateString);
}

void DefineVisitDialog::setClientLabel(QString clientName)
{
    ui->clientLabel->clear();
    ui->clientLabel->setAlignment(Qt::AlignCenter);
    ui->clientLabel->setText("Klient: " + clientName);
}

void DefineVisitDialog::updateTreeView()
{
    QStandardItemModel *def_model = new QStandardItemModel(this);
    def_model->setColumnCount(4);
    def_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Usługa")));
    def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Produkty")));
    def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Sygnatura")));
    def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Ilość")));

    for(int j=0;j<ServiceList.size();j++){
        QStandardItem *serviceNameItem = new QStandardItem( ServiceList.at(j)->getName() );
        serviceNameItem->setEditable(false);

        QList<Product*> products = ServiceList.at(j)->getProductList();
        for(int k=0;k<products.size();k++){
            QStandardItem *productNameItem = new QStandardItem( products.at(k)->getName() );
            QStandardItem *productSignatureItem = new QStandardItem( products.at(k)->getSignature() );
            QStandardItem *productAmountItem = new QStandardItem( QString::number(products.at(k)->getAmount()) );
            QStandardItem *empty = new QStandardItem("");
            productNameItem->setEditable(false);
            productSignatureItem->setEditable(false);
            productAmountItem->setEditable(false);
            serviceNameItem->appendRow(QList<QStandardItem *>() << empty << productNameItem << productSignatureItem << productAmountItem );
        }
        def_model->setItem(j, 0, serviceNameItem);
    }

    ui->servicesList->setModel(def_model);
    ui->servicesList->expandAll();
}

void DefineVisitDialog::on_AddService_clicked()
{
    QStringList servicePackage;
    for (int i=0;i<ui->AvailableServices->selectedItems().size();i++){
        servicePackage.append(ui->AvailableServices->selectedItems().at(i)->text());
    }

    Service *newService=new Service;
    newService->setName(servicePackage.join(" + "));
    ServiceList.append(newService);

    updateTreeView();
    ui->AvailableServices->clearSelection();
}

void DefineVisitDialog::on_CancelButton_clicked()
{
    close();
}

void DefineVisitDialog::on_AddProducts_clicked()
{
    if (ui->servicesList->selectionModel()->hasSelection()){
        assignProduct.setWindowFlags(Qt::WindowCloseButtonHint);
        assignProduct.setWindowIcon(QIcon(iconPath));
        assignProduct.setWindowTitle("Salon Fryzjerski BLADES - produkty do usługi");
        assignProduct.setWindowFlags(Qt::WindowStaysOnTopHint);
        assignProduct.setModal(true);
        assignProduct.setLabels(ui->clientLabel->text(),ui->dateLabel->text(),ui->servicesList->selectionModel()->selectedIndexes().at(0).data().toString());
        assignProduct.setService(ServiceList.at(ui->servicesList->selectionModel()->selectedIndexes().at(0).row()));
        assignProduct.setProductReader(getProductsReader());
        assignProduct.setProductListToComboBoxes();
        assignProduct.show();
        updateTreeView();
    }else{
        QMessageBox::warning(this,"Nie wybrałeś usługi/pakietu usług!","Nie wybrałeś usługi/pakietu usług.");
    }
}

void DefineVisitDialog::on_DeleteService_clicked()
{
    if (ui->servicesList->selectionModel()->hasSelection() && ui->servicesList->selectionModel()->selectedIndexes().at(0).data().toStringList().at(0) != QString("")){
        ServiceList.removeAt(ui->servicesList->selectionModel()->selectedIndexes().at(0).row());
        updateTreeView();
    }else{
        QMessageBox::warning(this,"Nie wybrałeś usługi/pakietu usług!","Nie wybrałeś usługi/pakietu usług.");
    }
}

void DefineVisitDialog::on_productsUpdated()
{
    updateTreeView();
}

void DefineVisitDialog::setIconPath(const QString &value)
{
    iconPath = value;
}

void DefineVisitDialog::on_servicesList_clicked(const QModelIndex &index)
{
    ui->AddProducts->setDefault(true);
}

void DefineVisitDialog::on_AvailableServices_clicked(const QModelIndex &index)
{
    ui->AddService->setDefault(true);
}

void DefineVisitDialog::on_deleteProduct_clicked()
{
    if (ui->servicesList->selectionModel()->hasSelection() && ui->servicesList->selectionModel()->selectedIndexes().at(0).data().toStringList().at(0) == QString("")){
        qDebug()<<"service: " << ui->servicesList->selectionModel()->selectedIndexes().at(0).parent().row() << "product:" << ui->servicesList->selectionModel()->selectedIndexes().at(0).row();
        ServiceList.at(ui->servicesList->selectionModel()->selectedIndexes().at(0).parent().row())->getProductList().removeAt(ui->servicesList->selectionModel()->selectedIndexes().at(0).row());
        updateTreeView();
    }else{
        QMessageBox::warning(this,"Nie wybrałeś produktu!","Nie wybrałeś produktu.");
    }
}
