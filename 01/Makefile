CC=g++ -std=c++14
  
all: test  
  
test: main.o alloc.o   
	$(CC) -o allocator main.o alloc.o  
	./allocator
	
main.o: main.cpp alloc.h  
	$(CC) -c main.cpp  
  
alloc.o: alloc.cpp alloc.h  
	$(CC) -c alloc.cpp  
  
clean:  
	rm -rf *.o allocator
