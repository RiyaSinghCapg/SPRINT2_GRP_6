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
       int keylen=0,msglen=0;	       //keylength, msglength
       char bin_input[BUFFER],temp_input[SIZE],quot[BUFFER],rem[SIZE];
       char key[SIZE],key_cpy[SIZE];
       int choice;
       int str2bin=0;
       
       
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
	{
		printf("Socket created\n");
        }
       
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
        {
                printf("Connected to server\n");
           
        }
        
        
        
     	printf("Enter Data: ");	    // prompt the client to enter a string
     	scanf("%s",str);	 // reading the entered string
     	printf("\n");
     	size_t len = strlen(str);	//length of the string
	char *binary = NULL;	// declaring character pointer to store the binary
	binary = (char *)malloc(len*BYTE_SIZE + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    	binary[0] = '\0';
	str2bin = stringToBinary(str,binary);	// calling the stringToBinry function for conversion of the string
	if(str2bin == 0)
		printf("String is NULL");
	printf("THE BINARY OF THE FOLLOWING STRING:    ");
	
	puts(binary);	// displays the binary of the follwing string
	
	

	
	strcpy(bin_input,binary);	// copying the binary to bin_input variable
	
	
	  printf("\nEnter Key in binary: ");       //prompt a client to enter the divisor
	
	flag:
	scanf("%s",key);       //reading the divisor
		
	for(int key_itr=0;key[key_itr]!='\0';key_itr++)					/* key validation, takes bin_input
									   only in binary */ 
	{
		if((key[key_itr] == '0') || (key[key_itr] == '1'))
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


/* Cyclic Redundancy Check(CRC) implementation on client side */
	
	printf("\n");
	keylen=strlen(key);	// calculating the key length
	msglen=strlen(bin_input);	// calculating the message length
	strcpy(key_cpy,key);	// copying the key in key_cpy
	
/* Generating CRC  bits in the client side */
	CRCgenerator(temp_input,bin_input,rem,quot,key,key_cpy,keylen,msglen);
	strcpy(rem,temp_input);	// again copying the temp_input to remainder
	
	char final_result[BUFFER];	        // declaring the variable final_result for storing binary appended with CRC remainder
	
	/* displays the quotient in screen */
	printf("\nQuotient is ");
	for (int msglen_itr=0; msglen_itr<msglen; msglen_itr++)
	 printf("%c",quot[msglen_itr]);
	 
	/* displays the remainder in screen */  
	printf("\nRemainder is ");
	for (int divr_itr=0;divr_itr<keylen-1;divr_itr++)
	 printf("%c",rem[divr_itr]);
	
	
	/* Final data calculation by appending the bin_input and remainder */
	for (int msglen_itr=0;msglen_itr<msglen;msglen_itr++)
	 {
	 	//printf("%c",bin_input[i]);
	 	final_result[msglen_itr]=bin_input[msglen_itr];
	 }
	for (int divr_itr=0;divr_itr<keylen-1;divr_itr++)
	 {
	 	//printf("%c",rem[i]);
	 	final_result[msglen+divr_itr]=rem[divr_itr];
    	 }

/* End of Cyclic Redundancy Check(CRC) implementation on client side */    

	 
    	 printf("\nFinal Data with appended bits to be sent: ");
    	 for(int final_data=0; final_data<msglen+(keylen-1); final_data++)
    	 printf("%c",final_result[final_data]);	// printing the final data(binary + CRC remainder)
    	 
    
         write(sockfd,final_result,BUFFER);         // writing the data(binary + remainder) in socket file descriptor
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
         
         /* Negative testing */
        printf("\n Earlier final data: %s",final_result);
	printf("\n Do you want to change the final data to get tested for negative(0/1): ");
	scanf("%d",&choice);
	if(choice > 0){
	if(final_result[strlen(final_result)-2] == '0'){
	final_result[strlen(final_result)-2] = '1';
	}
	else{
	final_result[strlen(final_result) - 2] = '0';
	}
	printf("The new changed final data is: %s",final_result);

	write(sockfd,final_result,BUFFER);
	printf("\nServer result:");

       

         read(sockfd,quot,BUFFER);	   // Readimg the quotient from socket file descriptor

         read(sockfd,r,SIZE);	// Reading the remainder from socket file descriptor

         read(sockfd,s,SIZE);	// Reading the status from socket file descriptor

       

         printf("\n quotient= %s",quot);

         printf("\n rem= %s",r);

         printf("\nStatus= %s\n",s);
}
else 
{
	write(sockfd,"0",strlen("0"));
}
/* negative testing ends */
       
       
       
       	 close(sockfd);	  // closing the socket
       	 
       	 free(binary);
         return 0;
}

