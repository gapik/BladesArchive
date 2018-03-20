#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator baseTranslator;
    baseTranslator.load("qtbase_pl", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&baseTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
