#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h>
#include "err.h"

#ifndef NETWORKING_H
#define NETWORKING_H

#define PORT "19230"
#define BUFFER_SIZE 1024
union semun { 
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
                            /* (Linux-specific) */
 };

int server_setup();
int client_tcp_handshake(char*server_address);
int server_tcp_handshake(int listen_socket);
void sendSong(int server_socket, char* song);

#endif