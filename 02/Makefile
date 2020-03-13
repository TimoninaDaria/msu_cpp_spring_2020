CC=g++ -std=c++14
  
all: parser 

parser: test.o parser.o 
	$(CC) -o parser test.o parser.o  
 
test: parser  
	./parser
	
test.o: test.cpp parser.h  
	$(CC) -c test.cpp  
  
parser.o: parser.cpp parser.h  
	$(CC) -c parser.cpp  
  
clean:  
	rm -rf *.o parser
