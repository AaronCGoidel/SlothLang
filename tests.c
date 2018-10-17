#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "slothvm.h"

int main(){
  // Test Parser
  struct sloth_program* program = parse("Examples/HelloWorld.sloth");
  printf("TESTING PARSER (1/2)\n");
  assert(program->codes[0] == 1);
  assert(program->codes[1] == 3);
  assert(program->codes[2] == 1);
  assert(program->codes[14] == 8);
  assert(program->codes[17] == 10);
  printf("PARSER TEST PASSED\n");
  printf("----------------------------\n");
  freeProgram(program);


  // Test Execution
  program = parse("Examples/Count.sloth");
  printf("TESTING PROGRAM EXECUTION (2/2)\n");
  int x = execute(program);
  printf("Returned: %d\n", x);
  assert(x == 11);
  printf("EXECUTION TEST PASSED\n");
  printf("----------------------------\n");

  freeProgram(program);
  return 0;
}
