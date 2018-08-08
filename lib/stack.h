#include <stdbool.h>
#include <stdlib.h>

#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack_header *sstack_t;

sstack_t sstack_new();

void spush(sstack_t S, int x);

int spop(sstack_t S);

void sstack_free(sstack_t S);
#endif
