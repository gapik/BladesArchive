#ifndef CLIENTFILTER_H
#define CLIENTFILTER_H

#include <QList>
#include "client.h"

class Ui_MainWindow;

class clientFilter
{
public:
    clientFilter();

    void loadClientsToFilter(QList<Client*> clientList, Ui_MainWindow *ui);
};

#endif // CLIENTFILTER_H
