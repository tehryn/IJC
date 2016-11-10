/*
 * Author: Jiri Matejka
 * Login: xmatej52
 * School: VUT FIT, Brno
 * Date: 22-4-2016
 * Module: IJC-DU2 htab_clear.c
 * gcc version 4.9.2 (Debian 4.9.2-10)
 */
#include<stdio.h>
#include<stdlib.h>
#include"htable.h"


void htab_remove (htab_t *t, const char *key) {
	unsigned index = t->hash_fun_ptr(key, t->htab_size);
	
	if (t->ptr[index]==NULL)
		return;

	htab_listitem *temp, *l = t->ptr[index];
	
	while (strcmp(l->key, key)) {
		temp = l;
		l = l->next;
		if (l == NULL)
			return;
	}
	
	if (!strcmp(t->ptr[index]->key, l->key))
		t->ptr[index] = t->ptr[index]->next;
	else temp->next = temp->next->next;
	free(l->key);
	free(l);	
}
