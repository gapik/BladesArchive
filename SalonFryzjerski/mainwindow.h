#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "addnewclient.h"
#include "editclient.h"
#include "manageservicesdialog.h"
#include "manageproducts.h"
#include "definevisitdialog.h"

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

    QString getIcoPath() const;

    void updateTreeView();

private slots:
    void on_Search_textChanged(const QString &arg1);
    void on_ClientList_itemSelectionChanged();

    void on_addClient_clicked();
    void on_ClientEdit_clicked();
    void on_deleteClient_clicked();

    void on_manageServices_clicked();
    void on_manageProducts_clicked();

    void on_addVisit_clicked();
    void on_editVisit_clicked();
    void on_expandCollapse_clicked();
    void on_deleteVisit_clicked();

    void on_newVisitDefined();

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
    DefineVisitDialog defineVisitDialogObj;

    //Has to be generalized...
//    QString logoPath = "D:/code/Qt/SalonBlades/SalonFryzjerski/blades.jpg";
//    QString icoPath = "D:/code/Qt/SalonBlades/SalonFryzjerski/nozyczki.ico";
    QString logoPath = "blades.jpg";
    QString icoPath = "nozyczki.ico";

    bool treeExpanded = true;
};

#endif // MAINWINDOW_H
