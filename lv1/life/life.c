#include <unistd.h>
#include <stdlib.h>

static int	count_neighbors(char *b, int w, int h, int x, int y)
{
	int dx, dy, c = 0;

	for (dy = -1; dy <= 1; dy++)
		for (dx = -1; dx <= 1; dx++)
			if ((dx || dy)
				&& x + dx >= 0 && x + dx < w
				&& y + dy >= 0 && y + dy < h
				&& b[(y + dy) * w + (x + dx)])
				c++;
	return (c);
}

int	main(int ac, char **av)
{
	int		w, h, it, x = 0, y = 0, pen = 0;
	char	c;
	char	*board;
	char	*next;

	if (ac != 4)
		return (0);
	w = atoi(av[1]);
	h = atoi(av[2]);
	it = atoi(av[3]);
	board = calloc(w * h, 1);
	next = calloc(w * h, 1);
	if (!board || !next)
		return (0);

	while (read(0, &c, 1) > 0)
	{
		if (c == 'x')
			pen = !pen;
		else if (c == 'w' && y > 0)
			y--;
		else if (c == 's' && y < h - 1)
			y++;
		else if (c == 'a' && x > 0)
			x--;
		else if (c == 'd' && x < w - 1)
			x++;
		if (pen)
			board[y * w + x] = 1;
	}

	while (it--)
	{
		for (y = 0; y < h; y++)
			for (x = 0; x < w; x++)
			{
				int n = count_neighbors(board, w, h, x, y);
				next[y * w + x] =
					(board[y * w + x] && (n == 2 || n == 3))
					|| (!board[y * w + x] && n == 3);
			}
		for (x = 0; x < w * h; x++)
		{
			board[x] = next[x];
			next[x] = 0;
		}
	}

	for (y = 0; y < h; y++)
	{
		for (x = 0; x < w; x++)
			write(1, board[y * w + x] ? "O" : " ", 1);
		write(1, "\n", 1);
	}

	free(board);
	free(next);
	return (0);
}
