#ifndef EDITCLIENT_H
#define EDITCLIENT_H

#include <QDialog>
#include "clientlistreader.h"
#include "clientfilter.h"
#include "ui_mainwindow.h"

namespace Ui {
class editClient;
}

class editClient : public QDialog
{
    Q_OBJECT

public:
    explicit editClient(QWidget *parent = 0);
    ~editClient();

    void setReader(ClientListReader *value);
    void setFilter(clientFilter *value);
    void setMainUi(Ui::MainWindow *ui);

    Ui::editClient *getUi() const;

    Client *getClientToEdit() const;
    void setClientToEdit(Client *client);

    int getClientToEditIndex() const;
    void setClientToEditIndex(int index);

private slots:
    void on_UpdateClientButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::editClient *ui;
    Ui::MainWindow *mainui;
    ClientListReader *reader;
    clientFilter *filter;

    Client *clientToEdit;
    int clientToEditIndex;
};

#endif // EDITCLIENT_H
