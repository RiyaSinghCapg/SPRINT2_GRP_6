#ifndef CLIENT_H
#define CLIENT_H


#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>


#define SERV_TCP_PORT 49152  // DEFINING MACRO FOR PORT
#define LOCAL_HOST "127.0.0.1"
#define SUCCESS 0
#define BUFFER 100
#define SIZE 30


/* function declaration of string to binary */
char* stringToBinary(char* );

void login (void);

void registration(void);



#endif
