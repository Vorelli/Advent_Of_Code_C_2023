#include "solver.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

long long getSolutionForLine(char *problemLine, bool toTheRight) {
  long long *sequence = loadLineIntoSequence(problemLine);
  long long sol = solutionGen(sequence, toTheRight);
  return sol;
}

long long solutionGen(long long *sequence, bool toTheRight) {
  long long *diff = malloc(sizeof(long long) * MAX_ELEMENTS);
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    diff[i] = LLONG_MAX;
  }
  bool allZeros = true;

  // printf("FIRST ELEMENT OF SEQUENCE: %llu\n", sequence[0]);
  long long last = sequence[0];
  for (int i = 1; sequence[i] != LLONG_MAX; i++) {
    diff[i - 1] = sequence[i] - sequence[i - 1];
    // printf("Diff current: %lld\n", diff[i - 1]);
    if (diff[i - 1] != 0)
      allZeros = false;
    if (toTheRight)
      last = sequence[i];
  }
  if (allZeros) {
    return last;
  }
  long long nextInSeq = solutionGen(diff, toTheRight);
  // printf("FOUND SOLUTION OF DIFF: %lld SUM: %lld\n", nextInSeq, last);
  free(diff);
  return last - nextInSeq;
}

long long *loadLineIntoSequence(char *problemLine) {
  long long *sequence = malloc(MAX_ELEMENTS * sizeof(long long));
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    sequence[i] = LLONG_MAX;
  }
  unsigned long seqNum = 0;
  unsigned long numChar = 0;
  char numArr[MAX_ELEMENTS];
  memset(numArr, 0, MAX_ELEMENTS);
  for (int i = 0; i < MAX_ELEMENTS && problemLine[i] != '\0'; i++) {
    if (problemLine[i] == ' ') {
      sequence[seqNum++] = atoll(numArr);
      memset(numArr, 0, MAX_ELEMENTS);
      numChar = 0;
    } else {
      numArr[numChar++] = problemLine[i];
    }
  }
  if (strlen(numArr) > 0) {
    sequence[seqNum++] = atoll(numArr);
  }

  return sequence;
}
