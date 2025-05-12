
#pragma once
#include "komunikacja.h"
#pragma comment(lib, "Ws2_32.lib")

class Manager
{
public:
    Manager(const char* port, int workerCount)
        : count(workerCount)
    {
        SOCKET ls = comm.createListener(port);
        if (ls == INVALID_SOCKET) exit(EXIT_FAILURE);
        listenSock = ls;
        std::cout << "Manager: listening on port " << port << std::endl;
    }

    void run(){
        const std::string zipPath="archive.zip";
        const std::string alphabet="abcdefghijklmnopqrstuvwxyz";
        uint8_t maxLen=5;
        uint64_t totalTasks=1000000;
        uint64_t chunk=totalTasks/count;
        uint64_t start=0;
        for(int i=0;i<count;i++){
            SOCKET s=comm.acceptConnection(listenSock);
            std::cout<<"Manager: worker"<<i+1<<" connected\n";
            comm.sendFile(s,zipPath);
            comm.sendString(s,alphabet);
            comm.sendUInt8(s,maxLen);
            uint64_t end=(i+1==count?totalTasks:start+chunk);
            comm.sendUInt64(s,start);
            comm.sendUInt64(s,end);
            std::cout<<"Sent range ["<<start<<","<<end<<"] alphabet(len="<<alphabet.size()<<") maxLen="<<(int)maxLen<<"\n";
            shutdown(s,SD_BOTH); closesocket(s);
            start+=chunk;
        }
    }

private:
    Komunikacja comm;
    SOCKET listenSock{INVALID_SOCKET};
    int count{0};
    std::vector<SOCKET> workers;
};
