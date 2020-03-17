#include "parser.h"
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <stdint.h>
#include <cstring>

using namespace std;

void Callback_on_number(int str)
{
    cout<<"number "<<str<<"\n";
}

void Callback_on_string(const string& str)
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

    string str;

    cout<<"Test 1\n";
    cout<<"Let's parse string\n\n'\n hhjf\n\n 2662    \nhhhh\t255621\n'\n";
    cout<<"\nResult of parsing:\n\n";
    str = "\n hhjf\n\n 2662    \nhhhh\t255621\n";
    parser(str);

    cout<<"\nTest 2\n";
    cout<<"Let's parse string\n\n'121 tgkkgk ::\n\t4344\t'\n";
    cout<<"\nResult of parsing:\n\n";
    str = "121 tgkkgk ::\n\t4344\t";
    parser(str);

    cout<<"\nTest 3\n";
    cout<<"Let's parse string\n\n'\t\t445 ttt\tttt'\n";
    cout<<"\nResult of parsing:\n\n";
    str = "\t\t445 ttt\tttt";
    parser(str);

    return 0;
}
