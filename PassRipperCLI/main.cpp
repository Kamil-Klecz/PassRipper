#include <QApplication>
#include "worker.h"
#include "mainwindow.h"
#include "manager.h"
#include <iostream>
int main(int argc, char *argv[])
{
    // std::string flush;
    // std::cin>>flush;
    // std::cin.clear();
    // std::string mode;
    // std::cout<<"Wybierz tryb: ";
    // std::cin>>mode;
    // QCoreApplication a(argc, argv);
    // if(mode=="manager"){
    //     std::string p;
    //     int c;
    //     std::cout<<"Port: ";
    //     std::cin>>p;
    //     std::cout<<"Ile Workerow: ";
    //     std::cin>>c;
    //     Manager m(p.c_str(),c);
    //     m.run();
    // }
    // else if(mode=="worker"){ std::string a,p;
    //     std::cout<<"Addr: ";
    //     std::cin>>a;
    //     std::cout<<"Port: ";
    //     std::cin>>p;
    //     Worker w(a,p);
    //     // Worker w(addr, port);
    //     w.run();

    // }
    // else std::cerr<<"Nie znany tryb\n";
    // std::cin>>mode;
    // return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(265,65);
    w.show();
    return a.exec();
}
