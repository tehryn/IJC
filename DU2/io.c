/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 io.c
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int get_word(char *s, int max, FILE *f) {
	static int error = 1; // for only one error output
	if(max <= 0)
		return 0;
	int c; // for fgetc()
	int i = 0;
	/* skiping spaces */
	while((c = fgetc(f)) != EOF && isspace(c));
	
	/* loading first char */
	if (c != EOF) {
		s[0] = c;
		i++;
	}
	
	/* loading word */
	while ((c = fgetc(f)) != EOF && !isspace(c) && i < max-1) {
		s[i] = c;
		i++;
	}
	
	/* strings end with '\0' */
	s[i] = '\0';
	
	/* max length of word was reached */
	if (i == max-1 && !isspace(c)) {
		if (error) {
			fprintf(stderr, "Word(s) in source are too long!\n");
			error = 0;
		}
		/* skipping rest of word */
		while((c = fgetc(f)) != EOF && !isspace(c));
	}
	if (i == 0)
		return EOF;
	return i;
}
