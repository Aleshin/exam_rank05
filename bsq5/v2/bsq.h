#ifndef BSQ_H
#define BSQ_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct s_bsq {
  char** map;
  size_t lines;
  char empty;
  char obstacle;
  char full;
} t_bsq;

// utils.c
void free_array(char** arr);
void free_map_data(t_bsq* data);
char* copy_line(const char* str);
bool map_error();
bool ft_isprint(int c);
bool ft_isnum(int c);
void remove_nl(char* str);
size_t ft_strlen(const char* str);

void print_data(t_bsq* data);

// bsq.c
void bsq(t_bsq* data);

#endif
