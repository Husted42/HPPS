#include <stdlib.h>
#include "numbers.h"

//// Variables
// struct bits8 nine = bits8_from_int(9);
// struct bits8 elleven = bits8_from_int(11);
// struct bits8 one = bits8_from_int(1);

int test_additon() {
  struct bits8 a = bits8_from_int(9);
  struct bits8 b = bits8_from_int(11);

  printf("---- Test for addition: -----\n");
  printf("Bit representaion of %d and %d: \n", bits8_to_int(a), bits8_to_int(b));
  bits8_print(a);
  printf("  and  ");
  bits8_print(b);

  unsigned int x1 = bits8_to_int(bits8_add(a, b));
  printf("%d", x1);
  printf("\n\n");
  return 0;
}


int testNegation() {
  struct bits8 a = bits8_from_int(9);
  struct bits8 b = bits8_from_int(11);
  struct bits8 c = bits8_from_int(1);

  printf("---- Test for negation: -----\n");
  // test for 9
  printf("%d: negation of: ", bits8_to_int(a));
  bits8_print(a);
  printf(" is: ");
  bits8_print(bits8_negate(a));
  printf("\n");
  printf("%d: negation of: ", bits8_to_int(b));
  bits8_print(b);
  printf(" is: ");
  bits8_print(bits8_negate(b));
  printf("\n");
  printf("%d: negation of: ", bits8_to_int(c));
  bits8_print(c);
  printf(" is: ");
  bits8_print(bits8_negate(c));
  printf("\n\n");
  return 0;
}

int test_multipliction(){
  struct bits8 a = bits8_from_int(5);
  struct bits8 b = bits8_from_int(2);
  printf("\n");
  printf("", bits8_to_int(bits8_mul(a, b)));
}

int main() {
  // unsigned int x = 11;
  // unsigned int b = bits8_to_int(bits8_from_int(x));
  // bits8_print(bits8_from_int(x));
  test_additon();
  testNegation();
  test_multipliction();
  printf("\n\nhello world!\n");
  return 0;
}
