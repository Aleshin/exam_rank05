#include "bsq.h"

bool extract_mapinfo(char* line, t_bsq* data) {
  size_t i = 0;
  remove_nl(line);

  if (ft_strlen(line) < 7)
    return map_error();

  while (line[i] == ' ')
    ++i;
  
  if (!ft_isnum(line[i]) && line[i] != '+')
    return map_error();

  if (line[i] == '+')
    ++i;

  while (ft_isnum(line[i])) {
    data->lines *= 10;
    data->lines += (line[i] - '0');
    ++i;
  }

  if (line[i] != ' ')
    return map_error();
  else {
    while (line[i] == ' ')
      ++i;
  }

  if (!ft_isprint(line[i]))
    return map_error();
  else {
    data->empty = line[i];
    ++i;
  }

  if (line[i] != ' ')
    return map_error();
  else {
    while (line[i] == ' ')
      ++i;
  }

  if (!ft_isprint(line[i]))
    return map_error();
  else {
    data->obstacle = line[i];
    ++i;
  }

  if (line[i] != ' ')
    return map_error();
  else {
    while (line[i] == ' ')
      ++i;
  }

  if (!ft_isprint(line[i]))
    return map_error();
  else {
    data->full = line[i];
    ++i;
  }
  
  if (line[i])
    return map_error();

  return true;
}

bool parse_map(t_bsq* data, FILE* input) {
  char* line = NULL;
  size_t n = 0;
  
  if (getline(&line, &n, input) != -1) {
    if (!extract_mapinfo(line, data)) {
      free(line);
      return false;
    }
  }
  else {
    free(line);
    return map_error();
  }

  if (data->lines < 1 || data->empty == data->obstacle || data->empty == data->full || data->obstacle == data->full) {
    free(line);
    return map_error();
  }
  size_t i = 0;
  data->map = calloc(data->lines + 1, sizeof(char*));
  if (!data->map)
    return map_error();

  while (getline(&line, &n, input) != -1) {
    if (i == data->lines) {
      free(line);
      return map_error();
    }
    remove_nl(line);
    data->map[i] = copy_line(line);
    if (!data->map[i]) {
      free(line);
      return map_error();
    }
    ++i;
  }
  free(line);

  if (i < data->lines)
    return map_error();
  
  return true;
}

bool verify_map(t_bsq* data) {
  size_t len = ft_strlen(data->map[0]);

  for (size_t y = 0; y < data->lines; ++y) {
    if (ft_strlen(data->map[y]) != len)
      return map_error();

    for (size_t x = 0; x < len; ++x) {
      char c = data->map[y][x];
      if (c != data->empty && c != data->obstacle)
        return map_error();
    }
  }
  return true;
}

int main(int ac, char** av) {
  if (ac == 1) {
    t_bsq* data = calloc(1, sizeof(t_bsq));
    if (!data)
      return EXIT_FAILURE;
    if (!parse_map(data, stdin) || !verify_map(data))
      return free_map_data(data), EXIT_FAILURE;
    bsq(data);
    free_map_data(data);
    return EXIT_SUCCESS;
  }

  for (size_t i = 1; av[i]; ++i) {
    t_bsq* data = calloc(1, sizeof(t_bsq));
    if (!data)
      return EXIT_FAILURE;
    FILE* input = fopen(av[i], "r");
    if (!input) {
      map_error();
      free_map_data(data);
      continue;
    }
    if (!parse_map(data, input) || !verify_map(data)) {
      fclose(input);
      free_map_data(data);
      if (av[i+1])
        fprintf(stdout, "\n");
      continue;
    }
    bsq(data);
    if (av[i+1])
      fprintf(stdout, "\n");
    fclose(input);
    free_map_data(data);
  }

  return EXIT_SUCCESS;
}
