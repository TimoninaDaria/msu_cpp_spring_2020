#include "merge.h"
#include <cassert>

int main(){
    int isok = sort_by_merge("numbers.dat");
    assert(isok == 0);
    return 0;
}
