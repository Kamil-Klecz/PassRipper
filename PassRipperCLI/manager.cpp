#include "manager.h"
#include "managerwindow.h"

void Manager::run()
{
    uint64_t totalTasks = 1000000;
    uint64_t chunk = totalTasks / count;
    uint64_t start = 0;

    std::vector<std::thread> workerThreads;
    std::mutex logMutex;

    for (int i = 0; i < count; i++)
    {
        uint64_t taskStart = start;
        uint64_t taskEnd = (i + 1 == count ? totalTasks : taskStart + chunk);
        start += chunk;

        workerThreads.emplace_back([=, &logMutex]()
           {
               SOCKET s = comm.acceptConnection(listenSock);
               {
                   std::lock_guard<std::mutex> lock(logMutex);
                   window->appendLog(QString("Worker %1 connected").arg(i + 1));
               }

               comm.sendFile(s, zipPath.toStdString());
               comm.sendString(s, alphabet.toStdString());
               comm.sendUInt8(s, maxLen);
               comm.sendUInt64(s, taskStart);
               comm.sendUInt64(s, taskEnd);

               // Receive result
               std::string status;
               if (comm.recvString(s, status))
               {
                   if (status == "FOUND")
                   {
                       std::string pwd;
                       if (comm.recvString(s, pwd))
                       {
                           {
                               std::lock_guard<std::mutex> lock(logMutex);
                               window->appendLog(QString("Worker %1 found password: %2").arg(i + 1).arg(QString::fromStdString(pwd)));
                               window->setInputsEnabled(true);
                           }
                       }
                   }
                   else if (status == "NOTFOUND")
                   {
                       std::lock_guard<std::mutex> lock(logMutex);
                       window->appendLog(QString("Worker %1 did not find password").arg(i + 1));
                   }
                   else
                   {
                       std::lock_guard<std::mutex> lock(logMutex);
                       window->appendLog(QString("Worker %1 returned unknown status: %2").arg(i + 1).arg(QString::fromStdString(status)));
                   }
               }
               else
               {
                   std::lock_guard<std::mutex> lock(logMutex);
                   window->appendLog(QString("Worker %1 failed to send result").arg(i + 1));
               }

               shutdown(s, SD_BOTH);
               closesocket(s);
           });
    }

    for (auto& t : workerThreads)
        if (t.joinable()) t.join();
}
