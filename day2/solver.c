#include "solver.h"

int *generateBaseCubeBag() {
  int *genericBag;
  genericBag = malloc(sizeof(int) * 3);
  genericBag[0] = 12;
  genericBag[1] = 14;
  genericBag[2] = 13;
  return genericBag;
}

void solve(char *filename, int solveLine(char *line)) {
  FILE *problem = getFile(filename);
  char line[BUFSIZ];
  int sum = 0;
  while (fgets(line, BUFSIZ, problem) != NULL) {
    sum += solveLine(line);
    printf("Sum after line %s: %d\n", line, sum);
  }
  printf("Solution to part one: %d\n", sum);
}

struct NextPosAndValue getNextPosAndGameId(char *problemLine) {
  for (unsigned long i = 0; i < strlen(problemLine); i++) {
    printf("Scanning @ position: %lu with value of: %d\n", i, problemLine[i]);
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
  printf("NONE FALSE!\n");
  return false;
}

struct NextPosAndValue readNumber(char *problemLine, int index) {
  problemLine[strlen(problemLine) - 1] = 0x00;
  char substr[BUFSIZ];
  strncpy(substr, problemLine + index, BUFSIZ);
  printf("Reading %s\n", substr);
  char numToBe[BUFSIZ] = {0};
  unsigned long lastPos;
  for (lastPos = (unsigned long)index; lastPos < strlen(problemLine);
       lastPos++) {
    if (problemLine[lastPos] == ' ' || problemLine[lastPos] == ':')
      break;
    printf("char: %c setting position %lu to char\n", problemLine[lastPos],
           lastPos);
    numToBe[lastPos - index] = problemLine[lastPos];
  }
  printf("numToBeFirstThree: %c%c%c\n", numToBe[0], numToBe[1], numToBe[2]);
  int quantity = atoi(numToBe);
  if (quantity == 0) {
    printf("num is equal to 0. probably error... index: %d ", index);
    printf("next 10: ");
    for (int i = 0; i < 10; i++) {
      printf("%c", problemLine[i]);
    }
    printf("\n");
  }
  struct NextPosAndValue n = {lastPos, quantity};
  return n;
}
