#include "bsq.h"

void free_results_array(int** results, t_bsq* data) {
  if (!results)
    return;
  for (size_t i = 0; i < data->lines; ++i)
    free(results[i]);
  free(results);
} 

int** init_result_array(t_bsq* data) {
  int** results = calloc(data->lines, sizeof(int*));
  if (!results)
    return NULL;
  for (size_t i = 0; i < data->lines; ++i) {
    results[i] = calloc(ft_strlen(data->map[0]), sizeof(int));
    if (!results[i])
      free_results_array(results, data);
  }
  return results;
}

int min_val(int a, int b, int c) {
  int lowest = (a < b) ? a : b;
  return (lowest < c) ? lowest : c;
}

void bsq(t_bsq* data) {
  int** results = init_result_array(data);
  if (!results)
    return;

  int winner = 0;
  int win_x = 0;
  int win_y = 0;
  
  size_t len = ft_strlen(data->map[0]);
  for (size_t y = 0; y < data->lines; ++y) {
    for (size_t x = 0; x < len; ++x) {
      if (data->map[y][x] == data->obstacle)
        results[y][x] = 0;
      else if (y == 0 || x == 0)
        results[y][x] = 1;
      else
        results[y][x] = min_val(results[y-1][x-1], results[y-1][x], results[y][x-1]) + 1;
      if (results[y][x] > winner) {
        winner = results[y][x];
        win_x = x;
        win_y = y;
      }
    }
  }

  if (winner > 0) {
    int win_size = results[win_y][win_x];
    int end_x = win_x - win_size + 1;
    int end_y = win_y - win_size + 1;
    for (size_t y = 0; y < data->lines; ++y) {
      for (size_t x = 0; x < data->lines; ++x) {
        if (y >= end_y && y <= win_y && x >= end_x && x <= win_x)
          data->map[y][x] = data->full;
      }
    }
  }

  free_results_array(results, data);

  for (size_t i = 0; i < data->lines; ++i)
    fprintf(stdout, "%s\n", data->map[i]);
}
