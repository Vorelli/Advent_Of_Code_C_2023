#include "part1.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Failed to provide exactly one arguments. Just looking for "
           "filename.\nRunning tests.\n");
    runTests(argc, argv, solvePartOne);
    return 1;
  }

  solvePartOne(argv[1]);
  return 0;
}

unsigned long solvePartOne(char *fileName) {
  FILE *f = fopen(fileName, "r");
  ArrayAndDims a = readFileIntoArray(f);
  char *instructions = a.array[0];
  HashMap h = create();
  for (int i = 2; i < a.numRow; i++)
    parseNodes(a.array[i], h);
  unsigned long i = 1;
  Node cur = *get(h, "AAA");
  while (true) {
    char dir = instructions[(i - 1) % strlen(instructions)];
    cur = *get(h, dir == 'L' ? cur.left->value : cur.right->value);
    if (strncmp("ZZZ", cur.value, 3) == 0)
      break;
    i++;
  }
  printf("Number of turns: %lu\n", i);

  fclose(f);
  return i;
}
