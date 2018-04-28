#include "editclient.h"
#include "ui_editclient.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>

editClient::editClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editClient)
{
    ui->setupUi(this);
}

editClient::~editClient()
{
    delete ui;
}

Ui::editClient *editClient::getUi() const
{
    return ui;
}

void editClient::on_UpdateClientButton_clicked()
{
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

        QString phoneNumber=ui->PhoneField->text();
        QString comment=ui->CommentField->text();
        Client *newClient = getClientToEdit();

//        if it duplicates another record
        for (int i=0;i<reader->getClientsList().size();i++){
            if(reader->getClientsList().at(i)->getFirstName() == fName
                    && reader->getClientsList().at(i)->getLastName() == lName){
                if (reader->getClientsList().at(i)->getClientID() != newClient->getClientID()){
                    QMessageBox::information(this,"Klient już istnieje!","Klient już istnieje.");
                    return;
                }
            }
        }

//        if there is any change
        bool changed=false;
        if(newClient->getFirstName() != fName){
            newClient->setFirstName(fName);
            changed=true;
        }
        if(newClient->getLastName() != lName){
            newClient->setLastName(lName);
            changed=true;
        }
        if(newClient->getPhoneNumber() != phoneNumber){
            newClient->setPhoneNumber(phoneNumber);
            changed=true;
        }
        if(newClient->getComment() != comment){
            newClient->setComment(comment);
            changed=true;
        }
        if (changed==false){
            QMessageBox::information(this,"Brak zmian!","Dane klienta nie zostały zmienione.");
            return;
        }

        filter->loadClientsToFilter(reader->getClientsList(),mainui);
        ui->NameField->clear();
        ui->LastnameField->clear();
        ui->PhoneField->clear();
        ui->CommentField->clear();
        mainui->Search->clear();
        QStandardItemModel *def_model = new QStandardItemModel(this);
        def_model->setColumnCount(4);
        def_model->setHorizontalHeaderItem(0, new QStandardItem(tr("Imię i Nazwisko (numer telefonu) [UWAGI]")));
        def_model->setHorizontalHeaderItem(1, new QStandardItem(tr("Sygnatura")));
        def_model->setHorizontalHeaderItem(2, new QStandardItem(tr("Ilość")));
        def_model->setHorizontalHeaderItem(3, new QStandardItem(tr("Cena")));
        mainui->treeView->setModel(def_model);

        //save xml
        reader->updateXML();

        close();
    }
}

void editClient::on_CancelButton_clicked()
{
    close();
}

int editClient::getClientToEditIndex() const
{
    return clientToEditIndex;
}

void editClient::setClientToEditIndex(int index)
{
    clientToEditIndex = index;
}

Client *editClient::getClientToEdit() const
{
    return clientToEdit;
}

void editClient::setClientToEdit(Client *client)
{
    clientToEdit = client;
}

void editClient::setReader(ClientListReader *value)
{
    reader = value;
}

void editClient::setFilter(clientFilter *value)
{
    filter = value;
}

void editClient::setMainUi(Ui::MainWindow *ui)
{
    mainui = ui;
}
