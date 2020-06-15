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
/* mk6_disk_pos_util.c - utilities for mark 6 disk_pos command */

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/params.h"
#include "../include/fs_types.h"
#include "../include/fscom.h"
#include "../include/shm_addr.h"
#include "../include/clib/clib.h"

void mk6_disk_pos_mon(output,count,lcl)
char *output;
int *count;
struct mk6_disk_pos_mon *lcl;
{
  
  output=output+strlen(output);
  
  switch (*count) {
  case 1:
    m5sprintf(output,"%Ld",&lcl->record.record,&lcl->record.state);
    break;
  case 2:
    m5sprintf(output,"%Ld",&lcl->play.play,&lcl->play.state);
    break;
  case 3:
      m5sprintf(output,"%Ld",&lcl->stop.stop,&lcl->stop.state);
      break;
  default:
    *count=-1;
  }
  
  if(*count > 0) *count++;
  return;
}

m5_2_mk6_disk_pos(ptr_in,lclm,ip,who) /* return values:
				  *  0 == no error
				  *  0 != error
				  */
     char *ptr_in;           /* input buffer to be parsed */

     struct mk6_disk_pos_mon *lclm; /* result structure with serial numbers
				    * blank means empty response
				    * null means no response
				    */
     int ip[5];   /* standard parameter array */
     char *who;
{
  char *new_str, *ptr, *ptr2, *ptr_save;
  int count, ierr;

  ptr=strchr(ptr_in,'?');
  if(ptr == NULL) {
    ierr=-901;
    goto error;
  }

  m5state_init(&lclm->record.state);
  m5state_init(&lclm->play.state);
  m5state_init(&lclm->stop.state);

  ptr=strchr(ptr+1,':');
  if(ptr!=NULL) {
    ptr=new_str=strdup(ptr+1);
    if(ptr==NULL) {
      logit(NULL,errno,"un",who);
      ierr=-902;
      goto error;
    }

    ptr2=strchr(ptr,';'); /* terminate the string at the ; */
    if(ptr2!=NULL)
      *ptr2=0;
    
    count=0;
    ptr_save=ptr;
    ptr=strsep(&ptr_save,":");
    while (ptr!=NULL) {
      switch (++count) {
      case 1:
	if(m5sscanf(ptr,"%Ld",&lclm->record.record, &lclm->record.state)) {
	  ierr=-501;
	  goto error2;
	}
	break;
      case 2:
	if(m5sscanf(ptr,"%Ld",&lclm->play.play, &lclm->play.state)) {
	  ierr=-502;
	  goto error2;
	}
	break;
      case 3:
	if(m5sscanf(ptr,"%Ld",&lclm->stop.stop, &lclm->stop.state)) {
	  ierr=-503;
	  goto error2;
	}
	break;
	
      default:
	goto done;
	break;
      }
      ptr=strsep(&ptr_save,":");
    }
  done:
    free(new_str);
  }

  return 0;

error2:
  free(new_str);
error:
  ip[0]=0;
  ip[1]=0;
  ip[2]=ierr;
  memcpy(ip+3,"3p",2);
  memcpy(ip+4,who,2);
  return -1;
}
