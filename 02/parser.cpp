#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <string>

using namespace std;

using OnNumber = void (*)(int token);
using OnString = void (*)(const string& token);
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

void parser(const string& text){
    char pos;
    string token = "";
    if(!Callback_on_start || !Callback_on_stop || !Callback_on_string || !Callback_on_number) return;
    Callback_on_start();
    for (int i =0; i < text.length(); ++i){
        while (isspace(text[i])){
        ++i;
        }
        while (!isspace(text[i]) && text[i]){
            token += text[i];
            ++i;
        }
        pos = text[i- 1];
        if (isdigit(pos)) Callback_on_number(stoi(token));
        else if(!isspace(pos)) Callback_on_string(token);
        token.erase();
    }
    Callback_on_stop();
}

