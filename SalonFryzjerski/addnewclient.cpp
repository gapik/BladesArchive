#include "addnewclient.h"
#include "ui_addnewclient.h"
#include "ui_mainwindow.h"

#include "client.h"
#include <QDebug>

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
    Client *newClient = new Client;
    //new to check if there is no equal record
    //new to check if firstname and lastname is provided - else print messagebox
    newClient->setFirstName(ui->NameField->text());
    newClient->setLastName(ui->LastnameField->text());
    newClient->setPhoneNumber(ui->PhoneField->text());
    newClient->setComment(ui->CommentField->text());
    reader->addNewClientToList(newClient);
    filter->loadClientsToFilter(reader->getClientsList(),mainui);
    ui->NameField->clear();
    ui->LastnameField->clear();
    ui->PhoneField->clear();
    ui->CommentField->clear();
    mainui->Search->clear();
    close();
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
