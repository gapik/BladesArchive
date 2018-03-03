#ifndef ADDNEWCLIENT_H
#define ADDNEWCLIENT_H

#include <QDialog>
#include "clientlistreader.h"
#include "clientfilter.h"
#include "ui_mainwindow.h"


namespace Ui {
class addNewClient;
}

class addNewClient : public QDialog
{
    Q_OBJECT

public:
    explicit addNewClient(QWidget *parent = 0);
    ~addNewClient();

    void setReader(ClientListReader *value);
    void setFilter(clientFilter *value);
    void setMainUi(Ui::MainWindow *ui);

private slots:
    void on_CancelButton_clicked();

    void on_AddClientButton_clicked();

private:
    Ui::MainWindow *mainui;
    Ui::addNewClient *ui;
    ClientListReader *reader;
    clientFilter *filter;
};

#endif // ADDNEWCLIENT_H
