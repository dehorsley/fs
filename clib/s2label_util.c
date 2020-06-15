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
/* S2 recorder label buffer parsing utilities */

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

int s2label_dec(lcl,count,ptr)
struct s2label_cmd *lcl;
int *count;
char *ptr;
{
    int ierr, arg_key(), arg_int();
    int len,i;

    ierr=0;
    if(ptr == NULL) ptr="";

    switch (*count) {
    case 1:
      if(strlen(ptr) > RCL_MAXSTRLEN_TAPEID-1)
	ierr=-200;
      else if (strlen(ptr) <= 0)
	ierr=-100;
      else {
	len=strlen(ptr)+1;
	for (i=0; i<len;i++)
	  lcl->tapeid[i]=toupper(ptr[i]);
      }
      break;      
    case 2:
      len=strlen(ptr);
      if(len!=1 && len !=6 && len!=0)
	ierr = -200;
      else {
	len=strlen(ptr)+1;
	for (i=0; i<len;i++)
	  lcl->tapetype[i]=toupper(ptr[i]);
      }
      break;
    case 3:
      if(strlen(ptr) > 33-1)
	ierr=-200;
      else if (strlen(ptr) <= 0)
	strcpy(lcl->format,"csa");
      else
	strcpy(lcl->format,ptr);
      break;
    default:
      *count=-1;
    }
    
    if(ierr!=0) ierr-=*count;
    if(*count>0) (*count)++;
    return ierr;
}

void s2label_enc(output,count,lcl)
char *output;
int *count;
struct s2label_cmd *lcl;
{
  int ivalue;

  output=output+strlen(output);
  
  switch (*count) {
  case 1:
    strcpy(output,lcl->tapeid);
    break;
  case 2:
    strcpy(output,lcl->tapetype);
    break;
  case 3:
    strcpy(output,lcl->format);
    break;
  default:
    *count=-1;
  }
  
  if(*count>0)
    *count++;
  return;
}
