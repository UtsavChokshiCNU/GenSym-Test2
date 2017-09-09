extern long g2ext_create_argument_list(/* int, char[] * */);
extern void g2ext_gensym_SIGALRM_handler(/* int */);
extern void g2ext_gensym_signal_handler(/* int */);
extern void g2ext_maybe_wait_for_return_key(/* void */);
extern void g2ext_print_backtrace(/* void */);
extern void g2ext_check_for_logfile(/* int, char[] * */);
extern void g2ext_print_command_line_usage(/* int */);
extern void g2ext_set_gensym_product(/* char * */);

extern void g2rtl_gsi_initialize_region_increments(/* void */);

extern void g2int_init_top_level(/* void */);
extern void g2int_userinit(/* void */);
extern void *launch_gsi(/* void */);  /* returns Object */

extern void gsi_initialize_callback(/* Object, Object */);
