/* onoff buffer parsing utilities */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>

#include "../include/dpi.h"
#include "../include/macro.h"
#include "../include/params.h"
#include "../include/fs_types.h"
#include "../include/fscom.h"         /* shared memory definition */
#include "../include/shm_addr.h"      /* shared memory pointer */

static char chanm[] = "0123";
static char chanv[] = "0abcd";
static char hex[]= "0123456789abcdef";
static char det[] = "dlu34567";
static char *lwhat[ ]={
"1l","2l","3l","4l","5l","6l","7l","8l","9l","al","bl","cl","dl","el",
"1u","2u","3u","4u","5u","6u","7u","8u","9u","au","bu","cu","du","eu",
"ia","ib","ic","id"};

static char *lmark[ ]={
  "v1","v2","v3","v4","v5","v6","v7","v8","v9","va","vb","vc","vd","ve",
  "i1","i2","i3"};

static char *lmarka[ ]={
  "v1","v2","v3","v4","v5","v6","v7","v8","v9","v10","v11","v12","v13","v14",
  "i1","i2","i3"};

static char *lmarkb[ ]={
  "vc1","vc2","vc3","vc4","vc5","vc6","vc7","vc8","vc9","vca","vcb","vcc",
  "vcd","vce","if1","if2","if3"};

static char *lmarkc[ ]={
  "vc1","vc2","vc3","vc4","vc5","vc6","vc7","vc8","vc9","vc10","vc11","vc12",
  "vc13","vc14","if1","if2","if3"};

int onoff_dec(lcl,count,ptr)
struct onoff_cmd *lcl;
int *count;
char *ptr;
{
    int ierr, arg_key(), arg_int();
    int i, j, k;
    double freq;
    static int iconv, isb;
    static int itpis_save[MAX_DET];

    ierr=0;
    if(ptr==NULL) {
      if(*count>5) {
	*count=-1;
      /*
      for(i=0;i<MAX_DET;i++)
	if(lcl->itpis[i]!=0)
	  printf("i %d lcl->itpis[i] %d lcl->ifc[i] %d lcl->lwhat[i] %2.2s\n",
		 i,lcl->itpis[i],lcl->ifc[i],lcl->lwhat[i]);
      */

	return 0;
      } else
	ptr="";
    }
    switch (*count) {
    case 1:
      for(i=0;i<MAX_DET;i++) {
	itpis_save[i]=lcl->itpis[i];
	lcl->itpis[i]=0;
      }
      lcl->setup=FALSE;
      ierr=arg_int(ptr,&lcl->rep,2,TRUE);
      if(ierr==0 && (lcl->rep < 0 || lcl->rep > 100))
	ierr=-200;
      break;
    case 2:
      ierr=arg_int(ptr,&lcl->intp,1,TRUE);
      if(ierr==0 && (lcl->intp < 0 || lcl->intp > 100))
	ierr=-200;
      break;
    case 3:
      ierr=arg_float(ptr,&lcl->cutoff,75.0,TRUE);
      if(ierr==0 && (lcl->cutoff < 0.0 || lcl->cutoff > 90.0))
	ierr=-200;
      break;
    case 4:
      ierr=arg_float(ptr,&lcl->step,3.0,TRUE);
      if(ierr==0 && (lcl->step < 0.0 || lcl->step > 90.0))
	ierr=-200;
      break;
    case 5:
      ierr=arg_int(ptr,&lcl->wait,120,TRUE);
      if(ierr==0 && (lcl->wait < 0 || lcl->wait > 1200))
	ierr=-200;
      break;
    default:
      if(*ptr==0) {
	  ierr=-106;
	  return ierr;
      }
      if(strcmp(ptr,"*")==0) {
	for (i=0;i<14;i++)
	  lcl->itpis[i]=itpis_save[i];
      } else if(shm_addr->equip.rack==MK3||shm_addr->equip.rack==MK4) {
	if(strcmp(ptr,"allvc")==0) {
	  for (i=0;i<14;i++)
	    lcl->itpis[i]=1;
	  goto done;
	} else if(strcmp(ptr,"all")==0) {
	  for (i=0;i<17;i++)
	    lcl->itpis[i]=1;
	  goto done;
	} else { 
	  for(i=0;i<sizeof(lmark)/sizeof(char *);i++) {
	    if(strcmp(ptr,lmark[i])==0||strcmp(ptr,lmarka[i])==0
	       ||strcmp(ptr,lmarkb[i])==0||strcmp(ptr,lmarkc[i])==0) {
	      lcl->itpis[i]=1;
	      strncpy(lcl->devices[i].lwhat,lmark[i],2);
	      goto done;
	    }
	  }
	  ierr=-206;
	  return ierr;
	}
      } else if(shm_addr->equip.rack==VLBA||shm_addr->equip.rack==VLBA4) {
	if(strcmp(ptr,"allbbc")==0) {
	  for (i=0;i<MAX_BBC*2;i++) {
	    lcl->itpis[i]=1;
	    strncpy(lcl->devices[i].lwhat,lwhat[i],2);
	  }
	  goto done;
	} else if(strcmp(ptr,"all")==0) {
	  for (i=0;i<MAX_DET;i++) {
	    lcl->itpis[i]=1;
	    strncpy(lcl->devices[i].lwhat,lwhat[i],2);
	  }
	  goto done;
	} else if(strcmp(ptr,"allu")==0) {
	  for (i=MAX_BBC;i<MAX_BBC*2;i++) {
	    lcl->itpis[i]=1;
	    strncpy(lcl->devices[i].lwhat,lwhat[i],2);
	  }
	  goto done;
	} else if(strcmp(ptr,"alll")==0) {
	  for (i=0;i<MAX_BBC;i++) {
	    lcl->itpis[i]=1;
	    strncpy(lcl->devices[i].lwhat,lwhat[i],2);
	  }
	  goto done;
	} else if(strcmp(ptr,"alli")==0) {
	  for (i=2*MAX_BBC;i<MAX_DET;i++) {
	    lcl->itpis[i]=1;
	    strncpy(lcl->devices[i].lwhat,lwhat[i],2);
	  }
	  goto done;
	} else { 
	  for(i=0;i<sizeof(lwhat)/sizeof(char *);i++) {
	    if(strcmp(ptr,lwhat[i])==0) {
	      lcl->itpis[i]=1;
	      strncpy(lcl->devices[i].lwhat,lwhat[i],2);
	      goto done;
	    }
	  }
	}
	ierr=-206;
	return ierr;
      }

    }
    done:
    if(ierr!=0) ierr-=*count;
    if(*count>0) (*count)++;
    return ierr;
}

void onoff_enc(output,count,lcl)
char *output;
int *count;
struct onoff_cmd *lcl;
{
  int ivalue,i,j,k,lenstart,limit;
  static int inext;

  output=output+strlen(output);

  if(*count == 1) {
    sprintf(output+strlen(output),"%d",lcl->rep);
    strcat(output,",");
    sprintf(output+strlen(output),"%d",lcl->intp);
    strcat(output,",");
    sprintf(output+strlen(output),"%.1f",lcl->cutoff);
    strcat(output,",");
    sprintf(output+strlen(output),"%.1f",lcl->step);
    strcat(output,",");
    sprintf(output+strlen(output),"%d",lcl->wait);
    strcat(output,",");
    if(lcl->setup) {
      sprintf(output+strlen(output),"%.4f",lcl->ssize*RAD2DEG);
      strcat(output,",");
      sprintf(output+strlen(output),"%.4f",lcl->fwhm*RAD2DEG);
    }
    inext=0;
  }
  
  if(*count >= 2) {
    for(i=inext;i<MAX_DET;i++) {
      inext=i+1;
      if(lcl->itpis[i]!=0) {
	if(lcl->setup) { 
	  sprintf(output+strlen(output),
		  "%2.2s,%d,%c,%.4f,%.2f,%.2lf,%.3f,%.3f,%.6f,%.4f,%.6f",
		  lcl->devices[i].lwhat,lcl->devices[i].ifchain,
		  lcl->devices[i].pol,
		  lcl->devices[i].fwhm*RAD2DEG,
		  lcl->devices[i].center,lcl->devices[i].tcal,
		  lcl->devices[i].flux,lcl->devices[i].corr,
		  lcl->devices[i].dpfu,lcl->devices[i].gain,
		  lcl->devices[i].dpfu*lcl->devices[i].gain);
	} else {
	  sprintf(output+strlen(output),"%2.2s,,,,,,,,,,",
		  lcl->devices[i].lwhat);
	}
	return;
      }
    }
    *count=-1;
  }

  return;
}