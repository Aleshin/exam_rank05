#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int min3(int a, int b, int c)
{
	return (a <= b && a <= c) ? a : (b <= c && b <= a) ? b : c;
}

int process_map(FILE* map)
{
	int h, w, i, j;
	char e, o, f;
	char* c;
	size_t len = 0;
	int s = 0;
	int x = 0;
	int y = 0;

	if (fscanf(map, "%d %c %c %c\n", &h, &e, &o, &f) !=4) return 1;
	if (h < 1 || e == o || e == f || o == f) return 1;
	if ((w = getline(&c, &len, map) - 1) <= 0) return free(c), 1;
	int m[h][w];

	for (j = 0; j < w; j++)
	{
		if (c[j] != o && c[j] != e) return free(c), 1;
		if (c[j] == o) m[0][j] = 0;
		else
		{
			m[0][j] = 1;
			if (m[0][j] > s)
			{
				s = 1;
				x = j;
			}
		}
	}
	i = 0;
	while((j = getline(&c, &len, map) - 1) > 0)
	{
		i++;
		if (j != w || i >= h) return free(c), 1;
		m[i][0] = 1;
		for (j = 0; j < w; j++)
		{
			if (c[j] != o && c[j] != e) return free(c), 1;
			if (c[j] == o) m[i][j] = 0;
			else
			{
				m[i][j] = min3(m[i - 1][j], m[i - 1][j - 1], m[i][j - 1]) + 1;
				if (m[i][j] > s)
				{
					s = m[i][j];
					x = j;
					y = i;
				}
			}
		}
	}
	free(c);

	if (i < h - 1) return 1;
	
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			if (m[i][j] == 0) printf("%c", o);
				else if (i > y - s && i <= y && j > x - s && j <= x) printf("%c", f);
					else printf("%c", e);
		}
		printf("\n");
	}
	return 0;
}

int main(int argc, char** argv)
{
	FILE* map;
	if (argc == 1)
	{
		map = stdin;
		if (!map) return fprintf(stderr, "Error: no stdin\n"), 1;
		if (process_map(map)) fprintf(stderr, "Error\n");
	} else if (argc == 2)
	{
		map = fopen(argv[1], "r");
		if (!map) return fprintf(stderr, "Error: map\n"), 1;
		if (process_map(map)) fprintf(stderr, "Error\n");
		fclose(map);
	} else fprintf(stderr, "Error: wrong args\n");
	return 0;
}
