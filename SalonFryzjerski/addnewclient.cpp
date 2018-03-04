#include "addnewclient.h"
#include "ui_addnewclient.h"
#include "ui_mainwindow.h"

#include "client.h"
#include <QDebug>
#include <QMessageBox>

addNewClient::addNewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addNewClient)
{
    ui->setupUi(this);
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
    //new to check if firstname and lastname is provided - else print messagebox
    if(ui->NameField->text() == "" || ui->LastnameField->text() == ""){
        QMessageBox::information(this,"Brak wymaganych danych!","Uzupełnij wymagane pola.");
    }else{
        bool duplicated=false;
        for (int i=0;i<reader->getClientsList().size();i++){
            if(reader->getClientsList().at(i)->getFirstName() == ui->NameField->text()
                    && reader->getClientsList().at(i)->getLastName() == ui->LastnameField->text()){
                duplicated=true;
                break;
            }
        }

        if (duplicated == true){
            QMessageBox::information(this,"Klient już istnieje!","Klient już istnieje.");
        }else{
            Client *newClient = new Client;
            newClient->setFirstName(ui->NameField->text());
            newClient->setLastName(ui->LastnameField->text());
            newClient->setPhoneNumber(ui->PhoneField->text());
            newClient->setComment(ui->CommentField->text());
            newClient->setClientID(reader->getClientsList().size());

            reader->addNewClientToList(newClient);
            filter->loadClientsToFilter(reader->getClientsList(),mainui);
            ui->NameField->clear();
            ui->LastnameField->clear();
            ui->PhoneField->clear();
            ui->CommentField->clear();
            mainui->Search->clear();
            close();
        }
    }
}

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
