/* fclib/fc_access.c */
void fc_access__(char *name, char *mode, int *error, int *perror, int nlen, int mlen);
/* fclib/fc_antcn_term.c */
void fc_antcn_term__(int *out);
/* fclib/fc_bbc2freq.c */
int fc_bbc2freq__(int *bits);
/* fclib/fc_brk_chk.c */
int fc_brk_chk__(char name[5], int lenn);
/* fclib/fc_brk_snd.c */
void fc_brk_snd__(char *prog, int lenp);
/* fclib/fc_chmod.c */
void fc_chmod__(char *filename, int *permissions, int *ilen, int *error, int flen);
/* fclib/fc_cls_clr.c */
void fc_cls_clr__(int *iclass);
/* fclib/fc_cls_rcv.c */
int fc_cls_rcv__(int *iclass, char *buffer, int *nchars, int *rtn1, int *rtn2);
/* fclib/fc_cls_snd.c */
void fc_cls_snd__(int *iclass, char *buffer, int *nchars, int *parm3, int *parm4);
/* fclib/fc_cls_sndc.c */
void fc_cls_sndc__(int *iclass, char *buffer, int *nchars, int *parm3, int *parm4, int blen);
/* fclib/fc_cshm_init.c */
void fc_cshm_init__(void);
/* fclib/fc_dad_pid.c */
int fc_dad_pid__(void);
/* fclib/fc_dbbc3n_v.c */
void fc_dbbc3n_d__(char device[2], int *ierr, int ip[5]);
void fc_dbbc3n_v__(double *dtpi, double *dtpi2, int ip[5], int *icont, int *isamples);
void fc_dbbc3n_r__(int ip[5]);
/* fclib/fc_dbbcn_pfb_v.c */
void fc_dbbcn_pfb_d__(char device[2], int *ierr, int ip[5]);
void fc_dbbcn_pfb_v__(double *dtpi, int ip[5]);
void fc_dbbcn_pfb_r__(int ip[5]);
/* fclib/fc_dbbcn_v.c */
void fc_dbbcn_d__(char device[2], int *ierr, int ip[5]);
void fc_dbbcn_v__(double *dtpi, double *dtpi2, int ip[5], int *icont, int *isamples);
void fc_dbbcn_r__(int ip[5]);
/* fclib/fc_dqa4_cnvrt.c */
void fc_dqa4_cnvrt__(char *ibuf, int jfrms[2], int jperr[2], int jsync[2], int *ierr);
/* fclib/fc_dscon_v.c */
void fc_dscon_d__(char device[2], int *ierr, int ip[5]);
void fc_dscon_v__(double *dtpi, int ip[5]);
/* fclib/fc_et_v.c */
void fc_et_v__(int ip[5], int *indxtp);
/* fclib/fc_exit.c */
void fc_exit__(int *status);
/* fclib/fc_get_5btime.c */
int fc_get_5btime__(int centisec[6], int fm_tim[6], int ip[5], int *to, char *m5sync, char *m5pps, char *m5freq, char *m5clock, int sz_m5sync, int sz_m5pps, int sz_m5freq, int sz_m5clock);
/* fclib/fc_get_fila10gtime.c */
int fc_get_fila10gtime__(int centisec[6], int fm_tim[6], int ip[5], int *to);
/* fclib/fc_get_flux_file.c */
void fc_get_flux_file__(int *ierr);
/* fclib/fc_get_k3time.c */
void fc_get_k3time__(int centisec[2], int fm_tim[6], int ip[5]);
/* fclib/fc_get_k4time.c */
void fc_get_k4time__(int centisec[2], int fm_tim[6], int ip[5]);
/* fclib/fc_get_rxgain_files.c */
void fc_get_rxgain_files__(int *ierr);
/* fclib/fc_get_s2time.c */
int fc_get_s2time__(char dev[], int centisec[6], int s2_tim[6], int *nanosec, int ip[5], int *to, int lendev);
/* fclib/fc_get_tcal_fwhm.c */
void fc_get_tcal_fwhm__(char device[2], float *tcal, float *fwhm, float *epoch, float *flux, float *corr, float *ssize, int *ierr);
/* fclib/fc_get_vatod.c */
void fc_get_vatod__(int *ichan, float *volt, int ip[5], int *indxtp);
/* fclib/fc_get_vaux.c */
void fc_set_vrptrk__(int itrk[2], int ip[5], int *indxtp);
void fc_get_verate__(int jperr[2], int jsync[2], int jbits[2], int itrk[2], int *itper, int ip[5]);
void fc_get_vaux__(int iaux[2], int itrk[2], int ip[5]);
/* fclib/fc_get_vtime.c */
int fc_get_vtime__(int centisec[6], int fm_tim[6], int ip[5], int *to);
/* fclib/fc_go_put.c */
void fc_go_put__(char name[5], int lenn);
/* fclib/fc_go_take.c */
int fc_go_take__(char name[5], int *flags, int lenn);
/* fclib/fc_head_vmov.c */
void fc_head_vmov__(int *ihead, int *idir, int *ispdhd, int *jm, int ip[5], int *indxtp);
/* fclib/fc_if_cmd.c */
int fc_if_cmd__(char *ibuf, char *nchar);
/* fclib/fc_incom_ini.c */
void fc_incom_ini__(int *iclbox, int *iclopr);
/* fclib/fc_lbaifpd.c */
void fc_lbaifpd__(int itpis[28]);
/* fclib/fc_loc_map.c */
void fc_loc_map__(int *b_1, int *e_1, int *b_2, int *e_2);
/* fclib/fc_loc_read.c */
void fc_loc_read__(int *b_1);
/* fclib/fc_loc_write.c */
void fc_loc_write__(int *b_1);
/* fclib/fc_lvdofn_v.c */
void fc_lvdofn_v__(int ip[5], int *indxtp);
/* fclib/fc_lvdonn_v.c */
void fc_lvdonn_v__(int *iflag, int ip[5], int *indxtp);
/* fclib/fc_mcbcn_v2.c */
void fc_mcbcn_d2__(char device1[2], char device2[2], int *ierr, int ip[5]);
void fc_mcbcn_v2__(double *dtpi1, double *dtpi2, int ip[5]);
void fc_mcbcn_r2__(int ip[5]);
/* fclib/fc_mcbcn_v.c */
void fc_mcbcn_d__(char device[2], int *ierr, int ip[5]);
void fc_mcbcn_v__(double *dtpi, int ip[5]);
void fc_mcbcn_r__(int ip[5]);
/* fclib/fc_mk4bbcd.c */
void fc_mk4bbcd__(int itpis[14]);
/* fclib/fc_mk4vcd.c */
void fc_mk4vcd__(int itpis[14]);
/* fclib/fc_mk5bbcd.c */
void fc_mk5bbcd__(int itpis[14]);
/* fclib/fc_mk5dbbcd.c */
void fc_mk5dbbcd__(int itpis[14]);
/* fclib/fc_mk5dbbcd_pfb.c */
void fc_mk5dbbcd_pfb__(int itpis[]);
/* fclib/fc_mk5vcd.c */
void fc_mk5vcd__(int itpis[14]);
/* fclib/fc_mvdis_v.c */
void fc_mvdis_v__(int ip[5], char *ibuf, int *nch);
/* fclib/fc_nsem_put.c */
void fc_nsem_put__(char name[5], int lenn);
/* fclib/fc_nsem_take.c */
int fc_nsem_take__(char name[5], int *flags, int lenn);
/* fclib/fc_nsem_test.c */
int fc_nsem_test__(char name[5], int lenn);
/* fclib/fc_ntp_synch.c */
int fc_ntp_synch__(int *errors);
/* fclib/fc_perror.c */
int fc_perror__(char *string);
/* fclib/fc_play_wav.c */
void fc_play_wav__(int *which);
/* fclib/fc_prog_exec.c */
void fc_prog_exec__(char *name, int nlen);
/* fclib/fc_putln2.c */
void fc_putln2__(char *string, int *len);
/* fclib/fc_putln.c */
void fc_putln__(char *string, int len);
/* fclib/fc_putpname.c */
void fc_putpname__(char *name, int nlen);
/* fclib/fc_rdbcn_v.c */
void fc_rdbcn_d__(char device[2], int *ierr, int ip[5]);
void fc_rdbcn_v__(double *dtpi, double *dtpi2, int *ip, int *icont, int *isamples);
/* fclib/fc_readlink.c */
int fc_readlink__(char path[ ], char link[ ], int *ierr, int lenp, int lenl);
/* fclib/fc_rte2secs.c */
void fc_rte2secs__(int it[6], int *seconds);
/* fclib/fc_rte_alarm.c */
int fc_rte_alarm__(int *centisec);
/* fclib/fc_rte_check.c */
void fc_rte_check__(int *iErr);
/* fclib/fc_rte_cmpt.c */
void fc_rte_cmpt__(int *poClock, int *plCentiSec);
/* fclib/fc_rte_fixt.c */
void fc_rte_fixt__(int *poClock, int *plCentiSec);
/* fclib/fc_rte_lock.c */
void fc_rte_lock__(int *ivalue);
/* fclib/fc_rte_prior.c */
int fc_rte_prior__(int *ivalue);
/* fclib/fc_rte_rawt.c */
void fc_rte_rawt__(int *plCentiSec);
/* fclib/fc_rte_sett.c */
int fc_rte_sett__(int *poFmClock, int *piFmHs, int *plCentiSec, char *pcMode, int iLenMode);
/* fclib/fc_rte_sleep.c */
int fc_rte_sleep__(int *centisec);
/* fclib/fc_rte_ticks.c */
void fc_rte_ticks__(int *plTicks);
/* fclib/fc_rte_time.c */
void fc_rte_time__(int it[5], int *it6);
/* fclib/fc_rwff_v.c */
void fc_rwff_v__(int ip[5], int *isub, int *ierr);
/* fclib/fc_secs2rte.c */
void fc_secs2rte__(int *seconds, int it[6]);
/* fclib/fc_set_k3aux.c */
void fc_set_k3aux__(char lauxfm[12], int ip[5]);
/* fclib/fc_setup_ids.c */
void fc_setup_ids__(void);
/* fclib/fc_setup_st.c */
void fc_setup_st__(void);
/* fclib/fc_set_vaux.c */
void fc_set_vaux__(char lauxfm[12], int ip[5]);
/* fclib/fc_shm_map.c */
void fc_shm_map__(int *b_1, int *e_1, int *b_2, int *e_2);
/* fclib/fc_shm_read.c */
void fc_shm_read__(int *b_1);
/* fclib/fc_shm_write.c */
void fc_shm_write__(int *b_1);
/* fclib/fc_skd_arg.c */
void fc_skd_arg__(int *n, char *buff, int len);
/* fclib/fc_skd_clr.c */
void fc_skd_clr__(char name[5], int len);
/* fclib/fc_skd_end_insnp.c */
int fc_skd_end_insnp__(char name[5], int *ip);
/* fclib/fc_skd_par.c */
void fc_skd_par__(int ip[5]);
/* fclib/fc_skd_run.c */
void fc_skd_run__(char name[5], char *wait, int ip[5], int lenn, int lenw);
/* fclib/fc_skd_wait.c */
void fc_skd_wait__(char name[5], int *ip, int *centisec, int len);
/* fclib/fc_system.c */
int fc_system__(char *string);
/* fclib/fc_tpi_dbbc3.c */
void fc_tpi_dbbc3__(int ip[5], int *itpis_dbbc3);
void fc_tpput_dbbc3__(int ip[5], int *itpis_dbbc3, int *isub, char *ibuf, int *nch, int *ilen);
void fc_tsys_dbbc3__(int ip[5], int *itpis_dbbc3, char *ibuf, int *nch, int *itask);
/* fclib/fc_tpi_dbbc.c */
void fc_tpi_dbbc__(int ip[5], int itpis_dbbc[34]);
void fc_tpput_dbbc__(int ip[5], int itpis_dbbc[34], int *isub, char *ibuf, int *nch, int *ilen);
void fc_tsys_dbbc__(int ip[5], int itpis_dbbc[34], char *ibuf, int *nch, int *itask);
/* fclib/fc_tpi_dbbc_pfb.c */
void fc_tpi_dbbc_pfb__(int ip[5], int itpis_dbbc_pfb[]);
void fc_tpput_dbbc_pfb__(int ip[5], int itpis_dbbc_pfb[], int *isub, char *ibuf, int *nch, int *ilen);
void fc_tsys_dbbc_pfb__(int ip[5], int itpis_dbbc_pfb[], char *ibuf, int *nch, int *itask);
/* fclib/fc_tpi_lba.c */
void fc_tpi_lba__(int ip[5], int itpis_lba[34]);
void fc_tpput_lba__(int ip[5], int itpis_lba[34], int *isub, char *ibuf, int *nch, int *ilen);
void fc_tsys_lba__(int ip[5], int itpis_lba[34], char *ibuf, int *nch, int *itask);
/* fclib/fc_tpi_norack.c */
void fc_tpi_norack__(int ip[5], int itpis_norack[2]);
void fc_tpput_norack__(int ip[5], int itpis_norack[2], int *isub, char *ibuf, int *nch, int *ilen);
void fc_tsys_norack__(int ip[5], int itpis_norack[2], char *ibuf, int *nch, int *itask);
/* fclib/fc_tpi_vlba.c */
void fc_tpi_vlba__(int ip[5], int itpis_vlba[34], int *isub);
void fc_tpput_vlba__(int ip[5], int itpis_vlba[34], int *isub, char *ibuf, int *nch, int *ilen);
void fc_tsys_vlba__(int ip[5], int itpis_vlba[34], char *ibuf, int *nch, int *itask);
/* fclib/fc_v2_head_vmov.c */
void fc_v2_head_vmov__(int *ihead, float *volt, int ip[5], int *indxtp);
/* fclib/fc_v2_vlt_head.c */
void fc_v2_vlt_head__(int *ihead, float *volt, int ip[5], int *indxtp);
/* fclib/fc_vlbabbcd.c */
void fc_vlbabbcd__(int itpis[28]);
/* fclib/fc_vset_zero.c */
void fc_vget_att__(char lwho[2], int ip[5], int *ichain1, int *ichain2);
void fc_vset_zero__(char lwho[2], int ip[5]);
void fc_vrst_att__(char lwho[2], int ip[5]);
/* fclib/put_buf_fc.c */
void put_buf_fc__(int *iclass, char *buffer, int *nchars, int *parm3, int *parm4);
