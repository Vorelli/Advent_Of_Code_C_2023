#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *generateEmptyCubeBag();
int *generateBaseCubeBag();
int bagPower(int *bag);
void compareBags(int *maxBag, int *curBag);
struct NextPosAndValue getNextPosAndGameId(char *problemLine);
struct NextPosAndValue readNumber(char *problemLine, int index);
void solve(char *filename, int solveLine(char *line));
bool anyFalse(int *bagArr);
