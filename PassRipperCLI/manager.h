#pragma once
#include "komunikacja.h"
#include <QString>
#pragma comment(lib, "Ws2_32.lib")

class Manager
{
public:
    QString zipPath;
    QString alphabet;
    uint8_t maxLen;

    Manager(const char* port, int workerCount)
        : count(workerCount)
    {
        SOCKET ls = comm.createListener(port);
        if (ls == INVALID_SOCKET) exit(EXIT_FAILURE);
        listenSock = ls;
        std::cout << "Manager: listening on port " << port << std::endl;
    }

    void run();

private:
    Komunikacja comm;
    SOCKET listenSock{INVALID_SOCKET};
    int count{0};
    std::vector<SOCKET> workers;
};
