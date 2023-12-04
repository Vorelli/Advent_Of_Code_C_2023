#include "solver.h"

int *generateBag() {
  int *genericBag;
  genericBag = malloc(sizeof(int) * 3);
  return genericBag;
}

int *generateEmptyCubeBag() {
  int *genericBag = generateBag();
  for (int i = 0; i < 3; i++)
    genericBag[i] = 0;
  return genericBag;
}

int *generateBaseCubeBag() {
  int *genericBag = generateBag();
  genericBag[0] = 12;
  genericBag[1] = 14;
  genericBag[2] = 13;
  return genericBag;
}

int bagPower(int *bag) {
  int res = bag[0] * bag[1] * bag[2];
  printf("Bag power: %d\n", res);
  return res;
}
void compareBags(int *maxBag, int *curBag) {
  for (unsigned long i = 0; i < sizeof(curBag); i++) {
    if (curBag[i] > maxBag[i])
      maxBag[i] = curBag[i];
  }
}

void solve(char *filename, int solveLine(char *line)) {
  FILE *problem = getFile(filename);
  char line[BUFSIZ];
  long long sum = 0;
  while (fgets(line, BUFSIZ, problem) != NULL) {
    sum += solveLine(line);
    printf("Sum after Game %d: %lld\n", getNextPosAndGameId(line).value, sum);
  }
  printf("Solution: %lld\n", sum);
}

struct NextPosAndValue getNextPosAndGameId(char *problemLine) {
  for (unsigned long i = 0; i < strlen(problemLine); i++) {
    if (problemLine[i] >= '0' && problemLine[i] <= '9') {
      return readNumber(problemLine, i);
    }
  }
  struct NextPosAndValue a = {0, 0};
  return a;
}

bool anyFalse(int *bagArr) {
  for (unsigned long i = 0; i < sizeof bagArr; i++) {
    if (bagArr[i] < 0)
      return true;
  }
  return false;
}
