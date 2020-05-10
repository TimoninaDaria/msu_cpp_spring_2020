CC=g++ -std=c++14

all: merge

merge: test.o merge.o
	$(CC) -o merge test.o merge.o

test: merge
	./merge

test.o: test.cpp merge.h
	$(CC) -c test.cpp

merge.o: merge.cpp merge.h
	$(CC) -c merge.cpp

clean:
	rm -rf *.o merge
