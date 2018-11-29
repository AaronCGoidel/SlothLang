#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "stack.h"

typedef struct list_node list;
struct list_node{
  int data;
  struct list_node* next;
};

typedef struct stack_header stack;
struct stack_header{
  list* top;
  list* bottom;
};

bool sstack_empty(stack* S){
  return S->top == S->bottom;
}

stack* sstack_new(){
  stack* S = malloc(sizeof(stack));
  list* p = malloc(sizeof(list));

  S->top = p;
  S->bottom = p;

  return S;
}

void spush(stack* S, int x){
  list* p = malloc(sizeof(list));
  p->data = x;
  p->next = S->top;
  S->top = p;
}

int spop(stack* S){
  int x = S->top->data;
  list* q = S->top;
  S->top = S->top->next;
  free(q);

  return x;
}

int speek(stack* S, int pos){
  list* l = S->top;
  for(; pos > 0; pos--){
    l = l->next;
  }
  return l->data;
}

void sprint(stack* S){
  printf("|");

  list* l = S->top;
  while(l != S->bottom){
    printf("%d ", l->data);
    l = l->next;
  }
  printf("\n");
}

void sstack_free(stack* S){
  while(S->top != S->bottom){
    list* p = S->top;
    S->top = S->top->next;
    free(p);
  }

  free(S->top);
  free(S);
}
