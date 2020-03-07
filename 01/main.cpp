#include "alloc.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>

using namespace std;

int main(){
    cout << "Testing has began. \n";
    makeAllocator(250);
    cout << "Allocation of 250 bytes has been done. \n";

    char* c = alloc(240);
    cout << "+ pointer was returned by function alloc(). \n";

    c = alloc(50);
    assert(c == nullptr);
    cout << "+ function alloc() returned nullptr. \n";

    reset();
    cout << "+ function reset() was called. \n";

    c = alloc(100);
    *(c+50) = 'D'; //try to write something
    *(c+60) = 'A'; //try to write something

    assert(c != nullptr);
    cout << "+ function alloc() hasn't returned nullptr. \n";

    reset();
    cout << "+ function reset() was called. \n";

    c = alloc(300);
    assert(c == nullptr);
    cout << "+ function alloc() has returned nullptr. \n\n";

    free(begin_pos);
    cout << "All tests are passed\n";
    return 0;
}
