CC?=gcc
CFLAGS?=-Wextra -Wall -pedantic -std=c99 -g -O2
LDFLAGS?=-lm

all: sort-example knn-bruteforce knn-svg knn-kdtree knn-genpoints

sort-example: sort-example.o sort.o
	$(CC) -o $@ $^ $(LDFLAGS)

knn-bruteforce: knn-bruteforce.o bruteforce.o io.o util.o sort.o
	$(CC) -o $@ $^ $(LDFLAGS)

knn-kdtree: knn-kdtree.o bruteforce.o io.o util.o kdtree.o sort.o
	$(CC) -o $@ $^ $(LDFLAGS)

knn-genpoints: knn-genpoints.o io.o
	$(CC) -o $@ $^ $(LDFLAGS)

knn-svg: knn-svg.o io.o util.o kdtree.o sort.o
	$(CC) -o $@ $^ $(LDFLAGS)

# A general rule that tells us how to generate an .o file from a .c
# file.  This cuts down on the boilerplate.
%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf knn-genpoints knn-bruteforce knn-svg knn-kdtree *.o *.dSYM
	rm -rf points queries indexes points.svg

# Testing rules

<<<<<<< HEAD
NUM_POINTS=100000
NUM_QUERIES=5000
K=100
=======
NUM_POINTS=1000
NUM_QUERIES=100
K=10
>>>>>>> 96c1383983f096929b5d20a9c3f89e5aa502dfb1

points: knn-genpoints
	./knn-genpoints $(NUM_POINTS) 2 > points

queries: knn-genpoints
	./knn-genpoints $(NUM_QUERIES) 2 > queries

indexes: points queries knn-bruteforce knn-kdtree
	./knn-bruteforce points queries $(K) indexes

points.svg: points queries indexes knn-svg
	./knn-svg points queries indexes > points.svg