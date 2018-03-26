#ifndef MANAGESERVICESDIALOG_H
#define MANAGESERVICESDIALOG_H

#include <QDialog>

#include "servicelistreader.h"

namespace Ui {
class manageServicesDialog;
}

class manageServicesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit manageServicesDialog(QWidget *parent = 0);
    ~manageServicesDialog();

    void setServicesReader(ServiceListReader *reader);
    void loadServiceList();

private slots:
    void on_addService_clicked();

    void on_deleteService_clicked();

    void on_AcceptChanges_clicked();

    void on_cancelButton_clicked();

private:
    Ui::manageServicesDialog *ui;

    ServiceListReader *servicesReader;
};

#endif // MANAGESERVICESDIALOG_H
