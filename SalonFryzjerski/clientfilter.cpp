#include "clientfilter.h"

#include "ui_mainwindow.h"

clientFilter::clientFilter()
{

}

void clientFilter::loadClientsToFilter(QList<Client *> clientList, Ui_MainWindow *ui)
{
    ui->ClientList->clear();
    for(int i=0;i<clientList.size();i++){
        ui->ClientList->addItem(clientList.at(i)->getFirstName() + ' ' + clientList.at(i)->getLastName());
    }
    ui->ClientList->sortItems();
    ui->Filter->setText(QString("Filtruj Klientów (%1)").arg(ui->ClientList->count()));
}
