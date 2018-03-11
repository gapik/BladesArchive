#include "manageservicesdialog.h"
#include "ui_manageservicesdialog.h"
#include "servicelistreader.h"

#include <QDebug>
#include <QDialogButtonBox>

//#include "addnewclient.h"
//#include "ui_addnewclient.h"
//#include "ui_mainwindow.h"

//#include "client.h"

#include <QMessageBox>
#include <QMainWindow>

manageServicesDialog::manageServicesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::manageServicesDialog)
{
    ui->setupUi(this);
}

manageServicesDialog::~manageServicesDialog()
{
    delete ui;
}

void manageServicesDialog::setServicesReader(ServiceListReader *reader)
{
    servicesReader = reader;
}

void manageServicesDialog::loadServiceList()
{
    ui->servicesList->clear();
    for (int i=0;i<servicesReader->getServicesList().size();i++){
        ui->servicesList->addItem(servicesReader->getServicesList().at(i)->getName());
    }
    ui->servicesList->sortItems();
}

void manageServicesDialog::on_addService_clicked()
{
    if (ui->newServiceName->text() == ""){
        QMessageBox::information(this,"Podaj nazwę usługi!","Podaj nazwę usługi.");
        return;
    }
    for (int i=0;i<servicesReader->getServicesList().size();i++){
        if (servicesReader->getServicesList().at(i)->getName() == ui->newServiceName->text()){
            QMessageBox::information(this,"Usługa " + ui->newServiceName->text() + " już istnieje!","Usługa " + ui->newServiceName->text() + " już istnieje.");
            return;
        }
    }

    Service *newService = new Service;
    newService->setName(ui->newServiceName->text());
    servicesReader->addNewServiceToList(newService);
    ui->servicesList->clear();
    for (int i=0;i<servicesReader->getServicesList().size();i++){
        ui->servicesList->addItem(servicesReader->getServicesList().at(i)->getName());
    }
    ui->servicesList->sortItems();
    ui->newServiceName->clear();
    firstSelection=false;
}

void manageServicesDialog::on_deleteService_clicked()
{
    if (!firstSelection){
        QMessageBox::information(this,"Wskaż usługę, która ma zostać skasowana!","Wskaż usługę, która ma zostać skasowana.");
        return;
    }else{
        servicesReader->removeServiceFromList(ui->servicesList->currentItem()->text());
        ui->servicesList->clear();
        for (int i=0;i<servicesReader->getServicesList().size();i++){
            ui->servicesList->addItem(servicesReader->getServicesList().at(i)->getName());
        }
        ui->servicesList->sortItems();
        firstSelection=false;
    }
}

void manageServicesDialog::on_servicesList_itemSelectionChanged()
{
    firstSelection=true;
}

void manageServicesDialog::on_AcceptChanges_clicked()
{
    //Save XML file with services
    qDebug() << "Need to add capability to save XML with services.";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdzenie zmian.", "Czy na pewno chcesz wprowadzić zmiany w liście usług?",
                                    QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        this->close();
    }
}

void manageServicesDialog::on_cancelButton_clicked()
{
    close();
}
