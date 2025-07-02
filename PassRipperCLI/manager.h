#pragma once

class ManagerWindow;

#include "komunikacja.h"
#include <QString>
#pragma comment(lib, "Ws2_32.lib")

class Manager
{
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

    void run();

private:
    Komunikacja comm;
    SOCKET listenSock{INVALID_SOCKET};
    int count{0};
    const char* port;
    std::vector<SOCKET> workers;
};
