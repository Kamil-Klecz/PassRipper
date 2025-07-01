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

    struct TaskRange {
        uint64_t start;
        uint64_t end;
    };

    Komunikacja() { initWinsock(); }
    ~Komunikacja() { cleanupWinsock(); }

    // Tworzy socket nasłuchujący na podanym porcie (IPv4, TCP)
    SOCKET createListener(const char* port) {
        addrinfo hints{};
        hints.ai_family   = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags    = AI_PASSIVE;

        addrinfo* res;
        if (getaddrinfo(nullptr, port, &hints, &res) != 0) {
            std::cerr << "getaddrinfo failed" << std::endl;
            return INVALID_SOCKET;
        }

        SOCKET listenSock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenSock == INVALID_SOCKET) {
            std::cerr << "socket creation failed" << std::endl;
            freeaddrinfo(res);
            return INVALID_SOCKET;
        }

        if (::bind(listenSock, res->ai_addr, int(res->ai_addrlen)) == SOCKET_ERROR) {
            std::cerr << "bind failed, err=" << WSAGetLastError() << std::endl;
            closesocket(listenSock);
            freeaddrinfo(res);
            return INVALID_SOCKET;
        }


        freeaddrinfo(res);

        if (listen(listenSock, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
            closesocket(listenSock);
            return INVALID_SOCKET;
        }

        return listenSock;
    }

    // Akceptuje jedno połączenie na listenerze
    SOCKET acceptConnection(SOCKET listenSock) {
        std::cout<<"Comm: Accepting commection..." <<std::endl;
        SOCKET client = accept(listenSock, nullptr, nullptr);
        if (client == INVALID_SOCKET) {
            std::cerr << "accept failed" << std::endl;
        }
        return client;
    }

    // Tworzy połączenie klienta do address:port
    SOCKET createClient(const char* address, const char* port) {
        addrinfo hints{};
        hints.ai_family   = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        addrinfo* res;
        if (getaddrinfo(address, port, &hints, &res) != 0) {
            std::cerr << "getaddrinfo failed" << std::endl;
            return INVALID_SOCKET;
        }

        SOCKET sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock == INVALID_SOCKET) {
            std::cerr << "socket creation failed" << std::endl;
            freeaddrinfo(res);
            return INVALID_SOCKET;
        }

        if (connect(sock, res->ai_addr, static_cast<int>(res->ai_addrlen)) == SOCKET_ERROR) {
            std::cerr << "connect failed" << std::endl;
            closesocket(sock);
            freeaddrinfo(res);
            return INVALID_SOCKET;
        }

        freeaddrinfo(res);
        return sock;
    }

    // Wysyła plik (hardkodowana ścieżka u managera), najpierw rozmiar, potem dane
    bool sendFile(SOCKET sock, const std::string& path) {
        HANDLE h = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h == INVALID_HANDLE_VALUE) {
            std::cerr << "sendFile: CreateFileA failed, err=" << GetLastError() << std::endl;
            return false;
        }
        LARGE_INTEGER size; GetFileSizeEx(h, &size);
        uint64_t netSize = htonll(static_cast<uint64_t>(size.QuadPart));
        if (::send(sock, reinterpret_cast<const char*>(&netSize), sizeof(netSize), 0) != sizeof(netSize)) {
            std::cerr << "sendFile: send size failed, err=" << WSAGetLastError() << std::endl;
            CloseHandle(h);
            return false;
        }
        std::vector<char> buf(8192);
        DWORD read;
        while (ReadFile(h, buf.data(), (DWORD)buf.size(), &read, NULL) && read > 0) {
            if (::send(sock, buf.data(), read, 0) == SOCKET_ERROR) {
                std::cerr << "sendFile: send data failed, err=" << WSAGetLastError() << std::endl;
                CloseHandle(h);
                return false;
            }
        }
        CloseHandle(h);
        return true;
    }

    // Odbiera plik, zapisuje pod path (hardkodowana ścieżka u workera)
    bool recvFile(SOCKET sock, const std::string& path) {
        uint64_t netSize;
        if (::recv(sock, reinterpret_cast<char*>(&netSize), sizeof(netSize), 0) != sizeof(netSize)) {
            std::cerr << "recvFile: recv size failed, err=" << WSAGetLastError() << std::endl;
            return false;
        }
        uint64_t size = ntohll(netSize);
        HANDLE h = CreateFileA(path.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (h == INVALID_HANDLE_VALUE) {
            std::cerr << "recvFile: CreateFileA failed, err=" << GetLastError() << std::endl;
            return false;
        }
        std::vector<char> buf(8192);
        uint64_t received = 0;
        while (received < size) {
            int toRead = static_cast<int>(std::min<uint64_t>(buf.size(), size - received));
            int r = ::recv(sock, buf.data(), toRead, 0);
            if (r < 0) {
                std::cerr << "recvFile: recv data failed, err=" << WSAGetLastError() << std::endl;
                CloseHandle(h);
                return false;
            } else if (r == 0) {
                // połączenie zostało zamknięte przez nadawcę
                break;
            }
            DWORD written;
            if (!WriteFile(h, buf.data(), r, &written, NULL) || written != (DWORD)r) {
                std::cerr << "recvFile: WriteFile failed, err=" << GetLastError() << std::endl;
                CloseHandle(h);
                return false;
            }
            received += r;
        }
        CloseHandle(h);
        return true;
    }
    //Wysyłanie stringów itp
    bool sendString(SOCKET sock, const std::string& s) {
        uint32_t len = htonl((uint32_t)s.size());
        if (::send(sock, (char*)&len, sizeof(len),0)!=sizeof(len)) return false;
        return ::send(sock, s.data(), s.size(),0)==(int)s.size();
    }

    bool recvString(SOCKET sock, std::string& s) {
        uint32_t netLen; if(::recv(sock,(char*)&netLen,sizeof(netLen),0)!=sizeof(netLen))return false;
        uint32_t len=ntohl(netLen);
        s.resize(len);
        return ::recv(sock,&s[0],len,0)==(int)len;
    }

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
