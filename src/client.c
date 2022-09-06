                            /* TCP/IP client side socket with Cyclic Redundancy Check(CRC) to check if the data has error or not */
                            
// including user defined header files
#include <client.h>


/* This is the main function 
 * creating a tcp/ip socket and connecting it with the server side with CRC 
 * This function has parameters argc which stores the number of command line arguments of type integer
   and argv is array of character pointers listing all the arguments
 */
int main(int argc,char * * argv)
{


 int option;
    printf("1. Register \n2. Login\n\n");
    scanf("%d",&option);

    getchar();
    
    if(option == 1)
    {                      
         registration();  
    }
    
    if(option==2)
    {  
  	 login();
    }
       
       
       int sockfd;	// file descriptor to store socket ID of type int
       struct sockaddr_in serv_addr;	// declaring the sockaddr_in structure
        
       char str[BUFFER];
       char r[SIZE],s[BUFFER];	//remainder, status char arrays
       int i,j;	                                  //loop variables 
       int keylen=0,msglen=0;	       //keylength, msglength
       char input[BUFFER],temp[SIZE],quot[BUFFER],rem[SIZE];
       char key[SIZE],key1[SIZE];
       
       
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
       
       
       serv_addr.sin_family=AF_INET;	// address family, AF_INET for IPv4 protocol
       serv_addr.sin_addr.s_addr=inet_addr(LOCAL_HOST);	// address of the local host
       serv_addr.sin_port=htons(SERV_TCP_PORT);	/* converting tcp port defined in the MACRO 
       						  from host byte to network byte order */
       						  
       						  
       /* The  connect() system call connects the socket referred to by the file descriptor 
          sockfd to the address specified by addr. 
        * The addrlen argument specifies the size of addr. 
        * The format of the address in addr is determined by the address space of the socket sockfd
        */				  
        if (connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < SUCCESS )
        {
        	perror("Error in connection");
        	exit(EXIT_FAILURE);
        }
        else 
        printf("Connected to server\n");
      
      
       
     	printf("Enter Data: ");	    // prompt the client to enter a string
     	scanf("%s",str);	 // reading the entered string
     	printf("\n");
	char *binary;	// declaring character pointer to store the binary
	binary = stringToBinary(str);	// calling the stringToBinry function for conversion of the string
	printf("THE BINARY OF THE FOLLOWING STRING:    ");
	puts(binary);	// displays the binary of the follwing string
	
	
/* Cyclic Redundancy Check(CRC) implementation on client side */
	
	strcpy(input,binary);	// copying the binary to input variable
	
	
	printf("\nEnter Key in binary: ");       //prompt a client to enter the divisor
	
	flag:
	scanf("%s",key);       //reading the divisor
		
	for(i=0;key[i]!='\0';i++)					/* key validation, takes input
									   only in binary */ 
	{
		if((key[i] == '0') || (key[i] == '1'))
		{
			printf("The key is valid");
			break;
			
		}
		else
		{
			printf("The key is not valid\n");
			printf("Enter the key in binary");
			goto flag; 
		}
	}



	
	printf("\n");
	keylen=strlen(key);	// calculating the key length
	msglen=strlen(input);	// calculating the message length
	strcpy(key1,key);	// copying the key in key1
	
	/* appending key-1 zeros in the message data */
	for (i=0;i<keylen-1;i++) {
		input[msglen+i]='0';
	}
	
	/* storing the input in temp variable for doing division based on length key */
	for (i=0;i<keylen;i++)
	 temp[i]=input[i];
	 
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
		rem[keylen-1]=input[i+keylen];	// character variable rem with size of key length -1
		strcpy(temp,rem);	// copying the remainder in temp
	}
	strcpy(rem,temp);	// again copying the temp to remainder
	
	char sub[100];	        // declaring the variable sub for storing binary appended with CRC remainder
	
	/* displays the quotient in screen */
	printf("\nQuotient is ");
	for (i=0;i<msglen;i++)
	 printf("%c",quot[i]);
	 
	/* displays the remainder in screen */  
	printf("\nRemainder is ");
	for (i=0;i<keylen-1;i++)
	 printf("%c",rem[i]);
	
	
	/* Final data calculation by appending the input and remainder */
	for (i=0;i<msglen;i++)
	 {
	 	//printf("%c",input[i]);
	 	sub[i]=input[i];
	 }
	for (i=0;i<keylen-1;i++)
	 {
	 	//printf("%c",rem[i]);
	 	sub[msglen+i]=rem[i];
    	 }

/* End of Cyclic Redundancy Check(CRC) implementation on client side */    

	 
    	 printf("\nFinal Data with appended bits to be sent: ");
    	 for(int i=0;i<msglen+(keylen-1);i++)
    	 printf("%c",sub[i]);	// printing the final data(binary + CRC remainder)
    	 
    
         write(sockfd,sub,BUFFER);         // writing the data(binary + remainder) in socket file descriptor
         write(sockfd,key,BUFFER);	        // writing the CRC remainder in socket file descriptor
         write(sockfd,binary,BUFFER);	// writing the binary data in socket file descriptor
         printf("\n");
         printf("\nServer result:");
       
         read(sockfd,quot,BUFFER);	   // Readimg the quotient from socket file descriptor
         read(sockfd,r,SIZE);	// Reading the remainder from socket file descriptor
         read(sockfd,s,SIZE);	// Reading the status from socket file descriptor
       
         printf("\n quotient= %s",quot);
         printf("\n rem= %s",r);
         printf("\nStatus= %s\n",s);
       
       
       	 close(sockfd);	  // closing the socket
       	 
       	 free(binary);
         return 0;
}
