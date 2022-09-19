                       /* TCP/IP server side socket with Cyclic Redundancy Check(CRC) to check if the data has error or not */


// including user defined header files
#include <server.h>


/* This is the main function 
 * creating a tcp/ip socket and connecting it with the server side with CRC 
 * This function has parameters argc which stores the number of command line arguments of type integer
   and argv is array of character pointers listing all the arguments
 */

int main(int argc, char **argv)
{
	int sockfd,newsockfd,clength;		/* declaring the variables for file descriptor,
			                  	   new file descriptor and for client length */
	struct sockaddr_in serv_addr,cli_addr;	// declaring the sockaddr_in structure for server and client address
	char final_cpy[BUFFER];	//creating the final_cpy variable for reciever side 
	char final_data[BUFFER];	//creating temp_data char array for reciver side
	int  keylen=0,msglen=0;
	char input[BUFFER], temp_data[SIZE],quot[BUFFER],rem[SIZE];	//input buffer, temp_data buffer, quotient buffer, remainder size
	char key[SIZE],key_cpy[SIZE];	//key or divisor char arrays
		
	
	 pid_t childpid; 	// child pid
	 int status;
	 	
	
	/* creating a socket with three parameters (communication domain, type, protocol)
         * Domain -> AF_INET -- IPv4 (AF_INET6 for IPv6)
         * Type -> – SOCK_STREAM -- TCP
                   – SOCK_DGRAM -- UDP
         * Protocol -> 0 (single protocol exists to support a particular socket type
                       within a given protocol family, in which case protocol can be specified as 0.
         */
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(!sockfd){
		perror("Error in opening socket");//error condition
		exit(EXIT_FAILURE);
	}
	else
	printf("Socket created\n");
	
	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;	// address family, AF_INET for IPv4 protocol
	serv_addr.sin_addr.s_addr=INADDR_ANY;	// source address, INADDR_ANY to choose the local address
	serv_addr.sin_port=htons(SERV_TCP_PORT);	/* converting tcp port defined in the MACRO 
       						           from host byte to network byte order */
	
	
	
	/* bind()reserves port for the socket.
  	 * It has three parameters socket identifier, struct sockaadr_in, 
  	   the port of the machine and size of the sockaddr struucture
  	 * sockfd -> file descriptor socket() returned
  	 * my_addr -> – struct sockaddr_in for IPv4
		      – casting (struct sockaddr_in*) to (struct sockaddr*)
  	 * addrlen -> size of the sockaddr_in 
  	 */
	if (bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < SUCCESS){
		perror("failed to bind");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Binded at port: %d",SERV_TCP_PORT);
	}
	
	/* listen for incoming connections
	 * sockfd -> file descriptor socket() returned
	 * backlog -> number of pending connections to queue
	 */
	if (listen(sockfd,5) < SUCCESS){
		perror("error in listen.");
		exit(EXIT_FAILURE);
	}
	else 
	{
		printf("\nListening....\n");
	}
	
	clength=sizeof(cli_addr);	// sizeof client address is saved in clength variable
	
	
	/* The  accept() system  call is used with connection-based socket types
         * The argument addr is a pointer to a sockaddr structure.
         * The addrlen argument is a value-result argument: the caller must initialize it to contain the size (in bytes) of the structure pointed to by addr; 
           on return it will contain the actual size of the client address.
         */
        while(1){
        
       	newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
	
	if(newsockfd < SUCCESS){
		perror("error in accept");
	}
	if ((childpid = fork()) == 0){
		
	
		
	
	memset(&final_data, 0, BUFFER);
	memset(&key, 0, BUFFER);
	memset(&input, 0, BUFFER);
	
	read(newsockfd,final_data,BUFFER);	//reading the final data(binary + remainder) from client side
	read(newsockfd,key,BUFFER);	//reading the divisor from client side
	read(newsockfd,input,BUFFER);	//reading the binary data from client side

	keylen=strlen(key);
	msglen=strlen(input);

	int flag=0;
    	 
	printf("\n");
	printf("the received data: %s\n",final_data);	// displays the final data from client side to server side
	
	printf("the actual data: %s\n",input);
	
	printf("the length: %d\n",msglen);
	
	//printf("enter data to check: ");	// //prompt a user to enter the received data from client
	//scanf("%s",final_cpy);	//reading the data
	strcpy(final_cpy,final_data);	
	
/* Cyclic Redundancy Check(CRC) implementation on server side */
	
	checkCRCServer(final_cpy, temp_data, rem, quot, key, key_cpy, keylen, msglen);
	strcpy(rem,temp_data);	//again copying the temp_data to remainder
	
	/* displays the quotient in screen */
	printf("\nQuotient is ");
	for (int msglen_itr=0;msglen_itr<msglen;msglen_itr++)
		printf("%c",quot[msglen_itr]);
	 
	/* displays the Remainder in screen */
	printf("\nRemainder is ");
	for (int divr_itr=0;divr_itr<keylen-1;divr_itr++)
		printf("%c",rem[divr_itr]);
	 
	 flag=0;	// initializing the flag to 0
	 
	 for(int key_itr=0;key_itr<keylen-1;key_itr++)	/*loop will iterate for keylength-1 times */
	 {
	 	if(rem[key_itr]=='1'){	/* in array of remaiinder if 1 is present, flag 
	 				  is 1 or else it will be 0 */
	 		flag=1;
	 		break;
	 		}
	 	else
	 		flag=0;
	 }
	
	

	write(newsockfd, quot, BUFFER);	// writing the server response(quotient) to the client
	write(newsockfd, rem, SIZE);	// writing the server response(remainder) to the client
	
	/* if flag is 0 the message has no error or else the message has error */
	if(flag==0){
	 	printf("\n No error\n");
	 	write(newsockfd,"Data received has no error",27);	// writing the server response to the client
	 	}
	else{
		printf("\nERROR\n");
		write(newsockfd,"Data received has an error",27);	// writing the server response to the client
	}
	
	
	/* Below block is to send the negative testing */

	memset(&final_data, 0, BUFFER);
	memset(&final_cpy, 0, BUFFER);
	read(newsockfd,final_data,BUFFER);	//reading the final data(binary + remainder) from client side
	
	//printf("\ntemp1=%s\n",final_data);
	if(check_num(final_data) == SUCCESS){
	
	
	keylen=strlen(key);
	msglen=strlen(input);

	flag=0;

	printf("\n");
	printf("the received data: %s\n",final_data);	// displays the final data from client side to server side
	printf("the actual data: %s\n",input);

	strcpy(final_cpy,final_data);	
	memset(&temp_data, 0, BUFFER);
	//memset(&rem, 0, BUFFER);
	//memset(&quot, 0, BUFFER);
	checkCRCServer(final_cpy, temp_data, rem, quot, key, key_cpy, keylen, msglen);
	
	strcpy(rem,temp_data);	//again copying the temp_data to remainder

	/* displays the quotient in screen */

	printf("\nQuotient is ");

	for (int msglen_itr=0;msglen_itr<msglen;msglen_itr++)

		printf("%c",quot[msglen_itr]);
	 
	/* displays the Remainder in screen */

	printf("\nRemainder is ");

	for (int divr_itr=0;divr_itr<keylen-1;divr_itr++)

		printf("%c",rem[divr_itr]);

	 flag=0;	// initializing the flag to 0

	 for(int key_itr=0;key_itr<keylen-1;key_itr++)	/*loop will iterate for keylength-1 times */

	 {

	 	if(rem[key_itr]=='1')	{	/* in array of remaiinder if 1 is present, flag 
	 				  is 1 or else it will be 0 */
	 		flag=1;
	 		break;
	}
	 	else
	 		flag=0;
	 }

	write(newsockfd, quot, BUFFER);	// writing the server response(quotient) to the client

	write(newsockfd, rem, SIZE);	// writing the server response(remainder) to the client

	

	/* if flag is 0 the message has no error or else the message has error */

	if(flag==0){

	 	printf("\n No error\n");
	 	write(newsockfd,"Data received has no error",27);	// writing the server response to the client
	 	}

	else{

		printf("\nERROR\n");
		write(newsockfd,"Data received has an error",27);	// writing the server response to the client

	}
}
/* ends the negative testing */
	_exit(EXIT_SUCCESS);
	
}

}

	close(sockfd);	//closing the socket
	
	return 0;
}


