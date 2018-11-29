#include <stdbool.h>
#include <stdlib.h>

#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack_header *sstack_t;

sstack_t sstack_new();

void spush(sstack_t S, int x);

bool sstack_empty(sstack_t S);

int spop(sstack_t S);

int speek(sstack_t S, int pos);

void sprint(sstack_t S);

void sstack_free(sstack_t S);
#endif
