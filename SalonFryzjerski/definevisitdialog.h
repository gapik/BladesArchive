#ifndef DEFINEVISITDIALOG_H
#define DEFINEVISITDIALOG_H

#include <QDialog>

#include "servicelistreader.h"
#include "productlistreader.h"

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

private slots:
    void on_AddService_clicked();

    void on_CancelButton_clicked();

private:
    Ui::DefineVisitDialog *ui;

    ServiceListReader *servicesReader;
    ProductListReader *productsReader;

};

#endif // DEFINEVISITDIALOG_H
