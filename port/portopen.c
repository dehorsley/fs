#include <memory.h>
#include <stdio.h>
#include <fcntl.h>
#include <termio.h>

int portopen_(port, name, len, baud, parity, bits, stop)
int *port;
char *name;   /* hollerith */
int *len;
long *baud;
int *parity;
int *bits;
int *stop;
{
  struct termio term;
  char device[65];
  char *end;

  if (*len < 0 || *len > 64)
    return -1;

  end = memccpy(device, name, ' ', *len);
  if (end != NULL)
    *(end-1) = '\0';
  else
    *(device + *len) = '\0';
 
  if ((*port = open(device, O_RDWR) )<0)
    return -2;

  if (ioctl(*port, TCGETA, &term) == -1) {
    return -3;
  }

/* ?
  term.c_iflag &= ~(INLCR | ICRNL | IUCLC | IXON | BRKINT);
  term.c_iflag |= ISTRIP;
*/

  term.c_iflag |= IGNBRK;
  term.c_iflag &= ~(BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP | INLCR |
                    IGNCR | ICRNL | IUCLC | IXON | IXANY | IXOFF);

  term.c_oflag &= ~OPOST;

  term.c_lflag &= ~(ICANON | ISIG | ECHO);

  term.c_cc[VEOF] = 1;
  term.c_cc[VEOL] = 1;

  switch (*stop) {
     case 1:
       term.c_cflag &= ~CSTOPB;
       break;
     case 2:
       term.c_cflag |= CSTOPB;
       break;
     default:
        return -4;
        break;
   }

  term.c_cflag &= ~CSIZE;
  switch (*bits) {
     case 5:
       term.c_cflag |= CS5;
       break;
     case 6:
       term.c_cflag |= CS6;
       break;
     case 7:
       term.c_cflag |= CS7;
       break;
     case 8:
       term.c_cflag |= CS8;
       break;
     default:
       return -5;
       break;
  };

  switch (*parity) {
      case 0:
        term.c_cflag &= ~PARENB;
        break;
      case 1:
        term.c_cflag |= PARENB;
        term.c_cflag |= PARODD;
        break;
      case 2:
        term.c_cflag |= PARENB;
        term.c_cflag &= ~PARODD;
        break;
      default:
        return -6;
        break;
  }

  term.c_cflag &= ~CBAUD;
  if( *baud==38400 )
    term.c_cflag |= B38400;
  else if (*baud > 32767)
    return -7;
  switch ((int)*baud){
    case 110:
      term.c_cflag |= B110;
      break;
    case 134:
      term.c_cflag |= B134;
      break;
    case 150:
      term.c_cflag |= B150;
      break;
    case 200:
      term.c_cflag |= B200;
      break;
    case 300:
      term.c_cflag |= B300;
      break;
    case 600:
      term.c_cflag |= B600;
      break;
    case 1200:
      term.c_cflag |= B1200;
      break;
    case 2400:
      term.c_cflag |= B2400;
      break;
    case 4800:
      term.c_cflag |= B4800;
      break;
    case 9600:
      term.c_cflag |= B9600;
      break;
    case 19200:
      term.c_cflag |= B19200;
      break;
    default:
      return -7;
  };
  if(ioctl (*port, TCSETA, &term)==-1)
    return -8;

  return 0;
}
