/* s2das/message.c */
void init_message(int *ip, char *title);
void clear_message(int *ip);
void send_message(int *ip);
void reset_message(int *ip, char *title);
void add_message(int *ip, char *text);
/* s2das/rcl_das.c */
/* s2das/s2das_util.c */
int valids2detector(char *name);
void check_s2dev__(char *dev, int *ierr);
void get_s2_tpi__(char *dev, double *tpi, int *ierr);
int str2int(char *string, int *value);
char *agc2str(int code);
int str2agc(char *string, char *code);
char *attn2str(char attn);
int str2attn(char *string, char *attn, char *old);
char *bw2str(char code, char *buffer);
int str2bw(char *string, char *code);
char *ifsrc2str(int code);
int str2ifsrc(char *string, char *code, char *src);
int str2state(char *string, char *state);
int str2bbc(char *string, char *bbc);
int str2tonedet(char *string, char *tone);
int str2lofreq(char *string, unsigned int *lofreq);
char *tpiavg2str(unsigned short avg);
int str2tpiavg(char *string, unsigned short *avg);
int str2src(char *string, char *code);
int str2encode(char *string, char *code);
int str2period(char *string, unsigned short *period);
char *lofreq2str(unsigned int lofreq);
char *lock2str(int code);
char *src2str(int code);
char *encode2str(int code);
void s2err(int err, int *ip, char *code);
void s2_get_attn__(int *ierr);
void s2_max_attn__(int *ierr);
void s2_old_attn__(int *ierr);
void s2_get_tpi__(char *dev, double *tpi, int *ierr);
void s2_get_bbc_source__(int *source, int *bbc_id);
void SetBitState(unsigned int *flag, int index, int state);
int GetBitState(unsigned int flag, int index);
/* s2das/stats.c */
void StatsInit(STATS *Stats, char *Title);
void StatsReset(STATS *Stats);
int StatsAdd(STATS *Stats, double Data);
int StatsSolve(STATS *Stats);
