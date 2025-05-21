#pragma once
#include "komunikacja.h"
#include <zip.h>
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

        // 5. Łamanie haseł
        bool found = false;
        std::string foundPwd;
        for (uint64_t idx = range.start; idx < range.end; ++idx) {
            std::string pwd = indexToPassword(idx, alphabet, maxLen);
            if (tryPassword(localZip, pwd)) {
                found = true;
                foundPwd = pwd;
                break;
            }
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
        int err = 0;
        zip* za = zip_open(zipPath.c_str(), ZIP_RDONLY, &err);
        if (!za) return false;

        zip_int64_t num_entries = zip_get_num_entries(za, 0);
        if (num_entries == 0) {
            zip_close(za);
            return false;
        }

        // Zakładamy, że testujemy pierwszy plik w archiwum
        zip_file* zf = zip_fopen_encrypted(za, 0, 0, password.c_str());
        if (!zf) {
            zip_close(za);
            return false;
        }

        char buf[16]; // próbujemy odczytać kilka bajtów
        zip_int64_t bytes_read = zip_fread(zf, buf, sizeof(buf));
        zip_fclose(zf);
        zip_close(za);

        return bytes_read > 0;
    }
};
