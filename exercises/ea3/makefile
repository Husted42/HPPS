CC=gcc
CFLAGS=-g -Wall -Wextra -pedantic

all: printpoints verifyindexes genpoints genindexes sortpoints sortindexes readpoints

test: test.c
	$(CC) -o test test.c io.o $(CFLAGS)

io.o: io.c
	$(CC) -c io.c $(CFLAGS)

printpoints: printpoints.c
	$(CC) -o printpoints printpoints.c io.o $(CFLAGS)

# clean:
# 	rm -f *.o printpoints verifyindexes genpoints genindexes sortpoints sortindexes