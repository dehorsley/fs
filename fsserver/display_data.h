#include <stdbool.h>

typedef struct {
	char *source;
	bool halted;
	bool on_source;

	double azimuth, elevation;
	double right_ascension, declination;
	char *host_time;
} display_data_t;

const display_data_t *display_data_fetch(void);
