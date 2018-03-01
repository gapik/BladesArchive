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

        QDomElement Visits = ClientNodes.at(5).toElement();
        VisitListNodes = Visits.childNodes();

        for(int j=0;j<VisitListNodes.count();j++){
            QDomElement singleVisit = VisitListNodes.at(j).toElement();
            VisitNodes = singleVisit.childNodes();

            Visit *newVisit = new Visit;
            newVisit->setPrice(VisitNodes.at(1).toElement().text().toDouble());
            newVisit->setVisitDateString(VisitNodes.at(2).toElement().text());

            for(int p=3;p<VisitNodes.count();p++){
                QDomElement Services = VisitNodes.at(p).toElement();
                ProductListNodes = Services.childNodes();

                Service *newService = new Service;
                newService->setName(ProductListNodes.at(0).toElement().text());

                for(int k=1;k<ProductListNodes.count();k++){
                    QDomElement singleService = ProductListNodes.at(k).toElement();
                    ProductNodes = singleService.childNodes();

                    Product *newProduct = new Product;
                    newProduct->setName(ProductNodes.at(0).toElement().text());
                    newProduct->setSignature(ProductNodes.at(1).toElement().text());
                    newProduct->setAmount(ProductNodes.at(2).toElement().text().toDouble());

                    newService->addProduct(newProduct);
                }
                newVisit->addService(newService);
            }
            newClient->addVisit(newVisit);
        }
        clientsList.append(newClient);
    }
}

QList<Client *> ClientListReader::getClientsList() const
{
    return clientsList;
}

QDomDocument ClientListReader::getXMLDatabase() const
{
    return XMLDatabase;
}
