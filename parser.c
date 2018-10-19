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

void freeProgram(struct sloth_program* P){
  free(P->codes);
  free(P);
}

//Read a line delimited by \n from file
//Result is null terminated
//If the line is blank result will be empty
//If end of file is reached while reading a line, the last non null character
//in the buffer will be -1. Or, if readline is called on a file that has been
//read completely to the end, the buffer will be empty.
char *readline(FILE *file){
  //Default length of 100 characters - feel free to use a different value
  const size_t default_len = 100;
  char *line = malloc(sizeof(char) * default_len);
  size_t len = default_len;
  size_t currentChar = 0;
  char c = '\0';

  while(c != -1){
    c = fgetc(file);
    //Get more memory to hold the line if needed
    if(currentChar == len){
      len *= 2;
      line = realloc(line, len);
    }
    if(c == '\n'){
      break;
    }

    line[currentChar] = c;
    currentChar++;
  }

  line[currentChar] = '\0';
  return line;
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
    if(c == '#'){
      while(c != '\n'){
        c = fgetc(sFile);
      }
      fseek(sFile, -1, SEEK_CUR);
    }else if(c == ' ' || c == '\n' || c == -1){
      cmd[count] = '\0';
      if(strcmp(cmd, "sloth") == 0){
        currentCode++;
      }else if(strcmp(cmd, "and") == 0){
        byteCode[codeNum] = currentCode;
        codeNum++;
        currentCode = 0x00;
      }else if(strcmp(cmd, "slothy") == 0){
        byteCode[codeNum] = 0x01;
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
  //   printf("%x\n", byteCode[i]);
  // }

  struct sloth_program* S = malloc(sizeof(struct sloth_program));
  S->codes = byteCode;
  return S;
}
