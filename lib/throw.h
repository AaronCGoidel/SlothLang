#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#ifndef _THROW_H_
#define _THROW_H_
void mathErr(char* msg);
void opErr(char* type, uint8_t code);
#endif
