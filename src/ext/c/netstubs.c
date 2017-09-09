
#include "cprim.h"

int g2ext_licensing_event_flag;

/* The following functions are defined in windows.c */

int g2ext_countXEventsQueuedAlready()
{
  return 0;
}

int g2ext_is_XPendingp()
{
  return 0;
}

#if defined(WIN32)
/*****************************************************************************
 * BOOL g2pvt_is_dialog_message (MSG *pMsg)
 *
 *   Description:
 *   Input Arguments:
 *   Returns:
 *   Notes:
 *     This is function defined only for the UI but is called from the Windows
 *     event loop in ext/c/ntevent.c. So we define a stub here for the real
 *     function in ext/c/dialogs.c. -fmw, 5/19/04, jv, 5/24/04, yduj, 6/15/04
 *     Moved to netstubs.c, yduj, 3/23/05
 *     -----
 *   Modifications:
 *****************************************************************************/
BOOL g2pvt_is_dialog_message (MSG *pMsg)
{
  return FALSE;
}

/* These two variables are referred to in ntevent.c, and defined for real in
   twpro.c.  Stub them out here.  --yduJ, 8/30/04 */
BOOL Frame_is_MDI = FALSE;
HWND hwndClient = NULL;

/* This is referred to in cprim.c, and defined in msmain.c. */
long g2pvt_uuid_create (UUID *uuid)
{
  return 0L;
}

/* These two are also referred to in cprim.c, and defined in msmain.c. */
void g2pvt_windows_shutdown()
{}

void g2pvt_update_taskbar_status_area ()
{}

#endif

long g2ext_icmp_read(int ni_handle, char *buffer, long buflen, char* frombuf, long fbuflen, unsigned short *seqid)
{
  return -1;
}

long g2ext_icmp_open(char *host, char *dotted_addr, int buflen)
{
  return -1;
}

long g2ext_icmp_write(G2pointer ni_handle, int ttl, int id, int seq,
		      char *buffer, long buflen)
{
  return -1;
}
