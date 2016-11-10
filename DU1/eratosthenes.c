// eratosthenes.c
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "eratosthenes.h"
#include "bit_array.h"


void Eratosthenes(bit_array_t array) {
	unsigned long size = ba_size(array);
	unsigned long idx;
	ba_set_bit(array, 0, 1);
	ba_set_bit(array, 1, 1);
	for (idx = 2; idx < size; idx++)
		ba_set_bit(array, idx, 0);
	
//	unsigned long max_step = sqrt(size);
	for (idx = 2; idx*idx < size; idx++)
		if (!ba_get_bit(array, idx))
			for (unsigned long int i = 2*idx; i < size; i+=idx)
				ba_set_bit(array, i, 1);
	
}
