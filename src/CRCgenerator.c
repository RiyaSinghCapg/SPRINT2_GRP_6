
#include<client.h>

int CRCgenerator(char *temp_input, char *bin_input, char *rem, char *quot, char *key, char *key_cpy, int keylen, int msglen){
	/* appending key-1 zeros in the message data */
	for (int input_itr=0; input_itr<keylen-1; input_itr++) {
		bin_input[msglen+input_itr] = '0';
	}
	
	/* storing the bin_input in temp_input variable for doing division based on length key */
	for (int temp_bin=0; temp_bin<keylen; temp_bin++)
	 temp_input[temp_bin] = bin_input[temp_bin];
	 
	/* Calculating the quotient and remainder by doing Exclusive-OR */ 
	for (int quot_itr=0; quot_itr<msglen;  quot_itr++) {
		quot[quot_itr] = temp_input[0];
		if(quot[quot_itr] == '0')
			for (int div_itr=0; div_itr<keylen; div_itr++)
		 		key[div_itr] = '0'; else
		 	for (int div_restore=0; div_restore<keylen; div_restore++)
				key[div_restore] = key_cpy[div_restore];
			for (int xor_chk=keylen-1; xor_chk>0; xor_chk--) {
				if(temp_input[xor_chk] == key[xor_chk])
			 	rem[xor_chk-1] = '0'; else
			 	rem[xor_chk-1] = '1';
		}
		rem[keylen-1] = bin_input[quot_itr+keylen];	// character variable rem with size of key length -1
		strcpy(temp_input,rem);	// copying the remainder in temp_input
	}
	return 0;
}
