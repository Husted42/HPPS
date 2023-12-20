#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include <math.h>

#include "record.h"
#include "coord_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data* data = malloc(sizeof(struct naive_data));
  data->rs = rs;
  data->n = n;
  return data;
}

void free_naive(struct naive_data* data) {
  free(data->rs);
  free(data);
  return;
}


const struct record* lookup_naive(struct naive_data *data, double lon, double lat) {
  double min_distance = INFINITY;
  const struct record* closest_place = NULL;

  for (int i = 0; i < data->n; i++) {
    double distance = sqrt(pow(data->rs[i].lon - lon, 2) + pow(data->rs[i].lat - lat, 2));
    if (distance < min_distance) {
      min_distance = distance;
      closest_place = &data->rs[i];
    }
  }
  return closest_place;
  }

int main(int argc, char** argv) {
  return coord_query_loop(argc, argv,
                          (mk_index_fn)mk_naive,
                          (free_index_fn)free_naive,
                          (lookup_fn)lookup_naive);
}
