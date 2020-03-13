#include "parser.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>

using namespace std;

void Callback_on_number(const char* str)
{
    cout<<"number "<<str<<"\n";
}

void Callback_on_string(const char* str)
{
    cout<<"string "<<str<<"\n";
}

void Callback_on_start()
{
    cout<<"Start"<<"\n";
}

void Callback_on_stop()
{
    cout<<"Stop"<<"\n";
}

int main(){
    register_on_string_callback(Callback_on_string);
    register_on_number_callback(Callback_on_number);
    register_on_start(Callback_on_start);
    register_on_stop(Callback_on_stop);

    cout<<"Test 1\n";
    cout<<"Let's parse string\n\n'\n hhjf\n\n 2662    \nhhhh\t255621\n'\n";
    cout<<"\nResult of parsing:\n\n";
    parser("\n hhjf\n\n 2662    \nhhhh\t255621\n");

    cout<<"\nTest 2\n";
    cout<<"Let's parse string\n\n'121 tgkkgk ::\n\t4344\t'\n";
    cout<<"\nResult of parsing:\n\n";
    parser("121 tgkkgk ::\n\t4344\t");

    cout<<"\nTest 3\n";
    cout<<"Let's parse string\n\n'\t\t445 ttt\tttt'\n";
    cout<<"\nResult of parsing:\n\n";
    parser("\t\t445 ttt\tttt");

    return 0;
}
