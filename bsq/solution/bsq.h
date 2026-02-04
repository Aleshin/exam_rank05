#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int rows, cols;
	char **map;
	char e, o, f;
	int *h;
	int sz, sr, sc;
} t_data;

int read_header(FILE *fp, t_data *d);
int read_map(FILE *fp, t_data *d);
void find_square(t_data *d);
void print_map(t_data *d);
void free_data(t_data *d);
int process_map(FILE *fp);

#endif
