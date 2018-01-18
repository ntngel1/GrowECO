#ifndef GROWECO_DEBUG_H_
#define GROWECO_DEBUG_H_

#include <Arduino.h>
#include <stdio.h>

char* __get_current_time__();
void debug_error(const char* err);
void debug_message(const char* msg);

#endif