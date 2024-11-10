//echo1.cpp
#include <iostream>
#include <cstring> // strlen
#include <arpa/inet.h> // inet_addr htons
#include <unistd.h> // socket bind connect send recv close
using namespace std;
int main()
{
    char buf[256];
    char msg[] = "Какой чудесный день, чтобы делать практику!\n";
    struct sockaddr_in self_addr;
    self_addr.sin_family = AF_INET;
    self_addr.sin_port = 0; // Автоматический выбор порта
    self_addr.sin_addr.s_addr = INADDR_ANY; // Принять соединения от любого адреса
    struct sockaddr_in srv_addr;
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(1234); // Порт сервера
    srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int s = socket(AF_INET, SOCK_STREAM, 0); //создает сокет для TCP-соединения
    if (s == -1) {
        cerr << "Error creating socket" << endl;
        return 1;
    }
    int e = bind(s, (struct sockaddr*)&self_addr, sizeof(self_addr)); //привязывает сокет к локальному адресу и порту
    if (e == -1) {
        cerr << "Error binding socket" << endl;
        close(s);
        return 1;
    }
    e = connect(s, (struct sockaddr*)&srv_addr, sizeof(srv_addr)); //подключает сокет к серверу по указанному адресу и порту
    if (e == -1) {
        cerr << "Error connecting socket" << endl;
        close(s);
        return 1;
    }
    e = send(s, msg, strlen(msg), 0); //отправляет сообщение серверу
    if (e == -1) {
        cerr << "Error sending socket" << endl;
        close(s);
        return 1;
    }
    cout << "Отправлено: " << msg; //выводит отправленное сообщение в консоль
    int rc = recv(s, buf, sizeof(buf), 0); // получает ответ от сервера и сохраняет его в буфере buf
    if (rc < 0) {
        cerr << "Error receiving data" << endl;
        close(s);
        return 1;
    }
    buf[rc] = '\0'; // добавляет завершающий нулевой символ в конец буфера
    cout << "Получено: " << buf; //выводит полученный ответ в консоль
    close(s); // закрывает сокет после завершения передачи данных
    return 0;
}
