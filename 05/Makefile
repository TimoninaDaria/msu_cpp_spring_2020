CC=g++ -std=c++14

all: bigint

bigint: test.o bigint.o
	$(CC) -o bigint test.o bigint.o

test: bigint
	./bigint

test.o: test.cpp bigint.h
	$(CC) -c test.cpp

bigint.o: bigint.cpp bigint.h
	$(CC) -c bigint.cpp

clean:
	rm -rf *.o bigint
