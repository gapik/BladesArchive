#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{
public:
    Product();

    QString getName() const;
    void setName(const QString &name);

    QString getSignature() const;
    void setSignature(const QString &signature);

    double getAmount() const;
    void setAmount(double amount);

private:
    QString productName = "";
    QString productSignature = "";
    double productAmount = 0;
};

#endif // PRODUCT_H
