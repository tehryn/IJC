// steg-decode.c
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "bit_array.h"
#include "eratosthenes.h"
#include "ppm.h"

int main(int argc, char **argv) {
	
	if (argc != 2) {
		warning_msg("Chybne argumenty\n");
		return 1;
	}

	struct ppm *image = ppm_read (argv[1]);
	if (image == NULL)
		fatal_error("Selhani pri alokaci pameti\n");
	
	unsigned long int size = image->xsize*image->ysize*3;

	unsigned long int *array=malloc(size + sizeof(unsigned long int));
	if (array == NULL) {
		if (image != NULL) free(image);
		fatal_error("Selhani pri alokaci pameti\n");
	}

	char *data = malloc(size);
	if (data == NULL) {
		if (image != NULL) free(image);
		if (array != NULL) free(image);
		fatal_error("Selhani pri alokaci pameti\n");
	}

	array[0] = size;
	Eratosthenes(array);
	for(unsigned long int i = 0, j = 0; i < size; i++) {
	    if(!ba_get_bit(array, i)){
	      DU1_SET_BIT_(data, j ,image->data[i] & 1); // DU1_GET_BIT_(array, i)
	      j++;
	    }
	}
	
	/* Printing data */
	unsigned long int i = 0;
	for(; data[i] != '\0' && data[i] != EOF && i < size; i++) {
		if (i == size-1 && data[i] != '\0') {
			if (array != NULL) free(array);
			if (data != NULL) free(data);
			if (image != NULL) free(image);
			fatal_error("Chybny format\n");
		}
		if (isprint(data[i])) printf("%c", data[i]);
		else {
			if (array != NULL) free(array);
			if (data != NULL) free(data);
			if (image != NULL) free(image);
			fatal_error("Chybny format\n");
		}	
	}

	if (data[i] != '\0') {
		if (array != NULL) free(array);
		if (data != NULL) free(data);
		if (image != NULL) free(image);
		fatal_error("chybny format\n");
	}
	

	/* free and return */
	if (array != NULL) free(array);
	if (data != NULL) free(data);
	if (image != NULL) free(image);
	return 0;
}
