CC=g++ -std=c++14
  
all: pool 

pool: test.o pool.o 
	$(CC) -o pool test.o pool.o  
 
test: pool  
	./pool
	
test.o: test.cpp pool.h  
	$(CC) -c test.cpp  
  
pool.o: pool.cpp pool.h  
	$(CC) -c pool.cpp  
  
clean:  
	rm -rf *.o pool
