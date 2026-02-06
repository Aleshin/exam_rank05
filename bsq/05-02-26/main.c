#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct s_map
{
	FILE *map;
	int h, w, s, i, j;
	char e, o, f;
} t_map;

int process_map(t_map data)
{
	char* line = NULL;
	size_t len = 0;
	int w, h;

	if (fscanf(data.map, "%d %c %c %c\n", &data.h, &data.e, &data.o, &data.f) != 4) return 0;
	data.w = getline(&line, &len, data.map) - 1;
	int m[data.h][data.w];
	data.i = 0;
	data.j = 0;
	data.s = 0;
	for (int i = 0; i < data.w; i++)
	{
		if (line[i] == data.o) m[0][i] = 0;
			else m[0][i] = 1;
	}

	h = 0;
	while((w = getline(&line, &len, data.map)) > 0)
	{
		if (line[w-1] == '\n') w--;
		if (w != data.w) return 0;
		h++;
		for (int i = 0; i < w; i++)
		{
			if (line[i] == data.o) m[h][i] = 0;
				else if (i == 0) m[h][i] = 1;
					else
					{
						if (m[h][i - 1] > m[h - 1][i - 1])
						{
							if (m[h - 1][i - 1] > m[h - 1][i]) m[h][i] = m[h - 1][i] + 1;
								else m[h][i] = m[h - 1][i - 1] + 1;
						}
						else if (m[h][i - 1] > m[h - 1][i]) m[h][i] = m[h - 1][i] + 1;
							else m[h][i] = m[h][i - 1] + 1;
						if (m[h][i] > data.s)
						{
							data.s = m[h][i];
							data.i = i;
							data.j = h;
						}
					}
		}
	}
	for (int i = 0; i < data.h; i++)
	{
		for (int j = 0; j < data.w; j++)
		{
//			printf("%d", m[i][j]);
			if (m[i][j] == 0) printf("%c", data.o);
				else if (i > data.j - data.s && i <= data.j && j > data.i - data.s && j <= data.i) printf("%c", data.f);
					else printf("%c", data.e);
		}
		printf("\n");		
	}

	if (h != data.h - 1) return 0;
	free(line);
	return 1;
}

int main(int argc, char** argv)
{
	t_map data;
	if (argc == 1)
	{
		data.map = stdin;
		if (!process_map(data)) return fprintf(stderr, "map error\n"), 0;
	}
	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			data.map = fopen(argv[i], "r");
			if (data.map)
			{
				if (!process_map(data))
				{
					fclose(data.map);
					fprintf(stderr, "map error\n");
					return 0;
				}
				fclose(data.map);
				printf("\n");
			}
		}
	}
return 0;
}