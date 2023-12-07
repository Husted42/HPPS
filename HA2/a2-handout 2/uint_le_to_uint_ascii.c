#include "numlib.h"
#include <assert.h>



// Can be tested by running: echo 123 456 789 | ./uint_ascii_to_uint_le | ./uint_le_to_uint_ascii
// Resulting in the conversion uint_ascii -> uint -> uint_ascii
// The output should be: 123\n 0123\n 456\n 0456\n 789\n 0789\n
int main(int argc, char* argv[]) {
  assert(argc == 1);
  while (1) {
    uint32_t x;
    int r = read_uint_le(stdin, &x);
    if (r == 0) {
      printf("\n%d", write_uint_ascii(stdout, x));
      if (write_uint_ascii(stdout, x) != 0) {
        fprintf(stderr, "%s: output error\n", argv[0]);
        return 1;
      }
      printf("\n");
    } else if (r == EOF) {
      return 0;
    } else {
      fprintf(stderr, "%s: input error\n", argv[0]);
      return 1;
    }
  }
}
