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
/* k4 VC IF buffer parsing utilities */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>

#include "../include/macro.h"
#include "../include/params.h"
#include "../include/fs_types.h"
#include "../include/fscom.h"         /* shared memory definition */
#include "../include/shm_addr.h"      /* shared memory pointer */
#include "../include/clib/clib.h"

static char device[]={"v4"};           /* device menemonics */

#define MAX_BUF 512

int k4vcif_dec(lcl,count,ptr)
struct k4vcif_cmd *lcl;
int *count;
char *ptr;
{
    int ierr;

    ierr=0;
    if(ptr == NULL) ptr="";

    if (*count >0 && *count <5) {
      ierr=arg_int(ptr,&lcl->att[*count-1],0,TRUE);
      if(ierr==0 && (lcl->att[*count-1]<0 || lcl->att[*count-1]>15))
	ierr=-200;
    } else
      *count=-1;

    if(ierr!=0) ierr-=*count;
    if(*count>0) (*count)++;
    return ierr;
}

void k4vcif_enc(output,count,lcl)
char *output;
int *count;
struct k4vcif_cmd *lcl;
{
  int ivalue, type;

  output=output+strlen(output);

  if(*count > 0 && *count < 5 ) {
    sprintf(output,"%02d",lcl->att[*count-1]);
  } else
    *count=-1;
  
  return;
}

void k4vcif_req_q(ip)
int ip[5];
{
 ib_req7(ip,device,13*16+2,"RD");

}
void k4vcif_req_c(ip,lclc)
int ip[5];
struct k4vcif_cmd *lclc;
{
  char buffer[30];

  sprintf(buffer,"AT1-%02d AT2-%02d AT3-%02d AT4-%02d",
	  lclc->att[0],lclc->att[1],lclc->att[2],lclc->att[3]);
  ib_req2(ip,device,buffer);

}

void k4vcif_res_q(lclc,ip)
struct k4vcif_cmd *lclc;
int ip[5];
{
  char buffer[MAX_BUF];
  int max,i;
  int icount;
  char lohi, loup;

  max=sizeof(buffer);
  ib_res_ascii(buffer,&max,ip);
  if(max < 0) {
    ip[2]=-1;
    return;
  }

  if(4!=(icount=sscanf(buffer+8*16,
		       "ATT 1-%2d,2-%2d,3-%2d,4-%2d",
		       lclc->att+0,
		       lclc->att+1,
		       lclc->att+2,
		       lclc->att+3))) {
    ip[2]=-1;
    return;
  }

}


