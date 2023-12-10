#include "part1.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Failed to provide exactly one arguments. Just looking for "
           "filename.\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  ArrayAndDims fileContents = readFileIntoArray(f);
  fclose(f);
  unsigned long sol = 0;
  for (int i = 0; i < fileContents.numRow; i++) {
    long long nextInSeq = getSolutionForLine(fileContents.array[i], false);
    printf("Found solution for line #%d: %lld total: %lu\n", i, nextInSeq, sol);
    sol += nextInSeq;
  }
  printf("Total solution: %lu\n", sol);
}
