#include <stdlib.h>
#include "numbers.h"

//// Variables
// struct bits8 nine = bits8_from_int(9);
// struct bits8 elleven = bits8_from_int(11);
// struct bits8 one = bits8_from_int(1);

int test_bits8_from_to_int() {
  struct bits8 a = bits8_from_int(9);
  struct bits8 b = bits8_from_int(11);
  struct bits8 c = bits8_from_int(1);

  printf("---- Test for bits8_to_int: -----\n");
  printf("Bit representaion of %d: \n", bits8_to_int(a));
  bits8_print(a);
  printf("\n");
  printf("Bit representaion of %d: \n", bits8_to_int(b));
  bits8_print(b);
  printf("\n");
  printf("Bit representaion of %d: \n", bits8_to_int(c));
  bits8_print(c);
  printf("\nreturn type test: ");
  printf("%d", bits8_to_int(bits8_from_int(bits8_to_int(bits8_from_int(9)))));
  printf("\n\n");
  return 0;
}

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
  printf("%d: negation of ", bits8_to_int(a));
  bits8_print(a);
  printf(" is ");
  bits8_print(bits8_negate(a));
  printf("\n");
  printf("%d: negation of ", bits8_to_int(b));
  bits8_print(b);
  printf(" is ");
  bits8_print(bits8_negate(b));
  printf("\n");
  printf("%d: negation of ", bits8_to_int(c));
  bits8_print(c);
  printf(" is ");
  bits8_print(bits8_negate(c));
  printf("\n\n");
  return 0;
}

int test_multipliction(){
  struct bits8 t_0 = bits8_mul(bits8_from_int(15), bits8_from_int(1));
  struct bits8 t_1 = bits8_mul(bits8_from_int(10), bits8_from_int(10));
  struct bits8 t_2 = bits8_mul(bits8_from_int(36), bits8_from_int(2));
  struct bits8 t_3 = bits8_mul(bits8_from_int(120), bits8_from_int(2));
  struct bits8 t_4 = bits8_mul(bits8_from_int(9), bits8_from_int(11));
  // for loop iterating through t_0 to t_4
  printf("---- Test for multiplication: -----\n");
  printf("15 * 1 = %d: ", bits8_to_int(t_0)); // 15
  bits8_print(t_0);
  printf("\n");
  printf("10 * 10 = %d: ", bits8_to_int(t_1)); // 15
  bits8_print(t_1);
  printf("\n");
  printf("36 * 2 = %d: ", bits8_to_int(t_2)); // 15
  bits8_print(t_2);
  printf("\n");
  printf("120 * 2 = %d: ", bits8_to_int(t_3)); // 15
  printf("120 * 2 = ");
  bits8_print(t_3);
  printf("\n");
  printf("9 * 11 = %d: ", bits8_to_int(t_4)); // 15
  bits8_print(t_4);
  printf("\n\n");

  return 0;
}

int main() {
  // unsigned int x = 11;
  // unsigned int b = bits8_to_int(bits8_from_int(x));
  // bits8_print(bits8_from_int(x));
  test_bits8_from_to_int();
  test_additon();
  testNegation();
  test_multipliction();
  printf("\n\nhello world!\n");
  return 0;
}
