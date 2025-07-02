#include "manager.h"
#include "managerwindow.h"

void Manager::run()
{
    uint64_t totalTasks=1000000;
    uint64_t chunk=totalTasks/count;
    uint64_t start=0;

    for(int i=0;i<count;i++)
    {
        SOCKET s=comm.acceptConnection(listenSock);
        window->appendLog(QString("Worker %1 connected").arg(i+1));
        comm.sendFile(s, zipPath.toStdString());
        comm.sendString(s, alphabet.toStdString());
        comm.sendUInt8(s, maxLen);
        uint64_t end=(i+1==count?totalTasks:start+chunk);
        comm.sendUInt64(s, start);
        comm.sendUInt64(s, end);
        std::cout<<"Sent range ["<<start<<","<<end<<"] alphabet(len="<<alphabet.size()<<") maxLen="<<(int)maxLen<<"\n";
        shutdown(s, SD_BOTH); closesocket(s);
        start+=chunk;
    }
}
