#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char **grid;
    char empty, obstacle, full;
    int  *dp;
    int  rows, cols;
    int  max_size, max_rows, max_cols;
} map;

int len(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

int pars_head(FILE *f, map *m)
{
    fscanf(f, "%d", &m->rows);
    if (m->rows <= 0) return 0;

    char *line = NULL; size_t l = 0;

    if (getline(&line, &l, f) <= 0)
        return 0;


    if (len(line) != 4) 
        return 0;
        
    m->empty = line[0];
    m->obstacle = line[1];
    m->full = line[2];

    return (m->empty != m->obstacle && m->empty != m->full && m->obstacle != m->full);
}

int load_map(FILE *f, map *m)
{
    char *line = NULL; size_t l = 0;
    if (getline(&line, &l, f) <= 0) 
        return 0;


    m->cols = len(line) - 1;
    if (m->cols <= 0)
        return 0;

    m->grid = malloc(m->rows * sizeof(char *));

    m->grid[0] = line;

    for (int i = 1; i < m->rows; i ++)
    {
        line = NULL; l = 0;
        if (getline(&line, &l, f) <= 0)
            return 0;

        if ((len(line) - 1) != m->cols)
            return 0;

        m->grid[i] = line;
    
        for (int j = 0; j < m->cols; j ++)
        {
            if (m->grid[i][j] != m->empty && m->grid[i][j] != m->obstacle)
                return 0;
        }
    }
    return 1;
}

int min3(int min, int a, int b)
{
    if (min > a)
        min = a;
    if (min > b)
        min = b;
    return min;
}

void find_big_square(map *m)
{
    m->dp   = calloc(m->cols * m->rows, 4);
    m->max_cols = 0; m->max_rows = 0; m->max_size = 0;
    for (int i = 0; i < m->rows; i ++)
    {
        for (int j = 0; j < m->cols; j ++)
        {
            if (m->grid[i][j] == m->obstacle)
                m->dp[i * m->cols + j] = 0;
            else
            {
                if (i == 0 || j == 0)
                    m->dp[i * m->cols + j] = 1;
                else
                {
                    m->dp[i * m->cols + j] = min3(m->dp[(i - 1) * m->cols + (j - 1)], m->dp[(i - 1) * m->cols + j], m->dp[i * m->cols + (j - 1)]) + 1;
                }
                if (m->dp[i * m->cols + j] > m->max_size)
                {
                    m->max_size = m->dp[i * m->cols + j];
                    m->max_cols = j - m->max_size + 1;
                    m->max_rows = i - m->max_size + 1;
                }
            }
        }
    }
}

void draw(map *m)
{
    for (int i = 0; i < m->rows; i ++)
    {
        for (int j = 0; j < m->cols; j ++)
        {
            if (i >= m->max_rows && i < m->max_rows + m->max_size &&
                j >= m->max_cols && j < m->max_cols + m->max_size)
                fprintf(stdout, "%c", m->full);
            else
                fprintf(stdout, "%c", m->grid[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

void proccess_map(FILE *f)
{
    map m = {0};
    if (!pars_head(f, &m) || !load_map(f, &m))
        { fprintf(stderr, "map error\n"); return ; }
    find_big_square(&m);
    draw(&m);
}


int main(int ac, char** av)
{
    if (ac == 1)
        proccess_map(stdin);
    else
    {
        FILE *f = fopen(av[1], "r");
        if (!f)
            { fprintf(stderr, "map error\n"); return 1; }
        proccess_map(f);
        fclose(f);
    }
    return 0;
}