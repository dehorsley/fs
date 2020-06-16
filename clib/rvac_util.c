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
/* ifd rvac buffer parsing utilities */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>
#include "../include/params.h"
#include "../include/fs_types.h"
#include "../include/macro.h"
#include "../include/fscom.h"
#include "../include/shm_addr.h"
#include "../include/clib/clib.h"

int rvac_dec(lcl,count,ptr)
struct rvac_cmd *lcl;
int *count;
char *ptr;
{
    int ierr, ind;

    ierr=0;
    if(ptr == NULL) ptr="";

    switch (*count) {
    case 1:
      if(0==strcmp(ptr,"*") && !lcl->set)
	ierr=-300;
      else {
	ierr=arg_float(ptr,&lcl->inches,0,FALSE);
	if(ierr==0)
	  lcl->set=TRUE;
      }
      break;
    default:
      *count=-1;
   }
   if(ierr!=0) ierr-=*count;
   if(*count>0) (*count)++;
   return ierr;
}

void rvac_enc(output,count,lcl)
char *output;
int *count;
struct rvac_cmd *lcl;
{
    int ind, ivalue;

    output=output+strlen(output);

    switch (*count) {
    case 1:
      if(lcl->set)
	flt2str(output,lcl->inches,32,1);
      break;
    default:
      *count=-1;
    }
    if(*count>0) *count++;
    return;
}

void rvac_mon(output,count,lcl,indx)
char *output;
int *count,indx;
struct rvac_mon *lcl;
{
    int ind;
    double outvac;

    output=output+strlen(output);

    switch (*count) {
      case 1:
        outvac=(double)lcl->volts;
        outvac = outvac*shm_addr->outscsl[indx] + shm_addr->outscint[indx];
        flt2str(output,outvac,32,1);
        break;
      default:
        *count=-1;
   }
   if(*count > 0) *count++;
   return;
}

void rvacD0mc(data,lcl,indx)
unsigned *data;
struct rvac_cmd *lcl;
int indx;
{
  double fvacuum;

  fvacuum=(lcl->inches*shm_addr->inscsl[indx]) + shm_addr->inscint[indx];
  *data = bits16on(14) & (int)(fvacuum);

  return;

}

void mcD0rvac(lcl, data,indx)
struct rvac_cmd *lcl;
unsigned data;
int indx;
{
  double volts;

  volts= bits16on(14) & data;
  if(fabs(shm_addr->inscsl[indx]) > 1e-12)
    lcl->inches=(volts - shm_addr->inscint[indx])/shm_addr->inscsl[indx];
  else
    lcl->inches=-99;
  lcl->set=TRUE;
  return;
}

void mc57rvac(lcl, data)
struct rvac_mon *lcl;
unsigned data;
{
       lcl->volts =  (data & bits16on(12));

       return;
}
