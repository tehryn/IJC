// bit_array.h
// Řešení IJC-DU1, makefile 23.3.2016
// Autor: Matějka Jiří, FIT VUT 
// gcc (Debian 4.9.2-10) 4.9.2
// Many thanks to:
// http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
// would not be ayble to create macros and understand bit array without them
/* === NOTE === */
/* I know, this code is really ugly, but I could not help myself... I am so sorry if someone is trying to debug this code or just readig.
   Happy debuging! */
#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H
#ifndef ERROR_H
#include "error.h"
#endif

#define ULSIZE ((sizeof(unsigned long int)*8))  //to make sure it will work on 32-bit as well as on 64-bit
#define BITS(element) (sizeof(element)*8) // size of element in bits

/* replaced by 1 or 0 */
#define DU1_GET_BIT_(p,i) (p[(i)/(BITS((p)[0]))] & 1UL<< ((i)%(BITS((p)[0]))) )

/* replaced by command */
#define DU1_SET_BIT_(p,i,b) ((b)?(p[(i)/(BITS(p[0]))] |= 1UL << ((i)%(BITS(p[0]))) ) : ( p[(i)/(BITS(p[0]))] &= ~(1UL<<((i)%(BITS(p[0])))) ) )

typedef unsigned long int *bit_array_t;

/* So, lets pretend, unsigned long integer has 32 bits everewhere. When I need array of 32 bits, I will get array of 32 bits
   but when I need array of 33 bits, I need alocate another space of 32 bits, so I need 32 + 32 = 64 bits*/
#define ba_create(array,size)  unsigned long int array[size%ULSIZE ? size/ULSIZE+2 : size/ULSIZE+1]= {size,0};

/* Using Inline function */
#ifdef USE_INLINE
	
	static inline unsigned long int ba_size(bit_array_t array) {
		return array[0];
	}
	
	static inline void ba_set_bit(bit_array_t array,unsigned long int idx,unsigned int value) {
		(idx >= ba_size(array))?(fatal_error("Index %ld mimo rozsah 0..%ld", (long)idx, (long)array[0]), 42):DU1_SET_BIT_(array,idx+ULSIZE,value);
	}
	
	
	static inline unsigned long int ba_get_bit(bit_array_t array, unsigned long int idx) {
		return (idx >= ba_size(array))?(fatal_error("Index %ld mimo rozsah 0..%ld", (long)idx, (long)array[0]), 42): DU1_GET_BIT_(array,idx+ULSIZE);
	}

/* Using macros */
#else

	#define ba_size(array) array[0]

	/* when value != 0 I shift 1 to position and logic OR set bit (1 or 1 is 1, 1 or 0 is 1) otherwise I use logic AND and with zero */
	#define ba_set_bit(array,idx,value)\
		(idx >= ba_size(array))?(fatal_error("Index %ld mimo rozsah 0..%ld\n", (long)idx, (long)array[0]), 42):DU1_SET_BIT_(array,idx+ULSIZE,value)

	/* This "return" (change into ) 1 or 0 becouse I am comparing 1 and bit (1 or 0) with logic AND*/
	#define ba_get_bit(array,idx) \
		((idx >= ba_size(array))?(fatal_error("Index %ld mimo rozsah 0..%ld\n", (long)idx, (long)array[0]), 42): DU1_GET_BIT_(array,idx+ULSIZE))

#endif
#endif
