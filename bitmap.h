#define BITMAP_CHAR_ON '*'
#define BITMAP_CHAR_OFF ' '
#define BITMAP_CHAR_BITS 8

struct bitmap {
	int cols;
	int rows;
	int size;
	unsigned char * data;
};

struct bitmap_coordinates {
	unsigned char * block;
	unsigned char block_bitmask;
};

struct bitmap *
bitmap_create(int cols, int rows);

void
bitmap_destroy(struct bitmap *);

void
bitmap_coordinates_load(struct bitmap *, int x, int y, struct bitmap_coordinates *);

void
bitmap_render(struct bitmap *);

void
bitmap_set(struct bitmap *, int x, int y, char on);

char
bitmap_isset(struct bitmap *, int x, int y);

void
bitmap_clear(struct bitmap *);

void
bitmap_load_rle(struct bitmap *, char * filepath);