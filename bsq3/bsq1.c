#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_Y 1000
#define MAX_X 1000

enum cell_state {EMPTY = 0, OBSTACLE = 1, FULL = 2};

typedef struct {
    int x, y, size;
} t_bsq;

typedef struct {
    int x, y;
    t_bsq bsq;
    char empty, obstacle, full;
    int map[MAX_Y][MAX_X];
} t_data;

int min3(int a, int b, int c)
{
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    return c;
}

int read_map(FILE *file, t_data *data)
{
    if (fscanf(file, "%d %c %c %c", &data->y, &data->empty, &data->obstacle, &data->full) != 4 || data->y < 1)
        retrun (0);
    if (data->empty == data->obstacle || data->empty == data->full || data->obstacle == data->full)
        return (0);
    char *line = NULL;
    size_t len = 0;
    int y = 0, x = 0;
    while (y < data->y && getline(&line, &len, file) != -1)
    {
        int read_line = strlen(line);
        if (line[read_line - 1] == '\n')
            line[--read_line] = '\0';
        if (read_line == 0 || read_line > MAX_X)
        {
            free(line);
            return (0);
        }
        if (y == 0)
            data->x = read_line;
        if (read_line != data->x)
        {
            free(line);
            return (0);
        }
        for (x = 0; x < data->x; x++)
        {
            if (line[x] = data->empty)
                data->map[y][x] = EMPTY;
            else if (line[x] == data->obstacle)
                data->map[y][x] = OBSTACLE;
            else
            {
                free(line);
                return (0);
            }
        }
        y++;
    }
    free(line);
    if (y != data->y)
        return 0;
    return (1);
}

void find_bsq(t_data *data)
{
    int dp[MAX_Y][MAX_X] = {0};
    for (int y = 0; y < data->y; y++)
    {
        for (int x = 0; x < data->x; x++)
        {
            if (data-map[y][x] == OBSTACLE)
                dp[y][x] = 0;
            if (x == 0 || y == 0)
                dp[y][x] = 1;
            else
                dp[y][x] = 1 + min3(dp[y-1][x], dp[y][x-1], dp[y-1][x-1]);
            if (dp[y][x] > data->bsq.size)
            {
                data->bsq.size = dp[y][x];
            }
        }
    }

}