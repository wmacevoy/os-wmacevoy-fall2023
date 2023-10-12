all: libmysquare.so test

libmysquare.so: mysquare.c
	gcc -shared -o libmysquare.so -fPIC mysquare.c

test: test.c
	gcc -o test test.c -ldl

clean:
	rm -f libmysquare.so test
