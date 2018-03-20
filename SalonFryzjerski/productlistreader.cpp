#include "productlistreader.h"

#include <QFile>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "product.h"

ProductListReader::ProductListReader()
{
    readXML();
    generateProductList();
}


QDomDocument ProductListReader::getXMLDatabase() const
{
    return XMLDatabase;
}

QList<Product *> ProductListReader::getProductsList() const
{
    return productsList;
}

void ProductListReader::addNewProductToList(Product *newProduct)
{
    productsList.append(newProduct);
}

void ProductListReader::removeProductFromList(QString name)
{
    for (int i=0;i<productsList.size();i++){
        if(productsList.at(i)->getName() == name){
            productsList.removeAt(i);
            return;
        }
    }
    qDebug() << "ProductsList does not contain" << name;
}

void ProductListReader::updateXML()
{
    //Save XML with current servicesList
}

void ProductListReader::readXML()
{
    QFile file(XMLpath);
    if (!file.exists() || !file.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Check your Product.xml file";
        }
    XMLDatabase.setContent(&file);
    file.close();
}

void ProductListReader::generateProductList()
{
    QDomNode root = XMLDatabase.namedItem("productsList");
    QDomNodeList XMLNodes = root.childNodes();
    for(int i=0;i<XMLNodes.count();i++)
    {
        QDomElement ProductList = XMLNodes.at(i).toElement();

        Product *newProduct = new Product;
        newProduct->setName(ProductList.toElement().text());
        productsList.append(newProduct);
    }
}
