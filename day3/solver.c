#include "solver.h"
#include <stdio.h>

struct valueAndNextPos readNumAndIsTouchingSymbol(char **allLines, int row,
                                                  int col, int numRow,
                                                  int numCol) {
  struct NextPosAndValue numAndLen = readNumber(allLines[row], col);
  int startingR = max(0, row - 1); // calculateStartingR(r, numRow);
  int startingC = max(0, col - 1);
  bool touchesSymbol = false;
  for (int r = startingR;
       r < min(numRow, row == 0 ? startingR + 2 : startingR + 3); r++) {
    for (int c = startingC; c < min(numCol - 1, numAndLen.nextPos + 1); c++) {
      if (isSymbol(allLines, r, c)) {
        touchesSymbol = true;
        break;
      }
    }
    if (touchesSymbol)
      break;
  }

  struct valueAndNextPos ret = {numAndLen.value, numAndLen.nextPos,
                                touchesSymbol};
  return ret;
}

int getNumRows(char **problem) {
  int i = 0;
  for (; problem[i][0] != '\0'; i++) {
  };
  return i;
}

void solveAndPrintSolution2(char *fileName) {
  FILE *f = fopen(fileName, "r");
  struct ArrayAndDims resultF = readFileIntoArray(f);
  char **fileInArrayFormat = resultF.array;
  long long res =
      findAllGears(fileInArrayFormat, resultF.numRow, resultF.numCol);
  printf("Result for part two: %lld\n", res);
  fclose(f);
}

long long findAllGears(char **grid, unsigned long numRows,
                       unsigned long numCols) {
  long long res = 0;

  for (unsigned long i = 0; i < numRows; i++) {
    for (unsigned long j = 0; j < numCols; j++) {
      if (grid[i][j] != '*')
        continue;
      int *surrounding = surroundedByTwoNumbers(grid, i, j, numRows, numCols);
      if (surrounding != NULL &&
          !(surrounding[0] == 0 && surrounding[1] == 0)) {
        res += (surrounding[0] * surrounding[1]);
      }
      free(surrounding);
    }
  }
  return res;
}

int *surroundedByTwoNumbers(char **grid, unsigned long row, unsigned long col,
                            unsigned long numRow, unsigned long numCol) {
  int startingR = max(0, row - 1);
  int startingC = max(0, col - 1);
  int numNumbers = 0;
  int *res = malloc(sizeof(int) * 2);
  for (int r = startingR;
       r < min(numRow, row == 0 ? startingR + 2 : startingR + 3); r++) {
    for (int c = startingC; c < min(numCol - 1, col + 2); c++) {
      if (isNumber(grid[r][c])) {
        int num = findBeginningAndReadNumber(grid[r], c);
        res[numNumbers++] = num;
        if (numNumbers > 2)
          break;
        if (isNumber(grid[r][min(numCol - 1, c + 1)]))
          break; // move on to next row
      }
    }
    if (numNumbers >= 2)
      break;
  }
  return numNumbers == 2 ? res : NULL;
}

void solveAndPrintSolution1(char *fileName) {
  FILE *f = fopen(fileName, "r");
  struct ArrayAndDims resultF = readFileIntoArray(f);
  char **fileInArrayFormat = resultF.array;
  unsigned long sum = 0;
  for (int i = 0; i < resultF.numRow; i++) {
    for (int j = 0; j < resultF.numCol; j++) {
      bool isANumber = isNumber(fileInArrayFormat[i][j]);
      if (isANumber) {
        struct valueAndNextPos result = readNumAndIsTouchingSymbol(
            fileInArrayFormat, i, j, resultF.numRow, resultF.numCol);
        if (result.isTouchingSymbol)
          sum += result.value;
        j = result.nextPos - 1;
      }
    }
  }
  printf("The solution is: %lu\n", sum);
  free(fileInArrayFormat);
  fclose(f);
}

int calculateStartingR(int r, int length) {
  r--;
  int end = r < 0 ? 0 : (r >= length ? length - 1 : r);
  return end;
}
int calculateStartingC(int c, int length) {
  c--;
  return c < 0 ? 0 : c >= length ? length - 1 : c;
}
