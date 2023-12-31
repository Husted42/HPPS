#include "numlib.h"
#include <assert.h>


// echo 123 456 789 | ./double_ascii_to_double_bin | ./double_bin_to_double_ascii
int main(int argc, char* argv[]) {
  assert(argc == 1);
  while (1) {
    double x;
    int r = read_double_ascii(stdin, &x);
    printf("r: %f\n", x);
    if (r == 0) {
      if (write_double_bin(stdout, x) != 0) {
        fprintf(stderr, "%s: output error\n", argv[0]);
        return 1;
      }
    } else if (r == EOF) {
      return 0;
    } else {
      fprintf(stderr, "%s: input error\n", argv[0]);
      return 1;
    }
    skipspaces(stdin);
  }
}
