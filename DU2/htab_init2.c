/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 htab_init2.c
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#include<stdio.h>
#include<stdlib.h>
#include"htable.h"

htab_t *htab_init2(unsigned size, unsigned (*hashfn)(const char *str, unsigned htab_size)) {
	htab_t *htab;
	if ((htab = malloc(sizeof(htab_t) + size * sizeof(htab_listitem *))) == NULL) 
		return NULL;
	htab->htab_size = size;
	htab->hash_fun_ptr = hashfn;
	htab->n = 0;
	for (unsigned i = 0; i < size; i++)
		htab->ptr[i] = NULL;
	return htab;
}
