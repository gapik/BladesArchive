#include "client.h"

#include "visit.h"

Client::Client()
{

}

QString Client::getFirstName() const
{
    return clientFirstName;
}

void Client::setFirstName(const QString &firstname)
{
    clientFirstName = firstname;
}

QString Client::getLastName() const
{
    return clientLastName;
}

void Client::setLastName(const QString &lastname)
{
    clientLastName = lastname;
}

QString Client::getPhoneNumber() const
{
    return clientPhoneNumber;
}

void Client::setPhoneNumber(const QString &phonenumber)
{
    clientPhoneNumber = phonenumber;
}

QString Client::getComment() const
{
    return clientComment;
}

void Client::setComment(const QString &comment)
{
    clientComment = comment;
}

QList<Visit *> Client::getVisitList()
{
    return VisitList;
}

void Client::addVisit(Visit *visit)
{
    VisitList.append(visit);
}

int Client::getClientID() const
{
    return clientID;
}

void Client::setClientID(int id)
{
    clientID = id;
}