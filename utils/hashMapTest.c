#include "utils.h"
#include <assert.h>
#include <stdio.h>

void shouldHandleUpToMaxElements(HashMap h) {
  for (unsigned long i = 0; i < MAX_BUCKETS; i++) {
    char str[BUFSIZ];
    sprintf(str, "%lu", i);
    assert(NULL == set(h, str, createNode(h, str, NULL, NULL)));
  }
}

void shouldReturnSameValue(HashMap h) {
  char *a = "a";
  char *b = "b";
  char *c = "c";

  set(h, a, createNode(h, a, NULL, NULL));
  set(h, b, createNode(h, b, NULL, NULL));
  set(h, c, createNode(h, c, NULL, NULL));
  assert(getNode(h, a)->value[0] == a[0]);
  assert(getNode(h, b)->value[0] == b[0]);
  assert(getNode(h, c)->value[0] == c[0]);
}

void randomR(HashMap h) { getNode(h, "a"); }

int main() {
  int numFunctions = 3;
  void (*functions[numFunctions])(HashMap);
  functions[2] = shouldHandleUpToMaxElements;
  functions[1] = shouldReturnSameValue;
  functions[0] = randomR;
  HashMap h = create();
  int i;
  for (i = 0; i < numFunctions; i++) {
    printf("Running function at %d\n", i);
    if (functions[i] == NULL)
      break;
    functions[i](h);
    clear(h);
  }
  printf("%d Test%s Complete!!\n", i, i == 1 ? "" : "s");
}
