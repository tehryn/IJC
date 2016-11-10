/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 wordcount.c
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#define MAX_LEN 127

/*
 * Print key, space(tab) and value of data
 */
void print_item(htab_listitem *l);
int main() {
	FILE *f = stdin;
	char *s = malloc(MAX_LEN);
	htab_t *t;
	htab_listitem *item;
	t = htab_init(6151); //Hope its not too big...
	if (t == NULL) {
		fprintf(stderr, "Allocation in htab_init failed\n");
		return 1;
	}
	while (get_word(s, MAX_LEN, f) != EOF) {
		item = htab_lookup_add(t, s);
		if (item == NULL) {
			fprintf(stderr, "Allocation htab_lookup_add failed\n"
							"Now I will try to free memory\n");
			htab_free(t);
			return 1;
		}
		item->data++;
	}

	htab_foreach(t, &print_item);
	free(s);
	htab_free(t);

	return 0;
}

void print_item(htab_listitem *l) {
	printf("%s\t%u\n", l->key, l->data);
}
