#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include "bitmap.h"

/**
 * Creates a bitmap, use bitmap_destroy() to free.
 */
struct bitmap *
bitmap_create(int cols, int rows)
{
	struct bitmap * b = (void *)malloc(sizeof(struct bitmap));
	int blocks;
	
	b->cols = cols;
	b->rows = rows;
	b->size = rows * cols;
	
	blocks = b->size / BITMAP_CHAR_BITS;
	if (b->size % BITMAP_CHAR_BITS)
		blocks += 1;
	
	b->data = (void *)malloc(blocks);
	
	return b;
}

/**
 * Destroy a bitmap, freeing its memory.
 */
void
bitmap_destroy(struct bitmap * b)
{
	free(b->data);
	free(b);
}

/**
 * Creates bitmap_coordinates.
 * Handles wrapping of would-be out-of-bounds access.
 */
void
bitmap_coordinates_load(struct bitmap * b, int x, int y, struct bitmap_coordinates * bc)
{
	if (x >= b->cols) x %= b->cols;
	else if (x < 0) x = b->cols + (x % b->cols);
	
	if (y >= b->rows) y %= b->rows;
	else if (y < 0) y = b->rows + (y % b->rows);
	
	bc->block = b->data + (x + y * b->cols) / BITMAP_CHAR_BITS;
	bc->block_bitmask = 1 << ((x + y * b->cols) % BITMAP_CHAR_BITS);
}

/**
 * Render the bitmap as an OpenGL matrix.
 */
void
bitmap_render(struct bitmap * b)
{	
	int row_i, col_i, x, y;
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 1.0, 0);

	for (row_i = 0; row_i < b->rows; row_i++)
	{
		for (col_i = 0; col_i < b->cols; col_i++)
		{
			x = (float)col_i * 5 + 2.5;
			y = (float)row_i * 5 + 2.5;
			
			if (bitmap_isset(b, col_i, row_i))
			{
				glBegin(GL_POINTS);
				glVertex2f(x, y);
				glEnd();
			}
		}
	}
	glFlush();
}

/**
 * Set or unset a bit.
 */
void
bitmap_set(struct bitmap * b, int x, int y, char on)
{
	struct bitmap_coordinates bc;
	
	bitmap_coordinates_load(b, x, y, &bc);

	*bc.block = on ?
		*bc.block | bc.block_bitmask :
		*bc.block & ~bc.block_bitmask;
}

/**
 * Whether the bit at the given coordinates is set.
 */
char
bitmap_isset(struct bitmap * b, int x, int y)
{
	struct bitmap_coordinates bc; 
	
	bitmap_coordinates_load(b, x, y, &bc);
	return (*bc.block & bc.block_bitmask) > 0;
}

/**
 * Clears a bitmap.
 */
void
bitmap_clear(struct bitmap * bitmap)
{
	int x, y;
	
	for (y = 0; y < bitmap->rows; y++)
		for (x = 0; x < bitmap->cols; x++)
			bitmap_set(bitmap, x, y, 0);
	
}

/**
 * Loads a bitmap from a Run Length Encoded ASCII file.
 * @see http://conwaylife.com/wiki/index.php?title=Run_Length_Encoded
 */
void
bitmap_load_rle(struct bitmap * bitmap, char * filepath)
{
	// TODO: open and validate file
	
	bitmap_clear(bitmap);
}