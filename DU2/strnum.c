/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 strnum.c
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#include <stdlib.h>
#include "strnum.h"
int is_int (char *string) {
	int i=0;
	if (string[i] == '-' || string[i] == '+') i++;
	for(; string[i] != '\0'; i++)
		if (string[i] < '0' || string[i] > '9')
			return 0;

	return 1;
}

int string_to_uint (char *string) {
	int long long value = 0;
	int test = 0;
	int i=0;
	if (string[i] == '-' || string[i] == '+') i++;
	for (; string[i] != '\0'; i++){
		
		/* testing overflow */
		test = value * 10 + ( string[i] - '0' );
		if (test < value)
			return -1;

		/* the value of number character (8 for example) - value of
		  character 0 = number (8) */
		value = value * 10 + ( string[i] - '0' );		

	}

	return(value);
}
