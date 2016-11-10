// ppm.h
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
#ifndef PPM_H
#define PPM_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef ERROR_H
#include "error.h"
#endif

struct ppm {
	unsigned xsize;
	unsigned ysize;
	char data[]; // RGB najty, celkem 3*xsize*ysize
};

/******************************************************************************/
/* Prototypes of functions */
struct ppm * ppm_read (const char *filename);
int ppm_write(struct ppm *p, const char * filename);

/******************************************************************************/

#endif
