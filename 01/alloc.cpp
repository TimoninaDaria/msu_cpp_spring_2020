#include "alloc.h"
#include <stdio.h>
#include <stdint.h>
#include <iostream>

using namespace std;

int8_t* begin_pos;
size_t pos = 0;
size_t maxSize;

void makeAllocator(size_t maxSize){
    begin_pos = (int8_t*)(malloc(maxSize));
    ::maxSize = maxSize;
}

char* alloc(size_t size){
    if (pos + size > maxSize) return nullptr;
    else {
        pos += size;
        return (char*)(begin_pos + pos - size);
    }
}

void reset(){
    pos = 0;
}
