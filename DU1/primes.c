// primes.c
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
#include <stdio.h>
#include <stdlib.h>
#include "bit_array.h"
#include "eratosthenes.h"
#define SIZE 202000000

/*TODO*/
int main() {
	ba_create(array, SIZE);
	Eratosthenes(array);
	
	for (long unsigned i = SIZE - 1, n = 0; i > 0 && n < 10; i--) {
		if (!ba_get_bit(array, i))
			n++;
		if (n == 10)
			for (; i < SIZE; i++)
				if (!ba_get_bit(array, i))
					printf ("%lu\n", i);
		}

	return 0;
}
