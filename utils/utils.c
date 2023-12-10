#include "utils.h"

FILE *getFile(char *fileName) {
  FILE *problemFile = fopen(fileName, "r");
  return problemFile;
}

ArrayAndDims readFileIntoArray(FILE *f) {
  char line[BUFSIZ];
  memset(line, 0, BUFSIZ);
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

unsigned long length(char *array) {
  unsigned long i = 0;
  for (; array[i] != '\0' && array[i] != '\n'; i++) {
  }
  return i;
}

unsigned long lenStringArr(char **array) {
  unsigned long i = 0;
  for (; array[i] != NULL; i++)
    ;
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

bool hasKey(char **keys, char *key) {
  for (short i = 0; i < MAX_PERMUTATIONS && keys[i] != NULL; i++) {
    if (strncmp(keys[i], key, strlen(key)) == 0) {
      return true;
    }
  }
  return false;
}

Node *createNode(HashMap *h, char *key, Node *l, Node *r) {
  h->keys[*h->numKeys] = strdup(key);
  *h->numKeys += 1;
  Node *n = malloc(sizeof(Node));
  char *value = strdup(key);
  n->value = value;
  n->left = l;
  n->right = r;
  Error a = set(h, key, n);
  if (a == NULL)
    return NULL;
  return n;
}

Node *lookupOrCreateNode(HashMap *h, char *key, Node *l, Node *r) {
  Node *n = getNode(h, key);
  if (n == NULL && !hasKey(h->keys, key)) {
    return createNode(h, key, l, r);
  } else if (n == NULL) {
    return NULL;
  }
  n->left = l;
  n->right = r;
  return n;
}

KeyAndNodePair **generateEmptyEntries() {
  KeyAndNodePair **entries = malloc(MAX_BUCKETS * sizeof(KeyAndNodePair *));
  for (int i = 0; i < MAX_BUCKETS; i++) {
    entries[i] = NULL;
  }
  return entries;
}

char **generateEmptyKeys() { return malloc(MAX_BUCKETS * sizeof(char *)); }

HashMap *create() {
  HashMap *map = malloc(sizeof(HashMap));
  map->numKeys = malloc(sizeof(unsigned long));
  (*map->numKeys) = 0;
  map->entries = generateEmptyEntries();
  map->keys = generateEmptyKeys();
  return map;
}

bool has(HashMap *h, char *key) { return getNode(h, key) != NULL; }

Node *getOrCreate(HashMap *h, char *key) {
  Node *potentialNode = getNode(h, key);
  if (potentialNode == NULL) {
    potentialNode = createNode(h, key, NULL, NULL);
  }
  return potentialNode;
}

Node *getNode(HashMap *h, char *key) {
  unsigned long index = generateHash(key);
  // printf("looking for key: %s index:%lu max buckets: %d\n", key, index,
  // MAX_BUCKETS);
  for (unsigned long i = index; i < (index + MAX_BUCKETS); i++) {
    // printf("right before NULL CHECK FOR h->entries\n");
    if (h->entries == NULL) {
      break;
    }
    if (h->entries[i % MAX_BUCKETS] == NULL) {
      break;
    }
    if (strncmp(h->entries[i % MAX_BUCKETS]->key, key, 3) == 0) {
      return h->entries[i % MAX_BUCKETS]->value;
    }
  }
  return NULL;
}

Node **getAllNodes(HashMap *h, char endingLetter) {
  short numNodes = 0;
  Node **nodes = malloc(MAX_PERMUTATIONS * sizeof(Node *));
  memset(nodes, 0, MAX_PERMUTATIONS * sizeof(Node *));
  char **keys = getKeys(h, endingLetter);
  for (unsigned long i = 0; i < 676 && keys[i] != NULL; i++) {
    Node *n = getNode(h, keys[i]);
    if (n != NULL) {
      nodes[numNodes++] = n;
    }
  }
  free(keys);
  printf("ALL CURRENT NODES:");
  for (int i = 0; i < numNodes; i++) {
    printf(" %s", nodes[i]->value);
  }
  printf("\n");
  return nodes;
}

char **getKeys(HashMap *h, char endingLetter) {
  char **keys = malloc(MAX_PERMUTATIONS * sizeof(char *));
  short numKeys = 0;
  for (unsigned long i = 0; i < *h->numKeys; i++) {
    if (h->keys[i][2] == endingLetter) {
      // memset(keys[numKeys], 0, 8);
      keys[numKeys++] = h->keys[i];
    }
  }
  return keys;
}

Error set(HashMap *h, char *key, Node *value) {
  unsigned long hash = generateHash(key);
  KeyAndNodePair *k = malloc(sizeof(KeyAndNodePair));
  k->value = value;
  k->key = strdup(key);
  for (unsigned long i = hash; i < (hash + MAX_BUCKETS); i++) {
    if (h->entries[i % MAX_BUCKETS] == NULL) {
      h->entries[i % MAX_BUCKETS] = k;
      unsigned long *index = malloc(sizeof(unsigned long *));
      *index = i % MAX_BUCKETS;
      return index;
    }
  }
  return NULL;
}

unsigned long generateHash(char *key) {
  unsigned long hash = 5381;
  int c;

  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c;
  }

  return hash;
}

void clear(HashMap *h) {
  free(h->entries);
  h->entries = generateEmptyEntries();
}

void parseNodes(char *line, HashMap *h) {
  char **nodeNames = malloc(4 * sizeof(char *));
  for (int i = 0; i < 3; i++) {
    nodeNames[i] = malloc(4 * sizeof(char));
    memset(nodeNames[i], 0, 4);
  }
  int offsets[3] = {0, 7, 12};
  for (int i = 0; i < 3; i++) {
    strncpy(nodeNames[i], line + offsets[i], 3);
  }

  Node *l = getOrCreate(h, nodeNames[1]);
  Node *r = getOrCreate(h, nodeNames[2]);
  lookupOrCreateNode(h, nodeNames[0], l, r);

  for (int i = 0; i < 3; i++) {
    free(nodeNames[i]);
  }
  free(nodeNames);
}

void runTests(partOneTest solvePartOne, void (**functions)(partOneTest),
              int numTests) {
  int i;
  for (i = 0; i < numTests; i++) {
    printf("Running function at %d\n", i);
    (*functions[i])(solvePartOne);
  }
  printf("%d Test%s Complete!!\n", i, i == 1 ? "" : "s");
}

char *loadIntoMap(char *fileName, HashMap *h) {
  FILE *f = fopen(fileName, "r");
  ArrayAndDims a = readFileIntoArray(f);
  fclose(f);
  for (int i = 2; i < a.numRow; i++)
    parseNodes(a.array[i], h);
  return strdup(a.array[0]);
}
