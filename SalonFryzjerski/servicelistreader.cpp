#include "servicelistreader.h"

#include <QFile>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "service.h"

ServiceListReader::ServiceListReader()
{
    readXML();
    generateServiceList();
    qDebug() <<"done";
}

QDomDocument ServiceListReader::getXMLDatabase() const
{
    return XMLDatabase;
}

QList<Service *> ServiceListReader::getServicesList() const
{
    return servicesList;
}

void ServiceListReader::addNewServiceToList(Service *newService)
{
    servicesList.append(newService);
}

void ServiceListReader::removeServiceFromList(QString name)
{
    for (int i=0;i<servicesList.size();i++){
        if(servicesList.at(i)->getName() == name){
            servicesList.removeAt(i);
            return;
        }
    }
    qDebug() << "ServiceList does not contain" << name;
}


void ServiceListReader::readXML()
{
    QFile file(XMLpath);
    if (!file.exists() || !file.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "Check your file";
        }
    XMLDatabase.setContent(&file);
    file.close();
}

void ServiceListReader::generateServiceList()
{
    QDomNode root = XMLDatabase.namedItem("servicesList");
    QDomNodeList XMLNodes = root.childNodes();
    for(int i=0;i<XMLNodes.count();i++)
    {
        QDomElement ServiceList = XMLNodes.at(i).toElement();

        Service *newService = new Service;
        newService->setName(ServiceList.toElement().text());
        servicesList.append(newService);
    }
//    qDebug() << "size of serviceList" << servicesList.size();
//    for (int i=0;i<servicesList.size();i++) qDebug() << servicesList.at(i)->getName();
}
