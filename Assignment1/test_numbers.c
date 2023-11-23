#include <stdlib.h>
#include "numbers.h"

int main() {
  // unsigned int x = 11;
  // unsigned int b = bits8_to_int(bits8_from_int(x));
  // bits8_print(bits8_from_int(x));
  unsigned int jens = bits8_to_int(bits8_add(bits8_from_int(9), bits8_from_int(11)));
  bits8_print(bits8_add(bits8_from_int(9), bits8_from_int(11)));
  printf("\n%d\n", jens);
  return 0;
}
