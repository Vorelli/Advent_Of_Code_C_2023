#include "part2.h"
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
  int *maxBag = generateEmptyCubeBag();
  int *curBag = generateEmptyCubeBag();
  struct NextPosAndValue nextPosAndGameId = getNextPosAndGameId(problemLine);
  for (unsigned long i = nextPosAndGameId.nextPos; i < strlen(problemLine);
       i++) {
    if (problemLine[i] >= '0' && problemLine[i] <= '9') {
      struct NextPosAndValue result = readNumber(problemLine, i);
      i = result.nextPos + 1;
      int color = problemLine[i] == 'r' ? 0 : problemLine[i] == 'g' ? 2 : 1;
      curBag[color] += result.value;
      i += color + 3;
    }

    if (problemLine[i] == ',')
      i++;

    if (problemLine[i] == ';') {
      compareBags(maxBag, curBag);
      i++;
      curBag = generateEmptyCubeBag();
    }
  }
  compareBags(maxBag, curBag);
  free(curBag);
  return bagPower(maxBag);
}
