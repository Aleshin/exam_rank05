#include "bsq.h"

bool map_error() {
  fprintf(stderr, "map error\n");
  return false;
}

void free_map_data(t_map* data) {
  if (!data)
    return;
  if (!data->map) {
    free(data);
    return;
  }
  for (size_t i = 0; data->map[i]; ++i)
    free(data->map[i]);
  free(data->map);
  free(data);
}
