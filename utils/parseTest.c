#include "utils.h"
#include <assert.h>
#include <stdio.h>

void shouldReturnExpectedValue() {
  HashMap h = create();
  parseNodes("AAA = (BBB, CCC)", h);
  Node *n = get(h, "AAA");
  assert(n != NULL);
  assert(strcmp(n->value, "AAA") == 0);
  assert(strcmp(n->left->value, "BBB") == 0);
  assert(strcmp(n->right->value, "CCC") == 0);
}

int main() {
  int numFunctions = 1;
  void (*functions[numFunctions])();
  functions[0] = shouldReturnExpectedValue;

  int i;
  for (i = 0; i < numFunctions; i++) {
    printf("Running function at %d\n", i);
    if (functions[i] == NULL)
      break;
    functions[i]();
  }
  printf("%d Test%s Complete!!\n", i, i == 1 ? "" : "s");
}
