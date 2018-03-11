#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "addnewclient.h"
#include "editclient.h"
#include "manageservicesdialog.h"

#include "client.h"
#include "clientlistreader.h"
#include "servicelistreader.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *getUi() const;

    ClientListReader *getClientsReader() const;
    void setClientsReader(ClientListReader *reader);

    ServiceListReader *getServiceReader() const;
    void setServiceReader(ServiceListReader *reader);

    Client *getClientToEdit() const;
    void setClientToEdit(Client *client);

private slots:
    void on_Search_textChanged(const QString &arg1);
    void on_ClientList_itemSelectionChanged();

    void on_addClient_clicked();
    void on_ClientEdit_clicked();

    void on_manageServices_clicked();

private:
    Ui::MainWindow *ui;
    addNewClient addNewClientDialog;
    editClient editClientDialog;

    ClientListReader *clientsReader;
    ServiceListReader *servicesReader;

    manageServicesDialog manageServicesDialogObj;

    //Has to be generalized...
    QString logoPath = "D:/code/Qt/SalonBlades/SalonFryzjerski/blades.jpg";
    QString icoPath = "D:/code/Qt/SalonBlades/SalonFryzjerski/nozyczki.ico";

    bool firstSelection=false;
};

#endif // MAINWINDOW_H
