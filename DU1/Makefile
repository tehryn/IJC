## makefile
## Řešení IJC-DU1, makefile 23.3.2016
## Autor: Matějka Jiří, FIT VUT 
## gcc (Debian 4.9.2-10) 4.9.2

CFLAGS = -std=c99 -pedantic -Wall -Wextra #gcc flags
CC = gcc #compile files without linking

default: primes primes-inline steg-decode


primes: primes.o eratosthenes.o error.o
	$(CC) $(CFLAGS) -o primes primes.o eratosthenes.o error.o

primes-inline: primes-inline.o eratosthenes-inline.o error.o
	$(CC) $(CFLAGS) -o primes-inline primes-inline.o eratosthenes-inline.o error.o -DUSE_INLINE

steg-decode: steg-decode.o ppm.o error.o eratosthenes.o
	$(CC) $(CFLAGS) -o steg-decode steg-decode.o ppm.o error.o eratosthenes.o


primes.o: primes.c eratosthenes.h bit_array.h error.h
	$(CC) $(CFLAGS) -c primes.c

primes-inline.o: primes.c eratosthenes.h bit_array.h error.h
	$(CC) $(CFLAGS) -c primes.c -DUSE_INLINE -o $@

eratosthenes.o: eratosthenes.c eratosthenes.h bit_array.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c

eratosthenes-inline.o: eratosthenes.c eratosthenes.h bit_array.h error.h
	$(CC) $(CFLAGS) -c eratosthenes.c -DUSE_INLINE -o $@

error.o: error.c error.h
	$(CC) $(CFLAGS) -c error.c



steg-decode.o: steg-decode.c ppm.h error.h eratosthenes.h
	$(CC) $(CFLAGS) -c steg-decode.c

ppm.o: ppm.c ppm.h error.h 
	$(CC) $(CFLAGS) -c ppm.c
	
.PHONY: clean
clean:
	rm -f *.o
