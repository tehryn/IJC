#
# Author: Jiri Matejka
# Login: xmatej52
# School: VUT FIT, Brno
# Date: 22-4-2016
# Module: IJC-DU2 hash_function.c
# gcc version 4.9.2 (Debian 4.9.2-10) 
#
CFLAGS = -std=c99 -pedantic -Wall -Wextra -lm -g
CCFLAGS = -std=c++11 -pedantic -Wall -g

default: tail tail2 libhtable.so libhtable.a wordcount wordcount-dynamic

################################################################################

tail: tail.o strnum.o
	gcc $(CFLAGS) -o tail tail.o strnum.o

tail.o: tail.c strnum.c strnum.h
	gcc $(CFLAGS) -c tail.c

strnum.o: strnum.c strnum.h
	gcc $(CFLAGS) -c strnum.c

################################################################################

tail2: tail2.o strnum2.o
	g++ $(CCFLAGS) -o tail2 tail2.o strnum2.o

tail2.o: tail2.cc strnum.c strnum.h
	g++ $(CCFLAGS) -c tail2.cc

strnum2.o: strnum.c strnum.h
	g++ $(CCFLAGS) -c strnum.c -o $@

################################################################################

wordcount: wordcount.o io.o htable.h libhtable.a
	gcc $(CFLAGS) -o wordcount wordcount.o io.o libhtable.a

wordcount.o: wordcount.c io.c htable.h
	gcc $(CFLAGS) -c wordcount.c io.c

################################################################################

wordcount-dynamic: wordcount-dynamic.o io.o htable.h libhtable.so
	gcc $(CFLAGS) -o wordcount-dynamic wordcount-dynamic.o io.o -L$(PWD) -lhtable

wordcount-dynamic.o: wordcount.c io.c htable.h
	gcc $(CFLAGS) -c wordcount.c -o $@
# spusteni programu:
# LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH ./wordcount-dynamic

################################################################################

libhtable.so: hash_function.o htab_clear.o htab_foreach.o htab_free.o htab_init.o htab_init2.o htab_lookup_add.o htab_remove.o
	gcc -shared -o libhtable.so hash_function.o htab_clear.o htab_foreach.o htab_free.o htab_init.o htab_init2.o htab_lookup_add.o htab_remove.o
	export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH)


libhtable.a: hash_function.o htab_clear.o htab_foreach.o htab_free.o htab_init.o htab_init2.o htab_lookup_add.o htab_remove.o
	ar -cvq libhtable.a hash_function.o htab_clear.o htab_foreach.o htab_free.o htab_init.o htab_init2.o htab_lookup_add.o htab_remove.o
	ar -t libhtable.a
	ranlib libhtable.a

hash_function.o: hash_function.c htable.h
	gcc $(CFLAGS) -c hash_function.c -fpic
	
htab_clear.o: htab_clear.c htable.h
	gcc $(CFLAGS) -c htab_clear.c -fpic
	
htab_foreach.o: htab_foreach.c htable.h
	gcc $(CFLAGS) -c htab_foreach.c -fpic
 	
htab_free.o: htab_free.c htable.h
	gcc $(CFLAGS) -c htab_free.c -fpic
	
htab_init.o: htab_init.c htable.h
	gcc $(CFLAGS) -c htab_init.c -fpic
	
htab_init2.o: htab_init2.c htable.h 
	gcc $(CFLAGS) -c htab_init2.c -fpic
	
htab_lookup_add.o: htab_lookup_add.c htable.h
	gcc $(CFLAGS) -c htab_lookup_add.c -fpic
	
htab_remove.o: htab_remove.c
	gcc $(CFLAGS) -c htab_remove.c -fpic
	
io.o: io.c htable.h
	gcc $(CFLAGS) -c io.c

################################################################################

#wordcount2: wordcount2.o 
#	g++ $(CCFLAGS) -o wordcount2 wordcount2.o
	
#wordcount2.o: wordcount2.cc
#	g++ $(CCFLAGS) -c wordcount2.cc 

################################################################################

.PHONY: clean
clean:
	rm *.o libhtable.so libhtable.a tail tail2 wordcount wordcount-dynamic
