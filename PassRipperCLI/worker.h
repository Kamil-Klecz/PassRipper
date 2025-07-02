#pragma once

class WorkerWindow;

#include "komunikacja.h"
#include <zip.h>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

class Worker
{
public:
    unsigned numThreads;

    Worker(const std::string& address, const std::string& port, WorkerWindow* win)
        : addr(address), port(port), window(win)
    {}

    // Uruchamia odbiór danych i łamanie hasła
    void run();

    //Setup klienta
    void setup();

private:
    WorkerWindow* window;
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
