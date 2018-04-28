#ifndef ASSIGNPRODUCTSTOVISIT_H
#define ASSIGNPRODUCTSTOVISIT_H

#include <QDialog>
#include <service.h>
#include <productlistreader.h>

namespace Ui {
class assignProductsToVisit;
}

class assignProductsToVisit : public QDialog
{
    Q_OBJECT

public:
    explicit assignProductsToVisit(QWidget *parent = 0);
    ~assignProductsToVisit();

    void setLabels(QString clientName,QString date, QString ServiceName);
    void setProductListToComboBoxes();


    Service *getService() const;
    void setService(Service *value);

    ProductListReader *getProductReader() const;
    void setProductReader(ProductListReader *value);

signals:
    void productsUpdated();

private slots:
    void on_cancelButton_clicked();

    void on_addProductButton_clicked();

private:
    Ui::assignProductsToVisit *ui;

    Service *service;
    ProductListReader *productReader;
};

#endif // ASSIGNPRODUCTSTOVISIT_H
