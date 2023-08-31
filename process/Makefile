all : fork hello

clean :
	/bin/rm -rf fork hello

fork : fork.c
	$(CC) -g -o $@ $^

hello : hello.cpp
	$(CXX) -g -o $@ $^

test : fork hello
	./fork 4