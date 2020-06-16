#ifndef FS_CLIB_H
#define FS_CLIB_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include "../params.h"
#include "../fs_types.h"
/* clib/antcn_term.c */
int antcn_term(int *out);
/* clib/arg_util.c */
int cmd_parse(char *buf, struct cmd_ds *command);
char *arg_next(struct cmd_ds *command, int *ilast);
int arg_int(char *ptr, int *iptr, int dflt, int flag);
int arg_uns(char *ptr, unsigned *iptr, unsigned dflt, int flag);
int arg_long_long_uns(char *ptr, unsigned long long *iptr, unsigned long long dflt, int flag);
int arg_long_long_uns_scal(char *ptr, unsigned long long *iptr, unsigned long long dflt, int flag, int scal);
int arg_float(char *ptr, float *fptr, double dflt, int flag);
int arg_dble(char *ptr, double *dptr, double dflt, int flag);
int arg_key(char *ptr, char **key, int nkey, int *iptr, int dflt, int flag);
int arg_key_flt(char *ptr, char **key, int nkey, int *iptr, int dflt, int flag);
/* clib/bank_check_util.c */
int rtime_decode(struct rtime_mon *rtime_mon, struct bank_set_mon *bank_set_mon, int ip[5]);
int bank_set_check(int *done, int ip[5]);
int m5_2_rtime(char *ptr_in, struct rtime_mon *lclm, int ip[5]);
int m5_2_bank_set(char *ptr_in, struct bank_set_mon *lclm, int ip[5]);
int m5_2_vsn(char *ptr_in, struct vsn_mon *lclm, int ip[5]);
/* clib/bbc_util.c */
int bbc_dec(struct bbc_cmd *lcl, int *count, char *ptr);
void bbc_enc(char *output, int *count, struct bbc_cmd *lcl);
void bbc_mon(char *output, int *count, struct bbc_mon *lcl);
void bbc00mc(unsigned *data, struct bbc_cmd *lcl);
void bbc01mc(unsigned *data, struct bbc_cmd *lcl);
void bbc02mc(unsigned *data, struct bbc_cmd *lcl);
void bbc03mc(unsigned *data, struct bbc_cmd *lcl);
void bbc05mc(unsigned *data, struct bbc_cmd *lcl);
void mc00bbc(struct bbc_cmd *lcl, unsigned data);
void mc01bbc(struct bbc_cmd *lcl, unsigned data);
void mc02bbc(struct bbc_cmd *lcl, unsigned data);
void mc03bbc(struct bbc_cmd *lcl, unsigned data);
void mc04bbc(struct bbc_mon *lcl, unsigned data);
void mc05bbc(struct bbc_cmd *lcl, unsigned data);
void mc06bbc(struct bbc_mon *lcl, unsigned data);
void mc07bbc(struct bbc_mon *lcl, unsigned data);
/* clib/bblv2db.c */
int bblvcode(double dB);
double bblvdB(int code);
/* clib/bit_density_util.c */
int bit_density_dec(int *lcl, int *count, char *ptr);
void bit_density_enc(char *output, int *count, int *lcl);
/* clib/brk_util.c */
int brk_get(key_t key, int size);
void brk_ini(key_t key);
void brk_att(key_t key);
void brk_snd(char name[5]);
int brk_chk(char name[ 5]);
int brk_rel(void);
/* clib/bs2code.c */
int bs2code(char *bs, char *type);
char *code2bs(int pin, char *type);
int code2det(int pin, char *type);
/* clib/bsfo2code.c */
int bsfo2code(char *bs);
char *code2bsfo(int pin);
/* clib/bsfo2vars.c */
int bsfo2vars(char *bs, int *ifp, int *sb, int *b, int *fo);
char *vars2bsfo(int bw, int ifp, int sb, int b);
/* clib/caccess.c */
void caccess(char *filename, char *mode, int *error, int *perror, int flen, int mlen);
/* clib/calrx_util.c */
int calrx_dec(struct calrx_cmd *lcl, int *count, char *ptr);
void calrx_enc(char *output, int *count, struct calrx_cmd *lcl);
/* clib/capture_util.c */
void capture_mon(char *output, int *count, struct capture_mon *lcl);
void mc48capture(struct capture_mon *lcl, unsigned data);
void mc49capture(struct capture_mon *lcl, unsigned data);
void mc4Acapture(struct capture_mon *lcl, unsigned data);
void mc4Bcapture(struct capture_mon *lcl, unsigned data);
/* clib/cchmod.c */
void cchmod(char *filename, int *permissions, int *ilen, int *error, int flen);
/* clib/clock_set_util.c */
int m5_2_clock_set(char *ptr_in, struct clock_set_cmd *lclc, int ip[5]);
/* clib/cls_util.c */
int cls_get(key_t key, int size);
void cls_ini(key_t key);
void cls_att(key_t key);
void cls_snd(int *class, char *buffer, int length, int parm3, int parm4);
int cls_alc(void);
int cls_rcv(int class, char *buffer, int length, int *rtn1, int *rtn2, int msgflg, int save);
void cls_clr(int class);
int cls_rel(void);
/* clib/cshm_init.c */
void cshm_init(void);
/* clib/data_check_util.c */
void data_check_mon(char *output, int *count, struct data_check_mon *lcl);
int m5_2_data_check(char *ptr_in, struct data_check_mon *lclm, int ip[5]);
/* clib/data_valid_util.c */
int data_valid_dec(struct data_valid_cmd *lcl, int *count, char *ptr, int kS2drive);
void data_valid_enc(char *output, int *count, struct data_valid_cmd *lcl, int kS2drive);
/* clib/daymy.c */
int daymy(int year, int month, int day);
/* clib/dbbc3_bbcnn_util.c */
int dbbc3_bbcnn_dec(struct dbbc3_bbcnn_cmd *lcl, int *count, char *ptr, int itask);
void dbbc3_bbcnn_enc(char *output, int *count, struct dbbc3_bbcnn_cmd *lcl);
void dbbc3_bbcnn_mon(char *output, int *count, struct dbbc3_bbcnn_mon *lcl);
void bbcnn_2_dbbc3(char *buff, int itask, struct dbbc3_bbcnn_cmd *lcl);
int dbbc3_2_bbcnn(struct dbbc3_bbcnn_cmd *lclc, struct dbbc3_bbcnn_mon *lclm, char *buff);
/* clib/dbbc3_cont_cal_util.c */
int dbbc3_cont_cal_dec(struct dbbc3_cont_cal_cmd *lcl, int *count, char *ptr);
void dbbc3_cont_cal_enc(char *output, int *count, struct dbbc3_cont_cal_cmd *lcl);
void cont_cal_2_dbbc3(char *buff, struct dbbc3_cont_cal_cmd *lcl);
int dbbc3_2_cont_cal(struct dbbc3_cont_cal_cmd *lclc, char *buff);
/* clib/dbbc3_if_power.c */
double dbbc3_if_power(unsigned counts, int como);
/* clib/dbbc3_iftpx_util.c */
void dbbc3_iftpx_mon(char *output, int *count, struct dbbc3_iftpx_mon *lcl);
int dbbc3_2_iftpx(struct dbbc3_iftpx_mon *lclm, char *buff);
/* clib/dbbc3_ifx_util.c */
int dbbc3_ifx_dec(struct dbbc3_ifx_cmd *lcl, int *count, char *ptr, int itask);
void dbbc3_ifx_enc(char *output, int *count, struct dbbc3_ifx_cmd *lcl);
void dbbc3_ifx_mon(char *output, int *count, struct dbbc3_ifx_mon *lcl);
void ifx_2_dbbc3(char *buff, int itask, struct dbbc3_ifx_cmd *lcl);
int dbbc3_2_ifx(struct dbbc3_ifx_cmd *lclc, struct dbbc3_ifx_mon *lclm, char *buff);
/* clib/dbbc3n_v.c */
void dbbc3n_d(char device[2], int *ierr, int ip[5]);
void dbbc3n_v(double *dtpi, double *dtpi2, int ip[5], int *icont, int *isamples);
void dbbc3n_r(int ip[5]);
/* clib/dbbc_cont_cal_util.c */
int dbbc_cont_cal_dec(struct dbbc_cont_cal_cmd *lcl, int *count, char *ptr, int polarity_control);
void dbbc_cont_cal_enc(char *output, int *count, struct dbbc_cont_cal_cmd *lcl);
void dbbc_cont_cal_2_dbbc(char *buff, struct dbbc_cont_cal_cmd *lcl);
int dbbc_2_dbbc_cont_cal(struct dbbc_cont_cal_cmd *lclc, char *buff);
/* clib/dbbcform_util.c */
int dbbcform_dec(struct dbbcform_cmd *lcl, int *count, char *ptr);
void dbbcform_enc(char *output, int *count, struct dbbcform_cmd *lcl);
void dbbcform_2_dbbc(char *buff, struct dbbcform_cmd *lcl);
int dbbc_2_dbbcform(struct dbbcform_cmd *lclc, char *buff);
/* clib/dbbcgain_util.c */
int dbbcgain_dec(struct dbbcgain_cmd *lcl, int *count, char *ptr, int itask);
void dbbcgain_enc(char *output, int *count, struct dbbcgain_cmd *lcl);
void dbbcgain_mon(char *output, int *count, struct dbbcgain_mon *lcl);
void dbbcgain_2_dbbc(char *buff, int itask, struct dbbcgain_cmd *lcl);
int dbbc_2_dbbcgain(struct dbbcgain_cmd *lclc, struct dbbcgain_mon *lclm, char *buff);
/* clib/dbbc_if_power.c */
double dbbc_if_power(unsigned counts, int como);
/* clib/dbbcifx_util.c */
int dbbcifx_dec(struct dbbcifx_cmd *lcl, int *count, char *ptr, int itask);
void dbbcifx_enc(char *output, int *count, struct dbbcifx_cmd *lcl);
void dbbcifx_mon(char *output, int *count, struct dbbcifx_mon *lcl);
void dbbcifx_2_dbbc(char *buff, int itask, struct dbbcifx_cmd *lcl);
int dbbc_2_dbbcifx(struct dbbcifx_cmd *lclc, struct dbbcifx_mon *lclm, char *buff);
/* clib/dbbcnn_util.c */
int dbbcnn_dec(struct dbbcnn_cmd *lcl, int *count, char *ptr, int itask);
void dbbcnn_enc(char *output, int *count, struct dbbcnn_cmd *lcl);
void dbbcnn_mon(char *output, int *count, struct dbbcnn_mon *lcl);
void dbbcnn_2_dbbc(char *buff, int itask, struct dbbcnn_cmd *lcl);
int dbbc_2_dbbcnn(struct dbbcnn_cmd *lclc, struct dbbcnn_mon *lclm, char *buff);
/* clib/dbbcn_pfb_v.c */
void dbbcn_pfb_d(char device[4], int *ierr, int ip[5]);
void dbbcn_pfb_v(double *dtpi, int ip[5]);
void dbbcn_pfb_r(int ip[5]);
/* clib/dbbcn_v.c */
void dbbcn_d(char device[2], int *ierr, int ip[5]);
void dbbcn_v(double *dtpi, double *dtpi2, int ip[5], int *icont, int *isamples);
void dbbcn_r(int ip[5]);
/* clib/dbbc_pfbx_util.c */
void dbbc_pfbx_mon(char *output, int *count, struct dbbc_pfbx_mon *lclm);
int dbbc_2_dbbc_pfbx(struct dbbc_pfbx_mon *lclm, char *buff);
/* clib/dbbc_version_check.c */
int dbbc_version_check(char *inbuf, char *output);
/* clib/dbbcvsi_clk_util.c */
int dbbc_2_vsi_clk(struct dbbcvsi_clk_mon *lclm, char *buff);
/* clib/dbbc_vsix_util.c */
int dbbc_vsix_dec(struct dbbc_vsix_cmd *lcl, int *count, char *ptr);
void dbbc_vsix_enc(char *output, int *count, struct dbbc_vsix_cmd *lcl);
void dbbc_vsix_2_dbbc(char *buff, struct dbbc_vsix_cmd *lcl, int itask, int core);
int dbbc_2_dbbc_vsix(struct dbbc_vsix_cmd *lclc, char *buff);
/* clib/disk2file_util.c */
int disk2file_dec(struct disk2file_cmd *lcl, int *count, char *ptr);
void disk2file_enc(char *output, int *count, struct disk2file_cmd *lcl);
void disk2file_mon(char *output, int *count, struct disk2file_mon *lcl);
int disk2file_2_m5_scan_set(char *ptr, struct disk2file_cmd *lcl);
int disk2file_2_m5(char *ptr, struct disk2file_cmd *lcl);
int m5_2_disk2file(char *ptr_in, struct disk2file_cmd *lclc, struct disk2file_mon *lclm, int ip[5]);
int m5_scan_set_2_disk2file(char *ptr_in, struct disk2file_cmd *lclc, struct disk2file_mon *lclm, int ip[5]);
/* clib/disk_pos_util.c */
void disk_pos_mon(char *output, int *count, struct disk_pos_mon *lcl);
int m5_2_disk_pos(char *ptr_in, struct disk_pos_mon *lclm, int ip[5]);
/* clib/disk_record_util.c */
int disk_record_dec(struct disk_record_cmd *lcl, int *count, char *ptr);
void disk_record_enc(char *output, int *count, struct disk_record_cmd *lclc, struct disk_record_mon *lclm);
void disk_record_mon(char *output, int *count, struct disk_record_mon *lcl);
int disk_record_2_m5(char *ptr, struct disk_record_cmd *lcl);
int m5_2_disk_record(char *ptr_in, struct disk_record_cmd *lclc, struct disk_record_mon *lclm, int ip[5]);
/* clib/disk_serial_util.c */
void disk_serial_mon(char *output, int *count, struct disk_serial_mon *lcl);
int m5_2_disk_serial(char *ptr_in, struct disk_serial_mon *lclm, int ip[5]);
/* clib/dist_util.c */
int dist_dec(struct dist_cmd *lcl, int *count, char *ptr);
void dist_enc(char *output, int *count, struct dist_cmd *lcl);
void dist_mon(char *output, int *count, struct dist_mon *lcl);
void dist01mc(unsigned *data, struct dist_cmd *lcl);
void dist02mc(unsigned *data, struct dist_cmd *lcl);
void mc01dist(struct dist_cmd *lcl, unsigned data);
void mc02dist(struct dist_cmd *lcl, unsigned data);
void mc04dist(struct dist_mon *lcl, unsigned data);
void mc06dist(struct dist_mon *lcl, unsigned data);
void mc07dist(struct dist_mon *lcl, unsigned data);
/* clib/dot_util.c */
int m5_2_dot(char *ptr_in, struct dot_mon *lclm, int ip[5]);
/* clib/dqa4_cnvrt.c */
void dqa4_cnvrt(char *ibuf, int jfrms[2], int jperr[2], int jsync[2], int *ierr);
/* clib/dqa_util.c */
int dqa_dec(struct dqa_cmd *lcl, int *count, char *ptr);
void dqa_enc(char *output, int *count, struct dqa_cmd *lcl);
void dqa_mon(char *output, int *count, struct dqa_mon *lcl, int dur, double rate);
void mcCAdqa(struct dqa_mon *lcl, unsigned uarray[32]);
/* clib/dscon_util.c */
void dscon_snd(struct ds_cmd *lcl, int ip[5]);
int dscon_rcv(struct ds_mon *lclm, int ip[5]);
int run_dscon(int ip[5]);
/* clib/dscon_v.c */
void dscon_d(char device[2], int *ierr, int ip[5]);
void dscon_v(double *dtpi, int ip[5]);
/* clib/ds_util.c */
int ds_dec(struct ds_cmd *lcl, int *count, char *ptr);
void ds_mon(char *output, int *count, struct ds_mon *lclm);
/* clib/dtlkup.c */
void dtlkup(struct req_rec *request, char device[2], int *ierr);
/* clib/et_v.c */
void et_v(int ip[5], int indxtp);
/* clib/fila10g_mode_util.c */
int fila10g_mode_dec(struct fila10g_mode_cmd *lcl, int *count, char *ptr);
void fila10g_mode_enc(char *output, int *count, struct fila10g_mode_cmd *lclc);
void fila10g_mode_mon(char *output, int *count, struct fila10g_mode_mon *lclm);
int vsi_bitmask_2_fila10g(char *ptr, struct fila10g_mode_cmd *lclc);
int vsi_samplerate_2_fila10g(char *ptr, struct fila10g_mode_cmd *lclc);
int vdif_frame_2_fila10g(char *ptr, struct fila10g_mode_cmd *lclc);
int fila10g_2_vsi_bitmask(char *ptr, struct fila10g_mode_cmd *lclc);
int fila10g_2_vsi_samplerate(char *ptr, struct fila10g_mode_cmd *lclc, struct fila10g_mode_mon *lclm);
/* clib/find_next_noncomment.c */
int find_next_noncomment(FILE *fp, char buff[], int sbuff);
/* clib/flux_val.c */
float flux_val(char *name, struct flux_ds flux[100], double nu, double epoch, double fwhm, float *corr, float *size);
/* clib/form4_util.c */
int form4_dec(struct form4_cmd *lcl, int *count, char *ptr);
void form4_enc(char *output, int *count, struct form4_cmd *lcl);
void form4_mon(char *output, int *count, struct form4_mon *lcl);
int form4CONma(char *buff, struct form4_cmd *lcl);
void form4RATma(char *buff, struct form4_cmd *lcl);
void form4MUXma(char *buff, struct form4_cmd *lcl);
void form4LIMma(char *buff, struct form4_cmd *lcl);
int form4ASSma(char *buff, struct form4_cmd *lcl, int start, int *start_map);
int form4ENAma(char *buff, struct form4_cmd *lcl, int start);
void form4ROLma(char *buff, struct form4_cmd *lcl);
void form4MODma(char *buff, struct form4_cmd *lcl);
void maLIMform4(struct form4_cmd *lclc, char *buff);
void maSTAform4(struct form4_cmd *lclc, struct form4_mon *lclm, char *buff);
void maSHOform4(struct form4_cmd *lclc, char *buff);
void maSSTform4(struct form4_cmd *lclc, char *buff);
/* clib/fr2bits.c */
int main(void);
int freq2bits(int freq);
int freq2bitsx(int freq);
int bits2freq(unsigned int bits);
/* clib/freq2bbc.c */
int freq2bbc(int freq);
int bbc2freq(unsigned int bits);
/* clib/fserr_cls.c */
void fserr_snd(char *buf, int nchars);
int fserr_rcv(char *buf, int nchars);
/* clib/fsmetc.c */
int fsmetc_(void);
/* clib/get_5btime.c */
int get_5btime(int centisec[6], int fm_tim[6], int ip[5], int to, char *m5sync, int sz_m5sync, char *m5pps, int sz_m5pps, char *m5freq, int sz_m5freq, char *m5clock, int sz_m5clock);
/* clib/get_fila10gtime.c */
int get_fila10gtime(int centisec[6], int fm_tim[6], int ip[5], int to, int iDBBC);
/* clib/get_gain_par.c */
int get_gain_par(int ifchain, double center, float *fwhm, float *dpfu, float *gain, float *tcal);
/* clib/get_k3time.c */
void get_k3time(int centisec[2], int fm_tim[6], int ip[5]);
/* clib/get_k4time.c */
void get_k4time(int centisec[2], int fm_tim[6], int ip[5]);
/* clib/get_RDBEtime.c */
int get_RDBEtime(int centisec[6], int fm_tim[6], int ip[5], int to, int iRDBE, int *vdif_epoch);
/* clib/get_rxgain.c */
int get_rxgain(char file[], struct rxgain_ds *rxgain);
/* clib/get_s2time.c */
int get_s2time(char dev[], int centisec[6], int it[6], int *nanosec, int ip[5], int to);
/* clib/get_tcal_fwhm.c */
void get_tcal_fwhm(char device[4], float *tcal, float *fwhm, double epoch, float *flux, float *corr, float *ssize, int *ierr);
/* clib/get_vatod.c */
void get_vatod(int ichan, float *volts, int ip[5], int indxtp);
/* clib/get_vaux.c */
void set_vrptrk(int itrk[2], int ip[5], int indxtp);
void get_verate(int jperr[2], int jsync[2], int jbits[2], int itrk[2], int itper, int ip[5]);
void get_vaux(int iaux[2], int itrk[2], int ip[5]);
/* clib/get_vtime.c */
int get_vtime(int centisec[6], int fm_tim[6], int ip[5], int to);
/* clib/go_util.c */
int go_get(key_t key, int nsems);
void go_att(key_t key);
int go_take(char name[5], int flags);
void go_put(char name[5]);
int go_test(char name[5]);
int go_rel(key_t key);
/* clib/head_vmov.c */
void head_vmov(int ihead, int idir, int ispdhd, int jm, int ip[5], int indxtp);
/* clib/helpstr.c */
void helpstr_(char *cnam, int *clength, char *runstr, int *rack, int *drive1, int *drive2, int *ierr, int clen, int rlen);
/* clib/holog_util.c */
int holog_dec(struct holog_cmd *lcl, int *count, char *ptr);
void holog_enc(char *output, int *count, struct holog_cmd *lcl);
/* clib/ib_util.c */
int ib_req1(int ip[5], char device[2]);
int ib_req2(int ip[5], char device[2], char ptr[]);
int ib_req3(int ip[5], char device[2]);
int ib_req4(int ip[5], char device[2], char ptr[], int n);
int ib_req5(int ip[5], char device[2], int ilen);
int ib_req6(int ip[5], char device[2], int ilen);
int ib_req7(int ip[5], char device[2], int ilen, char ptr[]);
int ib_req8(int ip[5], char device[2], int ilen, char ptr[]);
int ib_req9(int ip[5], char device[2]);
int ib_req10(int ip[5], char device[2]);
int ib_req11(int ip[5], char device[2], int ilen, char ptr[]);
int ib_req12(int ip[5], char device[2]);
int ib_res_ascii(char *out, int *max, int ip[5]);
int ib_res_bin(char *out, int *max, int ip[5]);
int ib_res_time(int centisec[2], int ip[5]);
/* clib/if_cmd.c */
int if_cmd(char *ibuf, char *nchar);
/* clib/in2net_util.c */
int in2net_dec(struct in2net_cmd *lcl, int *count, char *ptr);
void in2net_enc(char *output, int *count, struct in2net_cmd *lclc, struct in2net_mon *lclm);
void in2net_mon(char *output, int *count, struct in2net_mon *lcl);
int in2net_2_m5(char *ptr, struct in2net_cmd *lcl);
int m5_2_in2net(char *ptr_in, struct in2net_cmd *lclc, struct in2net_mon *lclm, int ip[5]);
/* clib/incom_ini.c */
void incom_ini(int *iclbox, int *iclopr);
/* clib/int2str.c */
void int2str(char *output, int ivalue, int width, int zorb);
/* clib/k3fm_util.c */
int k3fm_dec(struct k3fm_cmd *lcl, int *new_aux, int *count, char *ptr);
void k3fm_enc(char *output, int *count, struct k3fm_cmd *lcl);
void k3fm_mon(char *output, int *count, struct k3fm_mon *lcl);
int k3fm_req_q(int ip[5]);
int k3fm_req_c(int ip[5], struct k3fm_cmd *lclc, int new_aux);
int k3fm_res_q(struct k3fm_cmd *lclc, struct k3fm_mon *lclm, int ip[5]);
/* clib/k4ib_util.c */
int k4ib_dec(struct cmd_ds *command, int ip[5], int *ireq);
/* clib/k4label_util.c */
int k4label_dec(struct k4label_cmd *lcl, int *count, char *ptr);
void k4label_enc(char *output, int *count, struct k4label_cmd *lcl);
/* clib/k4pcalports_util.c */
int k4pcalports_dec(struct k4pcalports_cmd *lcl, int *count, char *ptr);
void k4pcalports_enc(char *output, int *count, struct k4pcalports_cmd *lcl);
void k4pcalports_mon(char *output, int *count, struct k4pcalports_cmd *lclc, struct k4pcalports_mon *lclm);
int k4pcalports_req_q(int ip[5]);
int k4pcalports_req_c(int ip[5], struct k4pcalports_cmd *lclc);
int k4pcalports_res_q(struct k4pcalports_cmd *lclc, struct k4pcalports_mon *lclm, int ip[5]);
/* clib/k4rec_mode_util.c */
int k4rec_mode_dec(struct k4rec_mode_cmd *lclc, int *count, char *ptr);
void k4rec_mode_enc(char *output, int *count, struct k4rec_mode_cmd *lclc);
void k4rec_mode_mon(char *output, int *count, struct k4rec_mode_mon *lclm, struct k4rec_mode_cmd *lclc);
int k4rec_mode_req_q(int ip[5]);
int k4rec_mode_req_c(int ip[5], struct k4rec_mode_cmd *lclc);
int k4rec_mode_res_q(struct k4rec_mode_cmd *lclc, struct k4rec_mode_mon *lclm, int ip[5]);
/* clib/k4recpatch_util.c */
int k4recpatch_dec(struct k4recpatch_cmd *lcl, int *count, char *ptr);
void k4recpatch_enc(char *output, int *count, struct k4recpatch_cmd *lcl);
/* clib/k4rec_util.c */
void k4rec_mon(char *output, int *count, struct k4rec_mon *lcl);
int k4rec_req_q(int ip[5]);
int k4rec_req_eject(int ip[5]);
int k4rec_req_ini(int ip[5]);
int k4rec_req_xsy(int ip[5]);
int k4rec_req_drum_on(int ip[5]);
int k4rec_req_drum_off(int ip[5]);
int k4rec_req_synch_on(int ip[5]);
int k4rec_req_synch_off(int ip[5]);
int k4rec_req_prl(int ip[5], char *ptr);
int k4rec_res_q(struct k4rec_mon *lcl, int ip[5]);
/* clib/k4st_util.c */
int k4st_dec(struct k4st_cmd *lcl, int *count, char *ptr);
void k4st_enc(char *output, int *count, struct k4st_cmd *lcl);
int k4st_req_q(int ip[5]);
int k4st_reqs_q(int ip[5]);
int k4st_req_c(int ip[5], struct k4st_cmd *lclc, int tcoff, int sqn);
int k4st_res_q(struct k4st_cmd *lclc, int ip[5]);
int k4st_ress_q(int ip[5], int *sqn);
/* clib/k4tape_util.c */
int k4tape_dec(int *reset, int *count, char *ptr);
void k4tape_mon(char *output, int *count, struct k4tape_mon *lcl);
int k4tape_req_q(int ip[5]);
int k4tape_req_c(int ip[5], int *reset);
int k4tape_res_q(struct k4tape_mon *lcl, int ip[5]);
/* clib/k4vcbw_util.c */
int k4vcbw_dec(struct k4vcbw_cmd *lcl, int *count, char *ptr, int itask);
void k4vcbw_enc(char *output, int *count, struct k4vcbw_cmd *lcl, int itask);
int k4vcbw_req_q(int ip[5], int itask);
int k4vcbw_req_c(int ip[5], struct k4vcbw_cmd *lclc, int itask);
int k4vcbw_res_q(struct k4vcbw_cmd *lclc, int ip[5], int itask);
/* clib/k4vcif_util.c */
int k4vcif_dec(struct k4vcif_cmd *lcl, int *count, char *ptr);
void k4vcif_enc(char *output, int *count, struct k4vcif_cmd *lcl);
int k4vcif_req_q(int ip[5]);
int k4vcif_req_c(int ip[5], struct k4vcif_cmd *lclc);
int k4vcif_res_q(struct k4vcif_cmd *lclc, int ip[5]);
/* clib/k4vclo_util.c */
int k4vclo_dec(struct k4vclo_cmd *lcl, int *ivc, int *count, char *ptr, int itask);
void k4vclo_enc(char *output, int *count, struct k4vclo_cmd *lcl, int itask);
void k4vclo_mon(char *output, int *count, struct k4vclo_mon *lcl, int itask);
int k4vclo_req_q(int ip[5], int itask);
int k4vclo_req_c(int ip[5], struct k4vclo_cmd *lclc, int ivc, int itask);
int k4vclo_res_q(struct k4vclo_cmd *lclc, struct k4vclo_mon *lclm, int ip[5], int itask);
/* clib/k4vc_util.c */
int k4vc_dec(struct k4vc_cmd *lcl, int *ivc, int *count, char *ptr, int itask);
void k4vc_enc(char *output, int *count, struct k4vc_cmd *lcl, int itask);
void k4vc_mon(char *output, int *count, struct k4vc_mon *lcl, int itask);
int k4vc_req_q(int ip[5], int itask);
int k4vc_req_c(int ip[5], struct k4vc_cmd *lclc, int ivc, int itask);
int k4vc_res_q(struct k4vc_cmd *lclc, struct k4vc_mon *lclm, int ip[5], int itask);
/* clib/lba_cor_util.c */
int lba_cor_dec(struct ifp *lcl, int *count, char *ptr);
void lba_cor_enc(char *output, int *count, struct ifp *lcl);
/* clib/lba_ft_util.c */
int lba_ft_dec(struct ifp *lcl, int *count, char *ptr);
void lba_ft_enc(char *output, int *count, struct ifp *lcl);
/* clib/lbaifpd.c */
void lbaifpd(int itpis[2*2]);
/* clib/lba_ifp_util.c */
int lba_ifp_dec(struct ifp *lcl, int *count, char *ptr);
void lba_ifp_enc(char *output, int *count, struct ifp *lcl);
int lba_tpi_from_level(unsigned short level);
void lba_ifp_mon(char *output, int *count, struct ifp *lcl);
int lba_ifp_setup(struct ifp *lcl, int n_ifp);
int reset_err_flags(int n_ifp);
int wait_for_sync(int n_ifp);
int lba_ifp_write(int n_ifp);
int lba_ifp_read(int n_ifp, int chekr);
/* clib/lba_mon_util.c */
int lba_mon_dec(struct ifp *lcl, int *count, char *ptr);
void lba_mon_enc(char *output, int *count, struct ifp *lcl);
/* clib/lba_trkfrm_util.c */
int lba_trkfrm_dec(struct das *lcl, int *count, char *ptr);
void lba_trkfrm_enc(char *output, int *count, struct das *lcl);
/* clib/log_stdout.c */
int ntp_synch(int errors);
/* clib/lo_util.c */
int lo_dec(struct lo_cmd *lcl, int *count, char *ptr);
void lo_enc(char *output, int *count, struct lo_cmd *lcl);
/* clib/lower.c */
char lower(char *buff);
/* clib/lvdofn_v.c */
void lvdofn_v(int ip[5], int indxtp);
/* clib/lvdonn_v.c */
void lvdonn_v(int okay, int ip[5], int indxtp);
/* clib/m5_utils.c */
char *m5trim(char *ptr);
int m5state_init(struct m5state *state);
int m5string_decode(char *ptr, char *ch, int sizech, struct m5state *state);
int m5sscanf(char *ptr, char *format, void *value, struct m5state *state);
int m5time_decode(char *ptr, struct m5time *time, struct m5state *state);
int m5time_encode(char *ptr, struct m5time *time, struct m5state *state);
int m5sprintf(char *ptr, char *format, void *value, struct m5state *state);
int m5key_encode(char *ptr, char *keys[ ], int nkeys, int value, struct m5state *state);
int m5state_encode(char *ptr, struct m5state *state);
int m5key_decode(char *ptr, int *value, char *keys[ ], int nkeys, struct m5state *state);
/* clib/mcbcn_v2.c */
void mcbcn_d2(char device1[2], char device2[2], int *ierr, int ip[5]);
void mcbcn_v2(double *dtpi1, double *dtpi2, int ip[5]);
void mcbcn_r2(int ip[5]);
/* clib/mcbcn_v.c */
void mcbcn_d(char device[2], int *ierr, int ip[5]);
void mcbcn_v(double *dtpi, int ip[5]);
void mcbcn_r(int ip[5]);
/* clib/mcb_util.c */
int mcb_dec(struct mcb_cmd *lcl, int *count, char *ptr);
void mcb_mon(char *output, int *count, struct mcb_mon *lcl);
/* clib/mk4bbcd.c */
void mk4bbcd(int itpis[2*16]);
/* clib/mk4vcd.c */
void mk4vcd(int itpis[14]);
/* clib/mk5bbcd.c */
void mk5bbcd(int itpis[16*2]);
/* clib/mk5b_mode_util.c */
int mk5b_mode_dec(struct mk5b_mode_cmd *lcl, int *count, char *ptr, int itask);
void mk5b_mode_enc(char *output, int *count, struct mk5b_mode_cmd *lclc, struct mk5b_mode_mon *lclm, int itask);
void mk5b_mode_mon(char *output, int *count, struct mk5b_mode_mon *lclm);
int mk5b_mode_2_m5(char *ptr, struct mk5b_mode_cmd *lclc, int itask);
int m5_2_mk5b_mode(char *ptr_in, struct mk5b_mode_cmd *lclc, struct mk5b_mode_mon *lclm, int itask, int ip[5]);
/* clib/mk5dbbcd.c */
void mk5dbbcd(int itpis[16*2]);
/* clib/mk5dbbcd_pfb.c */
void mk5dbbcd_pfb(int itpis[64]);
/* clib/mk5_status_util.c */
int mk5_status_set_error_rtn(int *ip, int eno, const char *modnm);
void mk5_status_replace_colons(char *ptr);
int mk5_status_mk5cn_exec(int *ip, const char *cmd, char *buf, const size_t bufsz);
int mk5_status_get_status(int *ip, unsigned int *statusword);
int mk5_status_get_error(int *ip, char *buf, const size_t bufsz);
/* clib/mk5vcd.c */
void mk5vcd(int itpis[14]);
/* clib/mk6_disk_pos_util.c */
void mk6_disk_pos_mon(char *output, int *count, struct mk6_disk_pos_mon *lcl);
int m5_2_mk6_disk_pos(char *ptr_in, struct mk6_disk_pos_mon *lclm, int ip[5], char *who);
/* clib/mk6_record_util.c */
int mk6_record_dec(struct mk6_record_cmd *lcl, int *count, char *ptr);
void mk6_record_enc(char *output, int *count, struct mk6_record_cmd *lclc);
void mk6_record_mon(char *output, int *count, struct mk6_record_mon *lclm);
int mk6_record_2_m6(char *ptr, struct mk6_record_cmd *lcl);
int m6_2_mk6_record(char *ptr_in, struct mk6_record_cmd *lclc, struct mk6_record_mon *lclm, int ip[5], char *who);
/* clib/mk6_scan_check_util.c */
void mk6_scan_check_mon(char *output, int *count, struct mk6_scan_check_mon *lcl);
int m5_2_mk6_scan_check(char *ptr_in, struct mk6_scan_check_mon *lclm, int ip[5], char *what);
/* clib/motion_done.c */
int motion_done(int ip[5], int indx);
/* clib/mvdis_v.c */
void mvdis_v(int ip[5], char *ibuf, int *nch);
/* clib/mvupper.c */
void mvupper_(char *ibuf1, int *is1, char *ibuf2, int *is2, int *nc);
/* clib/nsem_util.c */
int nsem_get(key_t key, int nsems);
void nsem_att(key_t key);
int nsem_take(char name[5], int flags);
void nsem_put(char name[5]);
int nsem_test(char name[5]);
int nsem_find(char name[5]);
int nsem_rel(key_t key);
/* clib/ntp_synch.c */
int ntp_synch(int errors);
/* clib/onoff_util.c */
int onoff_dec(struct onoff_cmd *lcl, int *count, char *ptr);
void onoff_enc(char *output, int *count, struct onoff_cmd *lcl);
/* clib/pcald_util.c */
int pcald_dec(struct pcald_cmd *lcl, int *count, char *ptr);
void pcald_enc(char *output, int *count, struct pcald_cmd *lcl);
/* clib/pcalform_util.c */
int pcalform_dec(struct pcalform_cmd *lcl, int *count, char *ptr);
void pcalform_enc(char *output, int *count, struct pcalform_cmd *lcl);
/* clib/pcalports_util.c */
int pcalports_dec(struct pcalports_cmd *lcl, int *count, char *ptr);
void pcalports_enc(char *output, int *count, struct pcalports_cmd *lcl);
void pcalportsPCAma(char *buff, struct pcalports_cmd *lcl);
/* clib/play_wav.c */
int play_wav(int iwhich);
/* clib/pps_source_util.c */
int m5_2_pps_source(char *ptr_in, struct pps_source_cmd *lclc, int ip[5]);
/* clib/prog_exec.c */
void prog_exec(char name[5]);
/* clib/rclcn_req_util.c */
void ini_rclcn_req(struct rclcn_req_buf *buffer);
void add_rclcn_request(struct rclcn_req_buf *buffer, char *device, char *request, int len);
void add_rclcn_request_string(struct rclcn_req_buf *buffer, char *device, char *request, int len, char *string);
void end_rclcn_req(int ip[5], struct rclcn_req_buf *buffer);
void add_rclcn_stop(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_play(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_record(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_rewind(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_ff(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_pause(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_unpause(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_eject(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_state_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_speed_set(struct rclcn_req_buf *buffer, char *device, int speed);
void add_rclcn_speed_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_speed_read_pb(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_error_decode(struct rclcn_req_buf *buffer, char *device, int err_code);
void add_rclcn_time_set(struct rclcn_req_buf *buffer, char *device, int year, int day, int hour, int min, int sec);
void add_rclcn_time_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_time_read_pb(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_mode_set(struct rclcn_req_buf *buffer, char *device, char *mode);
void add_rclcn_mode_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_tapeid_set(struct rclcn_req_buf *buffer, char *device, char *tapeid);
void add_rclcn_tapeid_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_tapeid_read_pb(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_user_info_set(struct rclcn_req_buf *buffer, char *device, int fieldnum, int label, char *user_info);
void add_rclcn_user_info_read(struct rclcn_req_buf *buffer, char *device, int fieldnum, int label);
void add_rclcn_user_info_read_pb(struct rclcn_req_buf *buffer, char *device, int fieldnum, int label);
void add_rclcn_user_dv_set(struct rclcn_req_buf *buffer, char *device, int user_dv, int pb_enable);
void add_rclcn_user_dv_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_user_dv_read_pb(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_group_set(struct rclcn_req_buf *buffer, char *device, int group);
void add_rclcn_group_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_tapeinfo_read_pb(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_delay_set(struct rclcn_req_buf *buffer, char *device, int relative, int nanosec);
void add_rclcn_delay_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_delaym_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_barrelroll_set(struct rclcn_req_buf *buffer, char *device, int barrelroll);
void add_rclcn_barrelroll_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_align(struct rclcn_req_buf *buffer, char *device, int year, int day, int hour, int min, int sec, int nanosec);
void add_rclcn_align_rel(struct rclcn_req_buf *buffer, char *device, int negative, int hour, int min, int sec, int nanosec);
void add_rclcn_align_realign(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_align_selfalign(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_position_set(struct rclcn_req_buf *buffer, char *device, int code, int position);
void add_rclcn_position_set_ind(struct rclcn_req_buf *buffer, char *device, int code, int position[]);
void add_rclcn_position_reestablish(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_position_read(struct rclcn_req_buf *buffer, char *device, int code);
void add_rclcn_errmes(struct rclcn_req_buf *buffer, char *device, int error);
void add_rclcn_esterr_read(struct rclcn_req_buf *buffer, char *device, int order_chantran);
void add_rclcn_pdv_read(struct rclcn_req_buf *buffer, char *device, int order_chantran);
void add_rclcn_scpll_mode_set(struct rclcn_req_buf *buffer, char *device, int scpll_mode);
void add_rclcn_scpll_mode_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_tapetype_set(struct rclcn_req_buf *buffer, char *device, char *tapetype);
void add_rclcn_tapetype_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_mk3_form_set(struct rclcn_req_buf *buffer, char *device, int mk3);
void add_rclcn_mk3_form_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_transport_times(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_station_info_read(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_consolecmd(struct rclcn_req_buf *buffer, char *device, char *command);
void add_rclcn_postime_read(struct rclcn_req_buf *buffer, char *device, int tran);
void add_rclcn_status(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_status_detail(struct rclcn_req_buf *buffer, char *device, int stat_code, int reread, int shortt);
void add_rclcn_status_decode(struct rclcn_req_buf *buffer, char *device, int stat_code, int shortt);
void add_rclcn_diag(struct rclcn_req_buf *buffer, char *device, int type);
void add_rclcn_berdcb(struct rclcn_req_buf *buffer, char *device, int op_type, int chan, int meas_time);
void add_rclcn_ident(struct rclcn_req_buf *buffer, char *device);
void add_rclcn_ping(struct rclcn_req_buf *buffer, char *device, int timeout);
void add_rclcn_version(struct rclcn_req_buf *buffer, char *device);
/* clib/rclcn_res_util.c */
void opn_rclcn_res(struct rclcn_res_buf *buffer, int ip[5]);
int get_rclcn_res(struct rclcn_res_buf *buffer);
int get_rclcn_res_data(struct rclcn_res_buf *buffer, void *ptr, int len);
int get_rclcn_res_string(struct rclcn_res_buf *buffer, char *ptr);
void clr_rclcn_res(struct rclcn_res_buf *buffer);
int get_rclcn_stop(struct rclcn_res_buf *buffer);
int get_rclcn_play(struct rclcn_res_buf *buffer);
int get_rclcn_record(struct rclcn_res_buf *buffer);
int get_rclcn_rewind(struct rclcn_res_buf *buffer);
int get_rclcn_ff(struct rclcn_res_buf *buffer);
int get_rclcn_pause(struct rclcn_res_buf *buffer);
int get_rclcn_unpause(struct rclcn_res_buf *buffer);
int get_rclcn_eject(struct rclcn_res_buf *buffer);
int get_rclcn_state_read(struct rclcn_res_buf *buffer, int *rstate);
int get_rclcn_speed_set(struct rclcn_res_buf *buffer);
int get_rclcn_speed_read(struct rclcn_res_buf *buffer, int *speed);
int get_rclcn_speed_read_pb(struct rclcn_res_buf *buffer, int *speed);
int get_rclcn_error_decode(struct rclcn_res_buf *buffer, char *err_msg);
int get_rclcn_time_set(struct rclcn_res_buf *buffer);
int get_rclcn_time_read(struct rclcn_res_buf *buffer, int *year, int *day, int *hour, int *min, int *sec, int *validated, int *centisec);
int get_rclcn_time_read_pb(struct rclcn_res_buf *buffer, int *year, int *day, int *hour, int *min, int *sec, int *validated);
int get_rclcn_mode_set(struct rclcn_res_buf *buffer);
int get_rclcn_mode_read(struct rclcn_res_buf *buffer, char *mode);
int get_rclcn_tapeid_set(struct rclcn_res_buf *buffer);
int get_rclcn_tapeid_read(struct rclcn_res_buf *buffer, char *tapeid);
int get_rclcn_tapeid_read_pb(struct rclcn_res_buf *buffer, char *tapeid);
int get_rclcn_user_info_set(struct rclcn_res_buf *buffer);
int get_rclcn_user_info_read(struct rclcn_res_buf *buffer, char *user_info);
int get_rclcn_user_info_read_pb(struct rclcn_res_buf *buffer, char *user_info);
int get_rclcn_user_dv_set(struct rclcn_res_buf *buffer);
int get_rclcn_user_dv_read(struct rclcn_res_buf *buffer, int *user_dv, int *pb_enable);
int get_rclcn_user_dv_read_pb(struct rclcn_res_buf *buffer, int *user_dv);
int get_rclcn_group_set(struct rclcn_res_buf *buffer);
int get_rclcn_group_read(struct rclcn_res_buf *buffer, int *group, int *num_groups);
int get_rclcn_tapeinfo_read_pb(struct rclcn_res_buf *buffer, unsigned char *table);
int get_rclcn_delay_set(struct rclcn_res_buf *buffer);
int get_rclcn_delay_read(struct rclcn_res_buf *buffer, int *nanosec);
int get_rclcn_delaym_read(struct rclcn_res_buf *buffer, int *nanosec);
int get_rclcn_barrelroll_set(struct rclcn_res_buf *buffer);
int get_rclcn_barrelroll_read(struct rclcn_res_buf *buffer, int *barrelroll);
int get_rclcn_align(struct rclcn_res_buf *buffer);
int get_rclcn_position_set(struct rclcn_res_buf *buffer);
int get_rclcn_position_read(struct rclcn_res_buf *buffer, int *code, union pos_union *position);
int get_rclcn_errmes(struct rclcn_res_buf *buffer);
int get_rclcn_esterr_read(struct rclcn_res_buf *buffer, int *num_entries, char esterr_list[]);
int get_rclcn_pdv_read(struct rclcn_res_buf *buffer, int *num_entries, char pdv_list[]);
int get_rclcn_scpll_mode_set(struct rclcn_res_buf *buffer);
int get_rclcn_scpll_mode_read(struct rclcn_res_buf *buffer, int *scpll_mode);
int get_rclcn_tapetype_set(struct rclcn_res_buf *buffer);
int get_rclcn_tapetype_read(struct rclcn_res_buf *buffer, char *tapetype);
int get_rclcn_mk3_form_set(struct rclcn_res_buf *buffer);
int get_rclcn_mk3_form_read(struct rclcn_res_buf *buffer, int *mk3);
int get_rclcn_transport_times(struct rclcn_res_buf *buffer, int *num_entries, unsigned short serial[], unsigned int tot_on_time[], unsigned int tot_head_time[], unsigned int head_use_time[], unsigned int in_service_time[]);
int get_rclcn_station_info_read(struct rclcn_res_buf *buffer, int *station, int *serialnum, char *nickname);
int get_rclcn_consolecmd(struct rclcn_res_buf *buffer);
int get_rclcn_postime_read(struct rclcn_res_buf *buffer, int *year, int *day, int *hour, int *min, int *sec, int *frame, int *position);
int get_rclcn_status(struct rclcn_res_buf *buffer, int *summary, int *num_entries, unsigned char *status_list);
int get_rclcn_status_detail(struct rclcn_res_buf *buffer, int *summary, int *num_entries, unsigned char *status_det_list);
int get_rclcn_status_decode(struct rclcn_res_buf *buffer, char *stat_msg);
int get_rclcn_diag(struct rclcn_res_buf *buffer);
int get_rclcn_berdcb(struct rclcn_res_buf *buffer, int *err_bits, int *tot_bits);
int get_rclcn_ident(struct rclcn_res_buf *buffer, char *devtype);
int get_rclcn_ping(struct rclcn_res_buf *buffer);
int get_rclcn_version(struct rclcn_res_buf *buffer, char *version);
/* clib/rcl_util.c */
int rcl_dec(struct cmd_ds *command, struct rclcn_req_buf *buffer, int *icmd);
/* clib/rdbcn_v.c */
void rdbcn_d(char device[4], int *ierr, int ip[5]);
void rdbcn_v(double *dtpi, double *dtpi2, int ip[5], int *icont, int *isamples);
/* clib/rdbe_2_tsysx.c */
int rdbe_2_tsysx(char *buf, int *ifc, int ip[5], int on[], int off[], char *who);
/* clib/rdbe_atten_util.c */
int rdbe_atten_dec(struct rdbe_atten_cmd *lcl, int *count, char *ptr);
void rdbe_atten_enc(char *output, int *count, struct rdbe_atten_cmd *lclc);
void rdbe_atten_mon(char *output, int *count, struct rdbe_atten_mon *lclm);
int rdbe_atten_2_rdbe(char *ptr, struct rdbe_atten_cmd *lcl);
int rdbe_2_rdbe_atten(char *ptr_in, struct rdbe_atten_mon *lclm, int ip[5]);
/* clib/rdbe_dot_util.c */
int rdbe_2_dot(char *ptr_in, struct rdbe_dot_mon *lclm, int ip[5]);
/* clib/rec_mode_util.c */
int rec_mode_dec(struct rec_mode_cmd *lcl, int *count, char *ptr);
void rec_mode_enc(char *output, int *count, struct rec_mode_cmd *lcl);
/* clib/req_util.c */
void ini_req(struct req_buf *buffer);
void add_req(struct req_buf *buffer, struct req_rec *request);
void end_req(int ip[5], struct req_buf *buffer);
/* clib/res_util.c */
void opn_res(struct res_buf *buffer, int ip[5]);
void get_res(struct res_rec *response, struct res_buf *buffer);
void clr_res(struct res_buf *buffer);
/* clib/rollform_util.c */
int rollform_dec(struct form4_cmd *lcl, int *count, char *ptr);
void rollform_enc(char *output, int *count, struct form4_cmd *lcl);
/* clib/rp2code.c */
int rp2code(char *bs);
char *code2rp(int pin);
/* clib/rp2codek41.c */
int rp2codek41(char *bs);
char *code2rpk41(int pin);
/* clib/rp2codek42.c */
int rp2codek42(char *bs);
char *code2rpk42(int pin);
/* clib/rvac_util.c */
int rvac_dec(struct rvac_cmd *lcl, int *count, char *ptr);
void rvac_enc(char *output, int *count, struct rvac_cmd *lcl);
void rvac_mon(char *output, int *count, struct rvac_mon *lcl, int indx);
void rvacD0mc(unsigned *data, struct rvac_cmd *lcl, int indx);
void mcD0rvac(struct rvac_cmd *lcl, unsigned data, int indx);
void mc57rvac(struct rvac_mon *lcl, unsigned data);
/* clib/rwff_v.c */
void rwff_v(int ip[5], int *isub, int *ierr);
/* clib/s2label_util.c */
int s2label_dec(struct s2label_cmd *lcl, int *count, char *ptr);
void s2label_enc(char *output, int *count, struct s2label_cmd *lcl);
/* clib/s2rec_util.c */
int s2rec_dec(int position[8], int *count, char *ptr);
/* clib/s2st_util.c */
int s2st_dec(struct s2st_cmd *lcl, int *count, char *ptr);
void s2st_enc(char *output, int *count, struct s2st_cmd *lcl);
/* clib/s2tape_util.c */
int s2tape_dec(int position[8], int *count, char *ptr);
/* clib/satellite_util.c */
int satellite_dec(struct satellite_cmd *lcl, int *count, char *ptr);
void satellite_enc(char *output, int *count, struct satellite_cmd *lcl);
/* clib/satoff_util.c */
int satoff_dec(struct satoff_cmd *lcl, int *count, char *ptr);
void satoff_enc(char *output, int *count, struct satoff_cmd *lcl);
/* clib/scan_check_util.c */
void scan_check_mon(char *output, int *count, struct scan_check_mon *lcl);
int m5_2_scan_check(char *ptr_in, struct scan_check_mon *lclm, int ip[5]);
/* clib/selectcmd_util.c */
int selectcmd_dec(int *lcl, int *count, char *ptr);
void selectcmd_enc(char *output, int *count, int *lcl);
/* clib/semid_util.c */
int semid_get(key_t key, int nsems, int *semid);
void semid_att(key_t key, int *semid);
void semid_take(int isem, int semid);
int semid_nb(int isem, int semid);
void semid_put(int isem, int semid);
int semid_val(int isem, int semid);
void semid_set(int isem, int val, int semid);
int semid_rel(key_t key, int *semid);
/* clib/sem_util.c */
int sem_get(key_t key, int nsems);
void sem_att(key_t key);
void sem_take(int isem);
int sem_nb(int isem);
void sem_put(int isem);
int sem_val(int isem);
void sem_set(int isem, int val);
int sem_rel(key_t key);
/* clib/set_k3aux.c */
void set_k3aux(char lauxfm[12], int ip[5]);
/* clib/setMK4FMrec.c */
int setMK4FMrec(int val, int ip[5]);
/* clib/setup_ids.c */
void setup_ids(void);
/* clib/set_vaux.c */
void set_vaux(char lauxfm[12], int ip[5]);
/* clib/shm_util.c */
int shm_get(key_t key, int size);
void shm_att(key_t key);
int shm_det(void);
int shm_rel(key_t key);
void shm_map(int *b_1, int *e_1, int *b_2, int *e_2);
void shm_read(int *b_read);
void shm_write(int *b_write);
/* clib/sig_ignore.c */
void sig_ignore(void);
/* clib/skd_util.c */
int skd_get(key_t key, int size);
void skd_ini(key_t key);
void skd_att(key_t key);
void skd_boss_inject_w(int *iclass, char *buffer, int length);
void skd_run(char name[5], int w, int ip[5]);
void skd_run_p(char name[5], int w, int ip[5], int *run_index);
void skd_run_arg(char name[5], int w, int ip[5], char *arg);
int skd_run_to(char name[5], int w, int ip[5], unsigned to);
void skd_par(int ip[5]);
void skd_arg_buff(char *buff, int len);
void skd_arg(int n, char *buff, int len);
int skd_chk(char name[ 5], int ip[5]);
int skd_end_inject_snap(char name[ 5], int ip[5]);
void skd_wait(char name[ 5], int ip[5], unsigned centisec);
void skd_end(int ip[5]);
void skd_clr(char name[ 5]);
int skd_rel(void);
void skd_set_return_name(char *name);
int skd_clr_ret(int ip[5]);
int dad_pid(void);
/* clib/str_util.c */
void uns2str(char *output, unsigned uvalue, int width);
void flt2str(char *output, double fvalue, int width, int deci);
void dble2str(char *output, double fvalue, int width, int deci);
void int2str(char *output, int ivalue, int width, int zorb);
/* clib/systracks_util.c */
int systracks_dec(struct systracks_cmd *lcl, int *count, char *ptr);
void systracks_enc(char *output, int *count, struct systracks_cmd *lcl);
void systracks82mc(unsigned *data, struct systracks_cmd *lcl);
void systracks83mc(unsigned *data, struct systracks_cmd *lcl);
void systracks84mc(unsigned *data, struct systracks_cmd *lcl);
void systracks85mc(unsigned *data, struct systracks_cmd *lcl);
void mc82systracks(struct systracks_cmd *lcl, unsigned data);
void mc83systracks(struct systracks_cmd *lcl, unsigned data);
void mc84systracks(struct systracks_cmd *lcl, unsigned data);
void mc85systracks(struct systracks_cmd *lcl, unsigned data);
/* clib/tape_util.c */
int tape_dec(struct tape_cmd *lcl, int *count, char *ptr, int indx);
void tape_enc(char *output, int *count, struct tape_cmd *lcl);
void tape_mon(char *output, int *count, struct tape_mon *lcl, int indx);
void tapeb6mc(unsigned *data, struct tape_cmd *lcl);
void tapeb8mc(unsigned *data, struct tape_cmd *lcl);
void mcb6tape(struct tape_cmd *lcl, unsigned data);
void mc30tape(struct tape_mon *lcl, unsigned data);
void mc33tape(struct tape_mon *lcl, unsigned data);
void mc57tape(struct tape_mon *lcl, unsigned data);
void mc72tape(struct tape_mon *lcl, unsigned data);
void mc73tape(struct tape_mon *lcl, unsigned data);
void mc74tape(struct tape_mon *lcl, unsigned data);
/* clib/tflt.c */
int main(void);
/* clib/tpicd_util.c */
int tpicd_dec(struct tpicd_cmd *lcl, int *count, char *ptr);
void tpicd_enc(char *output, int *count, struct tpicd_cmd *lcl);
/* clib/tpi_dbbc3.c */
void tpi_dbbc3(int ip[5], int itpis_dbbc3[(2*128 +8)]);
void tpput_dbbc3(int ip[5], int itpis_dbbc3[(2*128 +8)], int isubin, char *ibuf, int *nch, int ilen);
void tsys_dbbc3(int ip[5], int itpis_dbbc3[(2*128 +8)], char *ibuf, int *nch, int itask);
void cont_dbbc3(int itpis_dbbc3[(2*128 +8)], double dbbc3_tpi[2*128], double dbbc3_tpical[2*128], int samples, int isubin, int disp);
/* clib/tpi_dbbc.c */
void tpi_dbbc(int ip[5], int itpis_dbbc[(2*16 +4)]);
void tpput_dbbc(int ip[5], int itpis_dbbc[(2*16 +4)], int isubin, char *ibuf, int *nch, int ilen);
void tsys_dbbc(int ip[5], int itpis_dbbc[(2*16 +4)], char *ibuf, int *nch, int itask);
void cont_dbbc(int itpis_dbbc[(2*16 +4)], double dbbc_tpi[2*16], double dbbc_tpical[2*16], int samples, int isubin, int disp);
/* clib/tpi_dbbc_pfb.c */
void tpi_dbbc_pfb(int ip[5], int itpis_dbbc_pfb[(64 +4)]);
void tpput_dbbc_pfb(int ip[5], int itpis_dbbc_pfb[(64 +4)], int isubin, char *ibuf, int *nch, int ilen);
void tsys_dbbc_pfb(int ip[5], int itpis_dbbc_pfb[(64 +4)], char *ibuf, int *nch, int itask);
/* clib/tpi_lba.c */
void tpi_lba(int ip[5], int itpis_lba[2*2]);
void tpput_lba(int ip[5], int itpis_lba[2*2], int isubin, char *ibuf, int *nch, int ilen);
void tsys_lba(int ip[5], int itpis_lba[2*2], char *ibuf, int *nch, int itask);
/* clib/tpi_norack.c */
void tpi_norack(int ip[5], int itpis_norack[2]);
void tpput_norack(int ip[5], int itpis_norack[2], int isub, char *ibuf, int *nch, int ilen);
void tsys_norack(int ip[5], int itpis_norack[2], char *ibuf, int *nch, int itask);
/* clib/tpi_vlba.c */
void tpi_vlba(int ip[5], int itpis_vlba[(16*2+4)], int isub);
void tpput_vlba(int ip[5], int itpis_vlba[(16*2+4)], int isubin, char *ibuf, int *nch, int ilen);
void tsys_vlba(int ip[5], int itpis_vlba[(16*2+4)], char *ibuf, int *nch, int itask);
/* clib/tracks4_util.c */
int tracks4_dec(struct form4_cmd *lcl, int *count, char *ptr);
void tracks4_enc(char *output, int *count, struct form4_cmd *lcl);
/* clib/tracks_util.c */
int tracks_dec(struct vform_cmd *lcl, int *count, char *ptr);
void tracks_enc(char *output, int *count, struct vform_cmd *lcl);
/* clib/trkfrm4_util.c */
int trkfrm4_dec(struct form4_cmd *lcl, int *count, char *ptr);
void trkfrm4_enc(char *output, int *count, struct form4_cmd *lcl);
/* clib/trkfrm_util.c */
int trkfrm_dec(struct vform_cmd *lcl, int *count, char *ptr);
void trkfrm_enc(char *output, int *count, struct vform_cmd *lcl);
/* clib/user_device_util.c */
int user_device_dec(struct user_device_cmd *lcl, int *count, char *ptr);
void user_device_enc(char *output, int *count, struct user_device_cmd *lcl);
/* clib/user_info_util.c */
int user_info_dec(struct user_info_parse *lcl, int *count, char *ptr);
void user_info_enc(char *output, int *count, struct user_info_cmd *lcl);
/* clib/v2_head_vmov.c */
void v2_head_vmov(int ihead, double volt, int ip[5], int indxtp);
/* clib/v2_motion_done.c */
void set_chekr_v2_motion_done__(void);
int v2_motion_done(int ip[5], int indx);
/* clib/v2_vlt_head.c */
void v2_vlt_head(int ihead, float *volt, int ip[5], int indxtp);
/* clib/vacuum.c */
int vacuum(int *ierr, int indx);
/* clib/venable_util.c */
int venable_dec(struct venable_cmd *lcl, int *count, char *ptr, int indx);
void venable_enc(char *output, int *count, struct venable_cmd *lcl, int indx);
void venable80mc(unsigned *data, struct venable_cmd *lcl);
void venable81mc(unsigned *data, struct venable_cmd *lcl);
void mc80venable(struct venable_cmd *lcl, unsigned data);
void mc81venable(struct venable_cmd *lcl, unsigned data);
/* clib/vform_util.c */
int vform_dec(struct vform_cmd *lcl, int *count, char *ptr);
void vform_enc(char *output, int *count, struct vform_cmd *lcl);
void vform_mon(char *output, int *count, struct vform_mon *lcl);
void vform8Dmc(unsigned *data, struct vform_cmd *lcl);
void vform8Emc(unsigned *data, struct vform_cmd *lcl);
void vform8Fmc(unsigned *data, struct vform_cmd *lcl);
void vform90mc(unsigned *data, struct vform_cmd *lcl);
void vform91mc(unsigned *data, struct vform_cmd *lcl);
void vform92mc(unsigned *data, struct vform_cmd *lcl);
void vform93mc(unsigned *data, struct vform_cmd *lcl);
void vform99mc(unsigned *data, struct vform_cmd *lcl);
void vform9Amc(unsigned *data, struct vform_cmd *lcl);
void vform9Cmc(unsigned *data, struct vform_cmd *lcl);
void vform9Dmc(unsigned *data, struct vform_cmd *lcl);
void vformA6mc(unsigned *data, int hwid, struct vform_cmd *lcl);
void vformA7mc(unsigned *data, double posn);
void vformADmc(unsigned *data, struct vform_cmd *lcl);
void vformD2mc(int itracks[32], struct vform_cmd *lcl);
void mc20vform(struct vform_mon *lclm, unsigned data);
void mc21vform(struct vform_mon *lclm, unsigned data);
void mc22vform(struct vform_mon *lclm, unsigned data);
void mc23vform(struct vform_mon *lclm, unsigned data);
void mc24vform(struct vform_mon *lclm, unsigned data);
void mc60vform(struct vform_mon *lclm, unsigned data);
void mc8Dvform(struct vform_cmd *lclc, unsigned data);
void mc8Evform(struct vform_cmd *lclc, unsigned data);
void mc8Fvform(struct vform_cmd *lclc, unsigned data);
void mc90vform(struct vform_cmd *lclc, unsigned data);
void mc91vform(struct vform_cmd *lclc, unsigned data);
void mc92vform(struct vform_cmd *lclc, unsigned data);
void mc93vform(struct vform_cmd *lclc, unsigned data);
void mc99vform(struct vform_cmd *lclc, unsigned data);
void mc9Avform(struct vform_cmd *lclc, unsigned data);
void mcA6vform(unsigned char *hwid, unsigned data, struct vform_cmd *lcl);
void mcADvform(struct vform_cmd *lclc, unsigned data);
void mcD2vform(struct vform_cmd *lclc, int itracks[ ]);
/* clib/vlbabbcd.c */
void vlbabbcd(int itpis[2*16]);
/* clib/vrepro_util.c */
int vrepro_dec(struct vrepro_cmd *lcl, int *count, char *ptr, int indx);
void vrepro_enc(char *output, int *count, struct vrepro_cmd *lcl);
void vrepro90mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro91mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro92mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro93mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro94mc(unsigned *data, struct vrepro_cmd *lcl, int indx);
void vrepro95mc(unsigned *data, struct vrepro_cmd *lcl, int indx);
void vrepro96mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro97mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro98mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro99mc(unsigned *data, struct vrepro_cmd *lcl);
void vrepro9cmc_vlba2(unsigned *data, struct vrepro_cmd *lcl);
void vreproa8mc(unsigned *data, struct vrepro_cmd *lcl);
void mc90vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc91vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc92vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc93vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc94vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc95vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc96vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc97vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc98vrepro(struct vrepro_cmd *lcl, unsigned data);
void mc99vrepro(struct vrepro_cmd *lcl, unsigned data);
void mca8vrepro(struct vrepro_cmd *lcl, unsigned data);
/* clib/vset_zero.c */
void vget_att(char lwho[2], int ip[5], int ichain1, int ichain2);
void vset_zero(char lwho[2], int ip[5]);
void vrst_att(char lwho[2], int ip[5]);
/* clib/vsi4_util.c */
int vsi4_dec(struct vsi4_cmd *lcl, int *count, char *ptr);
void vsi4_enc(char *output, int *count, struct vsi4_cmd *lcl);
void vsi4_mon(char *output, int *count, struct vsi4_mon *lcl);
void ma2vsi4(struct vsi4_cmd *lclc, struct vsi4_mon *lclm, char *buff);
/* clib/vst_util.c */
int vst_dec(struct vst_cmd *lcl, int *count, char *ptr, int indx);
void vst_enc(char *output, int *count, struct vst_cmd *lcl);
void vstb1mc(unsigned *data, struct vst_cmd *lcl);
void vstb5mc(unsigned *data, struct vst_cmd *lcl);
void mcb5vst(struct vst_cmd *lcl, unsigned data);
void mcb1vst(struct vst_cmd *lcl, unsigned data);
/* clib/v_vlt_head.c */
void v_vlt_head__(int *ihead, float *volt, int ip[5], int *indxtp);
/* clib/wvolt_util.c */
int wvolt_dec(struct wvolt_cmd *lcl, int *count, char *ptr, int indx);
void wvolt_enc(char *output, int *count, struct wvolt_cmd *lcl, int indx);
void wvoltD2mc(unsigned *data, struct wvolt_cmd *lcl);
void wvoltD3mc(unsigned *data, struct wvolt_cmd *lcl);
void mcD2wvolt(struct wvolt_cmd *lcl, unsigned data);
void mcD3wvolt(struct wvolt_cmd *lcl, unsigned data);
#endif
