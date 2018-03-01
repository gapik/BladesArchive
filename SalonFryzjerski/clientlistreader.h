#ifndef CLIENTLISTREADER_H
#define CLIENTLISTREADER_H

#include <QString>
#include "client.h"
#include <QtXml/QDomDocument>

class ClientListReader
{
public:
    ClientListReader();
    QDomDocument getXMLDatabase() const;
    QList<Client*> getClientsList() const;

private:
    QString XMLpath = "D:/code/Qt/SalonBlades/SalonFryzjerski/Klienci.xml";

    void readXML();
    void generateClientList();

    QDomDocument XMLDatabase;
    QList<Client*> clientsList;
};

#endif // CLIENTLISTREADER_H
