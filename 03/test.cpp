#include "matrix.h"
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cassert>

using namespace std;

int main(){
    cout<<"Tests\n";

    int rows = 5;
    int cols = 3;

    Matrix m(rows, cols);

    assert(m.getRows() == 5);
    assert(m.getColumns() == 3);

    m[0][1] = 2;
    m *= 3;
    assert(m[0][1] == 6);

    m[0][1] = 8;
    assert(m[0][1] == 8);

    Matrix a(rows, cols);

    for (int i = 0; i < rows; ++i){
        for (int j = 0; j < cols; ++j){
            m[i][j] = i*j;
            a[i][j] = i*j;
        }
    }

    assert(a == m);

    m[0][1] = 100;
    assert(a != m);
    assert(m == m);

    a[0][1] = 100;
    assert(a == m);
    cout<<"All tests are passed";

}

