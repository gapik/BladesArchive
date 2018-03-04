#include "client.h"

#include "visit.h"
#include <QDebug>

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

bool Client::operator==(const Client &Client)
{
    if (this->getFirstName() == Client.getFirstName() && this->getLastName() == Client.getLastName()){
        qDebug() << "tak";
        return true;
    }else{
        qDebug() << "nie";
        return false;
    }
}

//bool Client::operator==(const Client &c){
//    if (this->getFirstName() == c.getFirstName() && this->getLastName() == c.getLastName()){
//        qDebug() << "tak";
//        return true;
//    } else {
//        qDebug() << "nie";
//        return false;
//    }
//}

//bool Symbol::operator==(Symbol& rhs)const{
//cout << "operator overloaded == " << rhs.name;
//if (this->name==rhs.name)
//return true;
//return false;
//}

