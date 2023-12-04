#include "solver.h"

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
    printf("%c\n", problem[i][0]);
  };
  printf("\n");
  return i;
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
  // printf("R: %d length: %d\n", r, length);
  r--;
  // printf("less than r: %s\n", r < 0 ? "true" : "false");
  // printf("greater than or equal to length: %s\n",
  // r >= length ? "true" : "false");
  int end = r < 0 ? 0 : (r >= length ? length - 1 : r);
  // printf("startingR Calculated: %d\n", end);
  return end;
}
int calculateStartingC(int c, int length) {
  c--;
  return c < 0 ? 0 : c >= length ? length - 1 : c;
}
