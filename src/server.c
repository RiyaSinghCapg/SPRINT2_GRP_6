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
	char temp2[BUFFER];	//creating the temp2 variable for reciever side 
	char temp1[BUFFER];	//creating temp char array for reciver side
	int i,j,keylen=0,msglen=0;
	char input[BUFFER], temp[SIZE],quot[BUFFER],rem[SIZE];	//input buffer, temp buffer, quotient buffer, remainder size
	char key[SIZE],key1[SIZE];	//key or divisor char arrays
		

		
	
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
	printf("Binded at port: %d",SERV_TCP_PORT);
	
	
	/* listen for incoming connections
	 * sockfd -> file descriptor socket() returned
	 * backlog -> number of pending connections to queue
	 */
	if (listen(sockfd,5) < SUCCESS){
		perror("error in listen.");
		exit(EXIT_FAILURE);
	}
	else 
	printf("\nListening....\n");
	
	
	clength=sizeof(cli_addr);	// sizeof client address is saved in clength variable
	
	
	/* The  accept() system  call is used with connection-based socket types
         * The argument addr is a pointer to a sockaddr structure.
         * The addrlen argument is a value-result argument: the caller must initialize it to contain the size (in bytes) of the structure pointed to by addr; 
           on return it will contain the actual size of the client address.
         */
	newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clength);
	
	if(newsockfd < SUCCESS){
		perror("error in accept");
	}
	
	
	
	read(newsockfd,temp1,BUFFER);	//reading the final data(binary + remainder) from client side
	read(newsockfd,key,BUFFER);	//reading the divisor from client side
	read(newsockfd,input,BUFFER);	//reading the binary data from client side

	keylen=strlen(key);
	msglen=strlen(input);

	int flag=0;
    	 
	printf("\n");
	printf("the received data: %s\n",temp1);	// displays the final data from client side to server side
	//printf("the key: %s\n",key);
	printf("the actual data: %s\n",input);
	
	printf("the length: %d\n",msglen);
	
	printf("enter data to check: ");	// //prompt a user to enter the received data from client
	scanf("%s",temp2);	//reading the data
		
	
/* Cyclic Redundancy Check(CRC) implementation on server side */
	
	/*storing the input in temp variable for do division based on length key */
	for (i=0;i<keylen;i++)
	 temp[i]=temp2[i];
	 
	/* Calculating the quotient and remainder by doing Exclusive-OR */ 
	for (i=0;i<msglen;i++) {
		quot[i]=temp[0];
		if(quot[i]=='0')
		 for (j=0;j<keylen;j++)
		 key[j]='0'; else
		 for (j=0;j<keylen;j++)
		 key[j]=key1[j];
		for (j=keylen-1;j>0;j--) {
			if(temp[j]==key[j])
			 rem[j-1]='0'; else
			 rem[j-1]='1';
		}
		
	rem[keylen-1]=temp2[i+keylen];	// character variable rem with size of key length -1
		strcpy(temp,rem);	// copying the remainder in temp
	}
	
	strcpy(rem,temp);	//again copying the temp to remainder
	
	/* displays the quotient in screen */
	printf("\nQuotient is ");
	for (i=0;i<msglen;i++)
		printf("%c",quot[i]);
	 
	/* displays the Remainder in screen */
	printf("\nRemainder is ");
	for (i=0;i<keylen-1;i++)
		printf("%c",rem[i]);
	 
	 flag=0;	// initializing the flag to 0
	 
	 for(i=0;i<keylen-1;i++)	/*loop will iterate for keylength-1 times */
	 {
	 	if(rem[i]=='1')		/* in array of remaiinder if 1 is present, flag 
	 				  is 1 or else it will be 0 */
	 		flag=1;
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

	close(sockfd);	//closing the socket
	return 0;
}
