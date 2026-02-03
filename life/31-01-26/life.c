#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc != 4) return 1;
	int w, h, it, x, y, pen, this, ney;
	char c;
	w = atoi(argv[1]);
	h = atoi(argv[2]);
	it = atoi(argv[3]);
	x = 1;
	y = 1;
	pen = 0;
	int m[2][h + 2][w + 2];

// init matrixes
	for (int this = 0; this < 2; this++)
		for (int i = 0; i < h + 2; i++)
			for (int j = 0; j < w +2; j++)
				m[this][i][j] = 0;

	this = 0;
	while (read(0, &c, 1)> 0)
	{
		if (c == 'w' && y > 1) --y;
		else if (c == 'a' && x > 1) --x;
		else if (c == 's' && y < h) ++y;
		else if (c == 'd' && y < w) ++x;
		else if (c == 'x') pen = !pen;
		if (pen == 1) m[this][y][x] = pen;
	}

//calculate
	for (int i = 0; i < it; i++)
	{
		for (int j = 1; j < h + 1; j++)
		{
			for (int k = 1; k < w + 1; k++)
			{
				ney = 0;
				ney += m[this][j-1][k-1] + m[this][j-1][k] + m[this][j-1][k+1];
				ney += m[this][j][k-1] + m[this][j][k+1];
				ney += m[this][j+1][k-1] + m[this][j+1][k] + m[this][j+1][k+1];
				if (m[this][j][k] == 1)
				{
					if (ney == 2 || ney == 3) m[!this][j][k] = 1;
					else m[!this][j][k] = 0;
				}
				else if (ney == 3) m[!this][j][k] = 1;
					else m[!this][j][k] = 0;
			}
		}
		this = !this;
	}
// print matrix
	for (int l = 1; l < h + 1; l++)
	{
		for (int p = 1; p < w + 1; p++)
		{
			if (m[this][l][p] == 1) putchar('0');
				else putchar(' ');
		}
		putchar('\n');
	}
	return 0;
}
