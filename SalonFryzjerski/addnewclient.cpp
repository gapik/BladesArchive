#include "addnewclient.h"
#include "ui_addnewclient.h"
#include "ui_mainwindow.h"

#include "client.h"

#include <QDebug>
#include <QMessageBox>
#include <QMainWindow>

addNewClient::addNewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewClient)
{
    ui->setupUi(this);
    ui->PhoneField->setValidator(new QIntValidator(0, 999999999, this));
}

addNewClient::~addNewClient()
{
    delete ui;
}

void addNewClient::on_CancelButton_clicked()
{
    close();
}

void addNewClient::on_AddClientButton_clicked()
{
    if (!ui->PhoneField->text().isEmpty()){
            if(ui->PhoneField->text().simplified().replace(" ","").split("").size()!= 11){
            QMessageBox::warning(this,"Błędny numer telefonu!","Błędny numer telefonu");
            return;
        }
    }
    //new to check if firstname and lastname is provided - else print messagebox
    QString fName;
    fName=ui->NameField->text().simplified();

    QString lName;
    lName=ui->LastnameField->text().simplified();

    if(fName == "" || lName == ""){
        QMessageBox::information(this,"Brak wymaganych danych!","Uzupełnij wymagane pola.");
    }else{
        if (fName.contains(" ")){
            QStringList tmp = fName.split(" ");
            for (int i=0; i<tmp.size(); i++){
                tmp[i]=tmp[i].toLower();
                tmp[i]=tmp[i].replace(0, 1, tmp[i][0].toUpper());
            }
            fName=tmp.join(",");
        }else if(fName.contains("-")){
            QStringList tmp = fName.split("-");
            for (int i=0; i<tmp.size(); i++){
                tmp[i]=tmp[i].toLower();
                tmp[i]=tmp[i].replace(0, 1, tmp[i][0].toUpper());
            }
            fName=tmp.join("-");
        }else {
            fName=fName.toLower();
            fName.replace(0, 1, fName[0].toUpper());
        }

        if (lName.contains(" ")){
            QStringList tmp = lName.split(" ");
            for (int i=0; i<tmp.size(); i++){
                tmp[i]=tmp[i].toLower();
                tmp[i]=tmp[i].replace(0, 1, tmp[i][0].toUpper());
            }
            lName=tmp.join("-");
        }else if(lName.contains("-")){
            QStringList tmp = lName.split("-");
            for (int i=0; i<tmp.size(); i++){
                tmp[i]=tmp[i].toLower();
                tmp[i]=tmp[i].replace(0, 1, tmp[i][0].toUpper());
            }
            lName=tmp.join("-");
        }else {
            lName=lName.toLower();
            lName.replace(0, 1, lName[0].toUpper());
        }

        bool duplicated=false;
        for (int i=0;i<reader->getClientsList().size();i++){
            if(reader->getClientsList().at(i)->getFirstName() == fName
                    && reader->getClientsList().at(i)->getLastName() == lName){
                duplicated=true;
                break;
            }
        }

        if (duplicated == true){
            QMessageBox::information(this,"Klient już istnieje!","Klient już istnieje.");
        }else{
            Client *newClient = new Client;
            newClient->setFirstName(fName);
            newClient->setLastName(lName);

            if(!ui->PhoneField->text().isEmpty()){
                QStringList formatting = ui->PhoneField->text().simplified().replace(" ","").split("");
                QString phoneNumber=QString(formatting.at(1) + formatting.at(2) + formatting.at(3) + " " + formatting.at(4) + formatting.at(5) + formatting.at(6) + " " + formatting.at(7) + formatting.at(8) + formatting.at(9));
                newClient->setPhoneNumber(phoneNumber);
            }else{
                newClient->setPhoneNumber(ui->PhoneField->text());
            }

            newClient->setComment(ui->CommentField->text());
            newClient->setClientID(reader->getClientsList().size());

            reader->addNewClientToList(newClient);
            filter->loadClientsToFilter(reader->getClientsList(),mainui);
            ui->NameField->clear();
            ui->LastnameField->clear();
            ui->PhoneField->clear();
            ui->CommentField->clear();
            mainui->Search->clear();

            //save xml
            reader->updateXML();

            close();

        }
    }
}

//void addNewClient::setMainWin(MainWindow *value)
//{
//    mainWin = value;
//}

void addNewClient::setReader(ClientListReader *value)
{
    reader = value;
}

void addNewClient::setFilter(clientFilter *value)
{
    filter = value;
}

void addNewClient::setMainUi(Ui::MainWindow *ui)
{
    mainui = ui;
}
