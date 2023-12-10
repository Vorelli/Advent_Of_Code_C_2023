#define MAX_ELEMENTS 1024
#include "../utils/utils.h"

long long getSolutionForLine(char *problemLine, bool toTheRight);
long long solutionGen(long long *sequence, bool toTheRight);
long long *loadLineIntoSequence(char *problemLine);
