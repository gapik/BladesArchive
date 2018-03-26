#ifndef SERVICELISTREADER_H
#define SERVICELISTREADER_H

#include <QString>
#include "service.h"
#include <QtXml/QDomDocument>

class ServiceListReader
{
public:
    ServiceListReader(QString path);
    QDomDocument getXMLDatabase() const;
    QList<Service*> getServicesList() const;
    void addNewServiceToList(Service *newService);
    void removeServiceFromList(QString name);

    void updateXML();

private:
    QString workDir;
    QString XMLpath;

    void readXML();
    void generateServiceList();

    QDomDocument XMLDatabase;
    QList<Service*> servicesList;
};

#endif // SERVICELISTREADER_H
