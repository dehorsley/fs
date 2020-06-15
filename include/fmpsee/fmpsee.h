/* fmpsee/fmpappend.c */
int fmpappend_(FILE **dcb, int *error);
/* fmpsee/fmpclose.c */
void fmpclose_(FILE **dcb, int *error);
/* fmpsee/fmperror_standalone_set.c */
void fmperror_standalone_set__(int *value);
/* fmpsee/fmpopen.c */
void fmpopen_(FILE **dcb, char *filename, int *error, char *options, int *dcbb, int len, int leno);
/* fmpsee/fmpposition.c */
int fmpposition_(FILE **dcb, int *error, int *record, int *position);
/* fmpsee/fmppost.c */
int fmppost_(FILE **dcb, int *error);
/* fmpsee/fmppurge.c */
int fmppurge_(char filename[], int *len);
/* fmpsee/fmpread.c */
int fmpread_(FILE **dcb, int *error, char *buf, int *len);
/* fmpsee/fmpreadstr.c */
int fmpreadstr_(FILE **dcb, int *error, char *cbuf, int len);
/* fmpsee/fmprewind.c */
void fmprewind_(FILE **dcb, int *error);
/* fmpsee/fmpsetline.c */
int fmpsetline_(FILE **dcb, int *error, int *position);
int readstr(FILE **dcb);
/* fmpsee/fmpsetpos.c */
int fmpsetpos_(FILE **dcb, int *error, int *record, int *position);
/* fmpsee/fmpwritestr.c */
int fmpwritestr_(FILE **dcb, int *error, char *cbuf, int len);
