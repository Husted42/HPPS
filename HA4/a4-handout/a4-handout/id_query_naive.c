#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>
#include <errno.h>
#include <assert.h>

#include "record.h"
#include "id_query.h"

struct naive_data {
  struct record *rs;
  int n;
};

// The mk_naive function in C creates and initializes a naive_data structure.
// It allocates memory for this structure, sets its rs member to point to the provided array of records,
// and its n member to the provided number of records.
// The function then returns a pointer to the newly created naive_data structure.
struct naive_data* mk_naive(struct record* rs, int n) {
  struct naive_data* data = malloc(sizeof(struct naive_data));
  data->rs = rs;
  data->n = n;
  return data;
}

// The `free_naive` function in C is designed to deallocate memory associated with a `naive_data` structure.
// It first frees the memory for the `record` structures pointed to by `data->rs`,
// then it frees the memory for the `naive_data` structure itself.
// This function is essential for preventing memory leaks in the program.
void free_naive(struct naive_data* data) {
  free(data->rs);
  free(data);
  return;
}

// The lookup_naive function in C searches for a record with a specific osm_id in a naive_data structure
// It iterates over each record, and if it finds a record with an osm_id that matches the provided needle, 
// it returns a pointer to that record. If no matching record is found after checking all records, 
// it returns NULL.
const struct record* lookup_naive(struct naive_data *data, int64_t needle) {
  for (int i = 0; i < data->n; i++) {
    if (data->rs[i].osm_id == needle) {
      return &data->rs[i];
    }
  }
  return NULL;
}

int main(int argc, char** argv) {
  return id_query_loop(argc, argv,
                    (mk_index_fn)mk_naive,
                    (free_index_fn)free_naive,
                    (lookup_fn)lookup_naive);
}
