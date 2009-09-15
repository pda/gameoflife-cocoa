#include "bitmap.h"

#define GOL_USLEEP 1000

struct gameoflife {
	struct bitmap * active;
	struct bitmap * inactive;
};

void
gameoflife_init(struct gameoflife * game, int cols, int rows);

void
gameoflife_destroy(struct gameoflife * game);

void
gameoflife_run(struct gameoflife *);

void
gameoflife_tick(struct gameoflife *);

char
gameoflife_neighbors(struct bitmap *, int x, int y);

void
gameoflife_bitmap_swap(struct gameoflife *);

void
gameoflife_bitmap_random(struct gameoflife *, int seed, int modulus);