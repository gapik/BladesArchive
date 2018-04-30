#include "assignproductstovisit.h"
#include "ui_assignproductstovisit.h"

#include <QDebug>
#include <QMessageBox>

assignProductsToVisit::assignProductsToVisit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::assignProductsToVisit)
{
    ui->setupUi(this);
    ui->Amount_1->setValidator(new QDoubleValidator(0, 1000, 1, this));
    ui->Amount_2->setValidator(new QDoubleValidator(0, 1000, 1, this));
    ui->Amount_3->setValidator(new QDoubleValidator(0, 1000, 1, this));
    ui->Amount_4->setValidator(new QDoubleValidator(0, 1000, 1, this));
    ui->Amount_5->setValidator(new QDoubleValidator(0, 1000, 1, this));
    ui->Amount_6->setValidator(new QDoubleValidator(0, 1000, 1, this));
    ui->Amount_7->setValidator(new QDoubleValidator(0, 1000, 1, this));
    ui->Amount_8->setValidator(new QDoubleValidator(0, 1000, 1, this));
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
            ui->productSelect_1->addItem("To samo");
            ui->productSelect_2->addItem("To samo");
            ui->productSelect_3->addItem("To samo");
            ui->productSelect_4->addItem("To samo");
            ui->productSelect_5->addItem("To samo");
            ui->productSelect_6->addItem("To samo");
            ui->productSelect_7->addItem("To samo");
            ui->productSelect_8->addItem("To samo");
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
    if (ui->productSelect_1->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_1 = new Product;
        newProduct_1->setName(ui->productSelect_1->currentText());
        newProduct_1->setSignature(ui->Signature_1->text());
        newProduct_1->setAmount(ui->Amount_1->text().toDouble());
        service->addProduct(newProduct_1);
        ui->productSelect_1->setCurrentIndex(0);
        ui->Signature_1->clear();
        ui->Amount_1->clear();
    }
    if (ui->productSelect_2->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_2 = new Product;
        newProduct_2->setName(ui->productSelect_2->currentText());
        newProduct_2->setSignature(ui->Signature_2->text());
        newProduct_2->setAmount(ui->Amount_2->text().toDouble());
        service->addProduct(newProduct_2);
        ui->productSelect_2->setCurrentIndex(0);
        ui->Signature_2->clear();
        ui->Amount_2->clear();
    }
    if (ui->productSelect_3->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_3 = new Product;
        newProduct_3->setName(ui->productSelect_3->currentText());
        newProduct_3->setSignature(ui->Signature_3->text());
        newProduct_3->setAmount(ui->Amount_3->text().toDouble());
        service->addProduct(newProduct_3);
        ui->productSelect_3->setCurrentIndex(0);
        ui->Signature_3->clear();
        ui->Amount_3->clear();
    }
    if (ui->productSelect_4->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_4 = new Product;
        newProduct_4->setName(ui->productSelect_4->currentText());
        newProduct_4->setSignature(ui->Signature_4->text());
        newProduct_4->setAmount(ui->Amount_4->text().toDouble());
        service->addProduct(newProduct_4);
        ui->productSelect_4->setCurrentIndex(0);
        ui->Signature_4->clear();
        ui->Amount_4->clear();
    }
    if (ui->productSelect_5->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_5 = new Product;
        newProduct_5->setName(ui->productSelect_5->currentText());
        newProduct_5->setSignature(ui->Signature_5->text());
        newProduct_5->setAmount(ui->Amount_5->text().toDouble());
        service->addProduct(newProduct_5);
        ui->productSelect_5->setCurrentIndex(0);
        ui->Signature_5->clear();
        ui->Amount_5->clear();
    }
    if (ui->productSelect_6->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_6 = new Product;
        newProduct_6->setName(ui->productSelect_6->currentText());
        newProduct_6->setSignature(ui->Signature_6->text());
        newProduct_6->setAmount(ui->Amount_6->text().toDouble());
        service->addProduct(newProduct_6);
        ui->productSelect_6->setCurrentIndex(0);
        ui->Signature_6->clear();
        ui->Amount_6->clear();
    }
    if (ui->productSelect_7->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_7 = new Product;
        newProduct_7->setName(ui->productSelect_7->currentText());
        newProduct_7->setSignature(ui->Signature_7->text());
        newProduct_7->setAmount(ui->Amount_7->text().toDouble());
        service->addProduct(newProduct_7);
        ui->productSelect_7->setCurrentIndex(0);
        ui->Signature_7->clear();
        ui->Amount_7->clear();
    }
    if (ui->productSelect_8->currentText() != QString("Wybierz produkt...")){
        Product *newProduct_8 = new Product;
        newProduct_8->setName(ui->productSelect_8->currentText());
        newProduct_8->setSignature(ui->Signature_8->text());
        newProduct_8->setAmount(ui->Amount_8->text().toDouble());
        service->addProduct(newProduct_8);
        ui->productSelect_8->setCurrentIndex(0);
        ui->Signature_8->clear();
        ui->Amount_8->clear();
    }

    if (reply == QMessageBox::Yes) {
        emit productsUpdated();
        this->close();
    }
}

