#include "part1.h"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Failed to provide exactly one arguments. Just looking for "
           "filename.\n");
    return 1;
  }
  solveAndPrintSolution1(argv[1], solveLine);
}
int solveLine(char *line) {
  int score = 0;
  struct NextPosAndIntPtr afterGame = readNextNumbersUntil(line, 0, ':');
  struct NextPosAndIntPtr res =
      readNextNumbersUntil(line, afterGame.nextPos, '|');
  struct NextPosAndIntPtr nums = readNextNumbersUntil(line, res.nextPos, '\n');
  for (unsigned long i = 0; i < NUM_MATCHING && nums.val[i] != 0; i++) {
    for (unsigned long j = 0; j < NUM_MATCHING && res.val[j] != 0; j++) {
      if (nums.val[i] == res.val[j]) {
        score = score == 0 ? 1 : score * 2;
      }
    }
  }
  return score;
}
