#ifndef SERVER_H
#define SERVER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include <ctype.h>

#define SERV_TCP_PORT 49152  // DEFINING MACRO FOR PORT
#define LOCAL_HOST "127.0.0.1"
#define SUCCESS 0
#define BUFFER 100
#define SIZE 30

int checkCRCServer(char *, char *, char *, char *, char *, char *, int , int );

int check_num(char *);

#endif

