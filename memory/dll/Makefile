all: run

.PHONY: run
run : run1 run2

clean:
	rm -f libmysquare.so mysquare.o test1.o test2.o test1 test2

# make position independent .o file from .c file 
mysquare.o: mysquare.c
	gcc -c -o mysquare.o -fPIC mysquare.c

# put .o file in shared library
libmysquare.so: mysquare.o
	gcc -shared -o libmysquare.so mysquare.o

# the main program does not have to be position independent
test1.o : test1.c
	gcc -c -o test1.o test1.c

test1: test1.o
	gcc -o test1 test1.o -ldl


# normal dynamic verion needs shared library at
# link time to make stub routines in the
# executable
test2.o : test2.c mysquare.h
	gcc -c -o test2.o test2.c

test2: test2.o libmysquare.so
	gcc -o test2 test2.o -L. -lmysquare


# test1 needs libmysquare.so to exist to run
.PHONY: run1
run1: test1 libmysquare.so
	./test1

# at runtime, the LD_LIBRARY_PATH in linux needs to be
# modified so it knows where to find the libmysquare library...
.PHONY: run2
run2: test2
	LD_LIBRARY_PATH=$$(pwd) ./test2
