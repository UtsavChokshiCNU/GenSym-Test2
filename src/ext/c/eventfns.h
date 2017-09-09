
/* definition of the externally visible next_event API. */

#if defined(__STDC__) || defined(_MSC_VER)
#define NE_API_PROTO(args) args
#else
#define NE_API_PROTO(args) ()
#endif

extern int ne_use_sck;

extern void ne_initialize_network_interface NE_API_PROTO((NETWORK_INTERFACE *network_intfc));

extern void ne_map_fd_to_handle NE_API_PROTO((fd_type fd, G2pointer ni_handle));
extern G2pointer ne_unmap_fd NE_API_PROTO((fd_type fd));

extern void ne_connect_ni NE_API_PROTO((G2pointer ni_handle));
extern void ne_register_active_ni NE_API_PROTO((G2pointer ni_handle));
extern void ne_deregister_inactive_ni NE_API_PROTO((G2pointer ni_handle));
extern void ne_enable_accept_events NE_API_PROTO((G2pointer ni_handle));
extern void ne_disable_accept_events NE_API_PROTO((G2pointer ni_handle));
extern void ne_enable_read_events NE_API_PROTO((G2pointer ni_handle));
extern void ne_disable_read_events NE_API_PROTO((G2pointer ni_handle));
extern void ne_enable_write_events NE_API_PROTO((G2pointer ni_handle));
extern void ne_disable_write_events NE_API_PROTO((G2pointer ni_handle));

extern void ne_enable_watch_events NE_API_PROTO((G2pointer ni_handle));

extern void ne_enable_display_events NE_API_PROTO((void));
extern void ne_disable_display_events NE_API_PROTO((void));
extern long ne_display_events_enabled NE_API_PROTO((void));
extern void ne_initialize_display_events NE_API_PROTO((int window_connection_number));

/* All of the following are called by translated lisp code, too. */
extern long g2_event_cycle NE_API_PROTO((long wait_allowed));
extern void g2_event_wait NE_API_PROTO((void));
extern long g2_event_ready NE_API_PROTO((long wait_allowed));

extern void ne_initialize_event_handling NE_API_PROTO((void));
extern void ne_print_events NE_API_PROTO((NETWORK_INTERFACE *ni));
extern void ne_sprint_events NE_API_PROTO((char *buffer,NETWORK_INTERFACE *ni));
extern G2pointer ne_lookup_handle_for_fd NE_API_PROTO((fd_type fd));

extern void ne_enqueue_scheduler_event NE_API_PROTO((void));
extern void ne_set_next_timer_event NE_API_PROTO((long milliseconds_to_go));

extern long ne_last_error_length NE_API_PROTO((long handle));
extern void ne_last_error_string NE_API_PROTO((long handle, char *buffer));


