#ifndef KOMUNIKACJA_H
#define KOMUNIKACJA_H


#include <cstdint>
#include <winsock2.h>
#include <vector>
#pragma comment(lib, "Ws2_32.lib")

class Komunikacja
{
public:
    Komunikacja();
};

//Struktura opisująca początek i koniec zakresu do wypróbowania
//Znając alfabet oraz max długość hasła można każdej kombinacji przypisać indeks.
//Ta struktura mówi o pierwszym i ostatnim indeksie do wypróbowania.
struct TaskRange {
    uint64_t start;
    uint64_t end;
};

//Zamiana start i end z TaskRange na format gotowy do przesyłu (odwrócenie bitów)
//Funkcja htonl przyjmuje tylko 32bit więc trzeba numery rozłożyć na 2 części
std::vector<uint8_t> serializeRange(const TaskRange &r) {
    std::vector<uint8_t> buf(16);
    //Odwrócenie bitów w start
    uint64_t s = htonl((uint32_t)(r.start >> 32)); //odwracamy 32 bity po prawej
    s = (s << 32) | htonl((uint32_t)(r.start & 0xFFFFFFFF)); //przesuwamy w lewo i łączymy OR-em z odwróconym początkiem
    //odwrócenie bitów w end
    uint64_t e = htonl((uint32_t)(r.end >> 32));
    e = (e << 32) | htonl((uint32_t)(r.end & 0xFFFFFFFF)); //0xFFFFFFFF zeruje nam 32 bity po prawej
    memcpy(buf.data(), &s, 8);
    memcpy(buf.data() + 8, &e, 8);
    return buf;
}

//Wysyłanie spreparowanych wczesniej danych
bool sendAll(SOCKET sock, const uint8_t *data, size_t len) {
    size_t sent = 0;
    while (sent < len) {
        int n = send(sock, (const char*)(data + sent), (int)(len - sent), 0);
        if (n == SOCKET_ERROR) return false;
        sent += n;
    }
    return true;
}

//odbieranie dancyh o określonej długości
bool recvAll(SOCKET sock, uint8_t *data, size_t len) {
    size_t recvd = 0;
    while (recvd < len) {
        int n = recv(sock, (char*)(data + recvd), (int)(len - recvd), 0);
        if (n <= 0) return false;
        recvd += n;
    }
    return true;
}

//Serializacja + Wysłanie zakresu do zbadania
bool sendRange(SOCKET sock, const TaskRange &r) {
    auto buf = serializeRange(r);
    return sendAll(sock, buf.data(), buf.size());
}

//Odebranie i deserializacja pakietu z zakresem
bool recvRange(SOCKET sock, TaskRange &r) {
    uint8_t buf[16];
    if (!recvAll(sock, buf, 16)) return false;
    uint64_t s, e;
    memcpy(&s, buf, 8);
    memcpy(&e, buf + 8, 8);
    uint64_t sh = ntohl((uint32_t)(s >> 32)); //operacje odwrotne niż przy serializacji
    sh = (sh << 32) | ntohl((uint32_t)(s & 0xFFFFFFFF));
    uint64_t eh = ntohl((uint32_t)(e >> 32));
    eh = (eh << 32) | ntohl((uint32_t)(e & 0xFFFFFFFF));
    r.start = sh;
    r.end = eh;
    return true;
}



#endif // KOMUNIKACJA_H
