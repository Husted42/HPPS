#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

int main() {
    FILE *f = fopen("20_5.points", "r");
    int n, d;
    double *data = read_points(f, &n, &d);
    for (int i = 0; i < n; i++) {
        printf("Point %d: ", i);
            for (int j = 0; j < d; j++) {
                printf("%f ", data[i*d+j]);
            }
        printf("\n");
    }
}
