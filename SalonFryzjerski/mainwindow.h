#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "addnewclient.h"
#include "editclient.h"
#include "manageservicesdialog.h"
#include "manageproducts.h"

#include "client.h"
#include "clientlistreader.h"
#include "servicelistreader.h"
#include "productlistreader.h"

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

    ProductListReader *getProductReader() const;
    void setProductReader(ProductListReader *reader);

    Client *getClientToEdit() const;
    void setClientToEdit(Client *client);

    QString getWorkDirectory() const;
    void setWorkDirectory(const QString &value);

private slots:
    void on_Search_textChanged(const QString &arg1);
    void on_ClientList_itemSelectionChanged();

    void on_addClient_clicked();
    void on_ClientEdit_clicked();

    void on_manageServices_clicked();
    void on_manageProducts_clicked();

private:
    Ui::MainWindow *ui;
    addNewClient addNewClientDialog;
    editClient editClientDialog;

    QString workDirectory;

    ClientListReader *clientsReader;
    ServiceListReader *servicesReader;
    ProductListReader *productsReader;

    manageServicesDialog manageServicesDialogObj;
    manageProducts manageProductsDialog;

    //Has to be generalized...
//    QString logoPath = "D:/code/Qt/SalonBlades/SalonFryzjerski/blades.jpg";
//    QString icoPath = "D:/code/Qt/SalonBlades/SalonFryzjerski/nozyczki.ico";
    QString logoPath = "blades.jpg";
    QString icoPath = "nozyczki.ico";
};

#endif // MAINWINDOW_H
