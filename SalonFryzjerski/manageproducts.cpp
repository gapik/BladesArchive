#include "manageproducts.h"
#include "ui_manageproducts.h"

#include "productlistreader.h"

#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>

manageProducts::manageProducts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manageProducts)
{
    ui->setupUi(this);
}

manageProducts::~manageProducts()
{
    delete ui;
}


void manageProducts::setProductReader(ProductListReader *reader)
{
    productsReader = reader;
}

void manageProducts::loadProductList()
{
    ui->productListWidget->clear();
    for (int i=0;i<productsReader->getProductsList().size();i++){
        ui->productListWidget->addItem(productsReader->getProductsList().at(i)->getName());
    }
    ui->productListWidget->sortItems();
}

void manageProducts::on_addProduct_clicked()
{
    QString productToBeAdd;
    productToBeAdd=ui->newProductName->text().simplified();
    if (productToBeAdd == ""){
        QMessageBox::information(this,"Podaj nazwę produktu!","Podaj nazwę produktu.");
        return;
    }

    if (productToBeAdd.contains(" ")){
        QStringList tmp = productToBeAdd.split(" ");
        for (int i=0; i<tmp.size(); i++){
            tmp[i]=tmp[i].toLower();
            tmp[i]=tmp[i].replace(0, 1, tmp[i][0].toUpper());
        }
        productToBeAdd=tmp.join(" ");
    }else if(productToBeAdd.contains("-")){
        QStringList tmp = productToBeAdd.split("-");
        for (int i=0; i<tmp.size(); i++){
            tmp[i]=tmp[i].toLower();
            tmp[i]=tmp[i].replace(0, 1, tmp[i][0].toUpper());
        }
        productToBeAdd=tmp.join("-");
    }else {
        productToBeAdd=productToBeAdd.toLower();
        productToBeAdd.replace(0, 1, productToBeAdd[0].toUpper());
    }

    for (int i=0;i<productsReader->getProductsList().size();i++){
        if (productsReader->getProductsList().at(i)->getName() == productToBeAdd){
            QMessageBox::information(this,"Produkt \"" + productToBeAdd + "\" już istnieje!","Produkt \"" + productToBeAdd + "\" już istnieje.");
            return;
        }
    }

    Product *newProduct = new Product;
    newProduct->setName(productToBeAdd);
    productsReader->addNewProductToList(newProduct);
    ui->productListWidget->clear();
    for (int i=0;i<productsReader->getProductsList().size();i++){
        ui->productListWidget->addItem(productsReader->getProductsList().at(i)->getName());
    }
    ui->productListWidget->sortItems();
    ui->newProductName->clear();
    firstSelection=false;
}

void manageProducts::on_removeProduct_clicked()
{
    if (!firstSelection){
        QMessageBox::information(this,"Wskaż produkt, który ma zostać skasowany!","Wskaż produkt, który ma zostać skasowany.");
        return;
    }else{
        productsReader->removeProductFromList(ui->productListWidget->currentItem()->text());
        ui->productListWidget->clear();
        for (int i=0;i<productsReader->getProductsList().size();i++){
            ui->productListWidget->addItem(productsReader->getProductsList().at(i)->getName());
        }
        ui->productListWidget->sortItems();
        firstSelection=false;
    }
}

void manageProducts::on_acceptChanges_clicked()
{
    //Save XML file with services
    qDebug() << "Need to add capability to save XML with services.";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdzenie zmian.", "Czy na pewno chcesz wprowadzić zmiany w liście produktów?",
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        productsReader->updateXML();
        this->close();
    }
}

void manageProducts::on_cancelButton_clicked()
{
    close();
}

void manageProducts::on_productListWidget_itemSelectionChanged()
{
    firstSelection=true;
}
