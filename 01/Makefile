CC=g++ -std=c++14
  
all: allocator 

allocator: main.o alloc.o 
	$(CC) -o allocator main.o alloc.o  
 
test: allocator  
	./allocator
	
main.o: main.cpp alloc.h  
	$(CC) -c main.cpp  
  
alloc.o: alloc.cpp alloc.h  
	$(CC) -c alloc.cpp  
  
clean:  
	rm -rf *.o allocator
