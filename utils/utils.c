#include "utils.h"
#include <stdio.h>

FILE *getFile(char *fileName) {
  FILE *problemFile = fopen(fileName, "r");
  return problemFile;
}

ArrayAndDims readFileIntoArray(FILE *f) {
  char line[BUFSIZ];
  fgets(line, BUFSIZ, f);
  unsigned long numCols = strlen(line);
  fseek(f, 0, SEEK_SET);
  unsigned long numRows = getNumRows(f);
  char **file = (char **)malloc(numRows * sizeof(char *));
  for (unsigned long i = 0; i < numRows; i++) {
    file[i] = (char *)malloc(numCols * sizeof(char));
    fgets(line, BUFSIZ, f);
    for (unsigned long j = 0; j < strlen(line) - 1; j++) {
      file[i][j] = line[j];
    }
  }
  return (ArrayAndDims){file, numRows, numCols};
}

unsigned long getNumRows(FILE *f) {
  unsigned long i;
  char line[BUFSIZ];
  for (i = 0; fgets(line, BUFSIZ, f) != NULL; i++)
    ;
  fseek(f, 0, SEEK_SET);
  return i;
}

/*HashMap readNodesIntoMap(ArrayAndDims fileContents) {
  HashMap h = create();
  for (unsigned long i = 0; i < fileContents.numRow; i++) {
    if (length(fileContents.array[i]) > 12) {
      parseNodes(fileContents.array[i], h);
    }
  }
  unsigned long long numTurns = 0;
  Node *cur = get(h, "AAA");
  while (true) {
    char dir = fileContents.array[0][numTurns % fileContents.numCol];
    switch (dir) {}
    numTurns++;
  }
}*/

unsigned long length(char *array) {
  unsigned long i = 0;
  for (; array[i] != '\0'; i++) {
  }
  return i;
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

Node *createNode(char *value, Node *l, Node *r) {
  Node *n = malloc(sizeof(Node));
  n[0] = (Node){value, l, r};
  return n;
}

Node *lookupOrCreateNode(HashMap h, char *value, Node *l, Node *r) {
  Node *n = get(h, value);
  if (n != NULL) {
    n->left = l;
    n->right = r;
    return n;
  }
  n = createNode(value, l, r);
  set(h, value, n);
  return n;
}

KeyAndNodePair *generateEmptyEntries() {
  KeyAndNodePair *entries = malloc(MAX_BUCKETS * sizeof(KeyAndNodePair));
  /*for (int i = 0; i < MAX_BUCKETS; i++) {
    entries[i] = malloc(sizeof(KeyAndValuePair));
  }*/
  return entries;
}

HashMap create() { return (HashMap){generateEmptyEntries()}; }

bool has(HashMap h, char *key) { return get(h, key) != NULL; }

Node *getOrCreate(HashMap h, char *key) {
  Node *potentialNode = get(h, key);
  if (potentialNode == NULL) {
    potentialNode = lookupOrCreateNode(h, key, NULL, NULL);
  }
  return potentialNode;
}

Node *get(HashMap h, char *key) {
  unsigned long index = generateHash(key) % MAX_BUCKETS;
  for (unsigned long i = index; i < index + MAX_BUCKETS; i++) {
    if (h.entries[i].key == NULL)
      break;

    if (strncmp(h.entries[i].key, key, 3) == 0) {
      return h.entries[i].value;
    }
  }
  return NULL;
}

Error set(HashMap h, char *key, Node *value) {
  unsigned long hash = generateHash(key);
  KeyAndNodePair k = {key, value};
  for (unsigned long i = hash; i < hash + MAX_BUCKETS; i++) {
    if (h.entries[i % MAX_BUCKETS].key == NULL) {
      h.entries[i % MAX_BUCKETS] = k;
      return NULL;
    }
  }
  return "FAIL";
}

unsigned long generateHash(char *key) {
  unsigned long hash = 5381;
  int c;

  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

void clear(HashMap h) {
  free(h.entries);
  h.entries = generateEmptyEntries();
}

void parseNodes(char *line, HashMap h) {
  char **nodeNames = malloc(3 * sizeof(char *));
  for (int i = 0; i < 3; i++)
    nodeNames[i] = malloc(3 * sizeof(char));
  int offsets[3] = {0, 7, 12};
  for (int i = 0; i < 3; i++) {
    strncpy(nodeNames[i], line + offsets[i], 3);
  }

  Node *l = getOrCreate(h, nodeNames[1]);
  Node *r = getOrCreate(h, nodeNames[2]);
  lookupOrCreateNode(h, nodeNames[0], l, r);
}
