#include "solver.h"

unsigned long solvePOne(HashMap *h, char *instructions, char *startingNode,
                        char *endingNode) {
  unsigned long i = 1;
  Node cur = *getNode(h, startingNode);
  while (true) {
    char dir = instructions[(i - 1) % length(instructions)];
    cur = *getNode(h, dir == 'L' ? cur.left->value : cur.right->value);
    int diff = endingNode[0] == '*'
                   ? 2
                   : 0; // matches last char when first character is a star
    if (strncmp(endingNode + diff, cur.value + diff, 3 - diff) == 0)
      break;
    i++;
  }
  printf("Found node %s: %s -> (%s, %s) ", endingNode, cur.value,
         cur.left->value, cur.right->value);
  printf("Number of turns: %lu\n", i);

  return i;
}
