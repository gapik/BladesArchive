#include "definevisitdialog.h"
#include "ui_definevisitdialog.h"

#include <QStandardItemModel>
#include <QDebug>

DefineVisitDialog::DefineVisitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DefineVisitDialog)
{
    ui->setupUi(this);
    QStandardItemModel *def_model = new QStandardItemModel(this);
    def_model->setColumnCount(4);
    def_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Usługa")));
    def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Produkty")));
    def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Ilość")));
    def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Sygnatura")));
    ui->servicesList->setModel(def_model);
    ui->servicesList->setColumnWidth(0,200);
    ui->servicesList->setColumnWidth(1,100);
    ui->servicesList->setColumnWidth(2,75);
    ui->servicesList->setColumnWidth(3,75);
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

void DefineVisitDialog::on_AddService_clicked()
{
    QStringList servicePackage;
    for (int i=0;i<ui->AvailableServices->selectedItems().size();i++){
        servicePackage.append(ui->AvailableServices->selectedItems().at(i)->text());
    }
    qDebug() << servicePackage.join(" + ");

//    QStandardItemModel *def_model = new QStandardItemModel(this);
//    def_model->setColumnCount(4);
//    def_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Usługa")));
//    def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Produkty")));
//    def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Ilość")));
//    def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Sygnatura")));

}

void DefineVisitDialog::on_CancelButton_clicked()
{
    close();
}
