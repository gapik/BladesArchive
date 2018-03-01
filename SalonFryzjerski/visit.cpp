#include "visit.h"

#include "service.h"

Visit::Visit()
{

}

double Visit::getPrice() const
{
    return visitPrice;
}

void Visit::setPrice(double price)
{
    visitPrice = price;
}

QList<Service *> Visit::getServiceList() const
{
    return ServiceList;
}


void Visit::addService(Service *service)
{
    ServiceList.append(service);
}

QDate Visit::getVisitDate() const
{
    return visitDate;
}

void Visit::setVisitDate(const QDate &date)
{
    visitDate = date;
}

QString Visit::getVisitDateString() const
{
    return visitDateString;
}

void Visit::setVisitDateString(const QString &date)
{
    visitDateString = date;
}
