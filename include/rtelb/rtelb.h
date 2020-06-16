#ifndef RTELB_H
#define RTELB_H
#include <sys/times.h>
#include <time.h>
/* rtelb/rte2secs.c */
void rte2secs(int it[6], int *seconds);
/* rtelb/rte_alarm.c */
unsigned rte_alarm(unsigned centisec);
/* rtelb/rte_check.c */
void rte_check(int *iErr);
/* rtelb/rte_cmpt.c */
void rte_cmpt(int *poClock, int *plCentiSec);
/* rtelb/rte_fixt.c */
void rte_fixt(int *poClock, int *plCentiSec);
/* rtelb/rte_lock.c */
void rte_lock(int ivalue);
/* rtelb/rte_prior.c */
int rte_prior(int ivalue);
/* rtelb/rte_rawt.c */
void rte_rawt(int *lRawTime);
/* rtelb/rte_secs.c */
int rte_secs(int *usec_off, unsigned int *ticks_off, int *error, int *perrno);
/* rtelb/rte_sett.c */
int rte_sett(int oFmClock, int iFmHs, int lCentiSec, char *sMode);
/* rtelb/rte_sleep.c */
unsigned rte_sleep(unsigned centisec);
/* rtelb/rte_ticks.c */
void rte_ticks(int *lRawTicks);
/* rtelb/rte_time.c */
void rte_time(int it[5], int *it6);
/* rtelb/rte_times.c */
clock_t rte_times(struct tms *buf);
/* rtelb/secs2rte.c */
void secs2rte(int *secs, int it[5]);
/* rtelb/secs_time.c */
void secs_times(int it[5], int it6);
#endif
