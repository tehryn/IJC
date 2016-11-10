// error.c
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
#include <stdlib.h>
#include <stdio.h>
#include "error.h"

void warning_msg (const char *fmt, ...) {
	va_list args;
	vfprintf (stderr,"CHYBA: ", args);
	va_start (args, fmt);
	vfprintf (stderr,fmt, args);
	va_end (args);
}

void fatal_error (const char *fmt, ...) {
	va_list args;
	vfprintf (stderr,"CHYBA: ", args);
	va_start (args, fmt);
	vfprintf (stderr,fmt, args);
	va_end (args);
	exit(1);
}
