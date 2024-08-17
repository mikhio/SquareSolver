#include <stdio.h>
#include <string.h>
#include "SqEquation.h"

#define MAX_ATTEMPTS 10
#define BUFF_SIZE    20

bool check_quit() {
  char buffer[BUFF_SIZE];
  fgets(buffer, BUFF_SIZE, stdin);

  if (strcmp(buffer, "quit\n") == 0)
    return true;

  return false;
}

int main() {
  SqEquation eq = {};

  int attempts = 0;

  while (attempts < MAX_ATTEMPTS) {
    printf("Enter a b c or quit: ");

    if (readEq(&eq)) {
      attempts = 0;

      solveEq(&eq);
      printEqRes(&eq);
    } else {
      if (check_quit()) 
        return 0;

      printf("ERROR: invalid input data, ATTEMPT %d from %d\n", ++attempts, MAX_ATTEMPTS);
    }
  }



  return 0;
}
