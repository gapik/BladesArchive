#ifndef SERVICELISTREADER_H
#define SERVICELISTREADER_H

#include <QString>
#include "service.h"
#include <QtXml/QDomDocument>

class ServiceListReader
{
public:
    ServiceListReader();
    QDomDocument getXMLDatabase() const;
    QList<Service*> getServicesList() const;
    void addNewServiceToList(Service *newService);
    void removeServiceFromList(QString name);

private:
    QString XMLpath = "D:/code/Qt/SalonBlades/SalonFryzjerski/Uslugi.xml";

    void readXML();
    void generateServiceList();

    QDomDocument XMLDatabase;
    QList<Service*> servicesList;
};

#endif // SERVICELISTREADER_H
