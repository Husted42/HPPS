#include "numlib.h"
#include <assert.h>

void utf32_to_binary(uint32_t utf32_number) {
    for (int i = 31; i >= 0; i--) {
        // Use bitwise AND to check the value of each bit
        int bit = (utf32_number >> i) & 1;
        printf("%d", bit);

        // Optionally, add spaces for better readability
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
  assert(argc == 1);
  while (1) {
    uint32_t x;
    int r = read_uint_be(stdin, &x);
    utf32_to_binary(x);
    if (r == 0) {
      if (write_uint_le(stdout, x) != 0) {
        fprintf(stderr, "%s: output error\n", argv[0]);
        return 1;
      }
    } else if (r == EOF) {
      return 0;
    } else {
      fprintf(stderr, "%s: input error\n", argv[0]);
      return 1;
    }
  }
}
