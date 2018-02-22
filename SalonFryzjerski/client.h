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
    void setFirstName(const QString &value);

    QString getLastName() const;
    void setLastName(const QString &value);

    QString getPhoneNumber() const;
    void setPhoneNumber(const QString &value);

    QString getComment() const;
    void setComment(const QString &value);

    QList<Visit> getVisitList() const;
    void addVisit(Visit *value);

private:
    QString FirstName;
    QString LastName;
    QString PhoneNumber;
    QString Comment;
    QList<Visit> *VisitList;
};

#endif // CLIENT_H
