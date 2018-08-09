#include <stdio.h>
#include "parser.h"
#include "slothvm.h"

int main(int argc, char **argv){
  if(argc != 2){
    fprintf(stderr, "Usage: sloth <source file>\n");
    return 1;
  }
  char* fileName = argv[1];
  struct sloth_program* program = parse(fileName);
  int x = execute(program);
  printf("%d\n", x);
  return 0;
}
