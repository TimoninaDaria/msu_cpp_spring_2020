#pragma once

void register_on_number_callback(void (*callback)(const char*token));
void register_on_string_callback(void (*callback)(const char*token));
void register_on_stop(void (*callback)());
void register_on_start(void (*callback)());
void parser(const char* text);
