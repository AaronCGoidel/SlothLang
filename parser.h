#include "slothvm.h"

#ifndef _PARSER_H_
#define _PARSER_H_

struct sloth_program* parse(char* filename);
void freeProgram(struct sloth_program* P);

#endif
