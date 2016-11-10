/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 tail.c
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strnum.h"

#define MAX_LEN 510 // Max length of line.

/*
 * Detect source file, -n switch and save value to adress pointed by *argc.
 * Return pointer to file or NULL when error, also print errors on stderr.
 */
FILE *get_source(int *argc, char **argv);

/*
 * Load file and print last lines. (Number of lines depends on size, that
 * represent allocated space)
 */
int output(FILE *source, char *buffer, long long unsigned size);

int main (int argc, char **argv) {
	int lines = argc;
	FILE *source = get_source(&lines, argv);
	if (source == NULL) return 1;

	if (lines <= 0) return 0;	
	long long unsigned size = MAX_LEN * lines + 2*lines;
	char *buffer = calloc(1, size); //1 for '\0'
	if (buffer == NULL) {
		fprintf(stderr,"Cannot allocate memory\n");
		return 1;
	}
	output(source, buffer, size);
	/* free memory */
	free(buffer);
	if (fclose(source) == EOF) {
		fprintf(stderr,"Unable to close source file\n");
		return 1;
	}
	return 0;
}

/*
 * Detect source file, -n switch and save value to adress pointed by *argc.
 * Return pointer to file or NULL when error, also print errors on stderr.
 */
FILE *get_source(int *argc, char **argv) {
	FILE *source;
	int arg_num = *argc;
	
	if (arg_num == 1) {
		*argc = 10;
		return stdin;
	}
	
	if (arg_num == 2) {
		if (!strcmp(argv[1], "-n")) {
			fprintf(stderr,"tail: přepínač vyžaduje argument – „n“\n");
			return NULL;
		}
		
		else {
			source = fopen(argv[1], "r");
			if (source == NULL) {
				fprintf(stderr,"tail: \"%s\" nelze otevřít pro čtení: Adresář"
								" nebo soubor neexistuje\n", argv[1]);
				return NULL;
			}
			*argc = 10;
			return source;
		}
	}
	
	int i = 1;
	/* Looking for -n */
	for (; i < arg_num; i++)
		if (!strcmp("-n", argv[i])) 
			break;
	
	/* if arg_num == i, -n was not found*/
	if (i != arg_num) {
		if (i == arg_num - 1 || !is_int(argv[i+1])) {
			fprintf(stderr,"tail: přepínač vyžaduje argument – „n“\n");
			return NULL;
		}
		else {
			*argc = string_to_uint(argv[i+1]);
			if (*argc < 0) {
				fprintf(stderr,"Owerflow detected\n");
				return NULL;
			}
			if (arg_num == 3) {
				source = stdin;
				return source;			
			}
			else {
				if (arg_num > 3 && i == 1)
					source = fopen(argv[3], "r");
				else
					source = fopen(argv[1], "r");
				if (source == NULL) {
					fprintf(stderr,"tail: \"%s\" nelze otevřít pro čtení: Adresář"
									" nebo soubor neexistuje\n", argv[1]);
					return NULL;
				}
				return source;		
			}
		}
	}
	
	/* -n was not found*/
	else {
		source = fopen(argv[1], "r");
		*argc = 10;
		if (source == NULL) {
			fprintf(stderr,"tail: \"%s\" nelze otevřít pro čtení: Adresář"
							" nebo soubor neexistuje\n", argv[1]);
			return NULL;
		}
		return source;
	}
	return NULL; // unknow error
}

/*
 * Load file and print last lines. (Number of lines depends on size, that
 * represent allocated space)
 */
int output(FILE *source, char *buffer, long long unsigned size) {
	static int error = 1;
	int read_char = 0; // char for row
	int c; // variable for fgetc
	long long unsigned int i = 0; // indexing buffer
	while ((c = fgetc(source)) != EOF) {
		read_char++;
		/* i index char out of allocated space, need to set it to 0 */
		if (i >= size) i = 0 ;

		/* Max length of line was reached */
		if (read_char > MAX_LEN && c != '\n') {
			read_char = 0;
			buffer[i] = '\n';
			buffer[i+1] = '\0';
			i+=2;
			if (error) {
				fprintf(stderr,"You have reached max lengh of line\n");
				error = 0;
			}
			while ((c = fgetc(source)) != '\n' && c != EOF);
			if (c == EOF) break;
			continue;
		}
		
		/* New line */
		if (c == '\n') {
			buffer[i] = '\n';
			buffer[i+1] = '\0';
			i+=2 + 1 + MAX_LEN - read_char;
			/* ^^^ 2 (loaded 2 chars) + (MAX_LEN - read_char + 1) to index first
			char for new line */	
			read_char = 0;
			continue;
		}

		buffer[i] = c;
		i++;
	}
	long long unsigned int j = i;
	
	/* Printing lines */
	/* This is how buffer can looks like:
	 * buffer [sentence1\n\0-----------ununicializated space------\0 <-- MAX_LEN
	 *         sentence2\n\0-----------ununicializated space------\0
	 *         sentence3 sentence3 sentence3 sentence3 sentence3 te\n\0
	 *        ]
	 * this is how buffer looks like, we can index lines by MAX_LEN and
	 * use %s in printf to print it by indexing first char in line
	 */
	for (; i < size; i+=MAX_LEN+2)
		printf ("%s", &buffer[i]);
	for (i = 0; i < j; i+=MAX_LEN+2)
		printf ("%s", &buffer[i]);
	return 0;
}
