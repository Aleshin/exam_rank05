#include "bsq.h"

bool extract_mapinfo(t_map* data, char* mapinfo) {
  size_t i = 0;
  remove_nl(mapinfo);

  if (ft_strlen(mapinfo) < 7)
    return map_error();
  
  while (mapinfo[i] == ' ')
    ++i;
  
  if (!ft_isnum(mapinfo[i]))
    return map_error();
  
  while (ft_isnum(mapinfo[i])) {
    data->lines *=10;
    data->lines += (mapinfo[i] - '0');
    ++i;
  }

  if (mapinfo[i] != ' ')
    return map_error();
  else {
    while (mapinfo[i] == ' ')
      ++i;
  }

  if (ft_isprint(mapinfo[i])) {
    data->empty = mapinfo[i];
    ++i;
  }
  else
    return map_error();

  if (mapinfo[i] != ' ')
    return map_error();
  else {
    while (mapinfo[i] == ' ')
      ++i;
  }
    
  if (ft_isprint(mapinfo[i])) {
    data->obstacle = mapinfo[i];
    ++i;
  }
  else
    return map_error();

  if (mapinfo[i] != ' ')
    return map_error();
  else {
    while (mapinfo[i] == ' ')
      ++i;
  }

  if (ft_isprint(mapinfo[i])) {
    data->full = mapinfo[i];
    ++i;
  }
  else
    return map_error();

  if (mapinfo[i] != '\0' || data->empty == data->obstacle || data->empty == data->full || data->obstacle == data->full || data->lines == 0)
    return map_error();

  return true;
}

bool parse_file(t_map* data, FILE* input) {
  char* line = NULL;
  size_t size = 0;

  if (getline(&line, &size, input) != -1) {
    if (!extract_mapinfo(data, line)) {
      free(line);
      return false;
    }
  }
  else {
    free(line);
    return map_error();
  }

  size_t i = 0;
  data->map = calloc(data->lines + 1, sizeof(char*));
  while(getline(&line, &size, input) != -1) {
    if (i == data->lines){
      free(line);
      return map_error();
    }
    data->map[i] = copy_line(line);
    ++i;
  }

  free(line);
  if (i < data->lines)
    return map_error();
  return true;
}

bool verify_map(t_map* data) {
  size_t len = ft_strlen(data->map[0]);
  for (size_t i = 0; data->map[i]; ++i) {
    if (ft_strlen(data->map[i]) != len || ft_strlen(data->map[i]) == 0)
      return map_error();
  }
  
  for (size_t i = 0; data->map[i]; ++i) {
    for (size_t j = 0; data->map[i][j] != '\0'; ++j) {
      char c = data->map[i][j];
      if (c != data->empty && c != data->obstacle)
        return map_error();
    }
  }

  return true;
}

int main(int ac, char** av) {
  if (ac == 1) {
    t_map* data = calloc(1, sizeof(t_map));
    if (!parse_file(data, stdin) || !verify_map(data)) {
      free_map_data(data); 
      return 1;
    }
    bsq(data);
    free_map_data(data);
  }
  else {
    for (size_t i = 1; av[i]; ++i) {
      t_map* data = calloc(1, sizeof(t_map));
      FILE* input = fopen(av[i], "r");
      if (!input) {
        map_error();
        free_map_data(data);
        continue;
      }
      if (!parse_file(data, input) || !verify_map(data)) {
        fclose(input);
        free_map_data(data);
        if (av[i + 1])
          fprintf(stdout, "\n");
        continue;
      }
      bsq(data);
      if (av[i + 1])
        fprintf(stdout, "\n");
      fclose(input);
      free_map_data(data);
    }
  }
  return 0;
}
