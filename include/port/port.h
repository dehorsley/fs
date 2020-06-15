/* port/portbaud.c */
int portbaud_(int *port, int *baud);
/* port/portclose.c */
int portclose_(int *port);
/* port/portdelay.c */
int portdelay(int port, int maxc, int time);
/* port/portflush.c */
int portflush_(int *port);
/* port/portopen.c */
int portopen_(int *port, char *name, int *len, int *baud, int *parity, int *bits, int *stop);
/* port/portoutdrain.c */
int portoutdrain_(int *port);
/* port/portread.c */
int portread_(int *port, unsigned char *buff, int *count, int *maxc, int *termch, int *to);
/* port/portwrite.c */
int portwrite_(int *port, char *buff, int *len);
