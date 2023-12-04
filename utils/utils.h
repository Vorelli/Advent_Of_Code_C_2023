#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NextPosAndValue {
  int nextPos;
  int value;
};
struct ArrayAndDims {
  char **array;
  int numRow;
  int numCol;
};

long getFileLength(FILE *problemFile);
FILE *getFile(char *fileName);
struct ArrayAndDims readFileIntoArray(FILE *f);
unsigned long fileSize(FILE *f);
struct NextPosAndValue readNumber(char *problemLine, int index);
int min(int a, int b);
int max(int a, int b);
bool isNumber(char ch);
bool isSymbol(char **problem, unsigned long r, unsigned long c);
bool isNumberOrIsNegative(char **problem, unsigned long r, unsigned long c);
