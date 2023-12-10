#include "test.h"

void part1TestOne(unsigned long (*solvePartOne)(char *)) {
  assert(solvePartOne("practice1.txt") == 2);
}

void part1TestTwo(unsigned long (*solvePartOne)(char *)) {
  assert(solvePartOne("practice2.txt") == 6);
}

void part2TestOne(unsigned long (*solvePartOne)(char *)) {
  assert(solvePartOne("practice3.txt") == 6);
}

void runPartOneTests(unsigned long (*solvePartOne)(char *)) {
  int numFunctions = 2;
  void (*functions[numFunctions])(unsigned long (*solvePartOne)(char *));
  functions[0] = part1TestOne;
  functions[1] = part1TestTwo;
  runTests(solvePartOne, functions, numFunctions);
}
void runPartTwoTests(unsigned long (*solvePartTwo)(char *)) {
  int numFunctions = 1;
  void (*functions[numFunctions])(unsigned long (*solvePartTwo)(char *));
  functions[0] = part2TestOne;
  runTests(solvePartTwo, functions, numFunctions);
}
