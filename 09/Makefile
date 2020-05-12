CC=g++ -std=c++14

all: merge

merge: test.o merge.o pool.o
	$(CC) -o merge test.o merge.o pool.o

test: merge
	./merge

test.o: test.cpp merge.h pool.h
	$(CC) -c test.cpp

merge.o: merge.cpp merge.h pool.h
	$(CC) -c merge.cpp

pool.o: merge.cpp merge.h pool.h
	$(CC) -c pool.cpp

clean:
	rm -rf *.o merge
