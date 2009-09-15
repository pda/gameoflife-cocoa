#include <sys/time.h>
#define PERIODS 3

struct framerate {
	float framerate[PERIODS];
	double seconds_last;
	int increments;
};

void
framerate_init(struct framerate *);

void
framerate_increment(struct framerate *, int frames);

int
framerate_get(struct framerate *);

double
framerate_seconds(void);