#include "part2.h"
#include <limits.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Failed to provide exactly one arguments. Just looking for "
           "filename.\nRunning tests.\n");
    runPartTwoTests(solvePartTwo);
    return 1;
  }

  solvePartTwo(argv[1]);
  return 0;
}

bool lessThanOrEqualToAll(unsigned long val, unsigned long *vals) {
  bool result = true;
  for (unsigned long i = 0; vals[i] != ULONG_MAX; i++) {
    printf("COMPARING %lu to %lu SHOULD BE FALSE TO CONTINUE: %s\n", val,
           vals[i], (val > vals[i]) ? "TRUE" : "FALSE");
    if (val > vals[i]) {
      result = false;
    }
  }
  printf("RETURNING: %s\n", result ? "true" : "False");
  return result;
}

bool divisibleByAll(unsigned long val, unsigned long *vals) {
  for (unsigned long i = 0; vals[i] != ULONG_MAX; i++) {
    printf("REMAINDER OF %lumod%lu : %lu ", vals[i], val, (vals[i] % val));
    if (vals[i] % val != 0)
      return false;
  }
  printf("\n DIVISIBLE BY ALL!!!\n");
  return true;
}

unsigned long sumOfAll(unsigned long *values, unsigned long gcd) {
  printf("GCD: %lu\n", gcd);
  unsigned long i = 1;
  for (int j = 0; values[j] != ULONG_MAX; j++) {
    printf("i %lu MULTIPLYING BY %lu ", i, (values[j] / gcd));
    i = (values[j] / gcd) * i;
    printf("i after mult: %lu\n", i);
  }
  printf("SUM OF ALL: %lu\n", i);
  return i;
}

long long GCD(long long int a, long long int b) {
  if (b == 0)
    return a;
  return GCD(b, a % b);
}

long long LCM(long long a, long long b) {
  if (a > b)
    return (a / GCD(a, b)) * b;
  else
    return (b / GCD(a, b)) * a;
}

unsigned long solvePartTwo(char *fileName) {
  HashMap *h = create();
  char *instructions = loadIntoMap(fileName, h);
  Node **currentNodes = getAllNodes(h, 'A');
  free(h);
  unsigned long values[676];
  memset(values, INT_MAX, 676 * sizeof(unsigned long));
  for (short j = 0; j < 676 && currentNodes[j] != NULL; j++) {
    h = create();
    free(loadIntoMap(fileName, h));
    values[j] = solvePOne(h, instructions, currentNodes[j]->value, "**Z");
    free(h);
  }
  unsigned long res = values[0];
  for (short j = 1; j < 676 && currentNodes[j] != NULL; j++) {
    res = res / GCD(res, values[j]) * values[j];
    printf("SOLUTION FOR NODE #%d: %lu\n", j, values[j]);
  }

  printf("Solution is %lu\n", res);
  free(currentNodes);
  return 0;
}
