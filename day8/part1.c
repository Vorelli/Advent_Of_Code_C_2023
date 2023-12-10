#include "part1.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Failed to provide exactly one arguments. Just looking for "
           "filename.\nRunning tests.\n");
    runPartOneTests(solvePartOne);
    return 1;
  }

  solvePartOne(argv[1]);
  return 0;
}

unsigned long solvePartOne(char *fileName) {
  HashMap *h = create();
  char *instructions = loadIntoMap(fileName, h);
  return solvePOne(h, instructions, "AAA", "ZZZ");
}
