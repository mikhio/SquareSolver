#include <stdio.h>
#include "CliInterface.h"
#include "SqEquation.h"

const int MAX_ATTEMPTS = 10;

int main() {
  SqEquation eq = {};
  
  int cur_attempt = 0;
  while (cur_attempt < MAX_ATTEMPTS) {
    if (readEq(&eq)) {
      cur_attempt = 0;

      solveEq(&eq);
      printEqRes(&eq);
    } else {
      fprintf(stderr, "ERROR: invalid input data, ATTEMPT %d from %d\n", ++cur_attempt, MAX_ATTEMPTS);
    }
  }

  return 0;
}
