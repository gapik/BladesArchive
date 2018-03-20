#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QList>

class Visit;

class Client
{
public:
    Client();

    QString getFirstName() const;
    void setFirstName(const QString &firstname);

    QString getLastName() const;
    void setLastName(const QString &lastname);

    QString getPhoneNumber() const;
    void setPhoneNumber(const QString &phonenumber);

    QString getComment() const;
    void setComment(const QString &comment);

    QList<Visit*> getVisitList();
    void addVisit(Visit *visit);

    int getClientID() const;
    void setClientID(int id);

private:
    QString clientFirstName;
    QString clientLastName;
    QString clientPhoneNumber;
    QString clientComment;
    QList<Visit*> VisitList;
    int clientID;
};

#endif // CLIENT_H
