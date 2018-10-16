#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "slothvm.h"
#include "lib/stack.h"
#include "lib/throw.h"

int execute(struct sloth_program* sbin){
  sstack_t S = sstack_new();
  size_t pc = 0;

  ubyte* P = sbin->codes;

  bool run = true;
  while(run){
    // sprint(S);
    switch(P[pc]){
      case EXIT: {
        if(sstack_empty(S)){
          sstack_free(S);
          return 0;
        }
        int x = spop(S);
        sstack_free(S);
        return x;
      }
      case ADD: {
        int b = spop(S);
        int a = spop(S);
        spush(S, a + b);

        pc++;
        break;
      }
      case SUB: {
        int b = spop(S);
        int a = spop(S);
        spush(S, a - b);

        pc++;
        break;
      }
      case MULT: {
        int b = spop(S);
        int a = spop(S);
        spush(S, a * b);

        pc++;
        break;
      }
      case DIV: {
        int b = spop(S);
        int a = spop(S);

        // Handle div by 0 errors
        if(b == 0) mathErr("division by zero");
        if(a == INT_MIN && b == -1) mathErr("division by zero");

        spush(S, a/b);
      
        pc++;
        break;
      }
      case COMP: {
        int b = spop(S);
        int a = spop(S);

        pc++;
        bool res = false;
        switch(P[pc]){
          case EQ: {
            res = a == b;
            break;
          }
          case NEQ: {
            res = a != b;
            break;
          }
          case LT: {
            res = a < b;
            break;
          }
          case LE: {
            res = a <= b;
            break;
          }
          case GT: {
            res = a > b;
            break;
          }
          case GE: {
            res = a >= b;
            break;
          }
          default: {
            opErr("comparison", P[pc]);
          }
        }
        spush(S, (int)res);

        pc++;
        break;
      }
      case INP: {
        pc++;

        switch(P[pc]){
          case INT: {
            int x;
            scanf(">%d", &x);
            spush(S, x);
            break;
          }
          case CHR: {
            char x;
            scanf(">%c", &x);
            spush(S, (int)x);
            break;
          }
          default: {
            opErr("input type", P[pc]);
          }
        }

        pc++;
        break;
      }
      case OUT: {
        pc++;

        switch(P[pc]){
          case INT: {
            int x = spop(S);
            printf("%d", x);
            break;
          }
          case CHR: {
            char x = spop(S);
            printf("%c", x);
            break;
          }
          default: {
            opErr("output type", P[pc]);
          }

          pc++;
          break;
        }

        pc++;
        break;
      }
      case GOTO: {
        pc++;
        if(spop(S) == 1){
          pc = P[pc];
        }else{
          pc++;
        }
        break;
      }
      case PUSH: {
        pc++;
        spush(S, P[pc]);

        pc++;
        break;
      }
      case DUP: {
        int x = spop(S);
        spush(S, x);
        spush(S, x);

        pc++;
        break;
      }
      default: {
        opErr("operation", P[pc]);
      }
    }
  }
  
  
  
  return 0;
}
