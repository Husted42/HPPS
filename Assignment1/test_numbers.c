#include <stdlib.h>
#include "numbers.h"

### Variables
struct bits8 nine = bits8_from_int(9);
struct bits8 elleven = bits8_from_int(11);
struct bits8 one = bits8_from_int(1);

int test_bytes(inp_a, inp_b) {
  struct bits8 a = inp_a:
  struct bits8 b = inp_b;
  int a_int = bit_to_int(a);
  int b_int = bit_to_int(b);

  printf("Bit representaion of 9 and 11: \n");
  bits8_print(a);
  printf("  and  ");
  bits8_print(b);

  unsigned int x1 = bits8_to_int(bits8_add(a, b));
  printf("%d", x1);
  return 0;
}

int testNegation() {
  struct bits8 a = bits8_from_int(9);
  struct bits8 b = bits8_from_int(11);
}

int main() {
  // unsigned int x = 11;
  // unsigned int b = bits8_to_int(bits8_from_int(x));
  // bits8_print(bits8_from_int(x));
  test_bytes();
  printf("\n\nhello world!\n");
  return 0;
}
