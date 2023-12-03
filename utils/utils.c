#include "utils.h"

FILE *getFile(char *fileName) {
  FILE *problemFile = fopen(fileName, "r");
  return problemFile;
}
