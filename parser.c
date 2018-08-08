#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slothvm.h"

int progLen(FILE* f){
  char c;
  int count = 0;
  for (c = getc(f); c != EOF; c = getc(f)){
    if (c == '\n'){
      count = count + 1;
    }
  }
  fseek(f, 0, SEEK_SET);
  return count * 3;
}

struct sloth_program* parse(char* filepath){
  FILE* sFile;

  sFile = fopen(filepath, "r");
  if(sFile == NULL){
    fprintf(stderr, "[ERROR] File could not be opened.");
    exit(1);
  }

  int numCodes = progLen(sFile);
  ubyte* byteCode = malloc(sizeof(char) * numCodes);

	char c = '\0';
  int count = 0;
  char cmd[6];
  size_t codeNum = 0;
  unsigned char currentCode = 0;

	while(c != -1){
    c = fgetc(sFile);
		if(c == ' ' || c == '\n' || c == -1){
      cmd[count] = '\0';
			if(strcmp(cmd, "sloth") == 0){
        currentCode++;
      }else if(strcmp(cmd, "and") == 0){
        byteCode[codeNum] = currentCode;
        codeNum++;
        currentCode = 0x00;
      }else if(strcmp(cmd, "climb") == 0){
        byteCode[codeNum] = 0x0A;
        codeNum++;
      }else if(strcmp(cmd, "nap") == 0){
        currentCode = 0x00;
      }

      if(c != ' '){
        byteCode[codeNum] = currentCode;
        codeNum++;
        currentCode = 0;
      }
      count = 0;
		}else{
			cmd[count] = c;
      count++;
		}
	}

  // for(int i = 0; i < numCodes; i++){
  //   printf("%02x\n", byteCode[i]);
  // }
  struct sloth_program* S = malloc(sizeof(struct sloth_program));
  S->codes = byteCode;
  return S;
}
