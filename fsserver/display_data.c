#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "display_data.h"

#include "../include/params.h"

#include "../include/fs_types.h"
#include "../include/fscom.h"

extern struct fscom *shm_addr;

static display_data_t data = {};

void setup_ids(); // clib

const display_data_t *display_data_fetch(void) {
	static struct fscom *fs;
	char *saveptr;
    time_t timer;
    struct tm* tm_info;

	if (!fs) {
		setup_ids();
		fs = shm_addr;
	}

	if (!data.source) {
		data.source = calloc(1, sizeof(fs->lsorna)+1);
	}
	strncpy(data.source, fs->lsorna, sizeof(fs->lsorna));
    char *ptr;
    for(ptr=data.source; (ptr-data.source) < sizeof(fs->lsorna) && *ptr!=' '; ptr++);
    *ptr = '\0';

	strtok_r(data.source, " ", &saveptr);

	data.halted    = (shm_addr->KHALT != 0);
	data.on_source = (shm_addr->ionsor != 0);

	// TODO:
	// - monit2
	// - moint5
	// - dbbc3
	// - host_time
	//
	if (!data.host_time) {
		data.host_time = calloc(1, 26);
	}
    timer = time(NULL);
    tm_info = localtime(&timer);
    strftime(data.host_time, 26, "%Y-%m-%dZ%H:%M:%S", tm_info);

	return &data;
}
