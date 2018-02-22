#include "client.h"

Client::Client()
{

}

QString Client::getFirstName() const
{
    return FirstName;
}

void Client::setFirstName(const QString &value)
{
    FirstName = value;
}

QString Client::getLastName() const
{
    return LastName;
}

void Client::setLastName(const QString &value)
{
    LastName = value;
}

QString Client::getPhoneNumber() const
{
    return PhoneNumber;
}

void Client::setPhoneNumber(const QString &value)
{
    PhoneNumber = value;
}

QString Client::getComment() const
{
    return Comment;
}

void Client::setComment(const QString &value)
{
    Comment = value;
}

QList<Visit> Client::getVisitList() const
{
    return VisitList;
}

void Client::addVisit(Visit *value)
{
    VisitList.append(value);
}
