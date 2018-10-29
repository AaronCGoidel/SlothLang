#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "slothvm.h"

int main(){
  // Test Parser
  struct sloth_program* program = parse("Examples/HelloWorld.sloth");
  printf("TESTING PARSER (1/3)\n");
  assert(program->codes[0] == 1);
  assert(program->codes[1] == 3);
  assert(program->codes[2] == 1);
  assert(program->codes[14] == 8);
  assert(program->codes[17] == 10);
  freeProgram(program);
  printf("----------------------------\n");

  program = parse("Examples/Gamut.sloth");
  printf("TESTING PARSER (2/3)\n");
  //Make sure all the instruction codes are in the parsed program
#define NUM_CODES 11
  int histogram[NUM_CODES] = {0,0,0,0,0,0,0,1,0,0,0};
  int i = 0;
  int pc = program->codes[i];
  while(pc != 0){
    if(pc > 0 && pc < NUM_CODES){
        histogram[pc]++;
    }
    i++;
    pc = program->codes[i];
  }
  //Skip checking for 0x0, since that is exit and we know all programs have to use it
  for(i = 1; i < NUM_CODES; i++){
    assert(histogram[i] > 0);
  }
  free(program);
  printf("PARSER TEST PASSED\n");
  printf("----------------------------\n");


  // Test Execution
  program = parse("Examples/Count.sloth");
  printf("TESTING PROGRAM EXECUTION (3/3)\n");
  int x = execute(program);
  printf("Returned: %d\n", x);
  assert(x == 11);
  printf("EXECUTION TEST PASSED\n");
  printf("----------------------------\n");

  freeProgram(program);
  return 0;
}
