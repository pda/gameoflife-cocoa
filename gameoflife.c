#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "gameoflife.h"

/**
 * Initialize a a gameoflife; create the bitmaps.
 */
void
gameoflife_init(struct gameoflife * game, int cols, int rows)
{
	game->active = bitmap_create(cols, rows);
	game->inactive = bitmap_create(cols, rows);
}

void
gameoflife_destroy(struct gameoflife * game)
{
	bitmap_destroy(game->active);
	bitmap_destroy(game->inactive);
}

void
gameoflife_run(struct gameoflife * game)
{
	while (1)
	{
		bitmap_render(game->active);
		gameoflife_tick(game);
	}	
}

void
gameoflife_tick(struct gameoflife * game)
{
	int x, y;
	char alive, neighbors;
	
	for (y = 0; y < game->active->rows; y++)
	{
		for (x = 0; x < game->active->cols; x++)
		{
			neighbors = gameoflife_neighbors(game->active, x, y);
			alive = bitmap_isset(game->active, x, y);
			
			if (alive && (neighbors < 2 || neighbors > 3))
			{
				bitmap_set(game->inactive, x, y, 0);
			}
			else if (!alive && neighbors == 3)
			{
				bitmap_set(game->inactive, x, y, 1);
			}
			else
			{
				bitmap_set(game->inactive, x, y, alive);
			}
		}
	}
	
	gameoflife_bitmap_swap(game);
}

char
gameoflife_neighbors(struct bitmap * b, int x, int y)
{
	int row, col;
	char count = 0;
	
	for (row = y - 1; row <= y + 1; row++)
	{
		for (col = x - 1; col <= x + 1; col++)
		{
			if (col == x && row == y) continue;
			
			count += bitmap_isset(b, col, row);
		}
	}
	
	return count;
}

void
gameoflife_bitmap_swap(struct gameoflife * game)
{
	struct bitmap * tmp = game->inactive;
	game->inactive = game->active;
	game->active = tmp;
}

void
gameoflife_bitmap_random(struct gameoflife * game, int seed, int modulus)
{
	int x, y;
	
	srandom(seed);
	
	for (y = 0; y < game->active->rows; y++)
		for (x = 0; x < game->active->cols; x++)
			bitmap_set(game->active, x, y, random() % modulus == 0);
}