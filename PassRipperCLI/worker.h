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
public:
    Worker(const std::string& address, const std::string& port)
        : addr(address), port(port)
    {
        // nawiąż połączenie do managera
        sock = comm.createClient(addr.c_str(), port.c_str());
        if (sock == INVALID_SOCKET) {
            std::cerr << "Worker: nie udało się połączyć z " << addr << ":" << port << std::endl;
                exit(EXIT_FAILURE);
        }
    }



    // Uruchamia odbiór danych i łamanie hasła
    void run() {
        // 1. Odbierz plik ZIP
        const std::string localZip = "worker_received.zip";
        if (!comm.recvFile(sock, localZip)) {
            std::cerr << "Worker: błąd odbioru pliku" << std::endl;
                return;
        }

        // 2. Odbierz alfabet
        if (!comm.recvString(sock, alphabet)) {
            std::cerr << "Worker: błąd odbioru alfabetu" << std::endl;
                return;
        }

        // 3. Odbierz maksymalną długość hasła
        if (!comm.recvUInt8(sock, maxLen)) {
            std::cerr << "Worker: błąd odbioru maxLen" << std::endl;
                return;
        }

        // 4. Odbierz zakres do przeszukania
        comm.recvUInt64(sock, range.start);
        comm.recvUInt64(sock, range.end);

        std::cout << "Worker: otrzymano zakres [" << range.start << "," << range.end << "] alfabet(len="
                  << alphabet.size() << ") maxLen=" << int(maxLen) << std::endl;

        // Wielowątkowe łamanie haseł
        const unsigned numThreads = std::thread::hardware_concurrency(); // lub stała np. 4
        std::atomic<bool> found(false);
        std::string foundPwd;
        std::mutex mtx;
        std::vector<std::thread> threads;

        uint64_t total = range.end - range.start;
        uint64_t chunkSize = total / numThreads;

        for (unsigned i = 0; i < numThreads; ++i) {
                uint64_t start = range.start + i * chunkSize;
                uint64_t end = (i == numThreads - 1) ? range.end : start + chunkSize;

                threads.emplace_back([&, start, end]() {
                    for (uint64_t idx = start; idx < end && !found.load(); ++idx) {
                        std::string pwd = indexToPassword(idx, alphabet, maxLen);
                        if (tryPassword(localZip, pwd)) {
                            std::lock_guard<std::mutex> lock(mtx);
                            if (!found.load()) {
                                foundPwd = pwd;
                                found = true;
                            }
                            break;
                        }
                    }
                });
        }


        // 6. Wyślij wynik
        if (found) {
            comm.sendString(sock, std::string("FOUND"));
            comm.sendString(sock, foundPwd);
            std::cout << "Worker: hasło znalezione: " << foundPwd << std::endl;
        } else {
            comm.sendString(sock, std::string("NOTFOUND"));
            std::cout << "Worker: nie znaleziono hasła w przydzielonym zakresie" << std::endl;
        }

        shutdown(sock, SD_BOTH);
        closesocket(sock);
    }

private:
    Komunikacja comm;
    SOCKET sock{INVALID_SOCKET};
    std::string addr, port;

    struct TaskRange {
        uint64_t start;
        uint64_t end;
    } range;

    std::string alphabet;
    uint8_t maxLen{0};

    // Konwersja indeksu na hasło
    std::string indexToPassword(uint64_t index, const std::string& alphabet, uint8_t maxLen) {
        std::string pwd;
        uint64_t base = alphabet.size();
        while ((index > 0) && (pwd.size() < maxLen)) {
            pwd.push_back(alphabet[index % base]);
            index /= base;
        }
        std::reverse(pwd.begin(), pwd.end());
        return pwd;
    }

    // Próba otwarcia archiwum ZIP za pomocą hasła
    bool tryPassword(const std::string& zipPath, const std::string& password) {

        std::cout << "proba: " << password << std::endl;
        int err = 0;
        zip* za = zip_open(zipPath.c_str(), ZIP_RDONLY, &err);
        if (!za) return false;

        zip_int64_t n = zip_get_num_entries(za, 0);
        for (zip_uint64_t i = 0; i < (zip_uint64_t)n; ++i) {
            struct zip_stat st;
            if (zip_stat_index(za, i, 0, &st) != 0)
                continue;
            // pomijamy katalogi lub pliki bez szyfrowania
            if (st.encryption_method == ZIP_EM_NONE)
                continue;

            // próbujemy otworzyć zaszyfrowany plik po nazwie
            zip_file_t* zf = zip_fopen_encrypted(za, st.name, 0, password.c_str());
            if (!zf) {
                zip_close(za);
                return false;
            }
            // próbujemy odczytać kilka bajtów
            char buf[16];
            zip_int64_t bytes = zip_fread(zf, buf, sizeof(buf));
            zip_fclose(zf);
            zip_close(za);

            return (bytes > 0);
        }

        // brak plików wymagających hasła -> nie złań
        zip_close(za);
        return false;
    }
};
