#include "connect.h"

int client_tcp_handshake(char * server_address) {
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  getaddrinfo(server_address, PORT, hints, &results); 
  int serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  err(serverd, "socket not created in client \n");
  bind(serverd, results->ai_addr, results->ai_addrlen);
  connect(serverd, results->ai_addr, results->ai_addrlen);
  free(hints);
  freeaddrinfo(results);

  return serverd;
}

int server_tcp_handshake(int listen_socket){
    int client_socket;
    socklen_t sock_size;
    struct sockaddr_storage client_address;
    sock_size = sizeof(client_address);
    client_socket = accept(listen_socket,(struct sockaddr *)&client_address, &sock_size);
    err(client_socket, "socket not accepted in server \n");
    return client_socket;
}

int server_setup() {
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; 
  hints->ai_flags = AI_PASSIVE; 
  getaddrinfo(NULL, PORT, hints, &results);  

  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  err(clientd, "socket not created in server \n");

  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt,"sockopt error \n");
  
  bind(clientd, results->ai_addr, results->ai_addrlen);
  listen(clientd, 10);

  free(hints);
  freeaddrinfo(results);
  
  return clientd;
}

void sendSong(int server_socket, char* song) {
  write(server_socket, song, strlen(song + 1));
}