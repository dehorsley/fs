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
/* systracks parsing utilities */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include "../include/macro.h"

#include "../include/params.h"
#include "../include/fs_types.h"
#include "../include/fscom.h"         /* shared memory definition */
#include "../include/shm_addr.h"      /* shared memory pointer */
#include "../include/clib/clib.h"

int systracks_dec(lcl,count,ptr)
struct systracks_cmd *lcl;
int *count;
char *ptr;
{
    int ierr, arg_key(), ind;
    static int idflt[]={0,1,34,35};

    ierr=0;
    if(ptr == NULL) ptr="";

    ind =*count-1;

    switch (*count) {
    case 1:
    case 2:
    case 3:
    case 4:
      ierr=arg_int(ptr,&lcl->track[ind],idflt[ind],TRUE);
      if(ierr ==0 && (lcl->track[ind]>35 || lcl->track[ind]<0))
	ierr=-200;
      break;
    default:
      *count=-1;
    }

    if(ierr!=0) ierr-=*count;
    if(*count>0) (*count)++;
    return ierr;
  }

void systracks_enc(output,count,lcl)
char *output;
int *count;
struct systracks_cmd *lcl;
{
    int ivalue, ind;

    output=output+strlen(output);

    ind=*count-1;

    switch (*count) {
      case 1:
      case 2:
      case 3:
      case 4:
        ivalue=lcl->track[ind];
        if(ivalue > -1 && ivalue < 36 )
           sprintf(output,"%d",ivalue);
        else
          strcpy(output,BAD_VALUE);
        break;
      default:
       *count=-1;
   }

   if(*count>0) *count++;
   return;
}

void systracks82mc(data,lcl)
unsigned *data;
struct systracks_cmd *lcl;
{

   *data= bits16on(6) & lcl->track[ 0];

   return;
}

void systracks83mc(data,lcl)
unsigned *data;
struct systracks_cmd *lcl;
{

   *data= bits16on(6) & lcl->track[ 1];

   return;
}

void systracks84mc(data,lcl)
unsigned *data;
struct systracks_cmd *lcl;
{
     *data= bits16on(6) & lcl->track[ 2];

     return;
}

void systracks85mc(data,lcl)
unsigned *data;
struct systracks_cmd *lcl;
{
     *data= bits16on(6) & lcl->track[ 3];

     return;
}

void mc82systracks(lcl, data)
struct systracks_cmd *lcl;
unsigned data;
{

       lcl->track[ 0] =  data & bits16on(6);

       return;
}

void mc83systracks(lcl, data)
struct systracks_cmd *lcl;
unsigned data;
{

       lcl->track[ 1] =  data & bits16on(6);

       return;
}

void mc84systracks(lcl, data)
struct systracks_cmd *lcl;
unsigned data;
{
       lcl->track[ 2] =  data & bits16on(6);

       return;
}

void mc85systracks(lcl, data)
struct systracks_cmd *lcl;
unsigned data;
{
       lcl->track[ 3] =  data & bits16on(6);

       return;
}
