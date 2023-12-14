#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int main(int argc, char** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file>\n", argv[0]);
    exit(1);
  }

    // Set pointer *f to file, such that we can call f later
  FILE *f = fopen(argv[1], "r");
  assert(f != NULL);

  int n, d;
  // nxd matrix of points
  double *points = read_points(f, &n, &d);
  assert(points != NULL);
    printf("d: %d\n", d);
  for (int i = 0; i < n; i++) {
    printf("Point %d: ", i);
    for (int j = 0; j < d; j++) {
      printf("%f ", points[i*d+j]);
    }
    printf("\n");
  }

  free(points);
}
