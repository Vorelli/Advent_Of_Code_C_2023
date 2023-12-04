#include "part2.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Too many or two few arguments. Only looking for filename.\n");
    return 1;
  }
  solveAndPrintSolution2(argv[1]);
}
