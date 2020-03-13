#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cstring>

using namespace std;

void (*Callback_on_number)(const char*token);
void (*Callback_on_string)(const char*token);
void (*Callback_on_start)();
void (*Callback_on_stop)();

bool isspace(char c){
    return (c == '\n' || c == '\t' || c == ' ');
}

void register_on_number_callback(void (*callback)(const char*token)){
    Callback_on_number = callback;
}

void register_on_string_callback(void (*callback)(const char*token)){
    Callback_on_string = callback;
}

void register_on_start(void (*callback)()){
    Callback_on_start = callback;
}

void register_on_stop(void (*callback)()){
    Callback_on_stop = callback;
}

void parser(const char* text){
    if(!Callback_on_start || !Callback_on_stop || !Callback_on_string || !Callback_on_number) return;
    (*Callback_on_start)();
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
        if (isdigit(*pos)) (*Callback_on_number)(token.c_str());
        else if(!isspace(*pos)) (*Callback_on_string)(token.c_str());
        token.erase();
    }
    (*Callback_on_stop)();
}

