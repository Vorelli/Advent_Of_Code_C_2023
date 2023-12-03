#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct NextPosAndValue {
  int nextPos;
  int value;
};

int *generateBaseCubeBag();
struct NextPosAndValue getNextPosAndGameId(char *problemLine);
struct NextPosAndValue readNumber(char *problemLine, int index);
void solve(char *filename, int solveLine(char *line));
bool anyFalse(int *bagArr);
