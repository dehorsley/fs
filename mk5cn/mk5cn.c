/* mk5cn: based on John Ball's tstMark5A of 2002 February 18 */
 
#include <stdio.h> 
#include <fcntl.h>
#include <string.h> /* For strrchr() */ 
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h> /* For socket() and connect() */
#include <sys/socket.h> /* For socket() and connect() */
#include <netinet/in.h> /* For socket() with PF_INET */ 
#include <netdb.h> /* For getservbyname() and gethostbyname() */ 
#include <unistd.h> /* For close() */ 

extern int h_errno; /* From gethostbyname() for herror() */ 
extern void herror(const char * s); /* Needed on HP-UX */ 
    /* Why (!) isn't this in one of these includes on HP-UX? */ 

#include "../include/params.h"
#include "../include/fs_types.h"
#include "../include/fscom.h"

extern struct fscom *shm_addr;

#define CONTROL_FILE "/usr2/control/mk5ad.ctl"
#define BUFSIZE 1024 /* size of the input and output buffers */
/*#define DEBUG
 */
static unsigned char inbuf[BUFSIZE];   /* input message buffer */
static unsigned char outbuf[BUFSIZE];  /* output message buffer */

char me[]="mk5cn" ; /* My name */ 
int iecho;
long fail;

static void nullfcn();
static jmp_buf sig_buf;

int sock; /* Socket */ 
FILE * fsock; /* Socket also as a stream */ 
char host[81]; /* maximum width plus one */
int port;
int is_open=FALSE;
int time_out;
int is_init=FALSE;

int main(int argc, char * argv[])
{

  int i, len, result;
  long ip[5];
  
  putpname("mk5cn");
  setup_ids();    /* attach to the shared memory */
  rte_prior(FS_PRIOR);
  host[0]=0;

  while (TRUE)    {
    skd_wait("mk5cn",ip,(unsigned) 0);
    iecho=shm_addr->KECHO;

#ifdef DEBUG
    fprintf(stderr,"entering mk5cn ip[0]=%d ip[1]=%d ip[2]=%d\n",
	    ip[0],ip[1],ip[2]);
#endif
    switch (ip[0]) {
    case 0:
      /* ** Initialize ** */ 
      fail=TRUE;
      result = doinit();
      ip[4]=fail;
      break;
    case 1:
      if(!is_init) {
	cls_clr(ip[1]);
	ip[0]=ip[1]=0;
	result=-98;
      } else
	result = doproc(ip);
      break;
    case 2:
      if(!is_init) {
	cls_clr(ip[1]);
	ip[0]=ip[1]=0;
	result=-98;
      } else
	result = dorelink(ip);
      break;
    case 3:
      if(!is_init) {
	cls_clr(ip[1]);
	ip[0]=ip[1]=0;
	result=-98;
      } else
	result = doclose(ip);
      break;
    default:
      result = -99;
      break;
    }
    ip[2] = result;
    memcpy(ip+3,"m5",2);
#ifdef DEBUG
    fprintf(stderr,"leaving mk5cn ip[0]=%d ip[1]=%d ip[2]=%d\n",
	    ip[0],ip[1],ip[2]);
#endif
  }
}


/* ********************************************************************* */

int doinit()
{
    FILE *fp;   /* general purpose file pointer */
    char check;
    int error;

    if ( (fp = fopen(CONTROL_FILE,"r")) == NULL) {
#ifdef DEBUG
        printf("cannot open MK5 address file %s\n",CONTROL_FILE);
#endif
        return -1 ;
    }

    check=fgetc(fp);
    while(check == '*' && check != EOF) {
      check=fgetc(fp);
      while(check != '\n' && check != EOF)
	check=fgetc(fp);
      if(check != EOF) 
	check=fgetc(fp);
    }
    if (check == EOF)
      /* ended in comment */      
      return 0;
    else if(ungetc(check, fp)==EOF)
      return -2;
   
    if ( fscanf(fp,"%80s %d %d",host,&port, &time_out)!=3) /* read a line */
      return -3;

#ifdef DEBUG
    printf ("Host %s port %d time_out %d\n",host,port,time_out);
#endif

    fclose (fp);
 
    is_init=TRUE;
    if (0 > (error = open_mk5(host,port))) { /* open mk5 unit */
#ifdef DEBUG
      printf ("Cannot open mk5 host %s port %d error %d\n",host,port,error);
#endif
      fail=FALSE;
      return error;
    }
    return 0;
}

/* ********************************************************************* */
int open_mk5(char *host, int port)
{   
  struct servent * set; /* From getservbyname() */ 
  struct sockaddr_in socaddin; /* For connect() info */ 
  struct hostent * hostinfo; /* From gethostbyname() */ 
  unsigned char * uc; /* To debug print IP address */ 
  int i;
  fd_set wfds;
  struct timeval tv;
  int retval, iret;
  int error,serror;
  long flags;

  /* * Create a socket * */ 
  if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) { /* Errors? */ 

#ifdef DEBUG
    (void) fprintf(stderr, /* Yes */ 
		   "%s ERROR: \007 socket() returned %d ", me, sock); 
    perror("error"); 
#endif

    logit(NULL,errno,"un");
    return -11; /* Error */ } 

#ifdef DEBUG
  (void) fprintf(stderr, "%s DEBUG:  sock is %d \n", me, sock); 
#endif

  socaddin.sin_family = PF_INET; /* To agree with socket() */ 

  /* * Get service number for socket m5drive * */ 
  socaddin.sin_port = htons(port); /* Port m5drive's number */
#ifdef DEBUG
  (void) fprintf(stderr, "%s DEBUG:  m5drive port is %d \n", 
		 me, ntohs(socaddin.sin_port)); 
#endif

  /* * Find IP address of host to connect to * */ 
  if(signal(SIGALRM,nullfcn) == SIG_ERR){
    fprintf( stderr,"mk5cn: setting up signals, gethostbyname()\n");
    exit(-1);
  }
  rte_alarm( time_out);
    
  if (setjmp(sig_buf)) {
    hostinfo=NULL;
    errno = EINTR;
    goto gethostbyname_return;
  }

#ifdef DEBUG
  { int itb[6],ita[6];
  rte_time(itb,itb+5);
#endif

  hostinfo = gethostbyname(host);

  gethostbyname_return:    

#ifdef DEBUG
  rte_time(ita,ita+5);
  printf(" itb[5...0] = %d %d %02d %02d %02d %02d\n",
	 itb[5],itb[4],itb[3],itb[2],itb[1],itb[0]);
  printf(" ita[5...0] = %d %d %02d %02d %02d %02d\n",
	 ita[5],ita[4],ita[3],ita[2],ita[1],ita[0]);
   }
#endif

  rte_alarm((unsigned) 0);
  if(signal(SIGALRM,SIG_DFL) == SIG_ERR){
    fprintf( stderr,"mk5cn: setting default signals, gethostbyname()\n");
    exit(-1);
  }

  if( hostinfo == NULL && errno == EINTR ) {
#ifdef DEBUG
    (void) fprintf(stderr, /* Nope */ 
		   "%s ERROR: \007 gethostbyname() on %s timed-out ",
		   me, host);
#endif
    (void) close(sock); 
    logit(NULL,errno,"un");
    return -25 ; /* Error */ }
  else if (hostinfo == NULL) { /* Get IP, OK? */

#ifdef DEBUG
    (void) fprintf(stderr, /* Nope */ 
		   "%s ERROR: \007 gethostbyname() on %s returned NULL ",
		   me, host);
    herror("error"); /* Error */ 
#endif

    switch (h_errno) { /* Which error? */
    case HOST_NOT_FOUND :
#ifdef DEBUG
      (void) fprintf(stderr, "%s ERROR:  host %s not found \n", me, host);
#endif
      (void) close(sock); 
      return -17;
      break;
    case TRY_AGAIN :
#ifdef DEBUG
      (void) fprintf(stderr,
		     "%s ERROR:  no response, try again later \n", me);
#endif
      (void) close(sock); 
      return -18;
      break;
    case NO_RECOVERY :
#ifdef DEBUG
      (void) fprintf(stderr,
		     "%s ERROR:  unknown error, not recoverable \n", me);
#endif
      (void) close(sock); 
      return -19;
      break;
    case NO_ADDRESS : /* = NO_DATA */
#ifdef DEBUG
      (void) fprintf(stderr, "%s:  No Internet address available \n", me);
#endif
      (void) close(sock); 
      return -20;
    } /* End of switch */ 
    (void) close(sock); 
    logit(NULL,errno,"un");
    return -13 ; /* Error */
  } /* End of if hostinfo NULL */
    
  if (hostinfo->h_addr_list[0] == NULL) { /* First IP address OK? */ 
#ifdef DEBUG
    (void)
      fprintf(stderr, /* Nope */ 
	      "%s ERROR: \007 gethostbyname() on %s returned NULL IP \n", 
	      me, host); 
#endif
    (void) close(sock); 
    return -14 ; /* Error */ } 
    
#ifdef DEBUG
  uc = (unsigned char *) hostinfo->h_addr_list[0]; /* Yes */ 
  (void) fprintf(stderr, /* Yes */ 
		 "%s DEBUG:  IP address of %s is [", me, host); 
  for (i = 0; i < hostinfo->h_length; i++) { 
    if (i > 0) 
      (void) printf("."); 
    (void) printf("%u", uc[i]); } 
  (void) printf("] \n");
#endif
  
  socaddin.sin_addr.s_addr = *((unsigned long *) hostinfo->h_addr_list[0]); 
  /* Use first address */ 
  /* * Connect this socket to Mark5A on host * */ 
#ifdef DEBUG
  (void) fprintf(stderr, "%s DEBUG:  Trying to connect() \n", me); /* Yes */ 
#endif

  /* set-up select() */
  flags=fcntl(sock,F_GETFL);
  flags |= O_NONBLOCK;
  fcntl(sock,F_SETFL,flags);
  FD_ZERO(&wfds);
  FD_SET(sock, &wfds);
  /* Wait up to time_out centiseconds  */
  tv.tv_sec = time_out/100;
  tv.tv_usec = (time_out%100)*10000;

#ifdef DEBUG
  { int itb[6],ita[6];
  printf ("time-out sec %d usec %d\n",tv.tv_sec,tv.tv_usec);
  rte_time(itb,itb+5);
#endif

  iret=connect(sock, (const struct sockaddr *) &socaddin, 
	       sizeof(struct sockaddr_in));
#ifdef DEBUG
  rte_time(ita,ita+5);
  printf(" itb[5...0] = %d %d %02d %02d %02d %02d\n",
	 itb[5],itb[4],itb[3],itb[2],itb[1],itb[0]);
  printf(" ita[5...0] = %d %d %02d %02d %02d %02d\n",
	 ita[5],ita[4],ita[3],ita[2],ita[1],ita[0]);
  }
#endif

#ifdef DEBUG
  printf(" iret %d errno %d EINPROGRESS %d\n",iret,errno,EINPROGRESS);
#endif

  if(iret<0 && errno == EINPROGRESS) {
#ifdef DEBUG
    { int itb[6],ita[6];
    rte_time(itb,itb+5);
#endif
    retval = select(sock+1, NULL, &wfds, NULL, &tv);
    /* Don't rely on the value of tv now! */
#ifdef DEBUG
    rte_time(ita,ita+5);
    printf(" itb[5...0] = %d %d %02d %02d %02d %02d\n",
	   itb[5],itb[4],itb[3],itb[2],itb[1],itb[0]);
    printf(" ita[5...0] = %d %d %02d %02d %02d %02d\n",
	   ita[5],ita[4],ita[3],ita[2],ita[1],ita[0]);
    }
    printf(" retval %d \n",retval);
#endif
    if(retval == -1) {
      close(sock);
      logit(NULL,errno,"un");
      return -24; /* Error */ } 
    else if (!retval) {
      close(sock);
      return -21;
    }
    
#ifdef DEBUG
    printf(" sock %d\n",sock);
#endif
    serror=sizeof(error);
    if(getsockopt(sock, SOL_SOCKET, SO_ERROR,
		  (void *) &error,(socklen_t *) &serror) < 0) {
      close(sock);
      logit(NULL,errno,"un");
      return -22; /* Error */ } 
    if(error!=0) {
      close(sock);
      logit(NULL,errno,"un");
      return -23;
    }
  } else if (iret < 0) { /* Connect, errors? */ 
#ifdef DEBUG
    (void) fprintf(stderr, /* Yes */
		   "%s ERROR: \007 connect() returned ", me);
    perror("error"); 
#endif
    logit(NULL,errno,"un");
    (void) close(sock); 
    return -15; /* Error */ } 

#ifdef DEBUG
  (void) fprintf(stderr, /* Yes */ 
		 "%s DEBUG:  Got a connect() on sock %d \n", me, sock); 
#endif
  
  /* * Open socket also to read as a stream * */ 
  if ((fsock = fdopen(sock, "r")) == NULL) { /* OK? */
#ifdef DEBUG
    (void) fprintf(stderr, /* Nope */
		   "%s ERROR: \007 fdopen() on sock %d returned ", me, sock);
    perror("error");
#endif
    logit(NULL,errno,"un");
    (void) close(sock); /* Error */ 
    return -16; /* Error */ } 
#ifdef DEBUG
  (void) fprintf(stderr, /* Yes */ 
		   "%s DEBUG:  Socket %d open also as a stream \n", me, sock); 
#endif

  /* End of initialization */ 
#ifdef DEBUG
  (void) printf("%s Ready\n", me); 
#endif

  is_open=TRUE;
  return 0;
}
int doproc(ip)
long ip[5];
{

  int rtn1;    /* argument for cls_rcv - unused */
  int rtn2;    /* argument for cls_rcv - unused */
  int msgflg;  /* argument for cls_rcv - unused */
  int save;    /* argument for cls_rcv - unused */
  char secho[3*BUFSIZE];

  long in_class;
  long out_class=0;
  int in_recs;
  int out_recs=0;
  int i, nchars;

  fd_set rfds;
  struct timeval tv;
  int retval;
  int error;

  secho[0]=0;
  in_class=ip[1];
  in_recs=ip[2];

  if(!is_open) {
    if (0 > (error = open_mk5(host,port))) { /* open mk5 unit */
#ifdef DEBUG
      printf ("Cannot open mk5 host %s port %d error %d\n",host,port,error);
#endif
      ip[2]=error;
      goto error;
    }
    rte_sleep(100); /* seem to need a 100 centisecond sleep here, is this
                      a Mark 5 or Linux problem? */
  }

  msgflg = save = 0;
  for (i=0;i<in_recs;i++) {
    if ((nchars = cls_rcv(in_class,inbuf,BUFSIZE,&rtn1,&rtn2,msgflg,save)) <= 0) {
#ifdef DEBUG
      printf ("mk5cn failed to get a request buffer\n");
#endif
      ip[2] = -101;
      goto error;
    }
#ifdef DEBUG
    { int j;
      (void) fprintf(stderr, /* Yes */ 
		     "%s DEBUG:  Got inbuf [] = ", me); 
      for (j=0;j<nchars;j++)
	fprintf(stderr,"%c",inbuf[j]);
      fprintf(stderr,"\n");
    }
#endif
    if(iecho) {
      int in, out;
      strcpy(secho,"[");
      for(in=0,out=strlen(secho);in <nchars;in++) {
	if(inbuf[in]=='\n') {
	  secho[out++]='\\';
	  secho[out++]='n';
	} else
	  secho[out++]=inbuf[in];
      }
      secho[out]=0;
      strcat(secho,"]");
    }
    /* * Send command * */ 
    if (send(sock, inbuf, nchars, 0) < nchars) { /* Send to socket, OK? */ 
#ifdef DEBUG
      (void) fprintf(stderr, /* Nope */ 
		     "%s ERROR: \007 send() on socket returned ",me); 
      perror("error"); 
#endif
      logit(NULL,errno,"un");
      ip[2] = -102; /* Error */
      goto error;
    }
#ifdef DEBUG
    (void) fprintf(stderr, /* Yes */ 
		   "%s DEBUG:  Sent inLine[%s] to socket\n",
		   me, inbuf,sock); 
#endif

      /* check for data to read */

    FD_ZERO(&rfds);
    FD_SET(fileno(fsock), &rfds);
    /* Wait up to time_out centiseconds. */
    tv.tv_sec = time_out/100;
    tv.tv_usec = (time_out%100)*10000;

#ifdef DEBUG
    { int itb[6],ita[6];
    printf ("time-out sec %d usec %d\n",tv.tv_sec,tv.tv_usec);
    rte_time(itb,itb+5);
#endif

    retval = select(fileno(fsock)+1, &rfds, NULL, NULL, &tv);
    /* Don't rely on the value of tv now! */
#ifdef DEBUG
    rte_time(ita,ita+5);
    printf(" itb[5...0] = %d %d %02d %02d %02d %02d\n",
    itb[5],itb[4],itb[3],itb[2],itb[1],itb[0]);
    printf(" ita[5...0] = %d %d %02d %02d %02d %02d\n",
    ita[5],ita[4],ita[3],ita[2],ita[1],ita[0]);
   }
#endif
 
    if(retval == -1) {
      logit(NULL,errno,"un");
      fclose(fsock);
      close(sock);
      is_open=FALSE;
      ip[2]=-105;
      goto error;
    } else if (!retval) {
      fclose(fsock);
      close(sock);
      is_open=FALSE;
      ip[2]=-104;
      goto error;
    }

    /* * Read reply * */ 
    if (fgets(outbuf, sizeof(outbuf), fsock) == NULL) { /* OK? */ 
#ifdef DEBUG
      (void) fprintf(stderr, /* Nope */ 
		       "%s ERROR: \007 fgets() on socket returned ", me); 
      perror("error"); 
#endif
      logit(NULL,errno,"un");
      fclose(fsock);
      close(sock);
      is_open=FALSE;
      ip[2] = -103;
      goto error;
    }
    if(iecho) {
      int in, out;
      strcat(secho,"<");
      for(in=0,out=strlen(secho);outbuf[in]!=0;in++) {
	if(outbuf[in]=='\n') {
	  secho[out++]='\\';
	  secho[out++]='n';
	} else
	  secho[out++]=outbuf[in];
      }
      secho[out]=0;
      strcat(secho,">");
      logit(secho,0,NULL);
    }
#ifdef DEBUG
      /* * Print reply * */ 
      (void) fputs(outbuf, stdout); /* Print to stdout */ 
#endif

    cls_snd(&out_class, outbuf, strlen(outbuf)+1 , 0, 0);
    out_recs++;

  } /* End of for loop  */ 

  ip[0]=out_class;
  ip[1]=out_recs;
  ip[2]=0;
  return 0;

 error:
  if(iecho) {
    logit(secho,0,NULL);
  }
  cls_clr(in_class);
  ip[0]=out_class;
  ip[1]=out_recs;
  return ip[2];
}
int dorelink(ip)
long ip[5];
{

  int error;

  ip[0]=ip[1]=0;

  if(is_open) {
    is_open=FALSE;
    fclose(fsock);
    close(sock);
  }

  if (0 > (error = open_mk5(host,port))) { /* open mk5 unit */
#ifdef DEBUG
    printf ("Cannot open mk5 host %s port %d error %d\n",host,port,error);
#endif
    ip[2]=error;
    return ip[2];
  }

  ip[2]=0;
  return 0;

}
int doclose(ip)
long ip[5];
{

  ip[0]=ip[1]=0;

  if(is_open) {
    is_open=FALSE;
    fclose(fsock);
    close(sock);
  }

  ip[2]=0;
  return 0;

}
static void nullfcn(sig)
int sig;
{

  if(signal(sig,SIG_IGN) == SIG_ERR ) {
    perror("nullfcn: error ignoring signal");
    exit(-1);
  }
  
  longjmp (sig_buf, 1);

  fprintf(stderr,"nullfcn: can't get here\n");

  exit(-1);
}