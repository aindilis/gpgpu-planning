all: libdbs.a
	gcc --std=c99 -pthread test-dbs.c -I. -o test-dbs

libdbs.a: dbs-ll.o
	ar r libdbs.a dbs-ll.o

dbs-ll.o: dbs-ll.c dbs-ll.h tls.h 
	gcc --std=c99 -pthread -I. -c -o dbs-ll.o dbs-ll.c
