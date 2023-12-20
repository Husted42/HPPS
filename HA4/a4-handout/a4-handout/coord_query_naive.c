#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#include "record.h"
#include "coord_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data *data = malloc(sizeof(struct naive_data));
  data->rs = rs;
  data->n = n;
  return data;
};

void free_naive(struct naive_data* data) {
  // As the records are not allocated in mk_naive, we do not free them here
  free(data);
};

double euclidean_distance(double lon1, double lat1, double lon2, double lat2) {
  return sqrt(pow(lon1 - lon2, 2) + pow(lat1 - lat2, 2));
};

const struct record* lookup_naive(struct naive_data *data, double lon, double lat) {
  const struct record *closest = NULL;
  double min_distance = DBL_MAX;

  for (int i = 0; i < data->n; i++) {
    double distance = euclidean_distance(lon, lat, data->rs[i].lon, data->rs[i].lat);
    if (distance < min_distance) {
      min_distance = distance;
      closest = &data->rs[i];
    }
  }

  return closest;
};

int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_naive,
                          (free_index_fn)free_naive,
                          (lookup_fn)lookup_naive);
};
