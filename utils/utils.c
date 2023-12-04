#include "utils.h"

FILE *getFile(char *fileName) {
  FILE *problemFile = fopen(fileName, "r");
  return problemFile;
}

struct ArrayAndDims readFileIntoArray(FILE *f) {
  unsigned long size = fileSize(f);
  char line[BUFSIZ];
  fgets(line, BUFSIZ, f);
  unsigned long numCols = strlen(line);
  unsigned long numRows = size / numCols;
  char **file = (char **)malloc(numRows * sizeof(char *));
  for (unsigned long i = 0; i < numRows; i++)
    file[i] = (char *)malloc(numCols * sizeof(char));
  unsigned long i = 0;
  while (i < numRows) {
    for (unsigned long j = 0; j < strlen(line) - 1; j++) {
      file[i][j] = line[j];
    }
    i++;
    fgets(line, BUFSIZ, f);
  }
  struct ArrayAndDims result = {file, numRows, numCols};
  return result;
}

unsigned long fileSize(FILE *f) {
  fseek(f, 0, SEEK_END);
  unsigned long size = ftell(f);
  fseek(f, 0, SEEK_SET);
  return size;
}

int findBeginningAndReadNumber(char *problemLine, int index) {
  for (int i = index; i >= 0; i--) {
    if (!isNumber(problemLine[i]))
      return readNumber(problemLine, i + 1).value;
  }
  return readNumber(problemLine, 0).value;
}

struct NextPosAndValue readNumber(char *problemLine, int index) {
  // problemLine[strlen(problemLine)] = 0x00;
  char numToBe[BUFSIZ] = {0};
  unsigned long lastPos;
  for (lastPos = (unsigned long)index; lastPos < strlen(problemLine);
       lastPos++) {
    if (problemLine[lastPos] < '0' || problemLine[lastPos] > '9')
      break;
    numToBe[lastPos - index] = problemLine[lastPos];
  }
  int quantity = atoi(numToBe);
  if (quantity == 0) {
    for (int i = 0; i < 10; i++) {
    }
  }
  struct NextPosAndValue n = {lastPos, quantity};
  return n;
}

int min(int a, int b) { return a > b ? b : a; }
int max(int a, int b) { return a < b ? b : a; }

bool isNumberOrIsNegative(char **problem, unsigned long r, unsigned long c) {
  return (problem[r][c] >= '0' && problem[r][c] <= '9') ||
         (problem[r][c] == '-' && isNumber(problem[r][c + 1]));
}

bool isNumber(char ch) { return ch >= '0' && ch <= '9'; }

bool isSymbol(char **problem, unsigned long r, unsigned long c) {
  return problem[r][c] != '.' && !isNumber(problem[r][c]);
}

struct NextPosAndIntPtr readNextNumbersUntil(char *line, int index,
                                             char until) {
  int *listOfNumbers = malloc(NUM_MATCHING * sizeof(int));
  int num = 0;
  unsigned long i;
  for (i = index; num < NUM_MATCHING && line[i] != '\0'; i++) {
    if (line[i] == until)
      break;
    if (isNumber(line[i])) {
      struct NextPosAndValue res = readNumber(line, i);
      i = res.nextPos - 1;
      listOfNumbers[num++] = res.value;
    }
  }
  struct NextPosAndIntPtr res = {i, listOfNumbers};
  return res;
}
