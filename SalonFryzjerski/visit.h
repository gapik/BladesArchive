#ifndef VISIT_H
#define VISIT_H

#include <QList>

class Service;

class Visit
{
public:
    Visit();

    double getPrice() const;
    void setPrice(double value);

    QList<Service> getServiceList() const;
    void addService(Service *service);

private:
    double price;
    QList<Service> *ServiceList;
};

#endif // VISIT_H
