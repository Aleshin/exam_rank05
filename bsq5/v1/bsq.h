#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct s_map {
  char** map;
  int lines;
  char empty;
  char obstacle;
  char full;
} t_map;

// utils.c
char* copy_line(char* str);
void remove_nl(char* str);
bool ft_isnum(int c);
bool ft_isprint(int c);
size_t ft_strlen(const char* str);
void print_data(t_map* data);

// error.c
bool map_error();
void free_map_data(t_map* data);

//bsq.c
void bsq(t_map* data);

#endif
