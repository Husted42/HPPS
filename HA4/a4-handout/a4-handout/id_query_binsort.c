#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct index_record {
  int64_t osm_id;
  const struct record *record;
};

struct indexed_data {
  struct index_record *irs;
  int n;
};

// Comparison function for qsort and bsearch
int compare_index_records(const void *a, const void *b) {
  int64_t id_a = ((struct index_record *)a)->osm_id;
  int64_t id_b = ((struct index_record *)b)->osm_id;
  return (id_a > id_b) - (id_a < id_b);
}

struct indexed_data *mk_indexed(struct record *rs, int n) {
  struct indexed_data *data = malloc(sizeof(struct indexed_data));
  data->irs = malloc(sizeof(struct index_record) * n);
  data->n = n;
  printf("test01\n");

  for (int i = 0; i < n; i++) {
    data->irs[i].osm_id = rs[i].osm_id;
    data->irs[i].record = &rs[i];
  }

  // Sort the index records using qsort
  qsort(data->irs, n, sizeof(struct index_record), compare_index_records);

  return data;
}

void free_indexed(struct indexed_data *data) {
  free(data->irs);
  free(data);
  printf("test02\n");
}

const struct record *lookup_indexed(struct indexed_data *data, int64_t needle) {
  struct index_record key;
  key.osm_id = needle;

  // Use bsearch for finding the record
  struct index_record *result = bsearch(&key, data->irs, data->n, sizeof(struct index_record), compare_index_records);

  if (result) {
    return result->record;
  }

  return NULL;
}

int main(int argc, char **argv) {
  return id_query_loop(argc, argv,
                       (mk_index_fn)mk_indexed,
                       (free_index_fn)free_indexed,
                       (lookup_fn)lookup_indexed);
}
