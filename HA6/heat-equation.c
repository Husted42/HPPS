#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>
#include "debugbmp.h"

size_t pos(size_t width, size_t x, size_t y) {
    return y*width + x;
}

// they only run for width and height iterations and just perform a simple assignment, 
// the overhead of creating and managing multiple threads might outweigh the benefits of parallelization.
void write_borders(float* data, size_t width, size_t height) {
    size_t i;
    for (i = 0; i < width; ++i){
        data[pos(width, i, 0)] = 20.0f;
        data[pos(width, i, height-1)] = -273.15f;
    }
    for (i = 0; i < height; ++i){
        data[pos(width, 0, i)] = -273.15f;
        data[pos(width, width-1, i)] = -273.15f;
    }
}

float stencil(float* data, size_t width, size_t x, size_t y, float alpha) {
    return alpha *  (data[pos(width, x-1, y)] +
                    data[pos(width, x+1, y)] + 
                    data[pos(width, x, y-1)] + 
                    data[pos(width, x, y+1)] + 
                    data[pos(width, x, y)]);
}

void apply_stencil(float* data, size_t width, size_t height, size_t offset, float alpha) {
    size_t x, y;
    // x and y are used as loop counters in the parallelized outer loop and the inner loop, respectively. 
    // By declaring them as private, you ensure that each thread has its own copies of x and y, 
    // which prevents race conditions that could occur if multiple threads were trying to update the same x or y variable simultaneously.
    // So, in this context, private(x, y) is not only correct but also necessary for the correct execution of the parallelized code
    #pragma omp parallel for private(x, y)
    for (x=1; x < width-1; ++x){
        for (y=1+((x + offset) % 2); y < height-1; y +=2){
            data[pos(width, x, y)] = stencil(data, width, x, y, alpha);
        }
    }
}

// This could potentially be parallelized with OpenMP, 
// but you would need to use a reduction to compute the sum of delta across all threads.
float compute_delta(float* data, float* prev, size_t width, size_t height) {
    size_t i, j;
    float delta = 0.0f;
    for (i=0; i < width-1; ++i){
        for (j=0; j < height; ++j){
            delta += fabs(prev[pos(width, i, j)] - data[pos(width, i, j)]);
        }
    }
    return delta / (width * height);
}

void run_simulation(size_t width, size_t height, size_t steps, const char* filename) {
    size_t size = width*height;

    float* data = malloc(size * sizeof(float));
    float* prev = malloc(size * sizeof(float));

    memset(data, 0, size * sizeof(float));
    write_borders(data, width, height);

    float delta = 0.0f;
    size_t n = 0;

    for(; n < steps; n++) {
        memcpy(prev, data, size*sizeof(float));
        apply_stencil(data, width, height, n % 2, 0.2f);
        delta = compute_delta(data, prev, width, height);
        if (delta < 0.001f)
            break;
    }

    printf("After %lu iterations, delta was %f\n", n, delta);
    if (filename != NULL) {
        debugbmp_writebmp(filename, (int)width, (int)height, data);
    }

    free(data);
    free(prev);
}

int main(int argc, char** argv) {
    if (argc != 4 && argc != 5) {
        fprintf(stderr, "Usage: %s <width> <height> <steps> [output-file]\n", argv[0]);
        return 1;
    }

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int steps = atoi(argv[3]);

    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Sizes must be positive integers\n");
        return 1;
    }

    if (steps < 0) {
        fprintf(stderr, "Steps must be non-negative\n");
        return 1;
    }

    char* filename = NULL;
    if (argc == 5) {
        filename = argv[4];
    }

    run_simulation((size_t)width, (size_t)height, (size_t)steps, filename);

    return 0;
}
