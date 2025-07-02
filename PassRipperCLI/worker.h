#pragma once
#include "komunikacja.h"
#include <zip.h>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
class Worker
{
public:
    unsigned numThreads = 4; //default

    Worker(const std::string& address, const std::string& port)
        : addr(address), port(port)
    {
        // nawiąż połączenie do managera
        sock = comm.createClient(addr.c_str(), port.c_str());
        if (sock == INVALID_SOCKET) {
            std::cerr << "Worker: nie udało się połączyć z " << addr << ":" << port << std::endl;
                //exit(EXIT_FAILURE);
        }
    }

    // Uruchamia odbiór danych i łamanie hasła
    void run();

private:
    Komunikacja comm;
    SOCKET sock{INVALID_SOCKET};
    std::string addr, port;

    Komunikacja::TaskRange range;

    std::string alphabet;
    uint8_t maxLen{0};

    // Konwersja indeksu na hasło
    std::string indexToPassword(uint64_t index, const std::string& alphabet, uint8_t maxLen);

    // Próba otwarcia archiwum ZIP za pomocą hasła
    bool tryPassword(const std::string& zipPath, const std::string& password);
};
