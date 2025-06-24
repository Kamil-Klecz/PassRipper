#include <QApplication>
#include "worker.h"
#include "mainwindow.h"
#include "manager.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(265,65);
    w.show();
    return a.exec();
}
