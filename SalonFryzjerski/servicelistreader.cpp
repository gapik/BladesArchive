#include "servicelistreader.h"

#include <QFile>
#include <QDir>
#include <QDebug>
#include <QtXml/QDomDocument>
#include <QMessageBox>

#include "service.h"

ServiceListReader::ServiceListReader(QString path)
{
    workDir=path;
    XMLpath=workDir + "/Uslugi.xml";
    readXML();
    generateServiceList();
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

void ServiceListReader::updateXML()
{
    QDomDocument updatedXMLDatabase;
    QDomElement root = updatedXMLDatabase.createElement("servicesList");
    updatedXMLDatabase.appendChild(root);
    for (int i=0;i<servicesList.size();i++){
        QDomElement service = updatedXMLDatabase.createElement("service");
        root.appendChild(service);

        QDomText tagservice = updatedXMLDatabase.createTextNode(servicesList.at(i)->getName());
        service.appendChild(tagservice);
    }
//    QDomElement service = updatedXMLDatabase.createElement("service");
//    root.appendChild(service);

//    QDomText tagservice = updatedXMLDatabase.createTextNode("developer:tomasz.gapski@gmail.com");
//    service.appendChild(tagservice);

    QFile bckfile(XMLpath);
    QDir bckdir(workDir + "/Backup");
    QStringList filters;
    filters << "Uslugi*";
    int lastInt=0;
    for (int i=0;i<bckdir.entryInfoList(filters).size();i++){
        QString lastFile = bckdir.entryInfoList(filters).at(i).fileName();
        if (QString(lastFile).remove(".xml").remove("Uslugi").toInt() > lastInt){
            lastInt=QString(lastFile).remove(".xml").remove("Uslugi").toInt();
        }
    }
    if (lastInt > 100){
        for (int i=0;i<lastInt-98;i++){
            qDebug() << "removing: "<< workDir + "/Backup/Uslugi"+QString::number(i)+".xml";
            QFile fileToRemove (workDir + "/Backup/Uslugi"+QString::number(i)+".xml");
            if (fileToRemove.exists()){
                fileToRemove.remove();
            }
        }
    }
    bckfile.rename(XMLpath,workDir + "/Backup/Uslugi" + QString::number(lastInt+1) + ".xml");

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
