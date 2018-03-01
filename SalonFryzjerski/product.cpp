#include "product.h"

Product::Product()
{

}

QString Product::getName() const
{
    return productName;
}

void Product::setName(const QString &name)
{
    productName = name;
}

QString Product::getSignature() const
{
    return productSignature;
}

void Product::setSignature(const QString &signature)
{
    productSignature = signature;
}

double Product::getAmount() const
{
    return productAmount;
}

void Product::setAmount(double amount)
{
    productAmount = amount;
}
