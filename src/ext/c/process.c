/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 +
 + Module:      process.c
 +
 + CVS location: ext/c
 +
 + Copyright (C) 1986-2017 Gensym Corporation.
 +            All Rights Reserved.
 +
 + Author(s):   John Hodgkinson
 +
 + Description: This file contains the per-process licensing system for G2
 +      and Telewindows. The basic idea is that each image has a listener
 +      which responds to queries about the options of that image (runtime,
 +      restricted use, and the like).
 +
 + Key:
 +   +++++++ Module Header.   Used for file-wide information.
 +   %%%%%%% Section Header.  Used to delimit logical sections.
 +   ******* Function Header. Used to define a single function.
 +
 +   0000000 Externally visible function
 +   1111111 Internal (static) function
 +
 +   A function banner may contain the following:
 +      Multiply Defined       Function appears multiple times, each definition
 +                             for an #ifdef specified platform.
 +      Conditionally Defined  Defined for some but not all platforms
 +      Mixed Ifdefs           Single definition for function containing
 +                             platform specific code #ifdef's.
 +
 + File Organization:
 +   Section:      INCLUDE FILES
 +   Section:      DEFINES
 +   Section:      GLOBALS
 +   Section:      FUNCTION GROUP - Utility Functions
 +      license_strpos()                 1111111
 +      fill_nodename_buffer()           1111111 Multiply Defined
 +      license_listener_probe()         1111111 Conditionally Defined
 +      license_listen_assure()          1111111 Conditionally Defined
 +      license_connect_assure()         1111111 Conditionally Defined
 +      license_connect()                2222222 Multiply Defined
 +      license_write()                  2222222 Multiply Defined
 +      license_read()                   1111111 Multiply Defined
 +      parse_license_answer()           1111111
 +      stop_license_option_gathering()  1111111
 +      license_close_query()            2222222 Multiply Defined
 +      broadcast_license_option_query() 1111111 Multiply Defined
 +      parse_license_query()            1111111
 +      handle_license_option_query()    1111111 Conditionally Defined
 +      read_license_query()             1111111 Conditionally Defined
 +      read_license_answer()            2222222 Conditionally Defined
 +      license_option_answer()          1111111 Conditionally Defined
 +      handle_license_answer()          1111111 Conditionally Defined
 +      handle_license_query()           1111111 Conditionally Defined
 +   Section:      FUNCTION GROUP - Licensing
 +      cc_register_licensed_product()   0000000 Multiply Defined
 +      cc_license_listen()              0000000 Multiply Defined
 +      cc_license_close_listener()      0000000 Multiply Defined
 +      cc_count_licensed_processes()    0000000 Multiply Defined
 +      cc_accept_license_option_query() 0000000 Multiply Defined
 +
 + External Interface:
 +
 +      long     cc_register_licensed_product(product, option)
 +                 To be called once, when G2 or TW is launched, and before
 +                 license_listen() is called.  Arguments product and option
 +                 are strings.
 +
 +      long     cc_license_listen()
 +                 To be called once, when G2 or TW is launched.
 +
 +      long     cc_count_licensed_processes(product, option)
 +                 To be called once, when G2 or TW launches, and after
 +                 license_listen() is called.  Arguments product and option
 +                 are strings.
 +
 +      long     cc_accept_license_option_query()
 +                 To be called repeatedly, whenever G2 or TW processes its
 +                 network requests (in process-icp-sockets, as of 8/12/91).
 +
 +      long     cc_license_close_listener()
 +                 To be called once, when G2 or TW exits.  If G2 or TW exits
 +                 without calling this function, the process (in UNIX) or the
 +                 machine (in VMS) could get clogged with unusable listeners.
 +
 + Dependencies: none
 +
 + Notes:
 +
 +      8/12/91, jh: (1) There is no error checking yet.  Any problem is
 +   interpreted as an attempt to tamper with the licensing scheme, and G2 will
 +   shut down.  As long as we are correct about the reliability of UNIX
 +   sockets and VMS mailboxes, this is acceptable for now.
 +   -----
 +      8/12/91, jh: (2) There is no idling yet.  This is marginally acceptable
 +   for now, since G2 only loops without idling once in its lifetime, when it
 +   is counting the other processes on the system.
 +
 + Modifications:
 +   usage: All modifications to this file should be listed here, with most
 +          recent first. In general, modification comments should merely
 +          provide a reference to a detailed modification comment in the
 +          appropriate section/function header.
 +
 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      INCLUDE FILES
 %
 % Description:  All required include files are referenced here.
 %
 % Notes:
 %
 % Modifications:
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#if defined(WIN32)
#  include <windows.h>
#endif

#include "cprim.h"
#include "networks.h"

/* platform-independent includes */
#include <string.h>
#include <signal.h>
#include <errno.h>

#if !(defined(sun) && !defined(sparc))
#  include <stdlib.h>
#endif

#ifdef unix
#  include <fcntl.h>
#  include <sys/types.h>
#  include <sys/socket.h>
#  include <netinet/in.h>
#  include <sys/ioctl.h>
#  include <unistd.h>
#endif /* unix includes */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Section:      DEFINES
%
% Description:  Module specific macros defined in this section.
%
% Notes:
%
% Modifications:
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/* standalone for testing, usually commented out */
/* #define TESTING_PER_PROCESS 1 */

/* standalone for debugging, usually commented out */
/* #define DEBUGGING_PER_PROCESS 1 */

/* devious names to thwart images which retain global symbols */
/* foreign functions in SEQUENCES1 */
#define cc_register_licensed_product   g2ext_update_callback_frames
#define cc_license_listen              g2ext_reduce_sleep_tolerance
#define cc_count_licensed_processes    g2ext_frequently_typed_chars
#define cc_accept_license_option_query g2ext_cache_deferred_rules
#define cc_license_close_listener      g2ext_shift_rule_ordering
#define cc_license_event_pending_p     g2ext_invokation_updates_needed

/* platform-independent behavior */
#define MAX_LICENSED_IMAGES    200
#define LICENSE_GATHERING_INTERVAL 4 /* seconds */
#define LICENSE_MESSAGE_DELIMITER   ':'

/* platform-independent string sizes */
#define MAX_LICENSED_PRODUCT   25
#define MAX_LICENSED_OPTION    25
#define MAX_LICENSE_MESSAGE    80 /* any higher breaks VMS sys$qiow */
#define MAX_NODENAME           20

/* platform-independent return codes */
#define PER_PROCESS_SUCCESS     1
#define LICENSE_SOCKET_FAILURE -1


#if defined(unix)
#define BASE_LICENSE_LISTENER 22222
/*
 * LICENSE_FLAGS is a modifying argument to the UNIX system calls sendto and
 * recvfrom.  This argument specifies vanilla options (no out-of-band listening,
 * no peeking, etc).
 */
#define LICENSE_FLAGS 0

#endif /* unix defines */


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      GLOBALS
 %
 % Description:  Module specific typedefs, variables, & externs defined here
 %
 % Notes:
 %
 % Modifications:
 %
 %    11/15/93, jh:  Added a check for duplicate responses to per-process
 %  license queries.  This involved adding a global duplicate_address_array
 %  which contains all addresses from which a response has already been
 %  received.  This array is then checked in handle_license_answer() on VMS and
 %  in license_option_answer() in UNIX.  This is a fix for a bug that first
 %  surfaced in multi-processor Sparcs, where each processor has a separate
 %  Ethernet card. This causes UDP to send duplicate packets, and thereby
 %  threw off our process count.
 %   -----
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

#if defined(unix)
struct sockaddr_in     remote_address_info;
#endif /* unix structs */



char    this_image_product[MAX_LICENSED_PRODUCT];
char    this_image_option[MAX_LICENSED_OPTION];

int     gathering_license_answers;

void    (*old_handler)(); /* int, not void, on some platforms */

char     nodename_buffer[MAX_NODENAME + 1];

#define LENGTH_OF_DUPLICATE_ARRAY 100
#define duplicate_address_array cached_foreign_image_ipc_ports
int     duplicate_address_array[LENGTH_OF_DUPLICATE_ARRAY];
#define next_unused_duplicate_index next_unused_foreign_ipc_port
int     next_unused_duplicate_index = 0;

extern int g2ext_licensing_event_flag;
extern int g2ext_license_socket;

extern long g2pvt_initialize_network_interface();

#if defined(unix)

int      license_address = LICENSE_SOCKET_FAILURE;

G2pointer license_g2pointer = LICENSE_SOCKET_FAILURE;
int      license_index = LICENSE_SOCKET_FAILURE;

int      query_socket = LICENSE_SOCKET_FAILURE;

static char message_buffer[MAX_LICENSE_MESSAGE] = { 0 };

extern long g2ext_network_close(/* long */);  /* networks.c */
extern void ne_map_fd_to_handle(/* fd_type, G2pointer */);  /* sckevent.c */
extern void ne_register_active_ni(/* G2pointer */);

#endif /* unix globals */

#if defined(WIN32)
static HANDLE hMap, hMap2;
extern HANDLE g2pvt_mutex;
#endif



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Utilities
 %
 % Description:
 %      These are helper functions for the licensing code.
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * int license_strpos(char *string, char *element)
 *
 *   Description:
 *     Finds the given substring in the given string
 *   Input Arguments:
 *     string
 *     element
 *   Returns:
 *     Substring location on success, -1 on Failure
 *   Notes:
 *     strpos is not available in ANSI (why?)
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static int license_strpos(string, element)
    char    *string;
    char     element;
{
  int     i = 0;

  /* GENSYMCID-1620: G2 abort on Linux, when no users are connected
     limit loop times within MAX_LICENSE_MESSAGE */
  while (string && i < MAX_LICENSE_MESSAGE) {
    if (string[0] == element)
      return i;
    string++;
    i++;
  }
  return -1;
}

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 * int fill_nodename_buffer()
 *
 *   Description:
 *     Puts the current nodename into the global nodename_buffer.
 *   Input Arguments: none
 *   Returns:
 *   Notes:
 *   Modifications:
 *****************************************************************************/
#if defined(unix)

static int fill_nodename_buffer()
{
  int     status;

  nodename_buffer[0] = '\0';
  status = gethostname(nodename_buffer, MAX_NODENAME);
  return status;
}

#endif


/*****************************************************************************
 * int license_connect( int socket_index)
 *
 *   Description:
 *     Called when the image wants to query a remote image for its
 *     authorization characteristics
 *   Input Arguments: none
 *   Returns:
 *   Notes:
 *       license_connect is called when the image wants to query a remote
 *     image for its authorization characteristics.  license_connect creates
 *     a "query socket", bound to a global variable, which a subsequent call
 *     to license_write uses to communicate with the remote image.
 *     ------
 *       We needn't make this socket non-blocking, since it is shut down
 *     immediately after the query and the reply is sent to the listener of the
 *     G2 being counted. Note that the default behavior is to deliver the
 *     information after the sending socket has been shut down.
 *     ------
 *   Modifications:
 *     3/16/93, mes: Replaced the bzero() call with the MEMZERO macro defined
 *     in cprim.h.
 *     ------
 *****************************************************************************/

/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/
#if defined(unix)

static int license_connect(socket_index) /* unix version */
  int     socket_index;
{
  int     sock;

  /* Create a UDP socket.  Fail if we can't do so. */
  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    query_socket = LICENSE_SOCKET_FAILURE;
    return 0;
  }

  /* Try to bind the socket to the address.  */
  MEMZERO(&remote_address_info, sizeof(remote_address_info));
  remote_address_info.sin_family = AF_INET;
  remote_address_info.sin_addr.s_addr = htonl(INADDR_ANY);
  remote_address_info.sin_port = htons(socket_index + BASE_LICENSE_LISTENER);

  query_socket = sock;
  return 0;
}

#endif /* unix license_connect */
/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/

/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/
#if defined(WIN32)

static int license_connect(socket_index)
  int     socket_index;
{
  return 0;
}

#endif /* Win32 license_connect */
/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/


/*****************************************************************************
 * int license_write(char *buff)
 *
 *   Description:
 *     writes to the query socket
 *   Input Arguments:
 *     buff
 *   Returns:
 *     returns: the number of bytes written if successful
 *              a non-positive integer if not.
 *   Notes:
 *       license_write always writes to the query socket, and thus only needs
 *     a single argument, the message to be written.
 *     ------
 *       Note that UNIX license_write uses remote_address_info, a global which
 *     is set up by license_connect immediately before the call to
 *     license_write.
 *     ------
 *       Note that remote_address_info has been filled in by the most recent
 *     call to license_connect(), so the sequence licence_connect ->
 *     license_write had better be atomic.
 *     ------
 *       VMS license_write always writes to a query_mailbox, since we only
 *     keep one outgoing mailbox at a time.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/
#if defined(unix)

static int license_write(buff) /* unix version */
  char     *buff;
{
  return sendto(query_socket,
                buff,
                strlen(buff),
                LICENSE_FLAGS,
                (struct sockaddr *) &remote_address_info,
                sizeof(remote_address_info));
}

#endif /* unix license_write */
/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/

/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/
#if defined(WIN32)

static int license_write(buff)
  char     *buff;
{
  return (strlen(buff));
}

#endif /* Win32 license_write */



/*****************************************************************************
 * int license_read()
 *
 *   Description:
 *     reads from the query socket
 *   Input Arguments:
 *     none
 *   Returns:
 *     return val: a nonnegative integer if it succeeds
 *              LICENSE_SOCKET_FAILURE if it fails
 *   Notes:
 *      Even though we pass a NULL to recvfrom, indicating that we don't care
 *     about the address, we have to declare from_address and pass its location
 *     for value-return.
 *     ------
 *       VMS license_read always reads from license_mailbox.  Note that this is
 *     an asynchronous read in VMS (as opposed to a non-blocking read in UNIX).
 *     When the VMS read returns, handle_license_read services it.  In UNIX, we
 *     have to keep polling.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*11111111111111111111111111 Multiply Defined 1111111111111111111111111111111*/
#if defined(unix)

static int license_read() /* unix version */
{
  int     from_address = 0;

  return recvfrom(g2ext_license_socket,
                  message_buffer,
                  MAX_LICENSE_MESSAGE,
                  LICENSE_FLAGS,
                  NULL,
                  &from_address);
}

#endif /* unix license_read */
/*11111111111111111111111111 Multiply Defined 1111111111111111111111111111111*/

/*11111111111111111111111111 Multiply Defined 1111111111111111111111111111111*/
#if defined(WIN32)

static int license_read()
{
  return 0;
}

#endif /* Win32 license_read */
/*11111111111111111111111111 Multiply Defined 1111111111111111111111111111111*/

/*****************************************************************************
 * void parse_license_answer(char *answer, int *answer_loc, int *address_loc)
 *
 *   Description:
 *     sets integer locations answer_loc and address_loc appropriately.
 *   Input Arguments:
 *     answer:      a string of the form "ANSWER:<boolean>:<return address>"
 *     answer_loc
 *     address_loc
 *   Returns:
 *     nothing
 *   Notes:
 *     ------
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void parse_license_answer(answer, answer_loc, address_loc)
  char     *answer;
  int      *answer_loc;
  int      *address_loc;
{
  char     *address;
  int       position;

  address = strrchr(answer, LICENSE_MESSAGE_DELIMITER);
  sscanf(&address[1], "%d", address_loc);

  answer = strchr(answer, LICENSE_MESSAGE_DELIMITER);
  answer = &answer[1];
  position = license_strpos(answer, LICENSE_MESSAGE_DELIMITER);
  if (-1 == position) return;

  answer[position] = '\0';
  sscanf(answer, "%d", answer_loc);
}

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 *   stop_license_option_gathering(int code)
 *
 *   Description:
 *     the signal handler which tells count_licensed_processes to time out.
 *   Input Arguments:
 *     answer:      a string of the form "ANSWER:<boolean>:<return address>"
 *   Returns:
 *     return val:
 *   Notes:
 *     ------
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void stop_license_option_gathering(code)
  int     code;
{
# ifdef DEBUGGING_PER_PROCESS
    printf("out-of-band stop\n");
# endif

  gathering_license_answers = 0;
}

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 * int license_close_query()
 *
 *   Description:
 *
 *   Input Arguments:
 *     none.
 *   Returns:
 *     return val:
 *   Notes:
 *       VMS license_close_query always closes the query_mailbox, since we only
 *     keep one outgoing mailbox open at a time.  Note that closing the channel
 *     to the query_mailbox will not affect it on the other end, so it will be
 *     able to read the message we put there before we closed the channel on
 *     this end.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/
#ifdef unix

static int license_close_query() /*unix*/
{
  close(query_socket);
  return 1;
}

#endif
/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/

/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/
#if defined(WIN32)

static int license_close_query() /*Win32*/
{
  return 1;
}

#endif
/*22222222222222222222222222 Multiply Defined 2222222222222222222222222222222*/


/*****************************************************************************
 * void broadcast_license_option_query(char *product, char *option)
 *
 *   Description:
 *     writes a query to a G2 process listening at other_address.
 *   Input Arguments:
 *     none
 *   Returns:
 *     nothing
 *   Notes:
 *       Since the listening process may receive multiple queries, a
 *     query contains the return address of the inquring process.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*11111111111111111111111111 Multiply Defined 1111111111111111111111111111111*/
#if defined(unix)

static void broadcast_license_option_query(product, option)
  char     *product;
  char     *option;
{
  int      other_address;
  int      other_index;

  fill_nodename_buffer();

  for (other_address = BASE_LICENSE_LISTENER, other_index = 0;
       other_address < BASE_LICENSE_LISTENER + MAX_LICENSED_IMAGES;
       other_address++, other_index++) {
    if (other_index != license_index) {
      license_connect(other_index);

      if (query_socket != LICENSE_SOCKET_FAILURE) {
        char     query_buff[MAX_LICENSE_MESSAGE];

        sprintf(query_buff, "QUERY%c%s%c%s%c%s%c%d",
                LICENSE_MESSAGE_DELIMITER, product,
                LICENSE_MESSAGE_DELIMITER, option,
                LICENSE_MESSAGE_DELIMITER, nodename_buffer,
                LICENSE_MESSAGE_DELIMITER, license_address);

        license_write(query_buff);
        /* See note under license_close about why it's OK to close the socket
         * immediately after a write.
         */
        license_close_query();

      } /* if != LICENSE_SOCKET_FAILURE */
    } /* if other_address != license_address */
  } /* for other_address from BAS_LICENSE_LISTENER */
} /* broadcast_license_option_query */

#endif


/*****************************************************************************
 * void parse_license_query(char *query, char *product_buff,
 *                           char *option_buff, char *nodename_buff,
 *                           int *address_loc)
 *
 *   Description:
 *     takes a query string and appropriately fills buffers
 *   Input Arguments:
 *     query:        a string of the form
 *                   "QUERY:<product>:<option>:<nodename>:<return address>"
 *     product_buff
 *     option_buff
 *     nodename_buff
 *     address_loc
 *   Returns:
 *     nothing
 *   Notes:
 *     ------
 *   Modifications:
 *****************************************************************************/

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

static void parse_license_query(query, product_buff, option_buff, nodename_buff, address_loc)
  char     *query;
  char     *product_buff;
  char     *option_buff;
  char     *nodename_buff;
  int      *address_loc;
{
  char     *address;
  int       position;

  address = strrchr(query, LICENSE_MESSAGE_DELIMITER);
  sscanf(&address[1], "%d", address_loc);

  query = strchr(query, LICENSE_MESSAGE_DELIMITER);
  query = &query[1];
  position = license_strpos(query, LICENSE_MESSAGE_DELIMITER);
  if (-1 == position) return;

  query[position] = '\0';
  strcpy(product_buff, query);
  query[position] = LICENSE_MESSAGE_DELIMITER;

  query = strchr(query, LICENSE_MESSAGE_DELIMITER);
  query = &query[1];
  position = license_strpos(query, LICENSE_MESSAGE_DELIMITER);
  if (-1 == position) return;

  query[position] = '\0';
  strcpy(option_buff, query);
  query[position] = LICENSE_MESSAGE_DELIMITER;

  query = strchr(query, LICENSE_MESSAGE_DELIMITER);
  query = &query[1];
  position = license_strpos(query, LICENSE_MESSAGE_DELIMITER);
  if (-1 == position) return;

  query[position] = '\0';
  strcpy(nodename_buff, query);
  query[position] = LICENSE_MESSAGE_DELIMITER;
}

/*111111111111111111111111111111111111111111111111111111111111111111111111111*/

/*****************************************************************************
 * void handle_license_option_query(char *query_buff)
 *
 *   Description:
 *     answers the querying image
 *   Input Arguments:
 *     query_buff
 *   Returns:
 *     nothing
 *   Notes:
 *     ------
 *   Modifications:
 *****************************************************************************/

/*11111111111111111111111 Conditionally Defined 11111111111111111111111111111*/
#if defined(unix)

static void handle_license_option_query(query_buff)
  char     *query_buff;
{
  char     product[MAX_LICENSED_PRODUCT];
  char     option[MAX_LICENSED_OPTION];
  char     nodename[MAX_NODENAME];
  int      address;
  int      answer = 0;
  char     answer_buff[MAX_LICENSE_MESSAGE];

  parse_license_query(query_buff, product, option, nodename, &address);

  /* There are scenarios where we shouldn't cache this, like when UU
   * transplants a dumped core.
   */
  fill_nodename_buffer();

  if (!strcmp(product, this_image_product) &&
      !strcmp(option, this_image_option) &&
      !strcmp(nodename, nodename_buffer))
    answer = 1;

  sprintf(answer_buff, "ANSWER%c%d%c%d",
          LICENSE_MESSAGE_DELIMITER, answer,
          LICENSE_MESSAGE_DELIMITER, license_address);

  license_connect(address - BASE_LICENSE_LISTENER);
  if (query_socket != LICENSE_SOCKET_FAILURE) {
    license_write(answer_buff);
    /* See note under license_close about why it's OK to close the socket
     * immediately after a write.
     */
    license_close_query();
  } else {
    /* printf("connect failed in handle_license_option_query, errno %d\n", errno); */
  }
}

#endif
/*11111111111111111111111 Conditionally Defined 11111111111111111111111111111*/

/*****************************************************************************
 * void read_license_query(read_socket)
 *
 *   Description:
 *
 *   Input Arguments:
 *     read_socket
 *   Returns:
 *     nothing
 *   Notes:
 *       UNIX read_license_query doesn't expect to read an answer, since any
 *     answer that it gets must have arrived after it timed out.  Thus it only
 *     takes action if it sees a "QUERY" tag at the beginning of the message.
 *     (Cf read_license_answer.)
 *     ------
 *   Modifications:
 *****************************************************************************/

/*11111111111111111111111 Conditionally Defined 11111111111111111111111111111*/
#if defined(unix)

static void read_license_query(read_socket) /* unix only */
  int      read_socket;
{
  if (license_read() > 0) {
    int position;

    position = license_strpos(message_buffer, LICENSE_MESSAGE_DELIMITER);
    /* GENSYMCID-1620: G2 abort on Linux, when no users are connected
       if above position is invalid, return directly. */
    if (-1 == position) return;

    message_buffer[position] = '\0';

    if (!strcmp(message_buffer, "QUERY")) {
      message_buffer[position] = LICENSE_MESSAGE_DELIMITER;
      handle_license_option_query(message_buffer);
    }
  }
}

#endif
/*11111111111111111111111 Conditionally Defined 11111111111111111111111111111*/

/*****************************************************************************
 * void read_license_answer(int read_socket, int *answer_loc, int *address_loc)
 *
 *   Description:
 *     read from a socket and dispatch on the type of message read
 *   Input Arguments:
 *     read_socket:
 *     answer_loc:
 *     address_loc:
 *   Returns:
 *     nothing
 *   Notes:
 *       It has to dispatch because a query could arrive while it is in the
 *     middle of gathering answers to its own query.  To keep things simple,
 *     read_license_answer does a value-return when it receives an answer and
 *     so requires arguments answer_loc and address_loc.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*22222222222222222222222 Conditionally Defined 22222222222222222222222222222*/
#ifdef unix

static void read_license_answer(read_socket, answer_loc, address_loc) /* unix version */
  int      read_socket;
  int     *answer_loc;
  int     *address_loc;
{
  if (license_read() > 0) {
    int     position;

    position = license_strpos(message_buffer, LICENSE_MESSAGE_DELIMITER);
    if (-1 == position) return;

    message_buffer[position] = '\0';

    if (!strcmp(message_buffer, "ANSWER")) {
      message_buffer[position] = LICENSE_MESSAGE_DELIMITER;
      parse_license_answer(message_buffer, answer_loc, address_loc);
    } else if (!strcmp(message_buffer, "QUERY")) {
      message_buffer[position] = LICENSE_MESSAGE_DELIMITER;
      handle_license_option_query(message_buffer);
    }
  }
}

#endif
/*22222222222222222222222 Conditionally Defined 22222222222222222222222222222*/

/*****************************************************************************
 * int license_option_answer()
 *
 *   Description:
 *
 *   Input Arguments:
 *     none
 *   Returns:
 *     return val:  1 if a remote G2 has authorization
 *                  Otherwise, it returns 0
 *   Notes:
 *       address could also eventually serve as a hook for implementing a
 *     better license_close (q.v.) if it turns out we have to.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*11111111111111111111111 Conditionally Defined 11111111111111111111111111111*/
#ifdef unix

static int license_option_answer()
{
  int     answer = 0;
  int     address = 0;

  read_license_answer(g2ext_license_socket, &answer, &address);
  if (answer) {
    int     i;

    for (i = 0; i < next_unused_duplicate_index; i++)
      if (duplicate_address_array[i] == address)
        return 0;
    if (next_unused_duplicate_index < LENGTH_OF_DUPLICATE_ARRAY)
      duplicate_address_array[next_unused_duplicate_index++] = address;
    return answer;
  } else
    return answer;
}

#endif


/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Licensing
 %
 % Description:
 %      These are the licensing functions
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/

/*****************************************************************************
 * long cc_register_licensed_product(char *product, char *option)
 *
 *   Description:
 *
 *   Input Arguments:
 *     none
 *   Returns:
 *     return val: PER_PROCESS_SUCCESS
 *   Notes:
 *     ------
 *   Modifications:
 *****************************************************************************/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(WIN32)

extern long g2ext_write_string_to_console(char *str);

long cc_register_licensed_product(product, option)
     char     *product;
     char     *option;
{
    int i;
    char mapname[128];
    DWORD dwWaitResult = WAIT_FAILED;

    g2ext_license_socket = LICENSE_SOCKET_FAILURE;

    g2pvt_mutex = CreateMutex(NULL,        // no security attributes
                              FALSE,        // initially not owned
                              "G2Mutex"); // name of mutex

    /* Find the first open slot and create a file mapping. */
    for(i=1; i<=MAX_LICENSED_IMAGES && hMap == NULL; i++) {
        sprintf(mapname, "%s:%s:%d", product, option, i);

        /* First, make sure nobody's counting while we register ours. */
        if (g2pvt_mutex != NULL)
          dwWaitResult = WaitForSingleObject(g2pvt_mutex, /* handle to mutex */
                                             500L);  /* half-second time-out interval */

        hMap = CreateFileMapping( (HANDLE)0xffffffff, NULL, PAGE_READONLY,
                                 0, 32, mapname );

        if (hMap != NULL && GetLastError() == ERROR_ALREADY_EXISTS) {
            CloseHandle(hMap);
            hMap = NULL;
        }

        if (dwWaitResult == WAIT_OBJECT_0) /* We got the mutex, must release */
          if (! ReleaseMutex(g2pvt_mutex)) {
            g2ext_write_string_to_console("Failed to release mutex!");
          }

    }
    return PER_PROCESS_SUCCESS;
}
/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#else

long cc_register_licensed_product(product, option)
   char     *product;
   char     *option;
{
  g2ext_license_socket = LICENSE_SOCKET_FAILURE;

  strcpy(this_image_product, product);
  strcpy(this_image_option, option);

  return PER_PROCESS_SUCCESS;
}

#endif
/*****************************************************************************
 * int cc_license_event_pending_p()
 *
 *****************************************************************************/

int cc_license_event_pending_p()
{

#if defined(unix)
  return (g2ext_licensing_event_flag);
#else
  return (0);                        /* elsewhere, there are never "licensing events." */
#endif

}

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*****************************************************************************
 * long cc_license_listen()
 *
 *   Description:
 *
 *   Input Arguments: none
 *   Returns:
 *   Notes:
 *       The idea is that each process listens on a "license socket" throughout
 *     its lifespan, and issues process queries on a "query socket" once in its
 *     lifetime. Further, the queries are issued one at a time, so a single
 *     query socket is all that's necessary.  Note that we use the term
 *     "socket", even though the VMS implementation actually uses mailboxes,
 *     because the abstraction is closer in spirit to UNIX.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(unix)

long cc_license_listen() /* unix version */
{
  struct sockaddr_in     own_address_info;
  int                    port;
  int                    ioctl_status;
#if !defined(sparcsol) && !defined(linux)
  int                    non_blocking_flag = 1;
#endif

  /* Create a UDP socket.  Fail if we can't do so. */
  g2ext_license_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (g2ext_license_socket < 0)
    return LICENSE_SOCKET_FAILURE;

  license_g2pointer = g2pvt_initialize_network_interface(UDP, g2ext_license_socket,
                                                         "UDP", LISTEN_INTERFACE_STATUS,0);

  ne_map_fd_to_handle(g2ext_license_socket, license_g2pointer);

  if (license_g2pointer >= 0)
    ne_register_active_ni(license_g2pointer);

  /* Configure the socket so it won't block in recvfrom(). */
  ioctl_status = SET_NON_BLOCKING(g2ext_license_socket,non_blocking_flag);

  if (ioctl_status == -1)
    return LICENSE_SOCKET_FAILURE;

  /*
   * Try to bind the socket to make its address visible to other G2s.  Use the
   * first socket that we can bind (the unsuccessful sockets are probably
   * in use by other G2s).
   *
   * mes - 3/16/93: Replaced the bzero() call with the MEMZERO macro defined in
   * cprim.h.  MEMZERO was redefined only for sparcsol and should not change
   * the expansion for other platforms.
   */
  MEMZERO(&own_address_info,sizeof(own_address_info));
  own_address_info.sin_family = AF_INET;
  own_address_info.sin_addr.s_addr = htonl(INADDR_ANY);

  for (port = BASE_LICENSE_LISTENER;
       port < BASE_LICENSE_LISTENER + MAX_LICENSED_IMAGES;
       port++) {
    own_address_info.sin_port = htons(port);
    if (bind(g2ext_license_socket,
             (struct sockaddr *) &own_address_info,
             sizeof(own_address_info))
        >= 0) {
      license_index = port - BASE_LICENSE_LISTENER;
      license_address = port;
      return g2ext_license_socket;
    }
  }

  /* Fail if we were unable to bind any of the addresses reserved for license
   * sockets.
   */
  return LICENSE_SOCKET_FAILURE;
}

#endif /* unix license_listen() */
/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(WIN32)

long cc_license_listen()
{
    return 1;
}

#endif


/*****************************************************************************
 * long cc_license_close_listener()
 *
 *   Description:
 *     close the indicated socket
 *   Input Arguments:
 *     none
 *   Returns:
 *     return val: LICENSE_SOCKET_FAILURE if there was any problem
 *   Notes:
 *       Note that in the code below we close the socket immediately after
 *     reading or writing to it.  According to Stevens (UNIX Newtork
 *     Programming p 275), the UNIX kernel undertakes to deliver information
 *     left in a closed socket.  It is a bit unclear whether that applies to
 *     unreliable sockets like the datagram ones we use here, but it seems to
 *     work.  If we have problems in the future, we will have to implement one
 *     more message, which the querying process will send the answering
 *     process telling the answering process to shut down the socket through
 *     which it answered the query.  For the opposite direction, we can
 *     piggyback on the "ANSWER" message and shut down the socket when this is
 *     received.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(unix)

long cc_license_close_listener()
{
  if (-1 != license_g2pointer)
    g2ext_network_close(license_g2pointer);

  license_g2pointer = (G2pointer) -1;
  g2ext_license_socket = -1;
  return 1;
}

#endif /* unix license_close */
/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(WIN32)

long cc_license_close_listener()
{
#   if defined(WIN32)
       if (hMap)
          CloseHandle(hMap);
#   endif

    return 1;
}

#endif /* Win32 license_close */



/*****************************************************************************
 * long cc_count_licensed_processes(char *product, char *option)
 *
 *   Description:
 *
 *   Input Arguments:
 *     product:
 *     option:
 *   Returns:
 *     return val:
 *   Notes:
 *     ------
 *   Modifications:
 *****************************************************************************/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#ifdef unix

long cc_count_licensed_processes(product, option)
  char     *product;
  char     *option;
{
  int    count = 0;
  void   (*old_handler)(); /* int, not void, on some platforms */

  next_unused_duplicate_index = 0;

  broadcast_license_option_query(product, option);
  gathering_license_answers = 1;
  old_handler = signal(SIGALRM, stop_license_option_gathering);
  alarm(LICENSE_GATHERING_INTERVAL);

  while (gathering_license_answers) {
    count = count + license_option_answer();
  }

  signal(SIGALRM, old_handler);
  return count;
}

#endif /* unix count_licensed_processes */
/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(WIN32)

long cc_count_licensed_processes(product, option) /* Win32 version */
     char     *product;
     char     *option;
{
    int   count = 0;
    char  mapname[128];
    int   i;
    DWORD dwWaitResult = WAIT_FAILED;

    /* Loop thru all the possible file mapping names, tracking
     *  a count of ones that already exist.
     */
    for(i=1; i<=MAX_LICENSED_IMAGES; i++) {
        sprintf(mapname, "%s:%s:%d", product, option, i);

        /* Bug HQ-5399210 "G2 will not run despite available license":
           Avoid race by using mutex.  But don't panic about it if
           something bad happened during mutex initialization or if we
           don't actually ever get the lock.  The race is quite rare,
           and probably the mutex stuff is working.  If it's not, what
           can we really do about it?  Ignoring it will fall back to
           prior behavior. */

        if (g2pvt_mutex != NULL)
          dwWaitResult = WaitForSingleObject(g2pvt_mutex, /* handle to mutex */
                                             500L);  /* half-second time-out interval */

        hMap2 = CreateFileMapping( (HANDLE)0xffffffff, NULL, PAGE_READONLY,
                                  0, 32, mapname );

        if ((hMap2 != NULL && GetLastError() == ERROR_ALREADY_EXISTS) ||
            (GetLastError() == ERROR_ACCESS_DENIED)) {
          /* bug HQ-4735371: if the logon is another user we get access denied.*/
            count++;
        }

        if (hMap2)
            CloseHandle(hMap2);

        if (dwWaitResult == WAIT_OBJECT_0) /* We got the mutex, must release */
          if (! ReleaseMutex(g2pvt_mutex)) {
            g2ext_write_string_to_console("Could not release mutex!");
          }
    }

    /* 16-Jun-95, mpc: We should not include ourselves in the total. This
     * function is more appropriately  cc_count_OTHER_licensed_processes().
     */
    if (count)
        count--;

    return(count);
}

#endif /* Win32 count_licensed_processes */



/*****************************************************************************
 * long cc_accept_license_option_query()
 *
 *   Description:
 *     Called by process-icp-sockets so that a G2 always responds to licensing
 *     queries within a bounded time interval.
 *   Input Arguments:
 *     none.
 *   Returns:
 *     return val:
 *   Notes:
 *       accept_license_option_query is a no-op in VMS, since we do
 *     asynchronous reads there, and handle_license_read sets up its next call
 *     without outside intervention.
 *     ------
 *   Modifications:
 *****************************************************************************/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#ifdef unix

long cc_accept_license_option_query()
{
  read_license_query(g2ext_license_socket);
  return 1;
}

#endif /* unix accept_license_option_query */
/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/

/*00000000000000000000000000 Multiply Defined 0000000000000000000000000000000*/
#if defined(WIN32)

long cc_accept_license_option_query()
{
  return 1;
}

#endif



/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
 %
 % Section:      FUNCTION GROUP - Testing
 %
 % Description:
 %      These are the testing blocks
 %
 % Notes:
 %
 % Modifications:
 %   usage: Modifications in this header should be restricted to mentioning
 %      the addition or deletion of functions within this section. Actual
 %      function changes should be commented in the specific function's
 %      header.
 %
 %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/


/***********
 * Testing *
 ***********/

#ifdef TESTING_PER_PROCESS

#if defined(unix)

#define MAX_COUNTABLE_PROCESSES 100

int     countable_processes[MAX_COUNTABLE_PROCESSES];

/* cc -w -Dsparcsol process.c -o test -lsocket -lnsl # sparcsol 11/15/93 */

main(argc, argv) /* unix version */
int     argc;
char   *argv[];
{
 int    i;
 int    number_of_processes;
 int    processes_counted;
 int    fork_result = 1;

 if (argc < 2)
    printf("need number of processes to check\n");

 cc_license_listen();
 printf("base process listening at address %d, socket %d\n",
         license_address, g2ext_license_socket);

 number_of_processes = atoi(argv[1]);
 for (i = 0; i < number_of_processes; i++)
  {
   if ((fork_result = fork()) == 0)
      {/* child */
       printf("process #%d forked\n", i);
       /* every other process is "RUNTIME" */
       if (i % 2 == 1)
          cc_register_licensed_product("G2", "RUNTIME");
       else
          cc_register_licensed_product("G2", "RESTRICTED USE");
       cc_license_listen();
       printf("process #%d at address %d, socket %d\n",
              i, license_address, g2ext_license_socket);
       while (1)
        {
         /* should add some idling here ... */
         cc_accept_license_option_query();
        }
      }
   else
      {/* parent */
       countable_processes[i] = fork_result;
      }
  }

 sleep(2);

 if (fork_result != 0) /* parent */
    {
     printf("about to count processes ...\n");
     processes_counted =
      cc_count_licensed_processes("G2", "RUNTIME");
     printf("forked %d processes, counted %d process%s\n",
            number_of_processes,
            processes_counted,
            processes_counted == 1 ? "" : "es");
    }

 /*
  * Without this cleanup, all the children become orphans, the init
  * process becomes their parent, and thus the sockets they have open
  * persist until a reboot.  This can be disconcerting.
  */
 for (i = 0; i < number_of_processes; i++)
  {
   kill(countable_processes[i], SIGKILL);
  }
}

#endif /* unix main */



#if defined(WIN32)

/* Have to run separate processes on NT */

main(argc, argv) /* nt version */
     int     argc;
     char   *argv[];
{
 if (argc < 2)
    {
     printf("ntproc {counter | countee}");
     exit(0);
    }

 if (!strcmp(argv[1], "counter") ||
     !strcmp(argv[1], "COUNTER"))
    {
     int     count;

     printf("counter\n");

     cc_license_listen();
     printf("counter at address %d, socket %d\n",
             license_address, g2ext_license_socket);
     count = cc_count_licensed_processes("G2", "RUNTIME");
     printf("counted %d process%s\n", count, count == 1 ? "" : "es");
     cc_license_close_listener();
    }
 else if (!strcmp(argv[1], "countee") ||
          !strcmp(argv[1], "COUNTEE"))
    {
     if (argc > 2 &&
         (!strcmp(argv[2], "restricted") ||
          !strcmp(argv[2], "RESTRICTED")))
         cc_register_licensed_product("G2", "RESTRICTED USE");
     else
         cc_register_licensed_product("G2", "RUNTIME");

     cc_license_listen();
     printf("countee at address %d, socket %d\n",
             license_address, g2ext_license_socket);
     while(1)
      {
       cc_accept_license_option_query();
       Sleep(50);
      }
    }
 else
    {
     printf("can't handle command line arg \"%s\"\n\n", argv[1]);
     exit(0);
    }

 /* NT whines unless it gets the following */
 return 1;
}

#endif /* Win32 main */

#endif /* TESTING_PER_PROCESS */

