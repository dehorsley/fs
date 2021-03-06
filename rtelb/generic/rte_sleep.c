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
#include <sys/types.h>
#include <sys/times.h>
#include <time.h>

unsigned rte_sleep( centisec)
unsigned centisec;
{
    unsigned sleep();

     int times();
     struct tms buffer;
     int start, end, remain;

     start=times(&buffer);
     remain=100-((start-1)%100);
     if ( remain<=centisec) 
        sleep( ((centisec-remain)+99)/100);
     end=start+centisec;
     while (end>times(&buffer))
        ;

    return( (unsigned) 0);
}
