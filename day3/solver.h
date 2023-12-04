#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct valueAndNextPos {
  int value;
  int nextPos;
  bool isTouchingSymbol;
};

struct NumbersSurrounding {
  int number1;
  int number2;
};

struct valueAndNextPos readNumAndIsTouchingSymbol(char **allLines, int r, int c,
                                                  int numRow, int numCol);
void solveAndPrintSolution1(char *fileName);
void solveAndPrintSolution2(char *fileName);
int *surroundedByTwoNumbers(char **grid, unsigned long r, unsigned long c,
                            unsigned long numRows, unsigned long numCols);
long long findAllGears(char **grid, unsigned long numRows,
                       unsigned long numCols);
int calculateStartingR(int r, int length);
int calculateStartingC(int c, int length);
int getNumRows(char **problem);
