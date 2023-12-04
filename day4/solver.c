#include "solver.h"

void solveAndPrintSolution1(char *fileName, int solveLine(char *line)) {
  FILE *f = fopen(fileName, "r");
  struct ArrayAndDims fileInArrayFormat = readFileIntoArray(f);
  unsigned long long totalPoints = 0;
  for (int i = 0; i < fileInArrayFormat.numRow; i++) {
    totalPoints += solveLine(fileInArrayFormat.array[i]);
  }
  printf("Final solution: %llu\n", totalPoints);
  fclose(f);
}
