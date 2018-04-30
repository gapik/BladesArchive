#include "clientlistreader.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QtXml/QDomDocument>

#include "client.h"
#include "visit.h"
#include "service.h"
#include "product.h"

ClientListReader::ClientListReader(QString path)
{
    workDir = path;
    XMLpath = workDir + "/Klienci.xml";
    qDebug() << workDir << XMLpath;
    outXMLpath=path;
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

        if (ClientNodes.at(3).toElement().text() != QString("")){
            QStringList formatting = ClientNodes.at(3).toElement().text().simplified().replace(" ","").split("");
            QString phoneNumber=QString(formatting.at(1) + formatting.at(2) + formatting.at(3) + " " + formatting.at(4) + formatting.at(5) + formatting.at(6) + " " + formatting.at(7) + formatting.at(8) + formatting.at(9));
            newClient->setPhoneNumber(phoneNumber);
        }else{
            newClient->setPhoneNumber(ClientNodes.at(3).toElement().text());
        }


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
        newClient->sortVisitsByDate();
        clientsList.append(newClient);
    }
}

QList<Client *> ClientListReader::getClientsList() const
{
    return clientsList;
}

void ClientListReader::addNewClientToList(Client *newClient)
{
    clientsList.append(newClient);
}

void ClientListReader::removeClientFromList(Client *newClient)
{
    clientsList.removeOne(newClient);
}

void ClientListReader::updateXML()
{
    QDomDocument updatedXMLDatabase;
    QDomElement root = updatedXMLDatabase.createElement("ClientsList");
    updatedXMLDatabase.appendChild(root);
    for (int i=0;i<clientsList.size();i++){
        QDomElement client = updatedXMLDatabase.createElement("client");
        root.appendChild(client);

        QDomElement id = updatedXMLDatabase.createElement("id");
        client.appendChild(id);
        QDomText tagId = updatedXMLDatabase.createTextNode(QString::number(clientsList.at(i)->getClientID()+1));
        id.appendChild(tagId);

        QDomElement surname = updatedXMLDatabase.createElement("surname");
        client.appendChild(surname);
        QDomText tagSurname = updatedXMLDatabase.createTextNode(clientsList.at(i)->getLastName());
        surname.appendChild(tagSurname);

        QDomElement firstname = updatedXMLDatabase.createElement("firstname");
        client.appendChild(firstname);
        QDomText tagFirstname = updatedXMLDatabase.createTextNode(clientsList.at(i)->getFirstName());
        firstname.appendChild(tagFirstname);

        QDomElement phone = updatedXMLDatabase.createElement("phone");
        client.appendChild(phone);
        QDomText tagPhone = updatedXMLDatabase.createTextNode(clientsList.at(i)->getPhoneNumber());
        phone.appendChild(tagPhone);

        QDomElement comments = updatedXMLDatabase.createElement("comments");
        client.appendChild(comments);
        QDomText tagComments = updatedXMLDatabase.createTextNode(clientsList.at(i)->getComment());
        comments.appendChild(tagComments);

        QDomElement visits = updatedXMLDatabase.createElement("visits");
        client.appendChild(visits);
        for (int j=0;j<clientsList.at(i)->getVisitList().size();j++){
            QDomElement visit = updatedXMLDatabase.createElement("visit");
            visits.appendChild(visit);

            QDomElement visitId = updatedXMLDatabase.createElement("id");
            visit.appendChild(visitId);
            QDomText tagVisitId = updatedXMLDatabase.createTextNode(QString::number(clientsList.at(i)->getClientID()+1));
            visitId.appendChild(tagVisitId);

            QDomElement price = updatedXMLDatabase.createElement("price");
            visit.appendChild(price);
            QDomText tagPrice = updatedXMLDatabase.createTextNode(QString::number(clientsList.at(i)->getVisitList().at(j)->getPrice()));
            price.appendChild(tagPrice);

            QDomElement date = updatedXMLDatabase.createElement("date");
            visit.appendChild(date);
            QDomText tagDate = updatedXMLDatabase.createTextNode(clientsList.at(i)->getVisitList().at(j)->getVisitDateString());
            date.appendChild(tagDate);

            for (int k=0;k<clientsList.at(i)->getVisitList().at(j)->getServiceList().size();k++){
                QDomElement service = updatedXMLDatabase.createElement("service");
                visit.appendChild(service);

                QDomElement service_name = updatedXMLDatabase.createElement("service_name");
                service.appendChild(service_name);
                QDomText tagServiceName = updatedXMLDatabase.createTextNode(clientsList.at(i)->getVisitList().at(j)->getServiceList().at(k)->getName());
                service_name.appendChild(tagServiceName);

                for (int l=0;l<clientsList.at(i)->getVisitList().at(j)->getServiceList().at(k)->getProductList().size();l++){
                    QDomElement product = updatedXMLDatabase.createElement("product");
                    service.appendChild(product);

                    QDomElement productName = updatedXMLDatabase.createElement("name");
                    product.appendChild(productName);
                    QDomText tagProductName = updatedXMLDatabase.createTextNode(clientsList.at(i)->getVisitList().at(j)->getServiceList().at(k)->getProductList().at(l)->getName());
                    productName.appendChild(tagProductName);

                    QDomElement signature = updatedXMLDatabase.createElement("signature");
                    product.appendChild(signature);
                    QDomText tagSignature = updatedXMLDatabase.createTextNode(clientsList.at(i)->getVisitList().at(j)->getServiceList().at(k)->getProductList().at(l)->getSignature());
                    signature.appendChild(tagSignature);

                    QDomElement amount = updatedXMLDatabase.createElement("amount");
                    product.appendChild(amount);
                    QDomText tagAmount = updatedXMLDatabase.createTextNode(QString::number(clientsList.at(i)->getVisitList().at(j)->getServiceList().at(k)->getProductList().at(l)->getAmount()));
                    amount.appendChild(tagAmount);
                }
            }
        }
    }
    QDomElement client = updatedXMLDatabase.createElement("client");
    root.appendChild(client);

    QDomElement id = updatedXMLDatabase.createElement("id");
    client.appendChild(id);
    QDomText tagId = updatedXMLDatabase.createTextNode("0");
    id.appendChild(tagId);

    QDomElement surname = updatedXMLDatabase.createElement("surname");
    client.appendChild(surname);
    QDomText tagSurname = updatedXMLDatabase.createTextNode("Gapski");
    surname.appendChild(tagSurname);

    QDomElement firstname = updatedXMLDatabase.createElement("firstname");
    client.appendChild(firstname);
    QDomText tagFirstname = updatedXMLDatabase.createTextNode("Developer:Tomasz");
    firstname.appendChild(tagFirstname);

    QDomElement phone = updatedXMLDatabase.createElement("phone");
    client.appendChild(phone);
    QDomText tagPhone = updatedXMLDatabase.createTextNode("669788878");
    phone.appendChild(tagPhone);

    QDomElement comments = updatedXMLDatabase.createElement("comments");
    client.appendChild(comments);
    QDomText tagComments = updatedXMLDatabase.createTextNode("tomasz.gapski@gmail.com");
    comments.appendChild(tagComments);

    QFile bckfile(XMLpath);
    QDir bckdir(workDir + "/Backup");
    QStringList filters;
    filters << "Klienci*";
    int lastInt=0;
    for (int i=0;i<bckdir.entryInfoList(filters).size();i++){
        QString lastFile = bckdir.entryInfoList(filters).at(i).fileName();
        if (QString(lastFile).remove(".xml").remove("Klienci").toInt() > lastInt){
            lastInt=QString(lastFile).remove(".xml").remove("Klienci").toInt();
        }
    }
    if (lastInt > 1000){
        for (int i=0;i<lastInt-998;i++){
            qDebug() << "removing: "<< workDir + "/Backup/Klienci"+QString::number(i)+".xml";
            QFile fileToRemove (workDir + "/Backup/Klienci"+QString::number(i)+".xml");
            if (fileToRemove.exists()){
                fileToRemove.remove();
            }
        }
    }
    bckfile.rename(XMLpath,workDir + "/Backup/Klienci" + QString::number(lastInt+1) + ".xml");

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

QDomDocument ClientListReader::getXMLDatabase() const
{
    return XMLDatabase;
}
