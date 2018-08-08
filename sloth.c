#include <stdio.h>
#include "parser.h"
#include "slothvm.h"

int main(){
  struct sloth_program* program = parse("test.sloth");
  int x = execute(program);
  printf("%d\n", x);
  return 0;
}
