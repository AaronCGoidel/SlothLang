#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
//Allocates a null terminated buffer to hold the line.
//Caller is responsible for freeing it.
//If the line is blank result will be empty
//If end of file is reached while reading a line, the last non null character
//in the buffer will be -1.
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
  //If at end of file put EOF in buffer
  if(c == -1){
    line[currentChar] = -1;
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
  size_t count = 0;//Current position in line
  char *line = 0x0;
  size_t len = 0;
  size_t codeNum = 0;
  unsigned char currentCode = 0;
  char hadToken = 0;

  while(1){
    count = 0;
    currentCode = 0;

    line = readline(sFile);
    len = strlen(line);
    //Make sure the line is okay
    if(line[0] == -1){
      free(line);
      break;
    }
    if(len == 0){
      free(line);
      continue;
    }
    
    c = line[0];
    while(c != 0 && c != -1 && c != '#' && count <= len){
      //Check keywords
      if(strncmp("slothy", line + count, 6) == 0){
	byteCode[codeNum] = 0x1;
	codeNum++;
	count += 6;
  hadToken = 1;
      } else if(strncmp("sloth", line + count, 5) == 0){
	currentCode++;
	count += 5;
  hadToken = 1;
      }else if(strncmp("and", line + count, 3) == 0){
	byteCode[codeNum] = currentCode;
	codeNum++;
	currentCode = 0;
	count += 3;
  hadToken = 1;
      }else if(strncmp("nap", line + count, 3) == 0){
	byteCode[codeNum] = 0x0;
	codeNum++;
	count += 3;
  hadToken = 1;
      }else{
	//Ignore any other characters
	count++;
      }
      c = line[count];
    }

    if(hadToken){
    byteCode[codeNum] = currentCode;
    codeNum++;
    hadToken = 0;
    }
    free(line);
  }
//for(int i = 0; i < numCodes; i++){
//printf("%x\n", byteCode[i]);
//  }

  struct sloth_program* S = malloc(sizeof(struct sloth_program));
  S->codes = byteCode;
  return S;
}
