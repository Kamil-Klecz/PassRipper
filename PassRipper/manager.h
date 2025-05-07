#ifndef MANAGER_H
#define MANAGER_H
#include "komunikacja.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <vector>
#include <iostream>

class Manager{

    //Uwaga - cout są tymczasowe na czas debugowania w trybie konsolowym, w ostatecznej wersji aplikacji ich nie będzie
private:
    SOCKET listenSock{INVALID_SOCKET}; // Socket nasłuchujący
    std::vector<SOCKET> workers; // Lista podłączonych pracowników

public:
    // Konstruktor tworzący socket nasluchujący na podanym porcie
    Manager(const char* port){
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa); //Inicjalizacja Winsock
        addrinfo hints{}; // Struktura z informacjami o adresie i połączeniu. Dodajemy własne parametry.
        hints.ai_family = AF_INET;       // IPv4
        hints.ai_socktype = SOCK_STREAM; // TCP
        hints.ai_flags = AI_PASSIVE;     // Dla bind() - nasłuchiwanie na wszystkich interfejsach
        addrinfo* res;

        if (getaddrinfo(nullptr, port, &hints, &res) != 0) {
            std::cerr << "getaddrinfo failed" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Tworzymy socket zgodny z parametrami z getaddrinfo
        listenSock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        // Przypisujemy socket do konkretnego adresu i portu
        bind(listenSock, res->ai_addr, static_cast<int>(res->ai_addrlen));
        // Rozpoczynamy nasłuchiwanie na sockecie
        listen(listenSock, SOMAXCONN);
        freeaddrinfo(res); // Zwalniamy strukturę addrinfo
        std::cout << "Manager listening on port " << port << std::endl;
    }

    ~Manager(){
        if (listenSock != INVALID_SOCKET) {
            closesocket(listenSock); //zamkniecie gniazda
        }
        WSACleanup(); //czyszczenie Winsock
    }


    //główna funkcja do komunikacji z workerami
    void run(int workerCount, uint64_t totalTasks){
        std::cout << "Waiting for " << workerCount << " workers to connect..." << std::endl;

        // Akceptujemy połączenia od pracowników
        for (int i = 0; i < workerCount; ++i) {
            SOCKET client = accept(listenSock, nullptr, nullptr);
            if (client != INVALID_SOCKET) {
                workers.push_back(client); // Dodajemy połączenie do listy
                std::cout << "Worker " << i << " connected." << std::endl;
            }
        }

        // Obliczamy ile haseł przypada na jednego pracownika
        uint64_t chunk = totalTasks / workers.size();
        uint64_t start = 0;

        // Rozdzielamy zadania między pracowników
        for (size_t i = 0; i < workers.size(); ++i) {
            uint64_t end;

            // Ostatni pracownik dostaje resztę zakresu
            if (i + 1 == workers.size()) {
                end = totalTasks;
            } else {
                end = start + chunk;
            }

            TaskRange r;
            r.start = start;
            r.end = end;

            sendRange(workers[i], r); // Wysyłamy zakres do pracownika

            start += chunk; // Przesuwamy początek na kolejny fragment
        }
        std::cout << "Distributed tasks among " << workers.size() << " workers." << std::endl;
    }

};

#endif // MANAGER_H
