#ifndef SERVICE_H
#define SERVICE_H

#include <QString>
#include <QList>

class Product;

class Service
{
public:
    Service();

    QString getName() const;
    void setName(const QString &name);

    QList<Product*> getProductList() const;
    void addProduct(Product *product);

private:
    QString serviceName = "";
    QList<Product*> productList;
};

#endif // SERVICE_H
