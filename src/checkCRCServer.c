
#include<server.h>

int checkCRCServer(char *final_cpy, char *temp_data, char *rem, char *quot, char *key, char *key_cpy, int keylen, int msglen)
{
	
	
	/*storing the input in temp_data variable for doing division based on length key */

	for (int input_bin=0;input_bin<keylen;input_bin++)

	 temp_data[input_bin]=final_cpy[input_bin];

	/* Calculating the quotient and remainder by doing Exclusive-OR */ 

	for (int quot_itr=0;quot_itr<msglen;quot_itr++) {

		quot[quot_itr]=temp_data[0];

		if(quot[quot_itr]=='0')

		 for (int div_itr=0;div_itr<keylen;div_itr++)

		 key[div_itr]='0'; else

		 for (int div_restore=0;div_restore<keylen;div_restore++)

		 key[div_restore]=key_cpy[div_restore];

		 for (int xor_chk=keylen-1;xor_chk>0;xor_chk--) {

			if(temp_data[xor_chk]==key[xor_chk])

			 rem[xor_chk-1]='0'; else

			 rem[xor_chk-1]='1';

		}

	rem[keylen-1]=final_cpy[quot_itr+keylen];
	strcpy(temp_data,rem);	// copying the remainder in temp_data

	}
	return 0;
}
