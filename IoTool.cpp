#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "IoTool.h"
#include "SqEquation.h"

int check_quit() {
  char buffer[BUFF_SIZE] = {};
  fgets(buffer, BUFF_SIZE, stdin);

  if (strcmp(buffer, "quit\n") == 0)
    return 1;

  return 0;
}

int readEq(SqEquation *eq) {
  assert(eq != NULL);

  double a = 0, b = 0, c = 0;

  printf("Enter a b c or quit: ");
  int args = scanf("%lg %lg %lg", &a, &b, &c);

  if (args == 3) {
    eq->a = a;
    eq->b = b;
    eq->c = c;

    defineType(eq);

    return 1;
  } else if (check_quit()) {
    exit(0);
  }

  return 0;
}

int printEqRes(const SqEquation *eq) {
  assert(eq != NULL);

  switch (eq->type) {
    case NONE:
      printf("Result: NONE type\n");
      break;
    case ANY:
      printf("Result: Any\n");
      break;
    case LINEAR:
      printf("Result: x=%.4lg (Linear)\n", eq->x1);
      break;
    case SQUARE:
      printf("Result: x1=%.4lg x2=%.4lg\n", eq->x1, eq->x2);
      break;
    case FULL_SQUARE:
      printf("Result: x=%.4lg (Full square)\n", eq->x1);
      break;
    case D_NEGATIVE:
      printf("Result: None (D < 0)\n");
      break;
    default:
      fprintf(stderr, "ERORR: Unknown type of equation");
  }

  return 0;
}
