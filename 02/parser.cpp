#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;

using OnNumber = void (*)(int token);
using OnString = void (*)(const char*token);
using OnStartOrStop  = void (*)();

OnNumber Callback_on_number;
OnString Callback_on_string;
OnStartOrStop Callback_on_start;
OnStartOrStop Callback_on_stop;

bool isspace(char c){
    return (c == '\n' || c == '\t' || c == ' ');
}

void register_on_number_callback(OnNumber callback){
    Callback_on_number = callback;
}

void register_on_string_callback(OnString callback){
    Callback_on_string = callback;
}

void register_on_start(OnStartOrStop callback){
    Callback_on_start = callback;
}

void register_on_stop(OnStartOrStop callback){
    Callback_on_stop = callback;
}

void parser(const char* text){
    if(!Callback_on_start || !Callback_on_stop || !Callback_on_string || !Callback_on_number) return;
    Callback_on_start();
    string token = "";
    const char* pos;
    while (*text){
        while (isspace(*text)){
        ++text;
        }
        while (!isspace(*text) && *text){
            token += *text;
            ++text;
        }
        pos = text - 1;
        if (isdigit(*pos)) Callback_on_number(stoi(token));
        else if(!isspace(*pos)) Callback_on_string(token.c_str());
        token.erase();
    }
    Callback_on_stop();
}

