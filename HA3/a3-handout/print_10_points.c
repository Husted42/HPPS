#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int main() {
    // Set pointer *f to file, such that we can call f later
    FILE *f = fopen("points", "r");
    assert(f != NULL);

    int n, d;
    // nxd matrix of points
    double *points = read_points(f, &n, &d);
    printf("Dimmensions: %d x %d", n, d);
    assert(points != NULL);
    for (int i = 0; i < 10; i++) {
        printf("Point %d: ", i);
        for (int j = 0; j < d; j++) {
            printf("%f ", points[i*d+j]);
        }
        printf("\n");
    }

  free(points);
}
