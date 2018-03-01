#include "clientlistreader.h"

#include <QFile>
#include <QDebug>
#include <QtXml/QDomDocument>
//#include <QXmlStreamReader>
//#include <QtCore>

#include "client.h"
#include "visit.h"
#include "service.h"
#include "product.h"

ClientListReader::ClientListReader()
{
    readXML();
    generateClientList();
}

void ClientListReader::readXML()
{
    QFile file(XMLpath);
    if (!file.exists() || !file.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Check your file";
        }
    XMLDatabase.setContent(&file);
    file.close();
}

void ClientListReader::generateClientList()
{
    QDomNode root = XMLDatabase.namedItem("ClientsList");
    QDomNodeList XMLNodes = root.childNodes();
    QDomNodeList ClientNodes,VisitListNodes,VisitNodes,ProductListNodes,ProductNodes;
    for(int i=0;i<XMLNodes.count()-1;i++)
    {
        QDomElement ClientList = XMLNodes.at(i).toElement();
        ClientNodes = ClientList.childNodes();

        Client *newClient = new Client;
        newClient->setLastName(ClientNodes.at(1).toElement().text());
        newClient->setFirstName(ClientNodes.at(2).toElement().text());
        newClient->setPhoneNumber(ClientNodes.at(3).toElement().text());
        newClient->setComment(ClientNodes.at(4).toElement().text());
        newClient->setClientID(ClientNodes.at(0).toElement().text().toInt());

//        firstNameE->setText(Firstname);
//        surNameE->setText(Surname);
//        phoneE->setText(PhoneNumber);
//        commentE->setText(Comment);

//        QString label = Firstname.append(" " + Surname);
//        if (!PhoneNumber.isEmpty()){
//            label = label.append(" (" + PhoneNumber + ")");
//        }
//        if (!Comment.isEmpty()){
//            label = label.append(" [" + Comment + "]");
//        }
//        //qDebug() << label;
//        model->setHorizontalHeaderItem(0, new QStandardItem(label));

        QDomElement Visits = ClientNodes.at(5).toElement();
        VisitListNodes = Visits.childNodes();

//        model->setRowCount(VisitListNodes.count());

        for(int j=0;j<VisitListNodes.count();j++){
            QDomElement singleVisit = VisitListNodes.at(j).toElement();
            VisitNodes = singleVisit.childNodes();

            Visit *newVisit = new Visit;
            newVisit->setPrice(VisitNodes.at(1).toElement().text().toDouble());
            newVisit->setVisitDateString(VisitNodes.at(2).toElement().text());

//            QStandardItem *visitsItem = new QStandardItem( visitDate );
//            QStandardItem *priceItem = new QStandardItem( Price );
//            QStandardItem *emptyItem = new QStandardItem( empty );
//            QStandardItem *emptyItem2 = new QStandardItem( empty2 );
//            visitsItem->setEditable(false);
//            priceItem->setEditable(false);
//            emptyItem->setEditable(false);
//            emptyItem2->setEditable(false);

            for(int p=3;p<VisitNodes.count();p++){
                QDomElement Services = VisitNodes.at(p).toElement();
                ProductListNodes = Services.childNodes();

                Service *newService = new Service;
                newService->setName(ProductListNodes.at(0).toElement().text());

//                QStandardItem *serviceNameItem = new QStandardItem( serviceName );
//                serviceNameItem->setEditable(false);
//                visitsItem->appendRow( serviceNameItem );

                for(int k=1;k<ProductListNodes.count();k++){
                    QDomElement singleService = ProductListNodes.at(k).toElement();
                    ProductNodes = singleService.childNodes();

                    Product *newProduct = new Product;
                    newProduct->setName(ProductNodes.at(0).toElement().text());
                    newProduct->setSignature(ProductNodes.at(1).toElement().text());
                    newProduct->setAmount(ProductNodes.at(2).toElement().text().toDouble());

                    newService->addProduct(newProduct);
//                    QStandardItem *productNameItem = new QStandardItem( productName );
//                    QStandardItem *productSignatureItem = new QStandardItem( productSignature );
//                    QStandardItem *productAmountItem = new QStandardItem( productAmount );
//                    productNameItem->setEditable(false);
//                    productSignatureItem->setEditable(false);
//                    productAmountItem->setEditable(false);

//                    serviceNameItem->appendRow(QList<QStandardItem *>() << productNameItem << productSignatureItem << productAmountItem );
//                    model->setItem(j, 0, visitsItem);
//                    model->setItem(j, 1, emptyItem);
//                    model->setItem(j, 2, emptyItem2);
//                    model->setItem(j, 3, priceItem);
                }
                newVisit->addService(newService);
            }
            newClient->addVisit(newVisit);
        }
        clientsList.append(newClient);
    }
//    ui->treeView->setModel(model);
}

QList<Client *> ClientListReader::getClientsList() const
{
    return clientsList;
}

QDomDocument ClientListReader::getXMLDatabase() const
{
    return XMLDatabase;
}
