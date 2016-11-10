// ppm.c
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

struct ppm * ppm_read (const char *filename) {
	FILE *stream;
	if ((stream = fopen(filename, "r")) == NULL) {
		warning_msg("Nacitani souboru probehlo neuspesne\n");	
		return NULL;
	}
	struct ppm *data; // struct for loading data
	char buff[128] = {0}; // buffer for loading temporary string
	int c, support = 0, i = 0; // c for getc, i for loop, support for state machine
	unsigned x=0, y=0; // user will not lie about size... He/she will be nice...
	while ((c = getc(stream)) != EOF) {
		switch (support) { // State machine
		/* testing P6 */
		case 0:
			buff[i] = (char) c;
			i++;
			if (i == 2) {
				if (strcmp(buff, "P6") && !isspace((c = getc(stream)))) goto error; //testing next char too!!!!		
				support=1;
				break;
			}
			break;
		/* skipping whitespaces */
		case 1:
			if (isspace(c))	break; // one space have been checked in case 0
			support = 2; // no break here, we need to jump into case 2
			i = 0;
		/* loading x */
		case 2:
			if (isdigit(c)) {
				buff[i] = (char) c;
				i++;
				break;
			}
			
			if (!i) goto error;
			
			buff[i] = '\0';
			x=atoi(buff); //TODO atoi is ugly! I hate it
			support=3;
			i=0;
			break;
		/* loading y*/
		case 3:
			if (isdigit(c)) {
				buff[i] = (char) c;
				i++;
				break;
			}
			if (!i && !isspace(c)) goto error; //testing one space
				
			buff[i] = '\0';
			y=atoi(buff); //TODO atoi is ugly! I should do something about it
			support=4;
			i=0;
			break;		
		
		/* skipping white spaces */
		case 4:
			if (isspace(c)) break; // one space has been checked in case 3
			support = 5; // no break here, we need to jump into case 5
			i = 0;
		/* testing 255 */
		case 5:
			buff[i] = (char) c;
			i++;
			if (i == 3) {
				buff[i] = '\0';
				if (!isspace((c = getc(stream))) && strcmp(buff, "255")) goto error;
				support = 6;
				i=0;
				if ((data = malloc(x*y*3+sizeof(struct ppm))) == NULL) goto error;
				data->xsize = x;
				data->ysize = y;
				break;
			}
			break;
		/*loading data*/
		case 6:
			data->data[i] = (char) c;
			i++;
			break; // its not nessesary but still... its more readable
		}
	}
	
	fclose (stream);
	return data;
	/* my first goto, hope Ing. Ales Smrcka, Ph.D. will be proud of me */
	error:
		warning_msg("Nacitani souboru probehlo neuspesne\n");
		free(data);
		fclose(stream);
		return NULL;
}
