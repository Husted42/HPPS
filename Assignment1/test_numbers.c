#include <stdlib.h>
#include "numbers.h"

int test_bytes() {
  struct bits8 a = bits8_from_int(9);
  struct bits8 b = bits8_from_int(11);
  int a_int = bits8_to_int()
  int b_int = bits8_to_int()

  printf("Bit representaion of 9 and 11: \n");
  bits8_print(a);
  printf("  and  ");
  bits8_print(b);

  unsigned int x1 = bits8_to_int(bits8_add(a, b));
  printf("%d", x1);
  return 0;
}

int main() {
  // unsigned int x = 11;
  // unsigned int b = bits8_to_int(bits8_from_int(x));
  // bits8_print(bits8_from_int(x));
  test_bytes();
  printf("\n\nhello world!\n");
  return 0;
}
