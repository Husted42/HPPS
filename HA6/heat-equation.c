#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <omp.h>
#include "debugbmp.h"

// Function to calculate position
size_t pos(size_t width, size_t x, size_t y) {
    return y * width + x;
}

// Function to write borders
void write_borders(float* data, size_t width, size_t height) {
    #pragma omp parallel for 
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
                data[pos(width, x, y)] = 1.0f;
            }
        }
    }
}

// Function to apply stencil
float stencil(float* data, size_t width, size_t x, size_t y, float alpha) {
    float t = data[pos(width, x, y)];
    t += alpha * (data[pos(width, x+1, y)] - 2*data[pos(width, x, y)] + data[pos(width, x-1, y)]);
    t += alpha * (data[pos(width, x, y+1)] - 2*data[pos(width, x, y)] + data[pos(width, x, y-1)]);
    return t;
}

// Function to apply stencil to all data
void apply_stencil(float* data, size_t width, size_t height, size_t offset, float alpha) {
    #pragma omp parallel for
    for (size_t y = 1; y < height - 1; y++) {
        for (size_t x = 1; x < width - 1; x++) {
            data[pos(width, x, y) + offset] = stencil(data, width, x, y, alpha);
        }
    }
}

// Function to compute delta
float compute_delta(float* data, float* prev, size_t width, size_t height) {
    float delta = 0.0f;
    #pragma omp parallel for 
    for (size_t y = 1; y < height - 1; y++) {
        for (size_t x = 1; x < width - 1; x++) {
            float diff = data[pos(width, x, y)] - prev[pos(width, x, y)];
            delta += diff * diff;
        }
    }
    return sqrt(delta);
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

