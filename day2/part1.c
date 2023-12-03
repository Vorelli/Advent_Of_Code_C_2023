#include "part1.h"
#include <stdio.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Failed to provide filename or too many arguments. Only filename "
           "expected");
    return 1;
  }
  solve(argv[1], solveLine);
}

int solveLine(char *problemLine) {
  struct NextPosAndValue gameIdAndPos = getNextPosAndGameId(problemLine);
  int *bag = generateBaseCubeBag();

  for (unsigned long i = gameIdAndPos.nextPos; i < strlen(problemLine); i++) {
    if (problemLine[i] >= '0' && problemLine[i] <= '9') {
      struct NextPosAndValue result = readNumber(problemLine, i);
      i = result.nextPos + 1;
      int color = problemLine[i] == 'r' ? 0 : problemLine[i] == 'g' ? 2 : 1;
      printf("color first initial: %c\n", problemLine[i]);
      bag[color] -= result.value;
    }
    if (problemLine[i] == ',')
      i++;
    if (problemLine[i] == ';') {
      i++;
      if (anyFalse(bag))
        return 0;
      free(bag);
      bag = generateBaseCubeBag();
    }
  }
  printf("Final line %d results: red: %d blue: %d green: %d\n",
         gameIdAndPos.value, bag[0], bag[1], bag[2]);
  return anyFalse(bag) ? 0 : gameIdAndPos.value;
}
