#pragma once
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>

extern int8_t* begin_pos;
void makeAllocator(size_t maxSize);
char* alloc(size_t size);
void reset();

