/* vex/print_vex.c */
void print_vex(struct vex *vex);
void print_vex_blocks(struct llist *blocks);
void print_def_block(struct llist *items, void func(void));
void print_qref_block(struct llist *items);
void print_block_name(int block);
void print_qualifiers(struct llist *items);
void print_lowl(struct llist *items);
void print_lowl_st(int statement, void *ptr);
void print_external(struct external *this);
void print_svalue(char *svalue);
void print_literal_list(struct llist *literals);
void print_comment(char *comment);
void print_comment_trailing(char *comment_trailing);
/* vex/vexf.c */
integer fvex_open(char **name, integer *vex);
integer fget_station_def(char **station, integer *station_len, integer *vex);
integer fget_mode_def(char **mode, integer *mode_len, integer *vex);
integer fget_source_def(char **source, integer *source_len, integer *vex);
integer fget_all_lowl(char **station, char **mode, char **statement, char **primitive, integer *vex);
integer fget_mode_lowl(char **station, char **mode, char **statement, char **primitive, integer *vex);
integer fget_station_lowl(char **station, char **statement, char **primitive, integer *vex);
integer fget_global_lowl(char **statement, char **primitive, integer *vex);
integer fget_scan_station(char **start, integer *start_len, char **mode, integer *mode_len, char **scanid, integer *scanid_len, char **station, integer *vex);
integer fget_scan_data_transfer(char **start, integer *start_len, char **mode, integer *mode_len, char **scanid, integer *scanid_len, char **station, integer *vex);
integer fget_scan(char **start, integer *start_len, char **mode, integer *mode_len, char **scanid, integer *scanid_len, integer *vex);
integer fget_station_scan(integer *n);
integer fget_data_transfer_scan(integer *n);
integer fget_source_lowl(char **source, char **statement, integer *vex);
integer fget_literal(char *string);
integer fget_literal_st(char **string);
integer fvex_len(char *field, ftnlen field_len);
integer fvex_field(integer *n, char **field, integer *field_len);
integer fvex_units(char **units, integer *units_len);
integer fvex_scan_source(integer *n, char **src, integer *src_len);
integer fvex_double(char **field, char **units, doublereal *double__);
integer fvex_int(char **field, integer *int__);
integer fvex_date(char **field, integer *iarray, doublereal *seconds);
integer fvex_ra(char **field, doublereal *ra);
integer fvex_dec(char **field, doublereal *dec);
char *ptr_ch(char *ptr, ftnlen len);
/* vex/vexf_put.c */
void fcreate_vex(char **file_or_screen);
void fcreate_version(char **number);
void fcreate_block(char **blockname);
void fcreate_def(char **defname);
void fend_def(void);
void fcreate_qref_qualifier(char **qualifier);
void fcreate_qref(char **blockname, char **keyword);
void fcreate_ref(char **blockname, char **keyword);
void fcreate_external_ref(char **filename, char **blockname, char **keyword);
void fcreate_scan(char **str);
void fend_scan(char **str);
void fcreate_comment(char **where, char **comment);
void fcreate_start(char **str);
void fcreate_mode(char **str);
void fcreate_source(char **str);
void fcreate_station(char **str, char **str2, char **str3, char **str4, char **str5, char **str6, char **str7, char **str8, char **str9);
void fcreate_station_drive_list(char **str);
void fcreate_data_transfer(char **str, char **str2, char **str3, char **str4, char **str5, char **str6, char **str7, char **str8);
void fcreate_antenna_diam(char **str, char **str2);
void fcreate_axis_type(char **str, char **str2);
void fcreate_axis_offset(char **str, char **str2);
void fcreate_antenna_motion(char **str, char **str2, char **str3, char **str4, char **str5);
void fcreate_pointing_sector(char **str, char **str2, char **str3, char **str4, char **str5, char **str6, char **str7, char **str8, char **str9, char **str10, char **str11);
void fcreate_bbc_assign(char **str, char **str2, char **str3);
void fcreate_clock(char **str, char **str2, char **str3, char **str4, char **str5);
void fcreate_record_transport_type(char **name);
void fcreate_electronics_rack_type(char **name);
void fcreate_number_drives(char **name);
void fcreate_headstack(char **str, char **str2, char **str3);
void fcreate_record_density(char **str, char **str2);
void fcreate_recording_system_id(char **name);
void fcreate_tape_length(char **str, char **str2, char **str3, char **str4);
void fcreate_tape_motion(char **str, char **str2, char **str3, char **str4, char **str5, char **str6, char **str7);
void fcreate_tape_control(char **str);
void fcreate_tai_utc(char **str, char **str2);
void fcreate_a1_tai(char **str, char **str2);
void fcreate_eop_ref_epoch(char **str);
void fcreate_num_eop_points(char **str);
void fcreate_eop_interval(char **str, char **str2);
void fcreate_ut1_utc(char **str, char **str2);
void fcreate_x_wobble(char **str, char **str2);
void fcreate_y_wobble(char **str, char **str2);
void fcreate_nut_ref_epoch(char **str);
void fcreate_num_nut_points(char **str);
void fcreate_nut_interval(char **str, char **str2);
void fcreate_delta_psi(char **str, char **str2);
void fcreate_delta_eps(char **str, char **str2);
void fcreate_nut_model(char **str);
void fcreate_exper_num(char **str);
void fcreate_exper_name(char **str);
void fcreate_exper_description(char **str);
void fcreate_exper_nominal_start(char **str);
void fcreate_exper_nominal_stop(char **str);
void fcreate_pi_name(char **str);
void fcreate_pi_email(char **str);
void fcreate_contact_name(char **str);
void fcreate_contact_email(char **str);
void fcreate_scheduler_name(char **str);
void fcreate_scheduler_email(char **str);
void fcreate_target_correlator(char **str);
void fcreate_chan_def(char **str, char **str2, char **str3, char **str4, char **str5, char **str6, char **str7, char **str8, char **str9);
void fcreate_chan_def_states(char **str);
void fcreate_sample_rate(char **str, char **str2);
void fcreate_bits_per_sample(char **str);
void fcreate_cycle(char **str, char **str2);
void fcreate_switching_cycle(char **str);
void fcreate_headstack_pos(char **str, char **str2);
void fcreate_headstack_reference(char **str);
void fcreate_if_def(char **str, char **str2, char **str3, char **str4, char **str5, char **str6, char **str7, char **str8, char **str9, char **str10);
void fcreate_phase_cal_detect(char **str);
void fcreate_phase_cal_detect_list(char **str);
void fcreate_s2_group_order(char **str);
void fcreate_tape_change(char **str, char **str2);
void fcreate_pass_order(char **str);
void fcreate_new_tape_setup(char **str, char **str2);
void fcreate_new_source_command(char **str, char **str2);
void fcreate_headstack_motion(char **str, char **str2);
void fcreate_tape_prepass(char **str, char **str2, char **str3);
void fcreate_parity_check(char **str, char **str2, char **str3);
void fcreate_setup_always(char **str, char **str2, char **str3);
void fcreate_postob_cal(char **str, char **str2, char **str3, char **str4);
void fcreate_midob_cal(char **str, char **str2, char **str3, char **str4);
void fcreate_preob_cal(char **str, char **str2, char **str3, char **str4);
void fcreate_roll(char **str);
void fcreate_procedure_name_prefix(char **str);
void fcreate_roll_reinit_period(char **str, char **str2);
void fcreate_roll_inc_period(char **str);
void fcreate_roll_def(char **str);
void fcreate_literal(char **str);
void fcreate_sefd_model(char **str);
void fcreate_sefd_model_parameter(char **str);
void fcreate_sefd(char **str, char **str2, char **str3, int str4);
void fcreate_site_name(char **str);
void fcreate_site_type(char **str);
void fcreate_site_id(char **str);
void fcreate_site_position(char **str, char **str2, char **str3, char **str4, char **str5, char **str6);
void fcreate_site_position_epoch(char **str);
void fcreate_site_position_ref(char **str);
void fcreate_site_velocity(char **str, char **str2, char **str3, char **str4, char **str5, char **str6);
void fcreate_horizon_map_az(char **str);
void fcreate_horizon_map_el(char **str);
void fcreate_horizon_map(char **str, char **str2);
void fcreate_zen_atmos(char **str, char **str2);
void fcreate_ocean_load_vert(char **str, char **str2, char **str3, char **str4);
void fcreate_ocean_load_horiz(char **str, char **str2, char **str3, char **str4);
void fcreate_occupation_code(char **str);
void fcreate_inclination(char **str, char **str2);
void fcreate_eccentricity(char **str);
void fcreate_arg_perigee(char **str, char **str2);
void fcreate_ascending_node(char **str, char **str2);
void fcreate_mean_anomaly(char **str, char **str2);
void fcreate_semi_major_axis(char **str, char **str2);
void fcreate_mean_motion(char **str);
void fcreate_orbit_epoch(char **str);
void fcreate_source_type(char **str, char **str2);
void fcreate_source_name(char **str);
void fcreate_ra(char **str);
void fcreate_iau_name(char **str);
void fcreate_dec(char **str);
void fcreate_ref_coord_frame(char **str);
void fcreate_source_position_ref(char **str);
void fcreate_source_position_epoch(char **str);
void fcreate_ra_rate(char **str, char **str2);
void fcreate_dec_rate(char **str, char **str2);
void fcreate_velocity_wrt_lsr(char **str, char **str2);
void fcreate_source_model(char **str, char **str2, char **str3, char **str4, char **str5, char **str6, char **str7, char **str8, char **str9, char **str10, char **str11, char **str12, char **str13);
void fcreate_vsn(char **str, char **str2, char **str3, char **str4);
void fcreate_fanin_def(char **str, char **str2, char **str3);
void fcreate_fanin_def_list(char **str);
void fcreate_fanout_def_subpass(char **str);
void fcreate_fanout_def_headstack(char **str);
void fcreate_fanout_trksid_list(char **str);
void fcreate_fanout_bitstream_list(char **str);
void fcreate_track_frame_format(char **str);
void fcreate_data_modulation(char **str);
void fcreate_vlba_frmtr_sys_trk(char **str, char **str2, char **str3, char **str4);
void fcreate_vlba_trnsprt_sys_trk(char **str, char **str2);
void fcreate_s2_recording_mode(char **str);
void fcreate_s2_data_source(char **str, char **str2, char **str3);
/* vex/vex_get.c */
int vex_open(char *name, struct vex **vex);
void *get_scan_start(Llist *lowls);
void *get_scan_mode(Llist *lowls);
void *get_scan_source_next(void);
void *get_scan_source(Llist *lowls_scan_in);
void *get_scan_station_next(Llist **lowls_scan, char **scanid);
void *get_scan_station(Llist **lowls_scan, char **scanid, char *station_in, struct vex *vex_in);
void *get_scan_next(char **scanid);
void *get_scan(char **scanid, struct vex *vex_in);
void *get_station_scan_next(void);
void *get_station_scan(Llist *lowls_in);
char *get_source_def_next(void);
char *get_source_def(struct vex *vex_in);
char *get_mode_def_next(void);
char *get_mode_def(struct vex *vex_in);
char *get_station_def_next(void);
char *get_station_def(struct vex *vex_in);
void *get_all_lowl_next(void);
void *get_all_lowl(char *station_in, char *mode_in, int statement_in, int primitive_in, struct vex *vex_in);
void *get_mode_lowl_next(void);
void *get_mode_lowl(char *station_in, char *mode_in, int statement_in, int primitive_in, struct vex *vex_in);
void *get_station_lowl_next(void);
void *get_station_lowl(char *station_in, int statement_in, int primitive_in, struct vex *vex_in);
void *get_source_lowl_next(void);
void *get_source_lowl(char *source_in, int statement_in, struct vex *vex_in);
void *get_global_lowl_next(void);
void *get_global_lowl(int statement_in, int primitive_in, struct vex *vex_in);
Llist *find_block(int block, struct vex *vex);
Llist *find_def(Llist *defs, char *mode);
Llist *find_lowl(Llist *lowls, int statement);
Llist *find_next_def(Llist *defs);
Llist *find_next_scan(Llist *defs);
char *get_literal_def_next(void);
char *get_literal_def(struct vex *vex_in);
void *get_literal_lowl_next(void);
void *get_literal_lowl(char *source_in, struct vex *vex_in);
void *get_next_literal(struct llist *lowls);
void *get_a_literal(struct llist *literals, char **text);
char *get_all_literals(struct llist *literals, char *array[]);
void *get_scan_data_transfer_next(Llist **lowls_scan, char **scanid);
void *get_scan_data_transfer(Llist **lowls_scan, char **scanid, char *data_transfer_in, struct vex *vex_in);
void *get_data_transfer_scan_next(void);
void *get_data_transfer_scan(Llist *lowls_in);
/* vex/vex_put.c */
void *create_vex(char *str);
void *create_block(char *str);
void *create_def(char *str);
void *end_def(void);
void *create_ref(char *str, char *str2);
void *create_qref(char *str, char *str2);
void *create_qref_qualifier(char *str);
void *create_external_ref(char *str, char *str2, char *str3);
void *create_version(char *str);
void *create_scan(char *str);
void *end_scan(void);
void *create_comment(char *str, char *str2);
void *create_start(char *str);
void *create_mode(char *str);
void *create_source(char *str);
void *create_station(char *str, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9);
void *create_station_drive_list(char *str);
void *create_data_transfer(char *str, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8);
void *create_antenna_diam(char *str, char *str2);
void *create_axis_type(char *str, char *str2);
void *create_axis_offset(char *str, char *str2);
void *create_antenna_motion(char *str, char *str2, char *str3, char *str4, char *str5);
void *create_pointing_sector(char *str, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9, char *str10, char *str11);
void *create_bbc_assign(char *str, char *str2, char *str3);
void *create_clock(char *str, char *str2, char *str3, char *str4, char *str5);
void *create_record_transport_type(char *str);
void *create_electronics_rack_type(char *str);
void *create_number_drives(char *str);
void *create_headstack(char *str, char *str2, char *str3);
void *create_record_density(char *str, char *str2);
void *create_tape_length(char *str, char *str2, char *str3, char *str4);
void *create_recording_system_id(char *str);
void *create_tape_motion(char *str, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7);
void *create_tape_control(char *str);
void *create_tai_utc(char *str, char *str2);
void *create_a1_tai(char *str, char *str2);
void *create_eop_ref_epoch(char *str);
void *create_num_eop_points(char *str);
void *create_eop_interval(char *str, char *str2);
void *create_ut1_utc(char *str, char *str2);
void *create_x_wobble(char *str, char *str2);
void *create_y_wobble(char *str, char *str2);
void *create_nut_ref_epoch(char *str);
void *create_num_nut_points(char *str);
void *create_nut_interval(char *str, char *str2);
void *create_delta_psi(char *str, char *str2);
void *create_delta_eps(char *str, char *str2);
void *create_nut_model(char *str);
void *create_exper_name(char *str);
void *create_exper_num(char *str);
void *create_exper_description(char *str);
void *create_exper_nominal_start(char *str);
void *create_exper_nominal_stop(char *str);
void *create_pi_name(char *str);
void *create_pi_email(char *str);
void *create_contact_name(char *str);
void *create_contact_email(char *str);
void *create_scheduler_name(char *str);
void *create_scheduler_email(char *str);
void *create_target_correlator(char *str);
void *create_chan_def(char *str, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9);
void *create_chan_def_states(char *str);
void *create_sample_rate(char *str, char *str2);
void *create_bits_per_sample(char *str);
void *create_switching_cycle(char *str);
void *create_cycle(char *str, char *str2);
void *create_headstack_reference(char *str);
void *create_headstack_pos(char *str, char *str2);
void *create_if_def(char *str, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9, char *str10);
void *create_pass_order(char *str);
void *create_s2_group_order(char *str);
void *create_phase_cal_detect(char *str);
void *create_phase_cal_detect_list(char *str);
void *create_tape_change(char *str, char *str2);
void *create_headstack_motion(char *str, char *str2);
void *create_new_source_command(char *str, char *str2);
void *create_new_tape_setup(char *str, char *str2);
void *create_setup_always(char *str, char *str2, char *str3);
void *create_parity_check(char *str, char *str2, char *str3);
void *create_tape_prepass(char *str, char *str2, char *str3);
void *create_preob_cal(char *str, char *str2, char *str3, char *str4);
void *create_midob_cal(char *str, char *str2, char *str3, char *str4);
void *create_postob_cal(char *str, char *str2, char *str3, char *str4);
void *create_procedure_name_prefix(char *str);
void *create_roll(char *str);
void *create_roll_reinit_period(char *str, char *str2);
void *create_roll_inc_period(char *str);
void *create_roll_def(char *str);
void *create_literal(char *str);
void *create_sefd_model(char *str);
void *create_sefd(char *str, char *str2, char *str3);
void *create_sefd_model_parameter(char *str);
void *create_site_name(char *str);
void *create_site_type(char *str);
void *create_site_ID(char *str);
void *create_site_position(char *str, char *str2, char *str3, char *str4, char *str5, char *str6);
void *create_site_position_epoch(char *str);
void *create_site_position_ref(char *str);
void *create_site_velocity(char *str, char *str2, char *str3, char *str4, char *str5, char *str6);
void *create_horizon_map(char *str, char *str2);
void *create_horizon_map_az(void);
void *create_horizon_map_el(void);
void *create_zen_atmos(char *str, char *str2);
void *create_ocean_load_vert(char *str, char *str2, char *str3, char *str4);
void *create_ocean_load_horiz(char *str, char *str2, char *str3, char *str4);
void *create_occupation_code(char *str);
void *create_inclination(char *str, char *str2);
void *create_eccentricity(char *str);
void *create_arg_perigee(char *str, char *str2);
void *create_ascending_node(char *str, char *str2);
void *create_mean_anomaly(char *str, char *str2);
void *create_semi_major_axis(char *str, char *str2);
void *create_mean_motion(char *str);
void *create_orbit_epoch(char *str);
void *create_source_type(char *str, char *str2);
void *create_source_name(char *str);
void *create_ra(char *str);
void *create_IAU_name(char *str);
void *create_dec(char *str);
void *create_ref_coord_frame(char *str);
void *create_source_position_ref(char *str);
void *create_source_position_epoch(char *str);
void *create_ra_rate(char *str, char *str2);
void *create_dec_rate(char *str, char *str2);
void *create_velocity_wrt_LSR(char *str, char *str2);
void *create_source_model(char *str, char *str2, char *str3, char *str4, char *str5, char *str6, char *str7, char *str8, char *str9, char *str10, char *str11, char *str12, char *str13);
void *create_vsn(char *str, char *str2, char *str3, char *str4);
void *create_fanin_def(char *str, char *str2, char *str3);
void *create_fanin_def_list(char *str);
void *create_fanout_def_subpass(char *str);
void *create_fanout_def_headstack(char *str);
void *create_fanout_bitstream_list(char *str);
void *create_fanout_trksID_list(char *str);
void *create_track_frame_format(char *str);
void *create_data_modulation(char *str);
void *create_vlba_frmtr_sys_trk(char *str, char *str2, char *str3, char *str4);
void *create_vlba_trnsprt_sys_trk(char *str, char *str2);
void *create_s2_recording_mode(char *str);
void *create_s2_data_source(char *str, char *str2, char *str3);
/* vex/vex_util.c */
struct llist *add_list(struct llist *start, void *ptr);
struct llist *ins_list(void *ptr, struct llist *start);
struct qref *make_qref(int primitive, char *name, struct llist *qualifiers);
struct def *make_def(char *name, struct llist *refs);
struct block *make_block(int block, struct llist *items);
struct vex *make_vex(struct llist *version, struct llist *blocks);
struct lowl *make_lowl(int statement, void *item);
struct chan_def *make_chan_def(char *band_id, struct dvalue *sky_freq, char *net_sb, struct dvalue *bw, char *chan_id, char *bbc_id, char *pcal_id, struct llist *states);
struct dvalue *make_dvalue(char *value, char *units);
struct external *make_external(char *file, int primitive, char *name);
struct switching_cycle *make_switching_cycle(char *origin, struct llist *periods);
struct station *make_station(char *key, struct dvalue *start, struct dvalue *stop, struct dvalue *start_pos, char *pass, char *sector, struct llist *drives);
struct data_transfer *make_data_transfer(char *key, char *method, char *destination, struct dvalue *start, struct dvalue *stop, char *options);
struct axis_type *make_axis_type(char *axis1, char *axis2);
struct antenna_motion *make_antenna_motion(char *axis, struct dvalue *rate, struct dvalue *offset);
struct pointing_sector *make_pointing_sector(char *sector, char *axis1, struct dvalue *lolimit1, struct dvalue *hilimit1, char *axis2, struct dvalue *lolimit2, struct dvalue *hilimit2);
struct bbc_assign *make_bbc_assign(char *bbc_id, struct dvalue *physical, char *if_id);
struct clock_early *make_clock_early(char *start, struct dvalue *offset, char *origin, struct dvalue *rate);
struct headstack *make_headstack(struct dvalue *stack, char *type, struct dvalue *offset);
struct tape_length *make_tape_length(struct dvalue *duration, char *speed, struct dvalue *tapes);
struct tape_motion *make_tape_motion(char *type, struct dvalue *early, struct dvalue *late, struct dvalue *gap);
struct headstack_pos *make_headstack_pos(struct dvalue *index, struct llist *positions);
struct if_def *make_if_def(char *if_id, char *physical, char *polar, struct dvalue *lo, char *sb, struct dvalue *pcal_spacing, struct dvalue *pcal_base);
struct phase_cal_detect *make_phase_cal_detect(char *pcal_id, struct llist *tones);
struct setup_always *make_setup_always(char *state, struct dvalue *time);
struct parity_check *make_parity_check(char *state, struct dvalue *time);
struct tape_prepass *make_tape_prepass(char *state, struct dvalue *time);
struct preob_cal *make_preob_cal(char *state, struct dvalue *time, char *name);
struct midob_cal *make_midob_cal(char *state, struct dvalue *time, char *name);
struct postob_cal *make_postob_cal(char *state, struct dvalue *time, char *name);
struct sefd *make_sefd(char *if_id, struct dvalue *flux, struct llist *params);
struct site_position *make_site_position(struct dvalue *x, struct dvalue *y, struct dvalue *z);
struct site_velocity *make_site_velocity(struct dvalue *x, struct dvalue *y, struct dvalue *z);
struct ocean_load_vert *make_ocean_load_vert(struct dvalue *amp, struct dvalue *phase);
struct ocean_load_horiz *make_ocean_load_horiz(struct dvalue *amp, struct dvalue *phase);
struct source_model *make_source_model(struct dvalue *component, char *band_id, struct dvalue *flux, struct dvalue *majoraxis, struct dvalue *ratio, struct dvalue *angle, struct dvalue *raoff, struct dvalue *decoff);
struct vsn *make_vsn(struct dvalue *drive, char *label, char *start, char *stop);
struct fanin_def *make_fanin_def(char *subpass, struct dvalue *hdstk, struct dvalue *track, struct llist *bitstreams);
struct fanout_def *make_fanout_def(char *subpass, struct llist *bitstream, struct dvalue *hdstk, struct llist *tracks);
struct vlba_frmtr_sys_trk *make_vlba_frmtr_sys_trk(struct dvalue *output, char *use, struct dvalue *start, struct dvalue *stop);
struct s2_data_source *make_s2_data_source(char *source, char *bbcx_id, char *bbcy_id);
int lowl2int(char *lowl);
int block2int(char *block);
char *int2lowl(int lowl);
char *int2block(int block);
int vex_field(int statement, void *ptr, int n, int *link, int *name, char **value, char **units);
int get_site_velocity_field(Site_velocity *site_velocity, int n, int *link, int *name, char **value, char **units);
