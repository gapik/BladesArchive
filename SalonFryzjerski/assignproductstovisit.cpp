#include "assignproductstovisit.h"
#include "ui_assignproductstovisit.h"

#include <QDebug>
#include <QMessageBox>

assignProductsToVisit::assignProductsToVisit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::assignProductsToVisit)
{
    ui->setupUi(this);
}

assignProductsToVisit::~assignProductsToVisit()
{
    delete ui;
}

void assignProductsToVisit::setLabels(QString clientName, QString date, QString ServiceName)
{
    ui->ClientData->setText(clientName);
    ui->VisitDate->setText(date);
    ui->ServiceName->setText("Usługa/Pakiet Usług: " + ServiceName);
}

void assignProductsToVisit::setProductListToComboBoxes()
{
    QList<Product *> productlist= productReader->getProductsList();
    for (int i=0;i<productlist.size();i++){
        if (i==0){
            ui->productSelect_1->addItem("Wybierz produkt...");
            ui->productSelect_2->addItem("Wybierz produkt...");
            ui->productSelect_3->addItem("Wybierz produkt...");
            ui->productSelect_4->addItem("Wybierz produkt...");
            ui->productSelect_5->addItem("Wybierz produkt...");
            ui->productSelect_6->addItem("Wybierz produkt...");
            ui->productSelect_7->addItem("Wybierz produkt...");
            ui->productSelect_8->addItem("Wybierz produkt...");
        }
        ui->productSelect_1->addItem(productlist.at(i)->getName());
        ui->productSelect_2->addItem(productlist.at(i)->getName());
        ui->productSelect_3->addItem(productlist.at(i)->getName());
        ui->productSelect_4->addItem(productlist.at(i)->getName());
        ui->productSelect_5->addItem(productlist.at(i)->getName());
        ui->productSelect_6->addItem(productlist.at(i)->getName());
        ui->productSelect_7->addItem(productlist.at(i)->getName());
        ui->productSelect_8->addItem(productlist.at(i)->getName());
    }
}

void assignProductsToVisit::setService(Service *value)
{
    service = value;
}

ProductListReader *assignProductsToVisit::getProductReader() const
{
    return productReader;
}

void assignProductsToVisit::setProductReader(ProductListReader *value)
{
    productReader = value;
}

void assignProductsToVisit::on_cancelButton_clicked()
{
    close();
}

void assignProductsToVisit::on_addProductButton_clicked()
{
    //Save XML file with services
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdzenie zmian.", "Czy na pewno chcesz dodać produkty do usługi?",
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qDebug() << "dodaj produkty" << service->getProductList().size();
        emit productsUpdated();
        this->close();
    }
}

