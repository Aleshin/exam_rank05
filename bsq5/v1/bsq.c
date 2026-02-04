#include "bsq.h"

int** create_results_table(t_map* data) {
  int** results = calloc(data->lines, sizeof(int*));
  for (int i = 0; i < data->lines; ++i) {
    results[i] = calloc(ft_strlen(data->map[0]), sizeof(int));
  }
  return results;
}

int min_value(int a, int b, int c) {
  int lowest = (a < b) ? a : b;
  lowest = (lowest < c) ? lowest : c;
  return lowest;
}

void free_results(int** arr, size_t lines) {
  if (!arr)
    return;
  for (int i = 0; i < lines; ++i)
    free(arr[i]);
  free(arr);
}

void bsq(t_map* data) {
  int** results = create_results_table(data);
  char** map = data->map;
  int lines = data->lines;
  int len = ft_strlen(data->map[0]);

  int winner = 0;
  int win_x = 0;
  int win_y = 0;

  for (size_t y = 0; y < lines; ++y) {
    for (size_t x = 0; x < len; ++x) {
      if (map[y][x] == data->obstacle)
        results[y][x] = 0;
      else if (y == 0 || x == 0)
        results[y][x] = 1;
      else
        results[y][x] = min_value(results[y - 1][x], results[y - 1][x - 1], results[y][x - 1]) + 1;
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
    for (size_t y = 0; y < lines; ++y) {
      for (size_t x = 0; x < len; ++x) {
        if (x >= end_x && x <= win_x && y >= end_y && y <= win_y)
          map[y][x] = data->full;
      }
    }
  }

  free_results(results, lines);

  for (size_t i = 0; i < lines; ++i) {
    fprintf(stdout, "%s\n", map[i]);
  }
}
