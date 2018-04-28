#ifndef DEFINEVISITDIALOG_H
#define DEFINEVISITDIALOG_H

#include <QDialog>

#include "servicelistreader.h"
#include "productlistreader.h"
#include "visit.h"

#include "assignproductstovisit.h"

namespace Ui {
class DefineVisitDialog;
}

class DefineVisitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DefineVisitDialog(QWidget *parent = 0);
    ~DefineVisitDialog();


    ServiceListReader *getServicesReader() const;
    void setServicesReader(ServiceListReader *value);

    ProductListReader *getProductsReader() const;
    void setProductsReader(ProductListReader *value);

    void loadServiceList();
    void setDateLabel(QString dateString);
    void setClientLabel(QString clientName);
    void updateTreeView();

    void setIconPath(const QString &value);

private slots:
    void on_AddService_clicked();

    void on_CancelButton_clicked();

    void on_AddProducts_clicked();

    void on_DeleteService_clicked();
    void on_productsUpdated();

    void on_servicesList_clicked(const QModelIndex &index);

    void on_AvailableServices_clicked(const QModelIndex &index);

    void on_deleteProduct_clicked();

private:
    Ui::DefineVisitDialog *ui;
    assignProductsToVisit assignProduct;

    ServiceListReader *servicesReader;
    ProductListReader *productsReader;

    Visit* newVisit;
    QList<Service*> ServiceList;

    QString iconPath;

};

#endif // DEFINEVISITDIALOG_H
