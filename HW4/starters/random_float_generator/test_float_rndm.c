/**
 * test_float_rndm.c - test random float generator
 *
 * Tests the random floating point numbers API within a specified range
 * Acknowledgement: Code by Thang Nguyen ( https://www.mycompiler.io/view/2go3N4CaLQJ )
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "float_rndm.h"

/*** typedefs, enums, constants ***/
#define MAX_LOOP    100

/*** MAIN() ***/
int main(void)
{
  int sel, i;
  double a, b;

  while (1) {
    printf("\n\nSelection:\n");
    printf("0 : Input range to generate random float\n");
    printf("1 : Exit\n");
    printf("Select: ");
    scanf("%d", &sel);

    switch (sel) {
    case 0:
      printf("Input a: ");
      scanf("%lf", &a);
      printf("Input b: ");
      scanf("%lf", &b);
      
      for (i = 0; i < MAX_LOOP; i++)
        printf("=> Random: %lf\n", positive_float_rand_in_range(a, b));
      break;
    case 1:
      return 0;
    default:
      printf("Option not available\n");
      break;
    }
  }

  return -1;
}
