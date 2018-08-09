#include <stdlib.h>

#ifndef _SLOTHVM_H_
#define _SLOTHVM_H_

enum opcodes {
  EXIT  = 0x00,
  PUSH  = 0x01,
  ADD   = 0x02, 
  SUB   = 0x03, 
  MULT  = 0x04, 
  DIV   = 0x05, 
  COMP  = 0x06,
  INP  = 0x07,
  OUT  = 0x08,
  GOTO  = 0x09
};

enum compCodes {
  EQ  = 0x01,
  NEQ = 0x02,
  LT  = 0x03,
  LE  = 0x04,
  GT  = 0x05,
  GE  = 0x06
};

enum typeCode {
  INT = 0x01,
  CHR = 0x02
};

typedef uint8_t ubyte;

struct sloth_program {
  ubyte* codes;
  size_t pc;
};

int execute(struct sloth_program* sbin);

#endif
