						/* check_num is for checking whether the input no is digit or not */
#include<server.h>

int check_num(char *str){
	int digit;
	if(strlen(str) > 2)
		return 0;
	for(digit=0; digit<strlen(str); digit++){
		if(isdigit(str[digit]) == 0)
		return 0;
		
	}
	return 1;
}
