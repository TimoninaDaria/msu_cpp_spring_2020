#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>
#include <sstream>
#include "bigint.h"
#include <cstring>
#include <string>
using namespace std;

int main(){

    BigInt x = "13";
    cout<<x<<" ";
    BigInt y = x;
    cout<<y<<" ";
    assert(x == y);
    BigInt h = 22;
    h = y;
    assert(h == y);

    cout<<(BigInt(15) - BigInt(16))<<" ";
    cout<<(BigInt(-15) + BigInt(16))<<" ";
    cout<<(BigInt("11") - BigInt(-17))<<" ";
    cout<<(x - BigInt(-12))<<" ";
    assert(BigInt(15)>=BigInt(-1));
    assert(BigInt(2)<BigInt(100));
    assert(BigInt(12)<=BigInt(12));
    assert(BigInt(13)-BigInt(12)+13 == BigInt(14));
    return 0;
}
