					/* REGISTRATION and LOGIN at client side socket */

#include <client.h>

#define USR_SIZE 30
#define PASWRD_SIZE 20

struct login
{
     char username[SIZE];
     char password[PASWRD_SIZE];
};


/*
login function to take credentials as input from user,
it reads from file named 'login.txt' where we have username and password stored.
it then validates the credentials entered by the user against the ones present in the file.
*/


void login (void)
{
    char username[SIZE],password[PASWRD_SIZE];
    
    FILE *log;
    relogin:
    log = fopen("../data/login.txt","r");//opened file in read mode

     if (log == NULL)      //if an error occurs, it'll display error message
     {
      fputs("Error at opening File!", stderr);
      exit(EXIT_FAILURE);
     }
    struct login l;


    //accepting username and password
    
    printf("\nPlease Enter your login credentials below\n\n");
    printf("Username:  ");
    fgets(username, SIZE, stdin);        
    printf("\nPassword: ");
     
    printf("\n");
    
    fgets(password, PASWRD_SIZE, stdin);
    bool keep_reading = true;       //bool to run loop to keep reading
    int current_line = 1;       //shows current line
    int username_line = 1;          //line with username
    int password_line = 2;          //line with password
    char buffer[USR_SIZE];
    //read from file and store username in l.username, password in l.password
    do 
    {
    // read the next line from the file, store it into buffer
    fgets(buffer, USR_SIZE, log);

    // now, we go to lines 1 & 2 and copy their values to l.username and l.password
    if (current_line == username_line)
    {
        keep_reading = true;
        strcpy(l.username, buffer);
    }
    else if (current_line == password_line)
    {
        keep_reading = false;
        strcpy(l.password, buffer);
    }

// continue to keep track of the current line we are reading
current_line++;

    } 
    while(keep_reading);    

    
    
       if(strcmp(username,l.username)==0 && strcmp(password,l.password)==0)
    {       
        printf("\nSuccessful Login\n");
        printf("\nPress any key to continue\n");
        getchar();
        system("clear");
        }
        else 
        {
                printf("\nIncorrect Login Details\nPlease enter the correct credentials\n");
                goto relogin;
        }

    fclose(log);
    
    return;
    
}

/*
registration function to register or change admin credentials,
it writes the credentials to the file named 'login.txt'.
it then leads to login function so the admin can login.
*/

void registration(void) 
{
     
     FILE *log;

     log=fopen("../data/login.txt","w");    //open file in write mode
     if (log == NULL)
     {
         fputs("Error opening File!", stderr);
     exit(1);
     }


     struct login l;

     //prompt client to choose username and password
     system("clear");
     printf("Choose a username and password as credentials for system login\n"); 

    //accept user name and password
    printf("\nEnter Username:\n");
    fgets(l.username, USR_SIZE, stdin);
    printf("\nEnter Password:\n");
  
    
    fgets(l.password, PASWRD_SIZE, stdin);

    //put username and password into the file leaving 1 line in between
    fputs(l.username,log);
   
    fputs(l.password,log);

    //close file
    fclose(log);

    //show user that account has been created
    printf("\nConfirming details...\n...\nWelcome!\n\n");
    printf("\nRegistration Successful!\n");
    printf("Press any key to continue...");

    getchar();
    system("clear");

    printf("\nNow running login utility\n");
   
    login();
}
    
    

    
    

