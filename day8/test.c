#include <assert.h>
#include <stdio.h>

void part1TestOne(unsigned long (*solvePartOne)(char *)) {
  assert(solvePartOne("practice1.txt") == 2);
}

void part1TestTwo(unsigned long (*solvePartOne)(char *)) {
  assert(solvePartOne("practice2.txt") == 6);
}

void runTests(int argc, char **argv, unsigned long (*solvePartOne)(char *)) {
  int a = argc;
  int b = a * sizeof(argv);
  if (b) {
  } else {
  }
  int numFunctions = 2;
  void (*functions[numFunctions])(unsigned long (*solvePartOne)(char *));
  functions[0] = part1TestOne;
  functions[1] = part1TestTwo;
  int i;
  for (i = 0; i < numFunctions; i++) {
    printf("Running function at %d\n", i);
    if (functions[i] == NULL)
      break;
    functions[i](solvePartOne);
  }
  printf("%d Test%s Complete!!\n", i, i == 1 ? "" : "s");
}
