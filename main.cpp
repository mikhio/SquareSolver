#include <stdio.h>
#include "SqEquation.h"

int main() {
  SqEquation eq {0};

  if (readEq(&eq)) {
    solveEq(&eq);
    printEqRes(&eq);
  } else {
    printf("Error: invalid input data\n");
  }

  return 0;
}
