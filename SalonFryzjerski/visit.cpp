#include "visit.h"

Visit::Visit()
{

}

double Visit::getPrice() const
{
    return price;
}

void Visit::setPrice(double value)
{
    price = value;
}

QList<Service> Visit::getServiceList() const
{
    return ServiceList;
}

void Visit::addService(Service *service)
{
    ServiceList->append(service);
}
