//server.cpp
#include <iostream>
#include <unistd.h> // socket bind connect send recv close
#include <arpa/inet.h> // htons
int main()
{
    int PORT = 1234;
    int buf_size = 256;
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    int addrlen = sizeof(address);
    char buf[buf_size];

    int s = socket(AF_INET, SOCK_STREAM, 0); // создает сокет для TCP-соединения

    bind(s, (struct sockaddr *)&address, sizeof(address)); // привязывает сокет к локальному адресу и порту
    listen(s, 3); // переводит сокет в режим прослушивания и указывает максимальное количество ожидающих соединений

    while (true) {
        // принимает входящее соединение от клиента и создает новый сокет new_socket для связи
        int new_socket = accept(s, (struct sockaddr *)&address, (socklen_t*)&addrlen); 
        recv(new_socket, buf, buf_size, 0); // получает данные от клиента и сохраняет их в буфере buf
        send(new_socket, buf, buf_size, 0); // отправляет данные обратно клиенту
        std::cout << buf; // выводит полученные данные
        close(new_socket); // закрывает сокет
    }
    return 0;
}
