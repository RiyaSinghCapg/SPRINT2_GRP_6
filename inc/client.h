#ifndef CLIENT_H
#define CLIENT_H


#include<stdio.h>
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
#define FAIL 1
#define BUFFER 100
#define SIZE 30
#define BYTE_SIZE 8	// 1 Byte size is 8 bits

/* function declaration of string to binary */
int stringToBinary(char*, char* );

int CRCgenerator(char *, char *, char *, char *, char *, char *, int , int );

void login (void);

void registration(void);



#endif
