// error.h
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
#ifndef ERROR_H
#define ERROR_H
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning_msg (const char *fmt, ...);
void fatal_error (const char *fmt, ...);


#endif
