#ifndef MANAGEPRODUCTS_H
#define MANAGEPRODUCTS_H

#include <QDialog>

#include "productlistreader.h"

namespace Ui {
class manageProducts;
}

class manageProducts : public QDialog
{
    Q_OBJECT

public:
    explicit manageProducts(QWidget *parent = 0);
    ~manageProducts();

    void setProductReader(ProductListReader *reader);
    void loadProductList();

private slots:
    void on_addProduct_clicked();

    void on_removeProduct_clicked();

    void on_acceptChanges_clicked();

    void on_cancelButton_clicked();

private:
    Ui::manageProducts *ui;

    ProductListReader *productsReader;
};

#endif // MANAGEPRODUCTS_H
