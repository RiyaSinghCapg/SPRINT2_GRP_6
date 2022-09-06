                                            /* Converting a string to Binary */

//including user defined header files
#include <client.h>

/*function call for stringToBinary */
char* stringToBinary(char* str) 
{
    if(str == NULL) // if str is null it will return 0
    {
       return 0; /* no binary string */
    }
    
    size_t len = strlen(str); // calculating the length of string
    
    char *binary = malloc(len*8 + 1); // each char is one byte (8 bits) and + 1 at the end for null terminator
    binary[0] = '\0';
    
    /* Converting the string to binary using bitwise AND &  shift operator */
    for(size_t i = 0; i < len; ++i) 
    {
        char ch = str[i];
        for(int j = 7; j >= 0; --j)
        {
            if(ch & (1 << j)) 
            {
                strcat(binary,"1");  // concating the 1 with binary
            } 
            else 
            {
                strcat(binary,"0"); // concating the 0 with binary
            }
        }
    }
    
    return binary; // return the binary of the string
    
}

