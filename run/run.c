/*
 * Copyright (c) 2020 NVI, Inc.
 *
 * This file is part of VLBI Field System
 * (see http://github.com/nvi-inc/fs).
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#include "../include/params.h"
#include "../include/fs_types.h"
#include "../include/fscom.h"

#define MAX_BUF     256

static int ipr[5] = { 0, 0, 0, 0, 0};
extern struct fscom *shm_addr;

main(argc, argv)
int argc;
char **argv;
{
    void setup_ids(), skd_run();
    char mess[20], wait, arg[MAX_BUF+1];
    int ivalue, first, i, count;

    if (argc < 2 ) {
      printf(" not enough args\n");
      exit(-1);
    }

    setup_ids();

    first = 1;
    wait = ' ';
    if (strcmp(argv[1],"-w")==0) {
      first = 2;
      wait='w';
      if (argc < 3){
	printf(" not enough args\n");
	exit(-1);
      }
    }

    count = 0;
    for(i = first; i < argc; i++)
      count+=strlen(argv[i])+1;
    if (count >MAX_BUF) {
      printf(
       "args too long, must be less than %d characters with separators\n",
	     MAX_BUF);
      exit(-1);
    }
    arg[0]='\0';
    for (i=first; i < argc; i++) {
      strcat(arg,argv[i]);
      if(i != argc-1)
	strcat(arg," ");
    }

    skd_run_arg(argv[first],wait,ipr,arg);
    if( wait == 'w') {
      sprintf(mess,"%-5.5s finished",argv[first]);
      memcpy(&ivalue,"to",2);
      cls_snd(&(shm_addr->iclbox),mess,14,0,ivalue);
    }

    exit( 0);
}
