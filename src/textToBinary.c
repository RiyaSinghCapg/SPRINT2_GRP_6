                                                           /* Converting a string to Binary */

//including user defined header files
#include <client.h>

/*function call for stringToBinary */
int stringToBinary(char* str, char* binary) 
{
    if(str == NULL) // if str is null it will return 0
    {
       return 0; /* no binary string */
    }
    
    size_t len = strlen(str); // calculating the length of string
    
       
    /* Converting the string to binary using bitwise AND &  shift operator */
    for(size_t str_length = 0; str_length < len; ++str_length) 
    {
        char ch = str[str_length];
        for(int bit_extract = 7; bit_extract >= 0; --bit_extract)
        {
            if(ch & (1 << bit_extract)) 
            {
                strcat(binary,"1");  // concating the 1 with binary
            } 
            else 
            {
                strcat(binary,"0"); // concating the 0 with binary
            }
        }
    }
    
    return 1; 
    
}

