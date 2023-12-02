#include "part1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  solveAndPrintSolution();
  return 0;
}

long getFileLength(FILE *problemFile) {
  fseek(problemFile, 0, SEEK_END);
  long size = ftell(problemFile);
  fseek(problemFile, 0, SEEK_SET);
  return size;
}

void solveAndPrintSolution() {
  FILE *problemFile = fopen("problem.txt", "r");
  long size = getFileLength(problemFile);
  int sum = 0;
  char problemArr[BUFSIZ];
  while (fgets(problemArr, sizeof problemArr, problemFile) != NULL) {
    int firstNumber = findNumber(problemArr, size, 0, true);
    int secondNumber =
        findNumber(problemArr, size, strlen(problemArr) - 1, false);
    sum += (firstNumber * 10) + secondNumber;
  }
  printf("Result %d\n", sum);
}

int findNumber(char file[], long size, unsigned long start, bool toTheRight) {
  char a;
  for (long i = start; toTheRight ? i < size : i >= 0;
       i += toTheRight ? 1 : -1) {
    a = file[i];
    int num = atoi(&a);
    if (num != 0 && num < 10)
      return num;
  }
  return 0;
}
