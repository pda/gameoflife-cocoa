#include "framerate.h"
#include <sys/time.h>

void
framerate_init(struct framerate * fr)
{
	fr->increments = 0;
	fr->seconds_last = framerate_seconds();
}

void
framerate_increment(struct framerate * fr, int frames)
{
	double seconds = framerate_seconds();
	double elapsed = seconds - fr->seconds_last;
	
	fr->framerate[fr->increments % PERIODS] = frames / elapsed;
	fr->seconds_last = seconds;
	fr->increments++;
}

int
framerate_get(struct framerate * fr)
{
	int i;
	float total = 0;
	
	for (i = 0; i < PERIODS && i < fr->increments; i++)
	{
		total += fr->framerate[i];
	}

	if (i == 0) return 0;
	
	return (int)(total / i);
}

double
framerate_seconds(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec + (double)tv.tv_usec / 1000000;
}