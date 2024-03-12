CC = gcc
CFLAGS = -Wall -g

build: main

main: main.o
	$(CC) -o quadtree $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

run: build
	./quadtree

clean:
	rm -f *.o quadtree