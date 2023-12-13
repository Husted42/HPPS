#include <stdlib.h>
#include "numbers.h"

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

int test_additon_negative() {
  struct bits8 a; // -1
  a.b0 = bit_from_int(1);
  a.b1 = bit_from_int(1);
  a.b2 = bit_from_int(1);
  a.b3 = bit_from_int(1);
  a.b4 = bit_from_int(1);
  a.b5 = bit_from_int(1);
  a.b6 = bit_from_int(1);
  a.b7 = bit_from_int(1);
  struct bits8 b; // -2
  b.b0 = bit_from_int(0);
  b.b1 = bit_from_int(1);
  b.b2 = bit_from_int(1);
  b.b3 = bit_from_int(1);
  b.b4 = bit_from_int(1);
  b.b5 = bit_from_int(1);
  b.b6 = bit_from_int(1);
  b.b7 = bit_from_int(1);

  printf("---- Test for negative addition: -----\n");
  bits8_print(a);
  printf(" + ");
  bits8_print(b);
  printf(" = ");
  bits8_print(bits8_add(a, b));
  printf("\n\n");
  return 0;

}

int test_multiplication_negative() {
  struct bits8 a; // -1
  a.b0 = bit_from_int(1);
  a.b1 = bit_from_int(1);
  a.b2 = bit_from_int(1);
  a.b3 = bit_from_int(1);
  a.b4 = bit_from_int(1);
  a.b5 = bit_from_int(1);
  a.b6 = bit_from_int(1);
  a.b7 = bit_from_int(1);
  struct bits8 b; // -2
  b.b0 = bit_from_int(0);
  b.b1 = bit_from_int(1);
  b.b2 = bit_from_int(1);
  b.b3 = bit_from_int(1);
  b.b4 = bit_from_int(1);
  b.b5 = bit_from_int(1);
  b.b6 = bit_from_int(1);
  b.b7 = bit_from_int(1);

  printf("---- Test for negative multiplication: -----\n");
  bits8_print(a);
  printf(" * ");
  bits8_print(b);
  printf(" = ");
  bits8_print(bits8_mul(a,b));
  return 1;
}

int main() {
  // test_bits8_from_to_int();
  // test_additon();
  // testNegation();
  // test_multipliction();
  // test_additon_negative();
  test_multiplication_negative();
  printf("\n\nhello world!\n");
  return 0;
}
