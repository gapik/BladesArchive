#include "productlistreader.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "product.h"

ProductListReader::ProductListReader(QString path)
{
    workDir=path;
    XMLpath=workDir + "/Produkty.xml";
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
//    qDebug() << "ProductsList does not contain" << name;
}

void ProductListReader::updateXML()
{
    QDomDocument updatedXMLDatabase;
    QDomElement root = updatedXMLDatabase.createElement("productsList");
    updatedXMLDatabase.appendChild(root);
    for (int i=0;i<productsList.size();i++){
        QDomElement product = updatedXMLDatabase.createElement("product");
        root.appendChild(product);

        QDomText tagproduct = updatedXMLDatabase.createTextNode(productsList.at(i)->getName());
        product.appendChild(tagproduct);
    }
//    QDomElement product = updatedXMLDatabase.createElement("product");
//    root.appendChild(product);

//    QDomText tagproduct = updatedXMLDatabase.createTextNode("developer:tomasz.gapski@gmail.com");
//    product.appendChild(tagproduct);

    QFile bckfile(XMLpath);
    QDir bckdir(workDir + "/Backup");
    QStringList filters;
    filters << "Produkty*";
    int lastInt=0;
    for (int i=0;i<bckdir.entryInfoList(filters).size();i++){
        QString lastFile = bckdir.entryInfoList(filters).at(i).fileName();
        if (QString(lastFile).remove(".xml").remove("Produkty").toInt() > lastInt){
            lastInt=QString(lastFile).remove(".xml").remove("Produkty").toInt();
        }
    }
    if (lastInt > 100){
        for (int i=0;i<lastInt-98;i++){
//            qDebug() << "removing: "<< workDir + "/Backup/Produkty"+QString::number(i)+".xml";
            QFile fileToRemove (workDir + "/Backup/Produkty"+QString::number(i)+".xml");
            if (fileToRemove.exists()){
                fileToRemove.remove();
            }
            fileToRemove.close();
        }
    }
    bckfile.rename(XMLpath,workDir + "/Backup/Produkty" + QString::number(lastInt+1) + ".xml");

    QFile outfile(XMLpath);
    if( !outfile.open( QIODevice::WriteOnly | QIODevice::Text ) )
    {
        qDebug( "Failed to open file for writing." );
    }
    QTextStream stream( &outfile );
    stream.setCodec("UTF-8");
    stream << updatedXMLDatabase.toString();
    outfile.close();
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
