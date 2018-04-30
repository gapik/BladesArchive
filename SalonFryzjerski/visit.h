#ifndef VISIT_H
#define VISIT_H

#include <QList>
#include <QDate>

class Service;

class Visit
{
public:
    Visit();

    double getPrice() const;
    void setPrice(double price);

    QList<Service*> getServiceList() const;
    void addService(Service *service);
    void removeAllServices();

    QDate getVisitDate() const;
    void setVisitDate(const QDate &date);

    QString getVisitDateString() const;
    void setVisitDateString(const QString &date);

private:
    double visitPrice=0;
    QDate visitDate;
    QString visitDateString = "";
    QList<Service*> ServiceList;
};

#endif // VISIT_H
