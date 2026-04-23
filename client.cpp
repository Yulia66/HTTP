  #include <arpa/inet.h>
  #include <netinet/in.h>
  #include <sys/socket.h>
  #include <unistd.h>
  #include <cstring>
  #include <iostream>

  #define PORT 8080

  int main() {

    int client = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    if(inet_pton(AF_INET, "127.0.0.1",&serv_addr.sin_addr) <= 0){
      std::cerr << "Invalid address / Address not supported" << std::endl;
      return -1;
    }

    connect(client,(struct sockaddr *)&serv_addr, sizeof(serv_addr));

    std::cout << "Подключено к серверу!" << std::endl;

    //char *hello = "hello from client";
   // while(true){
      std::string hello;
      hello = 
        "POST /tools/nmap HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: 28\r\n"
        "\r\n"
        "{\"target\":\"google.com\"}";  // ✅ Правильный JSON

      std::string cl;
      cl = 
        "GET /tools/0 HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Connection: close\r\n"
        "\r\n";  // ✅ Правильный JSON
      send(client,hello.c_str(), strlen(hello.c_str()),0 );
      std::cout <<"Message sent"<< std::endl;
      char buffer[1024];
      int bytes =recv(client,buffer,sizeof(buffer)-1,0);
      //std::cout <<buffer  << std::endl;



    
    for(int i=0; i< 12; i++){
      sleep(5);
      send(client,cl.c_str(), strlen(cl.c_str()),0 );
      std::cout <<"Message sent"<< std::endl;
     // После send
      char buffer_2[1024];
      int bytes_2 = recv(client, buffer_2, sizeof(buffer_2)-1, 0);

      if (bytes_2 > 0) {
          buffer_2[bytes_2] = '\0';           // ← главное исправление
          //std::cout << buffer_2 << std::endl;
      } else if (bytes_2 == 0) {
          std::cout << "Сервер закрыл соединение" << std::endl;
      } else {
          std::cout << "Ошибка при чтении" << std::endl;
      }

      if(std::string(buffer_2).find("completed")!= std::string::npos){
        std::cout << "✅ Задача выполнена!\n" << std::string(buffer_2) << std::endl;
            break;
        } else if (std::string(buffer_2).find("failed") != std::string::npos) {
            std::cout << "❌ Задача провалилась!\n" << std::string(buffer_2) << std::endl;
            break;
        } else {
            std::cout << "⏳ Попытка " << i+1 << "/12: задача ещё выполняется..." << std::endl;
        }
    }
      /*char buffer[1024];
      int bytes =recv(client,buffer,sizeof(buffer)-1,0);
      if (bytes > 0) {
      buffer[bytes] = '\0';  // ← ВАЖНО! Добавляем нулевой символ
      std::cout << buffer;
    }*/
//}


    return 0;
  }

