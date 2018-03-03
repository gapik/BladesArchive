#-------------------------------------------------
#
# Project created by QtCreator 2018-02-22T21:22:52
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SalonFryzjerski
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    visit.cpp \
    service.cpp \
    product.cpp \
    clientlistreader.cpp \
    clientfilter.cpp \
    addnewclient.cpp

HEADERS  += mainwindow.h \
    client.h \
    visit.h \
    service.h \
    product.h \
    clientlistreader.h \
    clientfilter.h \
    addnewclient.h

FORMS    += mainwindow.ui \
    addnewclient.ui
