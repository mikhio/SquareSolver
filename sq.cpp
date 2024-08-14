#include <stdio.h>
#include <math.h>

int main() {
  double a, b, c;
  printf("Enter a b c: ");
  int args = scanf("%lg %lg %lg", &a, &b, &c);

  if (args == 3) {
    if (a == 0) {
      if (b == 0) {
        printf("Result: Any\n");
      } else {
        double x = -c/b;
        printf("Result: x=%lg (Linear)\n", x);
      }
    } else {
      double D = b*b - 4*a*c;
      if (D >= 0) {
        double x1 = (-b + sqrt(D))/(2*a);
        double x2 = (-b - sqrt(D))/(2*a);

        if (D == 0) {
          printf("Result: x=%lg (Full square)\n", x1);
        } else {
          printf("Result: x1=%lg x2=%lg\n", x1, x2);
        }
      } else {
        printf("Result: None (D < 0)\n");
      }
    }
  } else {
    printf("Error: invalid input data\n");
  }
  return 0;
}
