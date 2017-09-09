/* these must match the codes used in lisp/network-event-handlers.lisp !!!  */


#if defined(WIN32)
#define NE_SCHEDULER_EVENT WM_APP+1 /* arbitrarily chosen; must be compiled for 4.0 NT */
#endif


#define NE_TIMER_ID 17		/* arbitrary number. */



#define MAX_NUMBER_OF_CONNECTIONS 1024

#define read_event 	     1
#define write_event	     2
#define connect_event        3    
#define accept_event         4
#define close_event          5
#define scheduler_event      6
#define display_event        7
#define read_and_block_event 8
#define watch_event          9
#define quit_event          10


/* this last is obviously not a bit field index :-| */
#define error_event     -1
/* when polling, for g2_event_ready */
#define no_event        0

#define	ENABLE_EVENT(n, p)	((p)->event_mask |= (1 << (n)))
#define	DISABLE_EVENT(n, p)	((p)->event_mask &= ~(1 << (n)))
#define	EVENT_ENABLED_P(n, p)	((p)->event_mask & (1 << (n)))
#define	ZERO_EVENT_MASK(p)	bzero((char *)(p), sizeof (*(p)))

/* second argument to ne_close_socket_handle() */
#define NE_SHUTDOWN_SOCKET 0
#define NE_RESET_SOCKET    1

#if defined(WIN32)
typedef unsigned int fd_type;
#else
typedef int fd_type;
#endif

#include "eventfns.h"
