#include "serial.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>
#include <sstream>

using namespace std;

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;
    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a,b,c);
    }
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

int main(){
Data x {11, true, 22};

std::stringstream s1;

Serializer serializer(s1);
serializer.save(x);

Data y { 0, false, 0 };
Deserializer d1(s1);
const Error err = d1.load(y);
assert(err == Error::NoError);
assert(x.a == y.a);
assert(x.b == y.b);
assert(x.c == y.c);

auto s2 = std::stringstream("3 4 5");
Deserializer d2(s2);
assert(d2.load(y) == Error::CorruptedArchive);

auto s3 = std::stringstream("");
Deserializer d3(s3);
assert(d3.load(y) == Error::CorruptedArchive);

auto s4 = std::stringstream("false 0");
Deserializer d4(s4);
assert(d4.load(y) == Error::CorruptedArchive);

auto s5 = std::stringstream("1400 false 15000");
Deserializer d5(s5);
assert(d5.load(y) == Error::NoError);
assert(y.a == 1400);
assert(y.b == false);
assert(y.c == 15000);

auto s6 = std::stringstream("10 true -300");
Deserializer d6(s6);
assert(d6.load(y) == Error::CorruptedArchive);

cout<<"Test is passed";
return 0;
}
