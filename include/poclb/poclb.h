#ifndef FS_POCLB_H
#define FS_POCLB_H

#include "../../poclb/novas.h"
#include "../pmodel.h"
#include "../params.h"
#include "../fs_types.h"

/* poclb/cnvrt.c */
void cnvrt(int mode, double ain1, double ain2, double *out1, double *out2, int it[6], double alat, double wlong);
void cnvrt2(int mode, double ain1, double ain2, double *out1, double *out2, int it[6], double dut, double alat, double wlong);
/* poclb/echoe.c */
void echoe(char *inbuf, char *iebuf, int inchar, int *outchar, int maxout);
/* poclb/equn2.c */
void equn2(int it[6], double *eqeq);
/* poclb/equn.c */
void equn(int nyrf, int nday, double *eqofeq);
/* poclb/fln.c */
double fln(int iwhich, double x, double y, struct pmdl *pmodel);
/* poclb/flt.c */
double flt(int iwhich, double x, double y, struct pmdl *pmodel);
/* poclb/gmodl.c */
int gmodl(char *model_file, struct pmdl *pmodel);
/* poclb/iadt.c */
void iadt(int it[6], int idt, int ires);
/* poclb/limit.c */
void limit(double *a1, double *a2);
/* poclb/logita.c */
int logita(char *msg, int ierr, char *who, char *what);
/* poclb/logit.c */
int logits(char *msg, int ierr, char *who, int lsor);
int logit(char *msg, int ierr, char *who);
int logit_nd(char *msg, int ierr, char *who);
/* poclb/logite.c */
int logite(char *msg, int ierr, char *who);
/* poclb/logitf.c */
int logitf(char *msg);
/* poclb/logitn.c */
int logitn(char *msg, int ierr, char *who, int what);
/* poclb/novas.c */
short int app_star(double tjd, short int earth, fk5_entry *star, double *ra, double *dec);
short int topo_star(double tjd, short int earth, double deltat, fk5_entry *star, site_info *location, double *ra, double *dec);
short int app_planet(double tjd, short int planet, short int earth, double *ra, double *dec, double *dis);
short int topo_planet(double tjd, short int planet, short int earth, double deltat, site_info *location, double *ra, double *dec, double *dis);
short int virtual_star(double tjd, short int earth, fk5_entry *star, double *ra, double *dec);
short int local_star(double tjd, short int earth, double deltat, fk5_entry *star, site_info *location, double *ra, double *dec);
short int virtual_planet(double tjd, short int planet, short int earth, double *ra, double *dec, double *dis);
short int local_planet(double tjd, short int planet, short int earth, double deltat, site_info *location, double *ra, double *dec, double *dis);
short int astro_star(double tjd, short int earth, fk5_entry *star, double *ra, double *dec);
short int astro_planet(double tjd, short int planet, short int earth, double *ra, double *dec, double *dis);
short int mean_star(double tjd, short int earth, double ra, double dec, double *mra, double *mdec);
short int get_earth(double tjd, short int earth, double *tdb, double *bary_earthp, double *bary_earthv, double *helio_earthp, double *helio_earthv);
void sidereal_time(double julianhi, double julianlo, double ee, double *gst);
void pnsw(double tjd, double gast, double x, double y, double *vece, double *vecs);
void spin(double st, double *pos1, double *pos2);
void wobble(double x, double y, double *pos1, double *pos2);
void proper_motion(double tjd1, double *pos, double *vel, double tjd2, double *pos2);
void geocentric(double *pos, double *earthvector, double *pos2, double *lighttime);
short int aberration(double *pos, double *ve, double lighttime, double *pos2);
short int precession(double tjd1, double *pos, double tjd2, double *pos2);
short int vector2radec(double *pos, double *ra, double *dec);
void angle2vector(double ra, double dec, double dist, double *vector);
void starvectors(fk5_entry *star, double *pos, double *vel);
short int calcnutation(double tdbtime, double *longnutation, double *obliqnutation);
short int nutate(double tjd, short int fn, double *pos, double *pos2);
void convert_tdb2tdt(double tdb, double *tdtjd, double *secdiff);
short int sun_field(double *pos, double *earthvector, double *pos2);
void terra(site_info *locale, double st, double *pos, double *vel);
void earthtilt(double tjd, double *mobl, double *tobl, double *eq, double *dpsi, double *deps);
/* poclb/novascon.c */
/* poclb/pmdlq.c */
void pmdlq(struct pmdl *pmodel);
/* poclb/pname.c */
void putpname(char *name);
void pname(char *name);
/* poclb/refrw.c */
double refrw(double delin, double tempc, double humi, double pres);
/* poclb/refrwn.c */
double refrwn(double delin, double tempc, double humi, double pres);
/* poclb/sider2.c */
void sider2(int it[6], double dut, double *sidto);
/* poclb/sider.c */
void sider(int it[6], int iyear, double *sidto);
int julda(int iday, int iyear);
void sidtm(int jd, double *sider, double *fract);
/* poclb/solsys3.c */
short int solarsystem(double tjd, short int body, short int origin, double *pos, double *vel);
void sun(double jd, double *ra, double *dec, double *dis);
#endif
