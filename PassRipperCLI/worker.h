#pragma once
#include "komunikacja.h"
#include "mz.h"
#include "mz_zip_rw.h"
class Worker
{
public:
    Worker(const std::string& address, const std::string& port)
    {
        sock = comm.createClient(address.c_str(), port.c_str());
        if (sock == INVALID_SOCKET) exit(EXIT_FAILURE);
        std::cout << "Worker: connected to " << address << ':' << port << std::endl;
    }

    // Konwersja indeksu na hasło
    std::string indexToPassword(uint64_t index, const std::string& alphabet, uint8_t maxLen) {
        std::string pwd;
        uint64_t base = alphabet.size();
        while (index > 0 && pwd.size() < maxLen) {
            pwd.push_back(alphabet[index % base]);
            index /= base;
        }
        std::reverse(pwd.begin(), pwd.end());
        return pwd;
    }


    bool tryPassword(const std::string& zipPath, const std::string& password) {
        // 1) Utwórz reader
        void* reader = mz_zip_reader_create();
        if (!reader) return false;

        // 2) Ustaw hasło
        mz_zip_reader_set_password(reader, password.c_str());

        // 3) Otwórz plik ZIP
        if (mz_zip_reader_open_file(reader, zipPath.c_str()) != MZ_OK) {
            // cleanup
            mz_zip_reader_delete(&reader); // albo free(reader) jeśli nie ma delete
            return false;
        }

        // 4) Przejdź do pierwszego wpisu
        bool ok = false;
        if (mz_zip_reader_goto_first_entry(reader) == MZ_OK) {
            if (mz_zip_reader_entry_open(reader) == MZ_OK) {
                mz_zip_reader_entry_close(reader);
                ok = true;
            }
        }

        // 5) cleanup
        mz_zip_reader_close(reader);
        mz_zip_reader_delete(&reader); // lub free(reader)

        return ok;
    }



    void run() {
        const std::string localZip = "worker.zip";

        // 1. Odbiór pliku ZIP
        std::cout << "Worker: receiving data..." << std::endl;
        if (!comm.recvFile(sock, localZip)) {
            std::cerr << "Worker: failed to receive ZIP" << std::endl;
            return;
        }

        // 2. Odbiór parametrów brute-force
        std::string alphabet;
        comm.recvString(sock, alphabet);
        uint8_t maxLen;
        comm.recvUInt8(sock, maxLen);
        uint64_t start, end;
        comm.recvUInt64(sock, start);
        comm.recvUInt64(sock, end);

        std::cout << "Worker: alphabet='" << alphabet << "' maxLen=" << (int)maxLen
                  << " range=[" << start << "," << end << "]" << std::endl;

        // 3. Brute-force
        std::string foundPwd;
        for (uint64_t idx = start; idx < end; ++idx) {
            // a) konstrukcja hasła
            std::string pwd = indexToPassword(idx, alphabet, maxLen);

            // b) tworzymy i konfigurujemy reader ZIPa
            void* reader = mz_zip_reader_create();
            if (!reader) continue;

            mz_zip_reader_set_password(reader, pwd.c_str());
            if (mz_zip_reader_open_file(reader, localZip.c_str()) != MZ_OK) {
                mz_zip_reader_delete(&reader);
                continue;
            }

            // c) przejście do pierwszego wpisu i próba otwarcia
            bool ok = false;
            if (mz_zip_reader_goto_first_entry(reader) == MZ_OK) {
                if (mz_zip_reader_entry_open(reader) == MZ_OK) {
                    mz_zip_reader_entry_close(reader);
                    ok = true;
                }
            }

            // d) sprzątanie
            mz_zip_reader_close(reader);
            mz_zip_reader_delete(&reader);

            if (ok) {
                foundPwd = pwd;
                break;
            }
        }

        // 4. Wysłanie wyniku do Managera
        comm.sendString(sock, foundPwd);
        if (!foundPwd.empty())
            std::cout << "Worker: found password '" << foundPwd << "'" << std::endl;
        else
            std::cout << "Worker: no password found" << std::endl;
    }

private:
    Komunikacja comm;
    SOCKET sock{INVALID_SOCKET};
};
