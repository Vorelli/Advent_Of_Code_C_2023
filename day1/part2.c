#include "part2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FOREACH_NUMBER_WORD(NUMBER_WORD)                                       \
  NUMBER_WORD(one)                                                             \
  NUMBER_WORD(two)                                                             \
  NUMBER_WORD(three)                                                           \
  NUMBER_WORD(four)                                                            \
  NUMBER_WORD(five)                                                            \
  NUMBER_WORD(six)                                                             \
  NUMBER_WORD(seven)                                                           \
  NUMBER_WORD(eight)                                                           \
  NUMBER_WORD(nine)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

enum NUMBER_WORDS { FOREACH_NUMBER_WORD(GENERATE_ENUM) };
static const char *NUMBER_WORD_STRINGS[] = {
    FOREACH_NUMBER_WORD(GENERATE_STRING)};

int main() {
  solveAndPrintSolution();
  return 0;
}

long getFileLength(FILE *problemFile) {
  fseek(problemFile, 0, SEEK_END);
  long size = ftell(problemFile);
  fseek(problemFile, 0, SEEK_SET);
  return size;
}

void solveAndPrintSolution() {
  FILE *problemFile = fopen("problem.txt", "r");
  long size = getFileLength(problemFile);
  int sum = 0;
  char problemArr[BUFSIZ];
  while (fgets(problemArr, sizeof problemArr, problemFile) != NULL) {
    int firstNumber = findNumber(problemArr, size, 0, true);
    int secondNumber = findNumber(problemArr, size, strlen(problemArr), false);
    sum += (firstNumber * 10) + secondNumber;
  }
  printf("Result %d\n", sum);
}

int findNumber(char file[], long size, unsigned long start, bool toTheRight) {
  char a;
  for (long i = start; toTheRight ? i < size : i >= 0;
       i += toTheRight ? 1 : -1) {
    int stringNum = findStringNum(file, i);
    if (stringNum != 0)
      return stringNum;

    a = file[i];
    int num = atoi(&a);
    if (num != 0)
      return num;
  }
  return 0;
}

int findStringNum(char file[], int i) {
  for (int j = one; j <= nine; j++) {
    const char *str = NUMBER_WORD_STRINGS[j];
    for (unsigned long k = 0; k < strlen(str); k++) {
      if (file[i + k] != str[k])
        break;

      if (k == strlen(str) - 1 && file[i + k] == str[k])
        return j + 1;
    }
  }
  return 0;
}
