#include "throw.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void mathErr(char* msg){
  if(msg != NULL) fprintf(stderr, "[ERROR] %s\n", msg);
  raise(SIGFPE);
}

void opErr(char* type, uint8_t code){
  if(type != NULL){
    fprintf(stderr, "[ERROR] invalid %s code: 0x%02x\n", type, code);
  }
  raise(SIGILL);
}
