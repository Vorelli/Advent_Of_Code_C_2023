#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct valueAndNextPos {
  int value;
  int nextPos;
  bool isTouchingSymbol;
};

struct valueAndNextPos readNumAndIsTouchingSymbol(char **allLines, int r, int c,
                                                  int numRow, int numCol);
void solveAndPrintSolution1(char *fileName);
int calculateStartingR(int r, int length);
int calculateStartingC(int c, int length);
int getNumRows(char **problem);
