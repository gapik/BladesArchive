#include "service.h"

#include "product.h"

Service::Service()
{

}

QString Service::getName() const
{
    return serviceName;
}

void Service::setName(const QString &name)
{
    serviceName = name;
}

QList<Product *> Service::getProductList() const
{
    return productList;
}

void Service::addProduct(Product *product)
{
    productList.append(product);
}

void Service::removeProductAtIndex(int index)
{
    productList.removeAt(index);
}

void Service::removeProductByName(QString name)
{
    for (int i=0;i<productList.size();i++){
        if (productList.at(i)->getName() == name){
            productList.removeAt(i);
            return;
        }
    }
}


