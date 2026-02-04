#include "bsq.h"

void free_array(char** arr) {
  if (!arr)
    return;
  for (size_t i = 0; arr[i]; ++i)
    free(arr[i]);
  free(arr);
}

void free_map_data(t_bsq* data) {
  if (!data)
    return;
  if (data->map)
    free_array(data->map);
  free(data);
}

char* copy_line(const char* str) {
  size_t len = ft_strlen(str);
  char* result = calloc(len + 1, sizeof(char));
  if (!result)
    return NULL;
  for (size_t i = 0; str[i]; ++i)
    result[i] = str[i];
  return result;
}

bool map_error() {
  fprintf(stderr, "map error\n");
  return false;
}

bool ft_isprint(int c) {
  return c > 31 && c < 127;
}

bool ft_isnum(int c) {
  return c > 47 && c < 58;
}

void remove_nl(char* str) {
  if (!str)
    return;
  size_t len = ft_strlen(str);
  if (str[len - 1] == '\n')
    str[len - 1] = '\0';
}

size_t ft_strlen(const char* str) {
  size_t i = 0;
  if (!str)
    return 0;
  while (str[i])
    ++i;
  return i;
}

void print_data(t_bsq* data) {
  printf("lines: %ld\n", data->lines);
  printf("empty: %c\n", data->empty);
  printf("obsta: %c\n", data->obstacle);
  printf("full:  %c\n", data->full);
  for (size_t i = 0; data->map[i]; ++i)
    printf("%s\n", data->map[i]);
}
