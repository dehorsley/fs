/* newlb/append_safe.c */
int append_safe(char *dest, char *src, size_t n);
/* newlb/ftn_purge.c */
int ftn_purge__(char *name, int *ierr, int len);
void ftn_rename__(char *old, int *erro, char *new, int *errn, int leno, int lenn);
int ftn_runprog__(char *in, int *ierr, int len);
int ftn_upd_time__(char *path, int *time, int *ierr, int len);
int ftn_rw_perm__(char *path, int *perm, int *ierr, int len);
int ftn_r_perm__(char *path, int *perm, int *ierr, int len);
/* newlb/ftn_upd_time.c */
int ftn_upd_time___(char *path, int *time, int *ierr, int len);
/* newlb/log_uname.c */
void log_uname__(void);
/* newlb/prog.c */
void fs_set_ibmat__(int *ibmat);
void fs_get_ibmat__(int *ibmat);
void fs_set_ibmcb__(int *ibmcb);
void fs_get_ibmcb__(int *ibmcb);
void fs_set_wrvolt__(float *wrvolt, int *i);
void fs_get_wrvolt__(float *wrvolt, int *i);
void fs_set_itpthick__(int *itpthick, int *i);
void fs_get_itpthick__(int *itpthick, int *i);
void fs_set_capstan__(int *capstan, int *i);
void fs_get_capstan__(int *capstan, int *i);
void fs_set_outscsl__(float *outscsl, int *i);
void fs_get_outscsl__(float *outscsl, int *i);
void fs_set_inscsl__(float *inscsl, int *i);
void fs_get_inscsl__(float *inscsl, int *i);
void fs_set_outscint__(float *outscint, int *i);
void fs_get_outscint__(float *outscint, int *i);
void fs_set_inscint__(float *inscint, int *i);
void fs_get_inscint__(float *inscint, int *i);
void fs_set_motorv__(float *motorv, int *i);
void fs_get_motorv__(float *motorv, int *i);
void fs_set_tempwx__(float *tempwx);
void fs_get_tempwx__(float *tempwx);
void fs_set_humiwx__(float *humiwx);
void fs_get_humiwx__(float *humiwx);
void fs_set_preswx__(float *preswx);
void fs_get_preswx__(float *preswx);
void fs_set_speedwx__(float *speedwx);
void fs_get_speedwx__(float *speedwx);
void fs_set_directionwx__(int *directionwx);
void fs_get_directionwx__(int *directionwx);
void fs_set_ep1950__(float *ep1950);
void fs_get_ep1950__(float *ep1950);
void fs_set_epoch__(float *epoch);
void fs_get_epoch__(float *epoch);
void fs_set_iclopr__(int *iclopr);
void fs_get_iclopr__(int *iclopr);
void fs_set_iclbox__(int *iclbox);
void fs_get_iclbox__(int *iclbox);
void fs_set_cablev__(float *cablev);
void fs_set_ra50__(double *ra50);
void fs_get_ra50__(double *ra50);
void fs_set_dec50__(double *dec50);
void fs_get_dec50__(double *dec50);
void fs_set_radat__(double *radat);
void fs_get_radat__(double *radat);
void fs_set_decdat__(double *decdat);
void fs_get_decdat__(double *decdat);
void fs_set_height__(float *height);
void fs_get_height__(float *height);
void fs_set_alat__(double *alat);
void fs_get_alat__(double *alat);
void fs_set_wlong__(double *wlong);
void fs_get_wlong__(double *wlong);
void fs_set_imodfm__(int *imodfm);
void fs_get_imodfm__(int *imodfm);
void fs_set_iratfm__(int *iratfm);
void fs_get_iratfm__(int *iratfm);
void fs_set_ispeed__(int *ispeed, int *i);
void fs_get_ispeed__(int *ispeed, int *i);
void fs_get_cips__(int *cips, int *i);
void fs_set_ienatp__(int *ienatp, int *i);
void fs_get_ienatp__(int *ienatp, int *i);
void fs_set_idirtp__(int *idirtp, int *i);
void fs_get_idirtp__(int *idirtp, int *i);
void fs_set_inp1if__(int *inp1if);
void fs_get_inp1if__(int *inp1if);
void fs_set_inp2if__(int *inp2if);
void fs_get_inp2if__(int *inp2if);
void fs_set_ionsor__(int *ionsor);
void fs_get_ionsor__(int *ionsor);
void fs_set_systmp__(float *systmp);
void fs_get_systmp__(float *systmp);
void fs_set_ipashd__(int ipashd[2][2], int *i);
void fs_get_ipashd__(int ipashd[2][2], int *i);
void fs_set_posnhd__(float posnhd[2][2], int *i);
void fs_get_posnhd__(float posnhd[2][2], int *i);
void fs_set_lfreqv__(char *lfreqv);
void fs_get_lfreqv__(char *lfreqv);
void fs_set_freqvc__(float *freqvc);
void fs_get_freqvc__(float *freqvc);
void fs_set_ibwvc__(int *ibwvc);
void fs_get_ibwvc__(int *ibwvc);
void fs_set_extbwvc__(float *extbwvc);
void fs_get_extbwvc__(float *extbwvc);
void fs_set_ifp2vc__(int *ifp2vc);
void fs_get_ifp2vc__(int *ifp2vc);
void fs_set_lnaant__(char *lnaant);
void fs_get_lnaant__(char *lnaant);
void fs_set_idevgpib__(char *idevgpib);
void fs_get_idevgpib__(char *idevgpib);
void fs_set_idevant__(char *idevant);
void fs_get_idevant__(char *idevant);
void fs_set_idevlog__(char *idevlog);
void fs_get_idevlog__(char *idevlog);
void fs_set_idevmcb__(char *idevmcb);
void fs_get_idevmcb__(char *idevmcb);
void fs_set_ndevlog__(int *ndevlog);
void fs_get_ndevlog__(int *ndevlog);
void fs_set_lsorna__(char *lsorna);
void fs_get_lsorna__(char *lsorna);
void fs_set_azoff__(float *AZOFF);
void fs_get_azoff__(float *AZOFF);
void fs_set_lexper__(int *LEXPER);
void fs_get_lexper__(int *LEXPER);
void fs_set_inext__(short *INEXT);
void fs_get_inext__(short *INEXT);
void fs_set_kenastk__(int *KENASTK, int *j);
void fs_get_kenastk__(int *KENASTK, int *j);
void fs_set_irdytp__(int *IRDYTP, int *i);
void fs_get_irdytp__(int *IRDYTP, int *i);
void fs_set_itraka__(int *ITRAKA, int *i);
void fs_get_itraka__(int *ITRAKA, int *i);
void fs_set_itrakb__(int *ITRAKB, int *i);
void fs_get_itrakb__(int *ITRAKB, int *i);
void fs_set_decoff__(float *DECOFF);
void fs_get_decoff__(float *DECOFF);
void fs_set_eloff__(float *ELOFF);
void fs_get_eloff__(float *ELOFF);
void fs_set_icaptp__(int *ICAPTP, int *i);
void fs_get_icaptp__(int *ICAPTP, int *i);
void fs_set_istptp__(int *ISTPTP, int *i);
void fs_get_istptp__(int *ISTPTP, int *i);
void fs_set_itactp__(int *ITACTP, int *i);
void fs_get_itactp__(int *ITACTP, int *i);
void fs_set_klvdt_fs__(int *KLVDT_FS, int *i);
void fs_get_klvdt_fs__(int *KLVDT_FS, int *i);
void fs_set_kecho__(int *KECHO);
void fs_get_kecho__(int *KECHO);
void fs_set_khalt__(int *KHALT);
void fs_get_khalt__(int *KHALT);
void fs_set_ichfm_cn_tm__(int *ichfm_cn_tm);
void fs_get_ichfm_cn_tm__(int *ichfm_cn_tm);
void fs_set_raoff__(float *RAOFF);
void fs_get_raoff__(float *RAOFF);
void fs_set_xoff__(float *XOFF);
void fs_get_xoff__(float *XOFF);
void fs_set_yoff__(float *YOFF);
void fs_get_yoff__(float *YOFF);
void fs_set_icheck__(int *icheck, int *N);
void fs_get_icheck__(int *icheck, int *N);
void fs_set_ichvlba__(int *ichvlba, int *N);
void fs_get_ichvlba__(int *ichvlba, int *N);
void fs_set_ichs2__(int *ichs2);
void fs_get_ichs2__(int *ichs2);
void fs_set_ichdbbcfm__(int *ichdbbcfm);
void fs_get_ichdbbcfm__(int *ichdbbcfm);
void fs_set_stchk__(int *ichk, int *n);
void fs_get_stchk__(int *ichk, int *n);
void fs_set_sterp__(int *sterp);
void fs_set_erchk__(int *erchk);
void fs_set_stcnm__(char lhol[2], int *n);
void fs_get_stcnm__(char lhol[2], int *n);
void fs_set_irenvc__(int *IRENVC);
void fs_get_irenvc__(int *IRENVC);
void fs_set_ilokvc__(int *ILOKVC);
void fs_get_ilokvc__(int *ILOKVC);
void fs_set_tpivc__(unsigned int *TPIVC, int *i);
void fs_get_tpivc__(unsigned int *TPIVC, int *i);
void fs_set_mifd_tpi__(unsigned int *MIFD_TPI, int *i);
void fs_get_mifd_tpi__(int *MIFD_TPI, int *i);
void fs_set_bbc_tpi__(unsigned int bbc_tpi[2], int *i);
void fs_get_bbc_tpi__(unsigned int bbc_tpi[2], int *i);
void fs_set_vifd_tpi__(unsigned int *VIFD_TPI, int *i);
void fs_get_vifd_tpi__(int *VIFD_TPI, int *i);
void fs_set_llog__(int *LLOG);
void fs_get_llog__(int *LLOG);
void fs_set_lfeet_fs__(char *LFEET_FS, int *i);
void fs_get_lfeet_fs__(char *LFEET_FS, int *i);
void fs_set_lgen__(short *lgen, int *j);
void fs_get_lgen__(short *lgen, int *j);
void fs_set_lnewpr__(int *LNEWPR);
void fs_get_lnewpr__(int *LNEWPR);
void fs_set_lnewsk__(int *LNEWSK);
void fs_get_lnewsk__(int *LNEWSK);
void fs_set_lprc__(int *LPRC);
void fs_get_lprc__(int *LPRC);
void fs_set_lstp__(int *LSTP);
void fs_get_lstp__(int *LSTP);
void fs_set_hwid__(int *hwid);
void fs_get_hwid__(int *hwid);
void fs_set_lskd__(int *LSKD);
void fs_get_lskd__(int *LSKD);
void fs_set_rack__(int *rack);
void fs_get_rack__(int *rack);
void fs_set_rack_type__(int *rack_type);
void fs_get_rack_type__(int *rack_type);
void fs_set_drive__(int *drive);
void fs_get_drive__(int *drive);
void fs_set_drive_type__(int *drive_type);
void fs_get_drive_type__(int *drive_type);
void fs_set_wx_met__(int *wx_met);
void fs_get_wx_met__(int *wx_met);
void fs_set_mk4sync_dflt__(int *mk4sync_dflt);
void fs_get_mk4sync_dflt__(int *mk4sync_dflt);
void fs_set_iskdtpsd__(int *iskdtpsd, int *i);
void fs_get_iskdtpsd__(int *iskdtpsd, int *i);
void fs_set_imaxtpsd__(int *imaxtpsd, int *i);
void fs_get_imaxtpsd__(int *imaxtpsd, int *i);
void fs_set_freqlo__(double *freqlo, int *N);
void fs_get_freqlo__(double *freqlo, int *N);
void fs_set_sblo__(int *sblo, int *N);
void fs_get_sblo__(int *sblo, int *N);
void fs_get_diaman__(float *diaman);
void fs_set_diaman__(float *diaman);
void fs_get_slew1__(float *slew1);
void fs_set_slew1__(float *slew1);
void fs_get_slew2__(float *slew2);
void fs_set_slew2__(float *slew2);
void fs_get_uplim1__(float *uplim1);
void fs_set_uplim1__(float *uplim1);
void fs_get_uplim2__(float *uplim2);
void fs_set_uplim2__(float *uplim2);
void fs_get_lolim1__(float *lolim1);
void fs_set_lolim1__(float *lolim1);
void fs_get_lolim2__(float *lolim2);
void fs_set_lolim2__(float *lolim2);
void fs_get_i70kch__(int *i70kch);
void fs_set_i70kch__(int *i70kch);
void fs_get_i20kch__(int *i20kch);
void fs_set_i20kch__(int *i20kch);
void fs_get_time_coeff__(int *secs_off, int *epoch, int *offset, float *rate, int *span, char *model, int *icomputer);
void fs_set_time_coeff__(int *secs_off, int *epoch, int *offset, float *rate, int *span, char *model, int *icomputer);
void fs_get_vgroup__(int *vgroup, int *i);
void fs_get_vfmenablehi__(int *vfmenablehi);
void fs_get_vfmenablelo__(int *vfmenablelo);
void fs_get_fm4enable__(int fm4enable[]);
void fs_get_vrepro_equalizer__(int *equalizer, int *n, int *i);
void fs_set_horaz__(float *HORAZ);
void fs_get_horaz__(float *HORAZ);
void fs_set_horel__(float *HOREL);
void fs_get_horel__(float *HOREL);
void fs_get_bbc_source__(int *source, int *n);
void fs_get_dbbc_source__(int *source, int *n);
void fs_get_wrhd_fs__(int *wrhd_fs, int *i);
void fs_set_wrhd_fs__(int *wrhd_fs, int *i);
void fs_get_rdhd_fs__(int *rdhd_fs, int *i);
void fs_set_rdhd_fs__(int *rdhd_fs, int *i);
void fs_get_vfm_xpnt__(int *vfm_xpnt);
void fs_set_vfm_xpnt__(int *vfm_xpnt);
void fs_set_cwrap__(char *cwrap);
void fs_get_cwrap__(char *cwrap);
void fs_set_vacsw__(int *vacsw, int *i);
void fs_get_vacsw__(int *vacsw, int *i);
void fs_set_motorv2__(float *motorv2, int *i);
void fs_get_motorv2__(float *motorv2, int *i);
void fs_set_itpthick2__(int *itpthick2, int *i);
void fs_get_itpthick2__(int *itpthick2, int *i);
void fs_set_thin__(int *thin, int *i);
void fs_get_thin__(int *thin, int *i);
void fs_set_vac4__(int *vac4, int *i);
void fs_get_vac4__(int *vac4, int *i);
void fs_set_wrvolt2__(float *wrvolt2, int *i);
void fs_get_wrvolt2__(float *wrvolt2, int *i);
void fs_set_wrvolt4__(float *wrvolt4, int *i);
void fs_get_wrvolt4__(float *wrvolt4, int *i);
void fs_set_wrvolt42__(float *wrvolt42, int *i);
void fs_get_wrvolt42__(float *wrvolt42, int *i);
void fs_set_user_dev1_name__(char *user_dev1_name);
void fs_get_user_dev1_name__(char *user_dev1_name);
void fs_set_user_dev2_name__(char *user_dev2_name);
void fs_get_user_dev2_name__(char *user_dev2_name);
void fs_set_user_dev1_value__(double *user_dev1_value);
void fs_get_user_dev1_value__(double *user_dev1_value);
void fs_set_user_dev2_value__(double *user_dev2_value);
void fs_get_user_dev2_value__(double *user_dev2_value);
void fs_set_freqif3__(int *freqif3);
void fs_get_freqif3__(int *freqif3);
void fs_set_imixif3__(int *imixif3);
void fs_get_imixif3__(int *imixif3);
void fs_set_reccpu__(int *reccpu, int *i);
void fs_get_reccpu__(int *reccpu, int *i);
void fs_get_select__(int *select);
void fs_set_select__(int *select);
void fs_set_knewtape__(int *knewtape, int *i);
void fs_get_knewtape__(int *knewtape, int *i);
void fs_get_ihdmndel__(int *ihdmndel, int *i);
void fs_set_ihdmndel__(int *ihdmndel, int *i);
void fs_set_iat1if__(int *iat1if);
void fs_get_iat1if__(int *iat1if);
void fs_set_iat2if__(int *iat2if);
void fs_get_iat2if__(int *iat2if);
void fs_set_iat3if__(int *iat3if);
void fs_get_iat3if__(int *iat3if);
void fs_set_ifd_set__(int *ifd_set);
void fs_get_ifd_set__(int *ifd_set);
void fs_set_if3_set__(int *if3_set);
void fs_get_if3_set__(int *if3_set);
void fs_set_cablevl__(float *cablevl);
void fs_set_imk4fmv__(int *imk4fmv);
void fs_get_imk4fmv__(int *imk4fmv);
void fs_set_itpivc__(int *itpivc);
void fs_get_itpivc__(int *itpivc);
void fs_set_iapdflg__(int *iapdflg);
void fs_get_iapdflg__(int *iapdflg);
void fs_set_iswif3_fs__(int *iswif3_fs);
void fs_get_iswif3_fs__(int *iswif3_fs);
void fs_set_ipcalif3__(int *ipcalif3);
void fs_get_ipcalif3__(int *ipcalif3);
void fs_set_ibds__(int *ibds);
void fs_get_ibds__(int *ibds);
void fs_set_idevds__(char *idevds);
void fs_get_idevds__(char *idevds);
void fs_set_ndas__(int *ndas);
void fs_get_ndas__(int *ndas);
void fs_set_idasfilt__(int *idasfilt);
void fs_get_idasfilt__(int *idasfilt);
void fs_set_idasbits__(int *idasbits);
void fs_get_idasbits__(int *idasbits);
void fs_set_ichlba__(int *ichlba, int *N);
void fs_get_ichlba__(int *ichlba, int *N);
void fs_set_ifp_tpi__(unsigned int ifp_tpi, int *i);
void fs_get_ifp_tpi__(unsigned int ifp_tpi, int *i);
void fs_set_logchg__(int *logchg);
void fs_get_logchg__(int *logchg);
void fs_set_tacd_port__(int *port);
void fs_get_tacd_port__(int *port);
void fs_set_tacd_hostpc__(char *hostpc);
void fs_get_tacd_hostpc__(char *hostpc);
void fs_set_abend_normal_end__(int *abend_normal_end);
void fs_get_disk_record_record__(int *disk_record_record);
void fs_set_satellite_satellite__(int *satellite);
void fs_get_satellite_satellite__(int *satellite);
void fs_set_dbbcddcv__(int *dbbcddcv);
void fs_get_dbbcddcv__(int *dbbcddcv);
void fs_set_dbbcddcvl__(char *dbbcddcvl);
void fs_get_dbbcddcvl__(char *dbbcddcvl);
void fs_set_dbbcddcvs__(char *dbbcddcvs);
void fs_get_dbbcddcvs__(char *dbbcddcvs);
void fs_set_scan_name_old__(char *scan_name_old);
void fs_set_scan_name__(char *scan_name);
void fs_set_dbbcddcvc__(int *dbbcddcvc);
void fs_get_dbbcddcvc__(int *dbbcddcvc);
void fs_set_dbbcddcsubv__(int *dbbcddcsubv);
void fs_get_dbbcddcsubv__(int *dbbcddcsubv);
void fs_set_dbbccontcalpol__(int *dbbccontcalpol);
void fs_get_dbbccontcalpol__(int *dbbccontcalpol);
void fs_set_dbbcpfbv__(int *dbbcpfbv);
void fs_get_dbbcpfbv__(int *dbbcpfbv);
void fs_set_dbbcpfbvl__(char *dbbcpfbvl);
void fs_get_dbbcpfbvl__(char *dbbcpfbvl);
void fs_set_dbbcpfbvs__(char *dbbcpfbvs);
void fs_get_dbbcpfbvs__(char *dbbcpfbvs);
void fs_set_dbbcpfbvc__(int *dbbcpfbvc);
void fs_get_dbbcpfbvc__(int *dbbcpfbvc);
void fs_set_dbbcpfbsubv__(int *dbbcpfbsubv);
void fs_get_dbbcpfbsubv__(int *dbbcpfbsubv);
void fs_set_dbbc_cond_mods__(int *dbbc_cond_mods);
void fs_get_dbbc_cond_mods__(int *dbbc_cond_mods);
void fs_set_dbbc_if_factors__(int *dbbc_if_factors);
void fs_get_dbbc_if_factors__(int *dbbc_if_factors);
void fs_set_dbbc_cont_cal_mode__(int *dbbc_cont_cal_mode);
void fs_get_dbbc_cont_cal_mode__(int *dbbc_cont_cal_mode);
void fs_set_m5b_crate__(int *m5b_crate);
void fs_get_m5b_crate__(int *m5b_crate);
void fs_set_mk6_units__(int *mk6_units);
void fs_get_mk6_units__(int *mk6_units);
void fs_set_mk6_active__(int *mk6_active);
void fs_get_mk6_active__(int *mk6_active);
void fs_set_wx_host__(char *wx_host);
void fs_get_wx_host__(char *wx_host);
void fs_set_rdbe_units__(int *rdbe_units);
void fs_get_rdbe_units__(int *rdbe_units);
void fs_set_rdbe_active__(int *rdbe_active);
void fs_get_rdbe_active__(int *rdbe_active);
void fs_set_rdbe_rms_t__(float *rdbe_rms_t);
void fs_get_rdbe_rms_t__(float *rdbe_rms_t);
void fs_set_rdbe_rms_min__(float *rdbe_rms_min);
void fs_get_rdbe_rms_min__(float *rdbe_rms_min);
void fs_set_rdbe_rms_max__(float *rdbe_rms_max);
void fs_get_rdbe_rms_max__(float *rdbe_rms_max);
void fs_set_rdbe_pcal_amp__(char *rdbe_pcal_amp);
void fs_get_rdbe_pcal_amp__(char *rdbe_pcal_amp);
void fs_set_dbbc3_ddc_v__(int *dbbc3_ddc_v);
void fs_get_dbbc3_ddc_v__(int *dbbc3_ddc_v);
void fs_set_dbbc3_ddc_vs__(char *dbbc3_ddc_vs);
void fs_get_dbbc3_ddc_vs__(char *dbbc3_ddc_vs);
void fs_set_dbbc3_ddc_vc__(int *dbbc3_ddc_vc);
void fs_get_dbbc3_ddc_vc__(int *dbbc3_ddc_vc);
void fs_set_dbbc3_ddc_bbcs_per_if__(int *dbbc3_ddc_bbcs_per_if);
void fs_get_dbbc3_ddc_bbcs_per_if__(int *dbbc3_ddc_bbcs_per_if);
void fs_set_dbbc3_ddc_ifs__(int *dbbc3_ddc_ifs);
void fs_get_dbbc3_ddc_ifs__(int *dbbc3_ddc_ifs);
void fs_get_dbbc3_bbcnn_source__(int *source, int *n);
void fs_set_dbbc3_cont_cal_mode__(int *dbbc3_cont_cal_mode);
void fs_get_dbbc3_cont_cal_mode__(int *dbbc3_cont_cal_mode);
void fs_set_fila10gvsi_in__(char *fila10gvsi_in);
void fs_get_fila10gvsi_in__(char *fila10gvsi_in);
void fs_set_dbbc_como_cores__(int *dbbc_como_cores);
void fs_get_dbbc_como_cores__(int *dbbc_como_cores);
void fs_set_dbbc_cores__(int *dbbc_cores);
void fs_get_dbbc_cores__(int *dbbc_cores);
void fs_set_user_device_zero__(int *zero);
void fs_get_user_device_zero__(int *zero);
void fs_get_sverrelease_fs__(int *sVerRelease_FS);
void fs_get_fortran__(int *fortran);
/* newlb/put_stderr.c */
int put_stderr__(char *string);