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
#include <time.h>
#include <errno.h>
#include <string.h>
#include <syslog.h>

#define MAX_BUF 80

void fc_err_report(str1,str2,flag,ierr,len1,len2)
int *flag,*ierr,len1,len2;
char *str1,*str2;
{

  err_report(str1,str2,*flag,*ierr);
  return;
}
err_report(str,file,flag,ierr)
char *str,*file;
int flag,ierr;
{
  time_t t;
  static time_t old=-1;
  FILE *fildes;
  char buff[MAX_BUF];

  if(old==-1)
#if 1
    openlog("tacdclient",LOG_CONS|LOG_PID,LOG_DAEMON);
#else
    openlog("tacdclient",LOG_CONS|LOG_PID|LOG_PERROR,LOG_DAEMON);
#endif

  buff[0]=0;
  if(flag) {
    snprintf(buff+strlen(buff),-1+sizeof(buff)-strlen(buff),"%s: ",str);
    snprintf(buff+strlen(buff),-1+sizeof(buff)-strlen(buff),"%s",strerror(errno));
  } else
    snprintf(buff+strlen(buff),-1+sizeof(buff)-strlen(buff),"%s",str);
  if(file!=NULL)
    snprintf(buff+strlen(buff),-1+sizeof(buff)-strlen(buff),", %s",file);
  if(ierr!=0)
    snprintf(buff+strlen(buff),-1+sizeof(buff)-strlen(buff),", Error =%d",
	     ierr);

  syslog(LOG_DAEMON|LOG_ERR,"%s",buff);

  t=time(NULL);
  if(old==-1||t-old > 3600) {
    old=t;

    fildes=fopen("/tmp/tacdclient.error","w+");

    fprintf(fildes,"%s\n",buff);

    fclose(fildes);

    system("/bin/cat /tmp/tacdclient.error | /usr/bin/mail -s 'tacdclient ERROR' oper");

    return;
  }
}
