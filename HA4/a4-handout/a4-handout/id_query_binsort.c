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

int compare_index_record(const void *a, const void *b) {
    int64_t a_id = ((struct index_record *)a)->osm_id;
    int64_t b_id = ((struct index_record *)b)->osm_id;
    return (a_id > b_id) - (a_id < b_id);
}

struct indexed_data* mk_binsort(struct record* rs, int n){
    struct indexed_data* data = malloc(sizeof(struct indexed_data));
    data->irs = malloc(sizeof(struct index_record) * n);
    data->n = n;
    printf("test01 %d\n", n);
    for (int i = 0; i < n; i++) {
        data->irs[i].osm_id = rs[i].osm_id;
        data->irs[i].record = &rs[i];
    }


    qsort(data->irs, n, sizeof(struct index_record), compare_index_record);
    return data;
}

void free_sort(struct indexed_data* data){
    free(data->irs);
    free(data);
    return;
}

const struct record *lookup_binsort(struct indexed_data *data, int64_t needle){
    struct index_record key;
    key.osm_id = needle;
    
    struct index_record *result = bsearch(&key, data->irs, data->n, sizeof(struct index_record), compare_index_record);

    if (result){
        return result->record;
    }
    return NULL;
}


int main(int argc, char** argv) {
    return id_query_loop(argc, argv,
                        (mk_index_fn)mk_binsort,
                        (free_index_fn)free_sort,
                        (lookup_fn)lookup_binsort);
}
