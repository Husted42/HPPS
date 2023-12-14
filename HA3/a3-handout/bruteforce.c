#include "bruteforce.h"
#include "util.h"
#include <stdlib.h>
#include <assert.h>
// brute-force k-NN. Your task is to implement the behaviour documented in the header file. You will
// need to make use of the definitions in util.h

void selection_sort(int n, double* distances, int* indices) {
  for (int i = 0; i < n - 1; i++) {
    int min_index = i;
    for (int j = i + 1; j < n; j++) {
      if (distances[j] < distances[min_index]) {
        min_index = j;
      }
    }
    // Swap the minimum distance and index with the current position
    double temp_distance = distances[min_index];
    int temp_index = indices[min_index];
    distances[min_index] = distances[i];
    indices[min_index] = indices[i];
    distances[i] = temp_distance;
    indices[i] = temp_index;
  }
}
int* knn(int k, int d, int n, const double *points, const double* query) {  
  // Calculate the distance between the query point and each reference point
  double* distances = (double*)malloc(n * sizeof(double));
  for (int i = 0; i < n; i++) {
    distances[i] = distance(d, &points[i * d], query);
  }

  // Sort the distances in ascending order using selection sort
  int* indices = (int*)malloc(n * sizeof(int));
  if (indices == NULL) {
    free(distances);
    return NULL;
  }
  for (int i = 0; i < n; i++) {
    indices[i] = i;
  }
  selection_sort(n, distances, indices);

  // Create the result array with the indices of the nearest neighbours
  int* result = (int*)malloc(k * sizeof(int));
  if (result == NULL) {
    free(distances);
    free(indices);
    return NULL;
  }
  for (int i = 0; i < k; i++) {
    result[i] = indices[i];
  }

  return result;
}