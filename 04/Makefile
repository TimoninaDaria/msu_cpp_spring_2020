CC=g++ -std=c++14
  
all: serial

serial: test.o
	$(CC) -o serial test.o  
 
test: serial  
	./serial
	
test.o: test.cpp serial.h  
	$(CC) -c test.cpp  
    
clean:  
	rm -rf *.o serial
