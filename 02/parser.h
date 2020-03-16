#pragma once

using OnNumber = void (*)(int token);
using OnString = void (*)(const char*token);
using OnStartOrStop  = void (*)();

void register_on_number_callback(OnNumber callback);
void register_on_string_callback(OnString callback);
void register_on_stop(OnStartOrStop callback);
void register_on_start(OnStartOrStop callback);
void parser(const char* text);
