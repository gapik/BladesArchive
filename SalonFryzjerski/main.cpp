#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QTranslator>
#include <QLibraryInfo>
#include <QFile>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator baseTranslator;
    baseTranslator.load("qtbase_pl", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&baseTranslator);

    QFile file("workdirpath.txt");
    QString dir;
    if (!file.exists() || !file.open(QFile::ReadOnly | QFile::Text)) {
        dir = QFileDialog::getExistingDirectory(0, "Wskaż folder z bazą danych",
                                                     "/home",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << dir << endl;
        }
    }else{
        QTextStream in(&file);
        dir=in.readLine(0);
    }
    file.close();

    QDir bckdir(dir + "/Backup");
    if (!bckdir.exists()) {
        bckdir.mkpath(".");
    }

    MainWindow w;
    w.setWorkDirectory(dir);
    w.show();

    return a.exec();
}
