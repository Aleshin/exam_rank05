#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int rows, cols;
	int **m;
	char e, o, f;
} t_data;

int min3(int a, int b, int c)
{
	return (a <= b && a <= c) ? a : (b <= a && b <= c) ? b : c;
}

int read_header(FILE *fp, t_data *d)
{
	if (fscanf(fp, "%d %c %c %c\n", &d->rows, &d->e, &d->o, &d->f) != 4)
		return 0;
	if (d->rows <= 0)
		return 0;
	if (d->e == d->o || d->e == d->f || d->o == d->f)
		return 0;
	if (d->e < 32 || d->e > 126 || d->o < 32 || d->o > 126 || d->f < 32 || d->f > 126)
		return 0;
	return 1;
}

int read_map(FILE *fp, t_data *d)
{
	char *line = NULL;
	size_t len = 0;

	d->m = malloc(d->rows * sizeof(int *));
	for (int i = 0; i < d->rows; i++)
		d->m[i] = NULL;

	for (int i = 0; i < d->rows; i++)
	{
		if (getline(&line, &len, fp) == -1)
			return free(line), 0;
		int l = strlen(line);
		if (l > 0 && line[l - 1] == '\n')
			line[--l] = 0;
		if (l == 0)
			return free(line), 0;
		if (i == 0)
			d->cols = l;
		else if (l != d->cols)
			return free(line), 0;
		d->m[i] = malloc(l * sizeof(int));
		for (int j = 0; j < l; j++)
		{
			if (line[j] == d->e)
				d->m[i][j] = 0;
			else if (line[j] == d->o)
				d->m[i][j] = -1;
			else
				return free(line), 0;
		}
	}
	free(line);
	return 1;
}

void find_square(t_data *d, int *sz, int *sr, int *sc)
{
	*sz = *sr = *sc = 0;

	// Инициализируем первую строку и первый столбец
	for (int j = 0; j < d->cols; j++)
	{
		if (d->m[0][j] == 0)
		{
			d->m[0][j] = 1;
			if (1 > *sz)
			{
				*sz = 1;
				*sr = 0;
				*sc = j;
			}
		}
	}

	for (int i = 1; i < d->rows; i++)
	{
		if (d->m[i][0] == 0)
		{
			d->m[i][0] = 1;
			if (1 > *sz)
			{
				*sz = 1;
				*sr = i;
				*sc = 0;
			}
		}

		for (int j = 1; j < d->cols; j++)
		{
			if (d->m[i][j] != -1)
			{
				int h = (d->m[i - 1][j] == -1 ? 0 : d->m[i - 1][j]) + 1;
				int l = (d->m[i][j - 1] == -1 ? 0 : d->m[i][j - 1]) + 1;
				int d_val = (d->m[i - 1][j - 1] == -1 ? 0 : d->m[i - 1][j - 1]) + 1;
				d->m[i][j] = min3(h, l, d_val);
				if (d->m[i][j] > *sz)
				{
					*sz = d->m[i][j];
					*sr = i - *sz + 1;
					*sc = j - *sz + 1;
				}
			}
		}
	}
}

void print_map(t_data *d, int sr, int sc, int sz)
{
	for (int i = 0; i < d->rows; i++)
	{
		for (int j = 0; j < d->cols; j++)
		{
			if (i >= sr && i < sr + sz && j >= sc && j < sc + sz)
				putchar(d->f);
			else
				putchar(d->m[i][j] == -1 ? d->o : d->e);
		}
		putchar('\n');
	}
}

void free_data(t_data *d)
{
	for (int i = 0; i < d->rows; i++)
		free(d->m[i]);
	free(d->m);
}

int process_map(FILE *fp)
{
	t_data d;
	int sz, sr, sc;

	if (!read_header(fp, &d))
		return fprintf(stderr, "map error\n"), 0;
	if (!read_map(fp, &d))
		return fprintf(stderr, "map error\n"), 0;
	find_square(&d, &sz, &sr, &sc);
	print_map(&d, sr, sc, sz);
	free_data(&d);
	return 1;
}

int main(int argc, char **argv)
{
	if (argc == 1)
		process_map(stdin);
	else
	{
		for (int i = 1; i < argc; i++)
		{
			FILE *fp = fopen(argv[i], "r");
			if (!fp)
				fprintf(stderr, "map error\n");
			else
			{
				process_map(fp);
				fclose(fp);
			}
		}
	}
	return 0;
}
