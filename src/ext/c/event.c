
#include "cprim.h"
#include "networks.h"
#include "netevent.h"

#ifdef WIN32
/* define the variable: win32internet_error_code_table */
#  include "winerr.h"
#endif

#define WIN32_USES_NTEVENT_AND_SCKEVENT

#ifdef WIN32
#  ifdef WIN32_USES_NTEVENT_AND_SCKEVENT
#    define SN_NE
#  else
#    define N_NE
#  endif
#else
#  define S_NE
#endif

#if defined(N_NE) || defined(SN_NE)

#define ne_initialize_network_interface n_ne_initialize_network_interface
#define ne_map_fd_to_handle n_ne_map_fd_to_handle
#define ne_unmap_fd n_ne_unmap_fd
#define ne_connect_ni n_ne_connect_ni
#define ne_register_active_ni n_ne_register_active_ni
#define ne_deregister_inactive_ni n_ne_deregister_inactive_ni
#define ne_enable_accept_events n_ne_enable_accept_events
#define ne_disable_accept_events n_ne_disable_accept_events
#define ne_enable_read_events n_ne_enable_read_events
#define ne_disable_read_events n_ne_disable_read_events
#define ne_enable_write_events n_ne_enable_write_events
#define ne_disable_write_events n_ne_disable_write_events
#define ne_enable_watch_events n_ne_enable_watch_events
#define ne_enable_display_events n_ne_enable_display_events
#define ne_disable_display_events n_ne_disable_display_events
#define ne_display_events_enabled n_ne_display_events_enabled
#define ne_initialize_display_events n_ne_initialize_display_events
#define g2_event_cycle n_g2_event_cycle
#define g2_event_wait n_g2_event_wait
#define g2_event_ready n_g2_event_ready
#define ne_initialize_event_handling n_ne_initialize_event_handling
#define ne_print_events n_ne_print_events
#define ne_sprint_events n_ne_sprint_events
#define ne_lookup_handle_for_fd n_ne_lookup_handle_for_fd
#define ne_enqueue_scheduler_event n_ne_enqueue_scheduler_event
#define ne_set_next_timer_event n_ne_set_next_timer_event
#define ne_last_error_length n_ne_last_error_length
#define ne_last_error_string n_ne_last_error_string

#include "eventfns.h"

#undef ne_initialize_network_interface
#undef ne_map_fd_to_handle
#undef ne_unmap_fd
#undef ne_connect_ni
#undef ne_register_active_ni
#undef ne_deregister_inactive_ni
#undef ne_enable_accept_events
#undef ne_disable_accept_events
#undef ne_enable_read_events
#undef ne_disable_read_events
#undef ne_enable_write_events
#undef ne_disable_write_events
#undef ne_enable_watch_events
#undef ne_enable_display_events
#undef ne_disable_display_events
#undef ne_display_events_enabled
#undef ne_initialize_display_events
#undef g2_event_cycle
#undef g2_event_wait
#undef g2_event_ready
#undef ne_initialize_event_handling
#undef ne_print_events
#undef ne_sprint_events
#undef ne_lookup_handle_for_fd
#undef ne_enqueue_scheduler_event
#undef ne_set_next_timer_event
#undef ne_last_error_length
#undef ne_last_error_string

#endif

#if defined(S_NE) || defined(SN_NE)

#define ne_initialize_network_interface g2ext_s_ne_initialize_network_interface
#define ne_map_fd_to_handle g2ext_s_ne_map_fd_to_handle
#define ne_unmap_fd g2ext_s_ne_unmap_fd
#define ne_connect_ni g2ext_s_ne_connect_ni
#define ne_register_active_ni g2ext_s_ne_register_active_ni
#define ne_deregister_inactive_ni g2ext_s_ne_deregister_inactive_ni
#define ne_enable_accept_events g2ext_s_ne_enable_accept_events
#define ne_disable_accept_events g2ext_s_ne_disable_accept_events
#define ne_enable_read_events g2ext_s_ne_enable_read_events
#define ne_disable_read_events g2ext_s_ne_disable_read_events
#define ne_enable_write_events g2ext_s_ne_enable_write_events
#define ne_disable_write_events g2ext_s_ne_disable_write_events
#define ne_enable_watch_events s_ne_enable_watch_events
#define ne_enable_display_events g2ext_s_ne_enable_display_events
#define ne_disable_display_events s_ne_disable_display_events
#define ne_display_events_enabled s_ne_display_events_enabled
#define ne_initialize_display_events s_ne_initialize_display_events
#define g2_event_cycle g2ext_s_g2_event_cycle
#define g2_event_wait g2ext_s_g2_event_wait
#define g2_event_ready g2ext_s_g2_event_ready
#define ne_initialize_event_handling g2ext_s_ne_initialize_event_handling
#define ne_print_events g2ext_s_ne_print_events
#define ne_sprint_events g2ext_s_ne_sprint_events
#define ne_lookup_handle_for_fd g2ext_s_ne_lookup_handle_for_fd
#define ne_enqueue_scheduler_event g2ext_s_ne_enqueue_scheduler_event
#define ne_set_next_timer_event g2ext_s_ne_set_next_timer_event
#define ne_last_error_length g2ext_s_ne_last_error_length
#define ne_last_error_string g2ext_s_ne_last_error_string

#include "eventfns.h"

#undef ne_initialize_network_interface
#undef ne_map_fd_to_handle
#undef ne_unmap_fd
#undef ne_connect_ni
#undef ne_register_active_ni
#undef ne_deregister_inactive_ni
#undef ne_enable_accept_events
#undef ne_disable_accept_events
#undef ne_enable_read_events
#undef ne_disable_read_events
#undef ne_enable_write_events
#undef ne_disable_write_events
#undef ne_enable_watch_events
#undef ne_enable_display_events
#undef ne_disable_display_events
#undef ne_display_events_enabled
#undef ne_initialize_display_events
#undef g2_event_cycle
#undef g2_event_wait
#undef g2_event_ready
#undef ne_initialize_event_handling
#undef ne_print_events
#undef ne_sprint_events
#undef ne_lookup_handle_for_fd
#undef ne_enqueue_scheduler_event
#undef ne_set_next_timer_event
#undef ne_last_error_length
#undef ne_last_error_string

#endif

#if defined(Q_NE)

#define ne_initialize_network_interface q_ne_initialize_network_interface
#define ne_map_fd_to_handle q_ne_map_fd_to_handle
#define ne_unmap_fd q_ne_unmap_fd
#define ne_connect_ni q_ne_connect_ni
#define ne_register_active_ni q_ne_register_active_ni
#define ne_deregister_inactive_ni q_ne_deregister_inactive_ni
#define ne_enable_read_events q_ne_enable_read_events
#define ne_disable_read_events q_ne_disable_read_events
#define ne_enable_write_events q_ne_enable_write_events
#define ne_disable_write_events q_ne_disable_write_events
#define ne_enable_watch_events q_ne_enable_watch_events
#define ne_enable_display_events q_ne_enable_display_events
#define ne_disable_display_events q_ne_disable_display_events
#define ne_display_events_enabled q_ne_display_events_enabled
#define ne_initialize_display_events q_ne_initialize_display_events
#define g2_event_cycle q_g2_event_cycle
#define g2_event_wait q_g2_event_wait
#define g2_event_ready q_g2_event_ready
#define ne_initialize_event_handling q_ne_initialize_event_handling
#define ne_print_events q_ne_print_events
#define ne_sprint_events q_ne_sprint_events
#define ne_lookup_handle_for_fd q_ne_lookup_handle_for_fd
#define ne_enqueue_scheduler_event q_ne_enqueue_scheduler_event
#define ne_set_next_timer_event q_ne_set_next_timer_event
#define ne_last_error_length q_ne_last_error_length
#define ne_last_error_string q_ne_last_error_string

#include "eventfns.h"

#undef ne_initialize_network_interface
#undef ne_map_fd_to_handle
#undef ne_unmap_fd
#undef ne_connect_ni
#undef ne_register_active_ni
#undef ne_deregister_inactive_ni
#undef ne_enable_accept_events
#undef ne_disable_accept_events
#undef ne_enable_read_events
#undef ne_disable_read_events
#undef ne_enable_write_events
#undef ne_disable_write_events
#undef ne_enable_watch_events
#undef ne_enable_display_events
#undef ne_disable_display_events
#undef ne_display_events_enabled
#undef ne_initialize_display_events
#undef g2_event_cycle
#undef g2_event_wait
#undef g2_event_ready
#undef ne_initialize_event_handling
#undef ne_print_events
#undef ne_sprint_events
#undef ne_lookup_handle_for_fd
#undef ne_enqueue_scheduler_event
#undef ne_set_next_timer_event
#undef ne_last_error_length
#undef ne_last_error_string

#endif

#ifdef SN_NE
#define CALL_NE(s,n,q,args)         (ne_use_sck)?s args: n args
#define CALL_NE_VOID(s,n,q,args) if (ne_use_sck) s args; else n args
#else
#ifdef S_NE
#define CALL_NE(s,n,q,args) s args
#endif
#ifdef N_NE
#define CALL_NE(s,n,q,args) n args
#endif
#ifdef Q_NE
#define CALL_NE(s,n,q,args) q args
#endif
#define CALL_NE_VOID(s,n,q,args) CALL_NE(s,n,q,args)
#endif

int ne_use_sck = TRUE;

void ne_initialize_network_interface(network_intfc)
  NETWORK_INTERFACE *network_intfc;
{
  CALL_NE_VOID(g2ext_s_ne_initialize_network_interface,
	       n_ne_initialize_network_interface,
	       q_ne_initialize_network_interface,
	       (network_intfc));
}

void ne_map_fd_to_handle(fd, ni_handle)
   fd_type fd;
   G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_map_fd_to_handle,
	       n_ne_map_fd_to_handle,
	       q_ne_map_fd_to_handle,
	       (fd, ni_handle));
}

G2pointer ne_unmap_fd(fd)
    fd_type fd;
{
  return CALL_NE(g2ext_s_ne_unmap_fd,
		 n_ne_unmap_fd,
		 q_ne_unmap_fd,
		 (fd));
}

void ne_connect_ni(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_connect_ni,
	       n_ne_connect_ni,
	       q_ne_connect_ni,
	       (ni_handle));
}

void ne_register_active_ni(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_register_active_ni,
	       n_ne_register_active_ni,
	       q_ne_register_active_ni,
	       (ni_handle));
}

void ne_deregister_inactive_ni(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_deregister_inactive_ni,
	       n_ne_deregister_inactive_ni,
	       q_ne_deregister_inactive_ni,
	       (ni_handle));
}

void ne_enable_accept_events(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_enable_accept_events,
	       n_ne_enable_accept_events,
	       q_ne_enable_accept_events,
	       (ni_handle));
}

void ne_disable_accept_events(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_disable_accept_events,
	       n_ne_disable_accept_events,
	       q_ne_disable_accept_events,
	       (ni_handle));
}

void ne_enable_read_events(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_enable_read_events,
	       n_ne_enable_read_events,
	       q_ne_enable_read_events,
	       (ni_handle));
}

void ne_disable_read_events(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_disable_read_events,
	       n_ne_disable_read_events,
	       q_ne_disable_read_events,
	       (ni_handle));
}

void ne_enable_write_events(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_enable_write_events,
	       n_ne_enable_write_events,
	       q_ne_enable_write_events,
	       (ni_handle));
}

void ne_disable_write_events(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(g2ext_s_ne_disable_write_events,
	       n_ne_disable_write_events,
	       q_ne_disable_write_events,
	       (ni_handle));
}

void ne_enable_watch_events(ni_handle)
    G2pointer ni_handle;
{
  CALL_NE_VOID(s_ne_enable_watch_events,
	       n_ne_enable_watch_events,
	       q_ne_enable_watch_events,
	       (ni_handle));
}

void ne_enable_display_events()
{
  CALL_NE_VOID(g2ext_s_ne_enable_display_events,
	       n_ne_enable_display_events,
	       q_ne_enable_display_events,
	       ());
}

void ne_disable_display_events()
{
  CALL_NE_VOID(s_ne_disable_display_events,
	       n_ne_disable_display_events,
	       q_ne_disable_display_events,
	       ());
}

long ne_display_events_enabled()
{
  return CALL_NE(s_ne_display_events_enabled,
		 n_ne_display_events_enabled,
		 q_ne_display_events_enabled,
		 ());
}

void ne_initialize_display_events(window_connection_number)
    int window_connection_number;
{
  CALL_NE_VOID(s_ne_initialize_display_events,
	       n_ne_initialize_display_events,
	       q_ne_initialize_display_events,
	       (window_connection_number));
}


/* All of the following are called by translated lisp code, too. */
long g2_event_cycle(wait_allowed)
    long wait_allowed;
{
  return CALL_NE(g2ext_s_g2_event_cycle,
		 n_g2_event_cycle,
		 q_g2_event_cycle,
		 (wait_allowed));
}

void g2_event_wait()
{
  CALL_NE_VOID(g2ext_s_g2_event_wait,
	       n_g2_event_wait,
	       q_g2_event_wait,
	       ());
}

long g2_event_ready(wait_allowed)
    long wait_allowed;
{
  return CALL_NE(g2ext_s_g2_event_ready,
		 n_g2_event_ready,
		 q_g2_event_ready,
		 (wait_allowed));
}


void ne_initialize_event_handling()
{
  CALL_NE_VOID(g2ext_s_ne_initialize_event_handling,
	       n_ne_initialize_event_handling,
	       q_ne_initialize_event_handling,
	       ());
}

void ne_print_events(ni)
  NETWORK_INTERFACE *ni;
{
  CALL_NE_VOID(g2ext_s_ne_print_events,
	       n_ne_print_events,
	       q_ne_print_events,
	       (ni));
}

void ne_sprint_events(buffer,ni)
  char *buffer;
  NETWORK_INTERFACE *ni;
{
  CALL_NE_VOID(g2ext_s_ne_sprint_events,
	       n_ne_sprint_events,
	       q_ne_sprint_events,
	       (buffer,ni));
}

G2pointer ne_lookup_handle_for_fd(fd)
    fd_type fd;
{
  return CALL_NE(g2ext_s_ne_lookup_handle_for_fd,
		 n_ne_lookup_handle_for_fd,
		 q_ne_lookup_handle_for_fd,
		 (fd));
}


void ne_enqueue_scheduler_event()
{
  CALL_NE_VOID(g2ext_s_ne_enqueue_scheduler_event,
	       n_ne_enqueue_scheduler_event,
	       q_ne_enqueue_scheduler_event,
	       ());
}

void ne_set_next_timer_event(milliseconds_to_go)
    long milliseconds_to_go;
{
  CALL_NE_VOID(g2ext_s_ne_set_next_timer_event,
	       n_ne_set_next_timer_event,
	       q_ne_set_next_timer_event,
	       (milliseconds_to_go));
}

long ne_last_error_length(ni_handle)
    long ni_handle;
{
  return CALL_NE(g2ext_s_ne_last_error_length,
		 n_ne_last_error_length,
		 q_ne_last_error_length,
		 (ni_handle));
}

void ne_last_error_string(handle, buffer)
    long handle;
    char *buffer;
{
  CALL_NE_VOID(g2ext_s_ne_last_error_string,
	       n_ne_last_error_string,
	       q_ne_last_error_string,
	       (handle, buffer));
}

/* Move from ntevents.c (win32 only) to here */
long handle_network_events = 0; 

void g2ext_set_handle_network_events (state)
   long state;
{	
	handle_network_events = state;
}
