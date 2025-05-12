#include <QCoreApplication>
#include "worker.h"
#include "manager.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string mode; std::cout<<"Wybierz tryb: "; std::cin>>mode;
    if(mode=="manager"){
        std::string p;
        int c;
        std::cout<<"Port: ";
        std::cin>>p;
        std::cout<<"Ile Workerow: ";
        std::cin>>c;
        Manager m(p.c_str(),c);
        m.run();
    }
    else if(mode=="worker"){ std::string a,p;
        std::cout<<"Addr: ";
        std::cin>>a;
        std::cout<<"Port: ";
        std::cin>>p; Worker w(a,p);
        w.run();
    }
    else std::cerr<<"Nie znany tryb\n";
    std::cin>>mode;
    return 0;
}
