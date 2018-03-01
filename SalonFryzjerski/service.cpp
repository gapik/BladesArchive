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


