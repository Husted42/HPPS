#include "util.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>
// The header file declares two functions that you will need to implement.
double distance(int d, const double *x, const double *y) {
  double sum = 0.0;
  for (int i = 0; i < d; i++) {
    double diff = x[i] - y[i];
    sum += diff * diff;
  }
  return sqrt(sum);
}

int insert_if_closer(int k, int d, const double *points, int *closest, const double *query, int candidate) {
  double dist_candidate = distance(d, &points[candidate * d], query);
  int updated = 0;

  for (int i = 0; i < k; i++) {
    if (closest[i] == -1) {
      closest[i] = candidate;
      updated = 1;
      break;
    } else {
      double dist_closest = distance(d, &points[closest[i] * d], query);
      if (dist_candidate < dist_closest) {
        for (int j = k - 1; j > i; j--) {
          closest[j] = closest[j - 1];
        }
        closest[i] = candidate;
        updated = 1;
        break;
      }
    }
  }
  return updated;
}