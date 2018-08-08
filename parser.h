#include "c0vm.h"

#ifndef _H_READ_PROGRAM
#define _H_READ_PROGRAM

struct bc0_file* read_program(string filename);
void free_program(struct bc0_file *program);

#endif // _H_READ_PROGRAM
