#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_hdr
{
	int rows;
	char e;
	char o;
	char f;
} t_hdr;

// Проверка заголовка: "rows e o f\n"
static int read_header(FILE *fp, t_hdr *h)
{
	if (fscanf(fp, "%d %c %c %c\n", &h->rows, &h->e, &h->o, &h->f) != 4)
		return 0;
	if (h->rows <= 0)
		return 0;
	if (h->e == h->o || h->e == h->f || h->o == h->f)
		return 0;
	if (h->e < 32 || h->e > 126 || h->o < 32 || h->o > 126 || h->f < 32 || h->f > 126)
		return 0;
	return 1;
}

// Проверка карты: правильное число строк, одинаковая длина, только e/o
static int validate_map(FILE *fp, const t_hdr *h)
{
	char *line = NULL;
	size_t cap = 0;
	int cols = -1;

	for (int i = 0; i < h->rows; i++)
	{
		ssize_t r = getline(&line, &cap, fp);
		if (r == -1)
			return free(line), 0;
		if (r > 0 && line[r - 1] == '\n')
			line[--r] = 0;
		if (r <= 0)
			return free(line), 0;
		if (cols == -1)
			cols = (int)r;
		else if (r != cols)
			return free(line), 0;
		for (int j = 0; j < cols; j++)
		{
			if (line[j] != h->e && line[j] != h->o)
				return free(line), 0;
		}
	}
	// Не должно быть лишних строк
	if (getline(&line, &cap, fp) != -1)
		return free(line), 0;
	free(line);
	return 1;
}

static int validate(FILE *fp)
{
	t_hdr h;

	if (!read_header(fp, &h))
		return 0;
	if (!validate_map(fp, &h))
		return 0;
	return 1;
}

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		if (validate(stdin))
			printf("ok\n");
		else
			fprintf(stderr, "map error\n");
		return 0;
	}
	for (int i = 1; i < argc; i++)
	{
		FILE *fp = fopen(argv[i], "r");
		if (!fp)
			fprintf(stderr, "map error\n");
		else
		{
			if (validate(fp))
				printf("ok\n");
			else
				fprintf(stderr, "map error\n");
			fclose(fp);
		}
	}
	return 0;
}
