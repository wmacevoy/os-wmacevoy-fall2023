all: libmysquare.so test1 test2

libmysquare.so: mysquare.c
	gcc -shared -o libmysquare.so -fPIC mysquare.c

test1: test1.c
	gcc -o test1 test1.c -ldl

test2: test2.c
	gcc -o test2 test2.c -L. -lmysquare

clean:
	rm -f libmysquare.so test1 test2
