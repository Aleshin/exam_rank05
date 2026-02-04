#include "bsq.h"

char* copy_line(char* str) {
  remove_nl(str);
  size_t len = ft_strlen(str) + 1;
  char* result = calloc(len, sizeof(char));
  for (size_t i = 0; i < len; ++i)
    result[i] = str[i];
  return result;
}

void remove_nl(char* str) {
  size_t len = ft_strlen(str);
  if (len > 0 && str[len - 1] == '\n')
    str[len - 1] = '\0';
}

bool ft_isnum(int c) {
  return (c > 47 && c < 58) ? true : false;
}

bool ft_isprint(int c) {
  return (c > 31 && c < 127) ? true : false;
}

size_t ft_strlen(const char* str) {
  if (!str)
    return 0;
  size_t i = 0;
  while (str[i])
    ++i;
  return i;
}

void print_data(t_map* data) {
  for (size_t i = 0; data->map[i]; ++i)
    printf("%s\n", data->map[i]);
  printf("lines: %d\n", data->lines);
  printf("empty: %c\n", data->empty);
  printf("obstc: %c\n", data->obstacle);
  printf("full:  %c\n", data->full);
}
