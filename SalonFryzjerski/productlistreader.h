#ifndef PRODUCTLISTREADER_H
#define PRODUCTLISTREADER_H

#include <QString>
#include <QList>
#include "product.h"
#include <QtXml/QDomDocument>

class ProductListReader
{
public:
    ProductListReader();

    QDomDocument getXMLDatabase() const;
    QList<Product*> getProductsList() const;
    void addNewProductToList(Product *newProduct);
    void removeProductFromList(QString name);

    void updateXML();

private:
    QString XMLpath = "D:/code/Qt/SalonBlades/SalonFryzjerski/Produkty.xml";

    void readXML();
    void generateProductList();

    QDomDocument XMLDatabase;
    QList<Product*> productsList;
};

#endif // PRODUCTLISTREADER_H




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

    void updateXML();

private:
    QString XMLpath = "D:/code/Qt/SalonBlades/SalonFryzjerski/Uslugi.xml";

    void readXML();
    void generateServiceList();

    QDomDocument XMLDatabase;
    QList<Service*> servicesList;
};

#endif // SERVICELISTREADER_H
