#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include "parser.h"
#include <cstring>
#include <iostream>
#include "http_handler.h"
#include "parser.h"

#define PORT 8080




int main() {
 int server = socket(AF_INET, SOCK_STREAM, 0);
if(server < 0){
  throw std::runtime_error("server not found");
}

 sockaddr_in serverAddress;
 serverAddress.sin_family = AF_INET;
 serverAddress.sin_port = htons(8080); // преобразование порта в сетевой порядок байт
 serverAddress.sin_addr.s_addr = INADDR_ANY;


  int yes = 1;
  if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
      perror("setsockopt");
      exit(1);
  }
 bind(server, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

 listen(server, 5);
 std::cout <<  "Сервер запущен на порту 8080..." << std::endl;


 sockaddr_in clientAddress;
 socklen_t clientSize = sizeof(clientAddress);

 while(true){
   int client = accept(server,(sockaddr*)&clientAddress,&clientSize);
   //const char* message = "Hello from server!";
   while(true){
    char buffer[1024];
    int bytes =recv(client,buffer,sizeof(buffer)-1,0);
    std::string message;

    if (bytes > 0) {
    buffer[bytes] = '\0';  // ← ВАЖНО! Добавляем нулевой символ
    ParsedHTTP parsed = parse(std::string(buffer));
    message = handle_http_request(parsed);
    //std::cout << buffer;
    
    }
    if(bytes == 0){
     std::cout << "Клиент отключился"<< std::endl;
     break;
    }
    if(bytes < 0){
     break;
    }
     send(client,message.c_str(), strlen(message.c_str()),0 );
    
    //close(client);  // ← ВАЖНО! Освобождаем файловый дескриптор
   }
  
  
  }

  return 0;
}

