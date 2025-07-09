#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <algorithm>

#pragma comment(lib, "Ws2_32.lib")
class Komunikacja
{
public:
    struct TaskRange
    {
        uint64_t start;
        uint64_t end;
    };

    Komunikacja() { initWinsock(); }
    ~Komunikacja() { cleanupWinsock(); }

    // Tworzy socket nasłuchujący na podanym porcie (IPv4, TCP)
    SOCKET createListener(const char* port);

    // Akceptuje jedno połączenie na listenerze
    SOCKET acceptConnection(SOCKET listenSock);

    // Tworzy połączenie klienta do address:port
    SOCKET createClient(const char* address, const char* port);

    // Wysyła plik, najpierw rozmiar, potem dane
    bool sendFile(SOCKET sock, const std::string& path);

    // Odbiera plik, zapisuje pod path (hardkodowana ścieżka u workera)
    bool recvFile(SOCKET sock, const std::string& path);

    //Wysyłanie stringów
    bool sendString(SOCKET sock, const std::string& s);

    //Odbieranie stringów
    bool recvString(SOCKET sock, std::string& s);

    bool sendUInt8(SOCKET sock, uint8_t v) { return ::send(sock,(char*)&v,1,0)==1; }
    bool recvUInt8(SOCKET sock, uint8_t&v) { return ::recv(sock,(char*)&v,1,0)==1; }

    bool sendUInt64(SOCKET sock, uint64_t v) {
        uint64_t n=htonll(v); return ::send(sock,(char*)&n,sizeof(n),0)==sizeof(n);
    }
    bool recvUInt64(SOCKET sock, uint64_t&v){
        uint64_t n; if(::recv(sock,(char*)&n,sizeof(n),0)!=sizeof(n))return false; v=ntohll(n); return true;
    }

private:
    void initWinsock() {
        WSADATA wsa{};
        if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    void cleanupWinsock() {
        WSACleanup();
    }
};
