#pragma once
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>

void makeAllocator(size_t maxSize);
char* alloc(size_t size);
void reset();
void free_mem();

