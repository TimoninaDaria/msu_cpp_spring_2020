CC=g++ -std=c++14

all: matrix

matrix: test.o matrix.o
	$(CC) -o matrix test.o matrix.o

test: matrix
	./matrix

test.o: test.cpp matrix.h
	$(CC) -c test.cpp

matrix.o: matrix.cpp matrix.h
	$(CC) -c matrix.cpp

clean:
	rm -rf *.o matrix
