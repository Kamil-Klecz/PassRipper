#include "worker.h"
#include "workerwindow.h"

void Worker::run()
{
    setup();

    // 1. Odbierz plik ZIP
    const std::string localZip = "worker_received.zip";
    if (!comm.recvFile(sock, localZip)) {
        emit logMessage("Failed to receive file path");
        window->setInputsEnabled(true);
        return;
    }

    // 2. Odbierz alfabet
    if (!comm.recvString(sock, alphabet)) {
        emit logMessage("Failed to receive alphabet");
        window->setInputsEnabled(true);
        return;
    }

    // 3. Odbierz maksymalną długość hasła
    if (!comm.recvUInt8(sock, maxLen)) {
        emit logMessage("Failed to receive password length");
        window->setInputsEnabled(true);
        return;
    }

    // 4. Odbierz zakres do przeszukania
    comm.recvUInt64(sock, range.start);
    comm.recvUInt64(sock, range.end);

    emit logMessage(QString("Worker: Received range [%1, %2], alphabet(len=%3), maxLen=%4")
                        .arg(range.start)
                        .arg(range.end)
                        .arg(alphabet.size())
                        .arg(int(maxLen)));

    // Wielowątkowe łamanie haseł
    std::atomic<bool> found(false);
    std::string foundPwd;
    std::mutex mtx;
    std::vector<std::thread> threads;

    uint64_t total = range.end - range.start;
    uint64_t chunkSize = total / numThreads;

    for (unsigned i = 0; i < numThreads; ++i)
    {
        uint64_t start = range.start + i * chunkSize;
        uint64_t end = (i == numThreads - 1) ? range.end : start + chunkSize;

        threads.emplace_back([&, start, end]()
        {
            for (uint64_t idx = start; idx < end && !found.load(); ++idx)
            {
                std::string pwd = indexToPassword(idx, alphabet, maxLen);
                if (tryPassword(localZip, pwd))
                {
                    std::lock_guard<std::mutex> lock(mtx);
                    if (!found.load())
                    {
                        foundPwd = pwd;
                        found.store(true); //semantycznie poprawna wersja 'found = true'
                    }
                    break;
                }
            }
        });
    }

    for (auto& t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    // 6. Wyślij wynik
    if (found)
    {
        comm.sendString(sock, std::string("FOUND"));
        comm.sendString(sock, foundPwd);
        emit logMessage(QString("Worker: password found: %1").arg(QString::fromStdString(foundPwd)));
    } else
    {
        comm.sendString(sock, std::string("NOTFOUND"));
        emit logMessage("Worker: did not find password in given range");
    }

    window->setInputsEnabled(true);

    shutdown(sock, SD_BOTH);
    closesocket(sock);
    emit finished();
}

std::string Worker::indexToPassword(uint64_t index, const std::string& alphabet, uint8_t maxLen)
{
    std::string pwd;
    uint64_t base = alphabet.size();
    do {
        index--;
        pwd.push_back(alphabet[index % base]);
        index /= base;
    } while (index > 0 && pwd.size() < maxLen);

    std::reverse(pwd.begin(), pwd.end());
    return pwd;
}


bool Worker::tryPassword(const std::string& zipPath, const std::string& password)
{
    std::cout << "proba: " << password << std::endl;
    int err = 0;
    zip* za = zip_open(zipPath.c_str(), ZIP_RDONLY, &err);
    if (!za) return false;

    zip_int64_t n = zip_get_num_entries(za, 0);
    for (zip_uint64_t i = 0; i < (zip_uint64_t)n; ++i)
    {
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


void Worker::setup()
{
    //std::cerr<<addr.c_str()<<std::endl;std::cerr<<port.c_str()<<std::endl;
    sock = comm.createClient(addr.c_str(), port.c_str());
    if (sock == INVALID_SOCKET)
    {
        emit logMessage("Connect in setup failed");
        //window->appendLogs(QString("Connection with %1:%2 failed").arg(QString::fromStdString(addr), QString::fromStdString(port)));
        //exit(EXIT_FAILURE);
    }
    std::cout<<"Setup completed"<<std::endl;
    //emit logMessage("Setup completed");
}
