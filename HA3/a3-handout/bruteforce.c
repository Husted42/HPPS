#include "bruteforce.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>
// brute-force k-NN. Your task is to implement the behaviour documented in the header file. You will
// need to make use of the definitions in util.h

int compare_double(const void *a, const void *b) {
  double diff = *(double*)a - *(double*)b;
  if (diff < 0) {
    return -1;
  } else if (diff > 0) {
    return 1;
  } else {
    return 0;
  }
}
int* knn(int k, int d, int n, const double *points, const double* query) {  
  // Calculate the distance between the query point and each reference point
  double* distances = (double*)malloc(n * sizeof(double));
  for (int i = 0; i < n; i++) {
    distances[i] = distance(d, &points[i * d], query);
  }

  // Sort the distances in ascending order
  qsort(distances, n, sizeof(double), compare_double); // Add the missing qsort function call

  // Allocate memory for the result array
  int* result = (int*)malloc(k * sizeof(int));

  // Find the indexes of the k nearest neighbours
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      if (distances[j] == i) {
        result[i] = j;
        break;
      }
    }
  }

  // Free the memory allocated for distances
  free(distances);

  return result;
}

// Function definition for compare_double