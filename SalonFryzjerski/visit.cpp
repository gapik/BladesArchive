#include "visit.h"

#include "service.h"

#include <QDebug>
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

void Visit::removeAllServices()
{
    while(ServiceList.size() != 0){
        ServiceList.removeAt(0);
    }
}

QDate Visit::getVisitDate() const
{
    return visitDate;
}

void Visit::setVisitDate(const QDate &date)
{
    visitDate = date;
//    qDebug() <<  visitDate.toString("d MMMM yyyy");
}

QString Visit::getVisitDateString() const
{
    return visitDateString;
}

void Visit::setVisitDateString(const QString &date)
{
    visitDateString = date;
    setVisitDate(QDate::fromString(visitDateString,"d MMMM yyyy"));
}
