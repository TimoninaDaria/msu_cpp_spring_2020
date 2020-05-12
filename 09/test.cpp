#include "merge.h"
#include <cassert>

using namespace std;

void test(const string inputfile, const string outputfile){

    ifstream f1(inputfile, ios::binary);
    ifstream f2(outputfile, ios::binary);
    int len_input = 0;
    int len_output = 1;
    uint64_t x, y;

    while(!f1.eof())
	{
	    f1.read(reinterpret_cast<char*>(&y), sizeof(uint64_t));
	    ++len_input;
    }

	f2.read(reinterpret_cast<char*>(&x), sizeof(uint64_t));

	while(!f2.eof())
	{
	    f2.read(reinterpret_cast<char*>(&y), sizeof(uint64_t));
	    ++len_output;
        assert(x <= y);
        x = y;
    }

    assert(len_input == len_output);

}

int main(){

    int isok = sort_by_merge("numbers.dat");
    assert(isok == 0);
    test("numbers.dat", "result.dat");
    return 0;
}
