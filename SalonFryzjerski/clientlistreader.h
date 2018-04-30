#ifndef CLIENTLISTREADER_H
#define CLIENTLISTREADER_H

#include <QString>
#include "client.h"
#include <QtXml/QDomDocument>

class ClientListReader
{
public:
    ClientListReader(QString path);
    QDomDocument getXMLDatabase() const;
    QList<Client*> getClientsList() const;
    void addNewClientToList(Client *newClient);
    void removeClientFromList(Client *newClient);
//    void updateClient(Client *newClient,int index);

    void updateXML();

private:
    QString workDir;
    QString XMLpath;
    QString outXMLpath = "D:/code/Qt/SalonBlades/SalonFryzjerski/Klienci2.xml";

    void readXML();
    void generateClientList();

    QDomDocument XMLDatabase;
    QList<Client*> clientsList;
};

#endif // CLIENTLISTREADER_H
