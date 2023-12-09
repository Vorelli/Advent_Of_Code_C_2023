#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUM_MATCHING 100
#define MAX_BUCKETS 1024

struct NextPosAndValue {
  int nextPos;
  int value;
};
struct NextPosAndIntPtr {
  int nextPos;
  int *val;
};
typedef struct {
  char **array;
  int numRow;
  int numCol;
} ArrayAndDims;

typedef struct Node {
  char *value;
  struct Node *left;
  struct Node *right;
} Node;

typedef struct {
  char *key;
  Node *value;
} KeyAndNodePair;

typedef struct {
  KeyAndNodePair *entries;
} HashMap;
typedef char *Error;

unsigned long getNumRows(FILE *f);
HashMap create();
Node *get(HashMap h, char *key);
bool has(HashMap h, char *key);
Error set(HashMap h, char *key, Node *value);
unsigned long generateHash(char *key);
void clear(HashMap h);
KeyAndNodePair *generateEmptyEntries();
Node *createNode(char *value, Node *l, Node *r);
Node *lookupOrCreateNode(HashMap h, char *value, Node *l, Node *r);
long getFileLength(FILE *problemFile);
FILE *getFile(char *fileName);
ArrayAndDims readFileIntoArray(FILE *f);
unsigned long fileSize(FILE *f);
struct NextPosAndValue readNumber(char *problemLine, int index);
int findBeginningAndReadNumber(char *problemLine, int index);
int min(int a, int b);
int max(int a, int b);
bool isNumber(char ch);
bool isSymbol(char **problem, unsigned long r, unsigned long c);
bool isNumberOrIsNegative(char **problem, unsigned long r, unsigned long c);
struct NextPosAndIntPtr readNextNumbersUntil(char *line, int index, char until);
void parseNodes(char *line, HashMap h);
unsigned long length(char *array);
