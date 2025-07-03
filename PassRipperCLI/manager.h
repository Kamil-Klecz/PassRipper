#pragma once

class ManagerWindow;

#include "komunikacja.h"
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <QString>
#include <QObject>
#pragma comment(lib, "Ws2_32.lib")

class Manager: public QObject
{
    Q_OBJECT
public:
    ManagerWindow* window;
    QString zipPath;
    QString alphabet;
    uint8_t maxLen;

    Manager(const char* port, int workerCount, ManagerWindow* win)
        : port(port), count(workerCount), window(win)
    {
        SOCKET ls = comm.createListener(port);
        if (ls == INVALID_SOCKET)
        {
            exit(EXIT_FAILURE);
        }
        listenSock = ls;
    }
public slots:
    void run();
signals:
    void finished();
private:
    Komunikacja comm;
    SOCKET listenSock{INVALID_SOCKET};
    int count{0};
    const char* port;
    std::vector<SOCKET> workers;
};
