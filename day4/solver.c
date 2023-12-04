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

void solveAndPrintSolution2(char *fileName, int solveLine(char *line)) {
  FILE *f = fopen(fileName, "r");
  struct ArrayAndDims fileInArrayFormat = readFileIntoArray(f);
  unsigned long long totalCards = 0;
  int numCards[fileInArrayFormat.numRow];
  memset(numCards, 0, sizeof(int) * fileInArrayFormat.numRow);
  for (int i = 0; i < fileInArrayFormat.numRow; i++) {
    int numMatches = solveLine(fileInArrayFormat.array[i]);
    int currentMultiplier = numCards[i];
    for (int j = i + 1; j <= i + numMatches; j++) {
      numCards[j] += (currentMultiplier + 1);
    }
    totalCards += currentMultiplier + 1;
  }
  printf("Final solution: %llu\n", totalCards);
  fclose(f);
}
