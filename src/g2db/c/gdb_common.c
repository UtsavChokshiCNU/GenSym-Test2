/*================================================================
 * GDB_COMMON.C - GDB Layer-2                             [source]
 *================================================================
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-2 = gdb_common.c
 *    - receive requests from Layer-1
 *    - manage messaging and data manipulation
 *    - provide interface and error handler to Layer-3
 *    - populate GENDA (GENsym Descriptor Area)
 *    - all calls to L3 must be done from this layer
 *================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#if defined(UNICODE)
#include <wchar.h>
#endif

#if defined(WIN32)
# include <windows.h>
# include <sql.h>
# include <odbcss.h>
#else
# include <errno.h>
#endif

#include "gsi_main.h"
#include "gdb_globals.h"
#include "gdb_genda.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#include "gdb_g2_client.h"

#define LAYER   LAYER2

/* globals */
CONTEXT_INFO  context[MAX_GDB_CONTEXTS] ;

long    stmt_handle_arr [MAX_GDB_CONTEXTS][MAX_CURSORS+1] ;
long    debug             = DBG_DEFAULT ;
long    layer_debug       = DBGALL ;
long    end_of_cursor     = 0 ;
long    gbl_float_flag    = DFLT_FLOAT_FLAG ;
long    trim_log_msgs     = FALSE ;

gsi_int context_num ;

BRIDGE_INFO bridge_info ;
extern long  gdb_poll_check ;
extern void *g2rtl_Gc_silence ;
extern trig_struct trigger ;

/*======================================================================
  load_msg
    - get the message,code,status, etc from gdb_messages and
      package into event_msg format.

    Arguments:
    - severity_cd: ERROR_CD,WARN_CD,SUCCESS_CD,etc.
    - idx: GDB message 'constant' (e.g. EINSMEM)
    - msg_code: 9000+ GDB message code
    - msg_buff: the GDB message as detailed by 'action'
    - action: TRUE  = prefix + message (PREFIX_SZ + MSG_SZ)
              FALSE = prefix only      (PREFIX_SZ)

    Returns:
    - msg_code = the 9000+ GDB message code
    - returned msg_buff must be large enough to 
      handle the message based on the action below
      (no checking is done)
    - function returns length of message, 0 if no message
  ======================================================================*/
long load_msg(long severity_cd, long idx, long *msg_code, GDB_CHAR *msg_buff, long action)
{
    GDB_CHAR prefix_buff[PREFIX_SZ];
    long      status = FALSE ;

    context_num = gsi_current_context() ;

    *msg_buff = 0 ;
    *msg_code = 0 ;
    prefix_buff[0] = 0 ;

    switch (severity_cd)
    {
        case SUCCESS_CD :
                            *msg_code = 0 ;
                            *msg_buff = 0 ;
                            return 0 ;
                            break ;

        case ERROR_CD :
                            if (IN_RANGE(idx, MIN_MSG_ERROR, MAX_MSG_ERROR))
                                *msg_code = -(GDB_MSG_BASE + idx) ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %s: %s: "), wDB_TYPE, context[context_num].name, ERROR_SYM) ;
                            else
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %d: %s: "), wDB_TYPE, context_num, ERROR_SYM) ;
                            if (action)
                                _snwprintf(msg_buff, STATUS_MSG_LEN, _T("%s%s"), prefix_buff, MSG_ERROR[idx]);
                            break ;

        case FATAL_CD :
                            if (IN_RANGE(idx, MIN_MSG_ERROR, MAX_MSG_ERROR))
                                *msg_code = -(GDB_MSG_BASE + idx) ;
                            else if (action)
                                status = TRUE ;
    
                            if (context_num >=0 && context[context_num].name != NULL)
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %s: %s: "), wDB_TYPE, context[context_num].name, FATAL_SYM) ;
                            else
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %d: %s: "), wDB_TYPE, context_num, FATAL_SYM) ;
                            if (action)
                                _snwprintf(msg_buff, STATUS_MSG_LEN, _T("%s%s"), prefix_buff, MSG_ERROR[idx]) ;
                            break ;

        case WARN_CD :
                            if (IN_RANGE(idx, MIN_MSG_WARN, MAX_MSG_WARN))
                                *msg_code = GDB_MSG_BASE + idx ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %s: %s: "), wDB_TYPE, context[context_num].name, WARN_SYM) ;
                            else
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %d: %s: "), wDB_TYPE, context_num, WARN_SYM) ;
                            if (action)
                                _snwprintf(msg_buff, STATUS_MSG_LEN, _T("%s%s"), prefix_buff, MSG_WARN[abs(idx-MIN_MSG_WARN)]) ;
                            break ;
  
        case INFO_CD :
                            if (IN_RANGE(idx, MIN_MSG_INFO, MAX_MSG_INFO))
                                *msg_code = GDB_MSG_BASE + idx ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %s: %s: "), wDB_TYPE, context[context_num].name, INFO_SYM) ;
                            else
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %d: %s: "), wDB_TYPE, context_num, INFO_SYM) ;
                            if (action)
                                _snwprintf(msg_buff, STATUS_MSG_LEN, _T("%s%s"), prefix_buff, MSG_INFO[idx]) ;
                            break ;

        case EOCURSOR_CD :
                            if (IN_RANGE(IEOFETC, MIN_MSG_INFO, MAX_MSG_INFO))
                                *msg_code = GDB_MSG_BASE + IEOFETC ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL) {
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %s: "), wDB_TYPE, context[context_num].name);
			    } else {
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %d: "), wDB_TYPE, context_num);
			    }
                            if (action)
                                _snwprintf(msg_buff, STATUS_MSG_LEN, _T("%s%s"), prefix_buff, MSG_INFO[idx]) ;
                            break ;

        case NOCONNECT_CD :
                            if (IN_RANGE(ENODBCT, MIN_MSG_ERROR, MAX_MSG_ERROR))
                                *msg_code = GDB_MSG_BASE + idx ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %s: %s: "), wDB_TYPE, context[context_num].name, NOCONNECT_SYM) ;
                            else
                                _snwprintf(prefix_buff, PREFIX_SZ, _T("G2-%s: %d: %s: "), wDB_TYPE, context_num, NOCONNECT_SYM) ;
                            if (action)
                                _snwprintf(msg_buff, STATUS_MSG_LEN, _T("%s%s"), prefix_buff, MSG_ERROR[idx]) ;
                            break ;

        default:
                            printf("Invalid message type\n");
                            return 0 ;
    }

    if (status)
    {
        printf("Invalid message index\n") ;
        return (0) ;
    }
  
    if (!action && !status)
        wcscpy(msg_buff, prefix_buff) ;

    return (wcslen(msg_buff)) ;
}


/*======================================================================
  set_stat
    - load gbl_status[0] struct with messages
    - load genStat[] section of GENDA with messages

    Arguments:
    - status_id: ERROR_CD,WARN_CD,SUCCESS_CD,etc.
    - msg_id: GDB message 'constant' (e.g. EINSMEM)
    - sqlGen: Put message in GENDA if not NULL
    - row_reset: (TRUE=reset last_row_sent to 0,FALSE=dont touch)
    - msg_addr: (if msg_id == 0 use msg_addr and do not load_msg)
  ======================================================================*/
long set_stat(long status_id, long msg_id, GENDA *sqlGen, long row_reset, GDB_CHAR *msg_addr )
{
    GDB_CHAR   msg_buff[STATUS_MSG_LEN] ;
    long      msg_len ;
    long      msg_code ;
    long      row ;

    context_num = gsi_current_context() ;

    if (context[context_num].gbl_status.msg == NULL)
    {
        if ((context[context_num].gbl_status.msg = (GDB_CHAR*)XCALLOC(STATUS_MSG_LEN+1, sizeof(GDB_CHAR))) == NULL)
            return GDB_ERROR ;
    }

    msg_buff[0] = 0 ;
    msg_code = status_id ;

    /*** get the message and code ***/

    /* perform a load_msg to get the msg_code & msg_buff if applic */
    if (!msg_id)
        msg_buff[0] = 0 ;
    else
        load_msg(status_id, msg_id, &msg_code, msg_buff, TRUE) ;

    if (msg_addr != NULL)
    {
        msg_buff[0] = 0 ;
        wcscat(msg_buff, msg_addr) ;
    }

    if (msg_buff == NULL || *msg_buff == 0)
        msg_len = 0 ;
    else
        msg_len = wcslen(msg_buff) ;

    /*** load gbl_status struct ***/
    context[context_num].gbl_status.code = msg_code ;
    context[context_num].gbl_status.status = status_id ;

    *(context[context_num].gbl_status.msg) = 0 ;
    if (*msg_buff != 0)
        wcscpy(context[context_num].gbl_status.msg, msg_buff) ;

    if (row_reset) context[context_num].gbl_status.rows_processed = 0 ;

    /*** load the GENDA struct ***/
    if (sqlGen != NULL)
    {
        row = sqlGen->genda_pos ;

        /*** alloc genStat buffers ***/
        if (sqlGen->genStat.msg == NULL)
        {
            if ((sqlGen->genStat.msg = (GDB_CHAR *)XCALLOC(1, sizeof(GDB_CHAR))) == NULL)
                return GDB_ERROR ;
        }
        sqlGen->genStat.code = msg_code ;
        sqlGen->genStat.status = status_id ;
        if (msg_len == 0)
            *sqlGen->genStat.msg = 0;  /*"NULL"*/
        else
        {
            if ((sqlGen->genStat.msg = (GDB_CHAR*)realloc(sqlGen->genStat.msg, (msg_len+1)*sizeof(GDB_CHAR))) == NULL)
                return GDB_ERROR ;
            wcscpy(sqlGen->genStat.msg, msg_buff) ;
        }
        if (row_reset) sqlGen->genStat.rows_processed = 0 ;
    }

    if ((debug & DBG5) && status_id != 0)
    { 
        printf("\nSQL Message Structure\n") ;
        printf("ver   : %s\n", bridge_info.bridge_version) ;
        printf("code  : %d\n", status_id) ;

        wprintf(_T("msg   : %S\n"), msg_buff) ;

        printf("nrows : %d\n", context[context_num].gbl_status.rows_processed) ;
        printf("stat  : %d\n", status_id) ;
    }

    return GDB_SUCCESS ;
}


/*======================================================================
  iomsg
    - compose a message and print to screen
    - log the message to logfile if active

    Arguments:
    - flag: debug switch (e.g. DBG3)
    - layer: the module layer calling from
    - write_logfile: write to logfile if open
    - setstat: true=perform set_stat & return to RPC
    - sqlGen: Put message in GENDA if not NULL
    - row_reset: (TRUE=reset last_row_sent to 0,FALSE=dont touch)
    - va_alist: the dynamic argument list similar to printf
      style formatters (e.g. "%s%f")
        * if 0th arg is %d-stat_cd, then load the 
          gdb_message
        * if 0arg is %d-stat_cd and 1arg is supplied
          and 0arg does not contain placeholders (i.e. '%'), 
          replace 0arg msg with 1arg msg preserving codes & status.  
 ======================================================================*/
long iomsg (long flag, long layer, long write_logfile, long setstat, GENDA *sqlGen,
            long row_reset, char *argtypes, ...)
{
    va_list args ;
    GDB_CHAR subbuf[MAX_SUBS][STATUS_MSG_LEN+1] ;
    GDB_CHAR t_stamp[MAX_TIMESTAMP_LEN] ;
    GDB_CHAR *ptr1, *ptr2, *ptr3 ;
    char   *fptr ;
    GDB_CHAR *msg;
    GDB_CHAR *ts_format;
    long    len, n ;
    long    num ;
    long    status = SUCCESS_CD ;
    long    msg_len ;
    long    msg_code ;
    long    replace_cnt;
    long    tmp_code = 0 ;

    context_num = gsi_current_context() ;

    if (!(-layer & layer_debug) && flag != DBGALL) return (GDB_SUCCESS) ;

    /*** get arg types (e.g. %d) from the dynamic format list ***/
    va_start(args, argtypes) ;

    len = 0 ;
    num = 0 ;
    for (fptr = argtypes; *fptr; fptr++)
    {
        if (*fptr != '%')
            continue ;

        switch (fptr[1])
        {
        case 's':
                            wcsncpy(subbuf[num], va_arg(args, GDB_CHAR*), STATUS_MSG_LEN) ;
                            subbuf[num][STATUS_MSG_LEN] = 0 ;
                            num++ ;
                            break ;
        case 'd':
                            if (!num)
                            {
                                status = SUCCESS_CD ;
                                if (flag & DBG2) status = INFO_CD ;
                                if (flag & DBG4) status = WARN_CD ;
                                if (flag & DBG3) status = ERROR_CD ;
                                if (flag & DBGM) status = FATAL_CD ;
                                if (flag == EOCURSOR_CD) status = EOCURSOR_CD ;
                                tmp_code = va_arg(args, int) ;
                                load_msg(status, tmp_code, &msg_code, subbuf[num], TRUE) ;
                            }
                            else {
                                _snwprintf(subbuf[num], STATUS_MSG_LEN, _T("%d\0"), va_arg(args, int));
			    }
                            num++ ;
                            break ;
        case 'c':
                            _snwprintf(subbuf[num], STATUS_MSG_LEN, _T("%c\0"), va_arg(args, int));

                            num++ ;
                            break ;
        case 'f':
                            _snwprintf(subbuf[num], STATUS_MSG_LEN, _T("%f\0"), va_arg(args, wchar_t *));

                            num++ ;
                            break ;
        default:
                            printf("Invalid format argument specified\n") ;
                            break ;
        }
        len += wcslen(subbuf[num-1]) ;
    } 
    va_end(args) ;

    if (!len)
    {
        set_stat(SUCCESS_CD, NULL_MSG, sqlGen, FALSE, NULL) ;
        fflush(stdout) ;
        return GDB_SUCCESS ;
    }

    /* len equals length of source + all substitution strings */
    if ((msg = (GDB_CHAR *)XCALLOC(len+5, sizeof(GDB_CHAR))) == NULL)
    {
        if (debug & DBG3) wprintf(_T("%s\n"), MSG_ERROR[EINSMEM]);

        fflush(stdout) ;
        return GDB_ERROR ;
    }

  /*** replace msg_delim with args if they exist ***/

    replace_cnt = 0 ;
    if (num > 1 && len < MSG_SZ)
    {
        ptr1 = subbuf[0] ;
        ptr2 = msg ;
        ptr3 = subbuf[1] ;
        msg_len = 0 ;
        n = 1 ;

        while (*ptr1 != 0 && msg_len < MSG_SZ) 
        {
            if (*ptr1 == MSG_DELIM && n <= num)
            {
                replace_cnt++ ;
                ptr1++ ;
                while (*ptr3 != 0 && msg_len < MSG_SZ)
                {
                    *ptr2++ = *ptr3++ ;
                    msg_len++ ;
                }
                n++ ;
                ptr3 = subbuf[n] ;
            }
            else
            {
                *ptr2++ = *ptr1++ ;
                msg_len++ ;
            }
        }
        *ptr2 = 0 ;
    }
    else
        wcscpy(msg, subbuf[0]);

    /*** replace the gdb_message with custom message ***/
    if (num > 1 && replace_cnt == 0 && tmp_code != 0)
    {
        load_msg(status, tmp_code, &msg_code, msg, FALSE) ;
        wcscat(msg, subbuf[1]);
    }

    /*** prepare screen-printed message ***/
    ts_format = _T("");
    if (context_num >= 0 && context[context_num].iomsg_ts)
        ts_format = DFLT_TS_FMT;

    if (context_num < 0 || (context[context_num].console_output && (debug & flag) && flag != EOCURSOR_CD))
    {
        switch (abs(layer)) 
        {
        case LAYER1 :
	  if (layer < 0) {
	    wprintf(_T("L1: %s\n"), msg);
	  } else {
	    wprintf(_T("%s\n"), msg);
	  }
	  break ;

        case LAYER2 :
	  if (layer < 0) {
	    wprintf(_T("  L2: %s\n"), msg);
	  } else {  
	    wprintf(_T("  %s %s\n"), TIME_STAMP(ts_format, t_stamp), msg);
	  }
	  break ;

        case LAYER3 :
	  if (layer < 0) {
	    wprintf(_T("    L3: %s\n"), msg);
	  } else {
	    wprintf(_T("    %s %s\n"), TIME_STAMP(ts_format, t_stamp), msg);
	  }
	  break ;
        }
    }

    /*** perform a set_stat ***/
    if (setstat)
    {
        status = SUCCESS_CD ;
        if (flag & DBG2) status  = INFO_CD ;
        if (flag & DBG4) status  = WARN_CD ;
        if (flag & DBG3) status  = ERROR_CD ;
        if (flag & DBGM) status = FATAL_CD ;
        if (flag == EOCURSOR_CD) status = EOCURSOR_CD ;

        set_stat(status, tmp_code, sqlGen, row_reset, msg) ;
    }

    /*** filter logfile messages ***/
    if (context_num >= 0 && write_logfile && status != EOCURSOR_CD )
    {
        if (context[context_num].logfile_filter & flag)
            logfileio(F_WRITE, msg) ;
    }

    XFREE(msg) ;
    fflush(stdout) ;
    return GDB_SUCCESS ;
}


/*======================================================================
  logfileio
    - open,close,write to a text file if open
    - iostr is action dependent

    Arguments:
    - action: F_OPEN,F_CLOSE,F_WRITE
    - iostr: filename or output string,etc.
 ======================================================================*/
long logfileio (long action, GDB_CHAR *iostr)
{
    FILE*       fptr ;
    long        max_msg_len ;
    long        n ;
    long        status ;
    GDB_CHAR     t_stamp[MAX_TIMESTAMP_LEN] ;

    context_num = gsi_current_context() ;

    if (context[context_num].logfile_name == NULL)
        return GDB_ERROR ;

    max_msg_len = STATUS_MSG_LEN ;
    if (trim_log_msgs)
        max_msg_len = MAX_PAGE_WIDTH ;
    if (context[context_num].logfile_ts)
    {
        TIME_STAMP(DFLT_TS_FMT, t_stamp) ;
        max_msg_len -= (wcslen(t_stamp)+3) ;
    }

    switch (action) 
    {
    case F_OPEN :
                    if (iostr == NULL)
                    {
                        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d", ENOLOGN) ;
                        return GDB_ERROR ;
                    }
#if defined(WIN32) && defined(UNICODE)
                    if ((context[context_num].logfile_ptr = (FILE*)_wfopen(iostr, L"a")) == NULL )  /* Sparc Warning */
                    {
                        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d%s", ELOGOPN, context[context_num].logfile_name) ;
                        context[context_num].logfile_active = FALSE ;
                        return GDB_ERROR ;
                    }
#else
                    if ((context[context_num].logfile_ptr = (FILE*)fopen((char *)iostr, "a")) == NULL )  /* Sparc Warning */
                    {
                        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d%s", ELOGOPN, context[context_num].logfile_name) ;
                        context[context_num].logfile_active = FALSE ;
                        return GDB_ERROR ;
                    }
#endif
                    context[context_num].logfile_active = TRUE ;
                    for (n=0; n < MAX_PAGE_WIDTH; n++)
                    fputc('=', context[context_num].logfile_ptr) ;

                    fprintf(context[context_num].logfile_ptr, "\nG2-%s Bridge Logfile\n\n", DB_TYPE);

                    if (context[context_num].logfile_ts)
                    {
                        iomsg(DBG0, LAYER, FALSE, TRUE, NULL, FALSE, "%d%s", ILOGOPN, context[context_num].logfile_name);
                        fputs("Logfile Opened: ", context[context_num].logfile_ptr) ;

                        fputws(t_stamp, context[context_num].logfile_ptr) ;
                        fputs("\n", context[context_num].logfile_ptr) ;
                    }

                    for (n=0;n<MAX_PAGE_WIDTH;n++)
		      fputc('=', context[context_num].logfile_ptr) ;
		    fputs("\n\n", context[context_num].logfile_ptr) ;

		    fflush(context[context_num].logfile_ptr) ;
		    break ;

    case F_CLOSE :
                    if (!context[context_num].logfile_active)
                        break ;

                    fputs("\n", context[context_num].logfile_ptr);

                    if (context[context_num].logfile_ts) 
                    {
                        fputs("Logfile Closed: ", context[context_num].logfile_ptr) ;
                        fputws(t_stamp, context[context_num].logfile_ptr) ;
                        fputs("\n", context[context_num].logfile_ptr) ;
                    }

                    for (n=0;n<MAX_PAGE_WIDTH;n++)
		            fputc('=', context[context_num].logfile_ptr) ;
                    fputs("\n\n", context[context_num].logfile_ptr) ;

                    fflush(context[context_num].logfile_ptr) ;
                    if (fclose(context[context_num].logfile_ptr) != 0) 
                    {
                        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d%s", ELOGCLO, context[context_num]. logfile_name);
                        fputs("Error: Could not close logfile.\n", context[context_num].logfile_ptr);

                        return  GDB_ERROR ;
                    }
                    else
                    {
                        context[context_num].logfile_active = FALSE;

                        iomsg(DBG0, LAYER, FALSE, TRUE, NULL, FALSE, "%d%s", ILOGCLO, context[context_num].logfile_name);
                    }
                    break ;

    case F_WRITE :
                    if (!context[context_num].logfile_active)
                        break ;
                    if (((long)wcslen(iostr))+1 > max_msg_len)
                    iostr[max_msg_len] = 0 ;
                    if (context[context_num].logfile_ts) {
                        status = fprintf(context[context_num].logfile_ptr, "%s | ", t_stamp);
			status = fwprintf(context[context_num].logfile_ptr, _T("%s\n"), iostr);
		    } else {
                        status = fwprintf(context[context_num].logfile_ptr, _T("%s\n"), iostr);
		    }
                    fflush(context[context_num].logfile_ptr) ;
                    if (status < 0 || status == EOF) 
                    {
                        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d", ELOGWRI) ;
                        context[context_num].logfile_active = FALSE ;
                        return GDB_ERROR ;
                    }
                    break ;

    case F_EXISTS :
#if defined(WIN32) && defined(UNICODE)
      if ((fptr = (FILE*)_wfopen(iostr, L"r")) == NULL ) /* Sparc warning */
	return GDB_ERROR;
      else
	fclose(fptr);
      break;
#else
      if ((fptr = (FILE*)fopen((char *)iostr, "r")) == NULL ) /* Sparc warning */
	return GDB_ERROR;
      else
	fclose(fptr);
      break;
#endif

    case F_DELETE :
#if defined(WIN32) && defined(UNICODE)
      if (_wremove(iostr))
	return GDB_ERROR ;
      break;
#else
      if (remove(iostr))
	return GDB_ERROR;
      break;
#endif

    case F_FLUSH :
                    fflush(context[context_num].logfile_ptr) ;
                    break ;

    default :
                    iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d", EINVARG) ;
                    break ;
    }

    return GDB_SUCCESS ;
}


/*======================================================================
  init_genda
    - allocates info & status areas of GENDA,
        does not alloc data area
    - must be called before ALLOC_GENDA
    - return addr of new GENDA

    Arguments:
    - obj_handle: object handle
 ======================================================================*/
GENDA *init_genda(long obj_handle)
{
    GENDA    *sqlGen ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("INIT_GENDA")) ;
    
    /*** alloc 1 GENDA ***/
    if ((sqlGen = (GENDA *)XCALLOC(1, sizeof(GENDA))) == (GENDA *)NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return NULL ;
    }  
    
    /*** initialize GENDA info area ***/
    sqlGen->obj_handle = obj_handle ;
    sqlGen->stmt_id = 0 ;
    if (!context[context_num].genda_rows) 
        context[context_num].genda_rows = MAX_GENDA_ROWS ;
    sqlGen->nrows = context[context_num].genda_rows ;
    sqlGen->array_size = 0 ;
    sqlGen->bind_processed = FALSE ;
    sqlGen->more_rows = 0 ;
    sqlGen->genStat.rows_processed = 0 ;
    
    /*** initialize genStat buffers ***/
    sqlGen->genStat.code = 0 ;
    sqlGen->genStat.status = 0 ;
    
    /*** allocate the msg buffer for use with rpc status and pre-fetch errors */
    if ((sqlGen->genStat.msg = (GDB_CHAR*)XCALLOC(STATUS_MSG_LEN+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return NULL ;
    }
    
    if (alloc_sqlda_ptrs()) 
        return NULL ;
    
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    return sqlGen ;
}

void init_stmt_handle()
{
    int i, j;
    for(i=0; i<MAX_GDB_CONTEXTS; i++)
        for(j=0; j<MAX_CURSORS+1; j++)
            stmt_handle_arr[i][j] = HDL_FREE;
}

/*======================================================================
  get_stmt_handle
    - get or release a handle which is used as an index into global
      arrays and for statement-name naming.

    Arguments:
    - shandle: address of handle variable
    - action:  
        GET   = reserve "next" available stmt_handle
                (valid handles => 1 to max_cursors)              
        FREE  = release stmt_handle
 ======================================================================*/
long get_stmt_handle(long *shandle, long action)
{
    long    hdl ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("GET_STMT_HANDLE")) ;
    
    switch (action)
    {
    case HDL_FREE:
        if (*shandle < 0 || *shandle > MAX_CURSORS)
        {
            iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%d", EINVHDL) ;
            return GDB_ERROR ;
        }
        /* if *shandle == 0, do nothing */
        if (*shandle > 0) 
        {
            stmt_handle_arr[context_num][*shandle] = HDL_FREE ;
            if (debug & DBG6) {
                iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("FREE Statement Handle : %"), *shandle);
	    }
            *shandle = 0 ;
            return GDB_SUCCESS ;
        }
        break ;
        
    case HDL_GET :   
        hdl = 1 ;  /**** handles MUST start from 1 ****/
        while (hdl <= MAX_CURSORS)
        {  /* was MAX_CURSORS+1  ??????? */
            if (!stmt_handle_arr[context_num][hdl])
            {
                stmt_handle_arr[context_num][hdl] = HDL_INUSE ;
                *shandle = hdl ;
                if (debug & DBG6) {
                    iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GET Statement Handle : %"), *shandle);
		}
                return GDB_SUCCESS ;  
            }
            hdl++ ;
        }
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOHNDL) ;
        *shandle = 0 ;  /* CRITICAL::must be set to 0 on error */
        return GDB_ERROR ;
        break ;
        
    default:
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINVARG) ;
        break ;      
    }
    return GDB_ERROR ;
}

                              
/*======================================================================
  free_genda
    Arguments:
    - action:
       DATA_ONLY
         * XFREE the DATA area of GENDA
       ALL 
         * XFREE the ID & DATA areas of GENDA (should only
           be done when cursor is deleted)
         * release stmt_handle
    - sqlGen: XFREE GENDA data structure if not NULL
 ======================================================================*/
long free_genda(long action, GENDA *sqlGen )
{
    register long    row, col ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("FREE_GENDA"));
    }

    if (sqlGen == NULL)
        return GDB_ERROR ;
    
    /*** XFREE data area of GENDA ***/
    if ((action == DATA_ONLY || action == ALL) && sqlGen->da_col_ptr != (COL_DATA *)NULL)
    {
        if (debug & DBG6) iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("- data"));

        for (col=0;col<sqlGen->ncols;col++) 
        {
            /*** XFREE value buffers ***/
            if (sqlGen->da_col_ptr[col].data_type == GDB_STRING_TYPE)
            {
                for (row=0;row<sqlGen->nrows+1/*more_rows+1*/;row++)
                {
                    if (sqlGen->da_col_ptr[col].val[row].gdb_str != NULL)
                    {
                        XFREE (sqlGen->da_col_ptr[col].val[row].gdb_str) ;
                        sqlGen->da_col_ptr[col].val[row].gdb_str = NULL ;
                    }
                }
            }
            
            /*** XFREE val ptrs ***/
            if (sqlGen->da_col_ptr[col].val != NULL)
            {
                XFREE (sqlGen->da_col_ptr[col].val) ;
                sqlGen->da_col_ptr[col].val = NULL ;
            }
            
            /*** XFREE indicators ***/
            if (sqlGen->da_col_ptr[col].ind != NULL)
            {
                XFREE (sqlGen->da_col_ptr[col].ind) ;
                sqlGen->da_col_ptr[col].ind = NULL ;
            }
            
            /*** XFREE column names ***/
            if (sqlGen->da_col_ptr[col].col_name != NULL)
            {
                XFREE (sqlGen->da_col_ptr[col].col_name) ;
                sqlGen->da_col_ptr[col].col_name = NULL ;
            }
        }
        if (sqlGen->da_col_ptr != NULL)
        {
            XFREE (sqlGen->da_col_ptr) ;
            sqlGen->da_col_ptr = NULL ;
        }
        
        /* initialize GENDA status & code arrays to 0 */
        sqlGen->genStat.code = 0 ; 
        sqlGen->genStat.status = 0 ;
        if (sqlGen->genStat.msg != NULL)
            *(sqlGen->genStat.msg) = 0 ;
        
        if (debug & (DBG6|DBG9)) {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("Deallocated % row(s)"), sqlGen->nrows);
	}
        
        if (action == DATA_ONLY) 
            return GDB_SUCCESS ;
    }
    
    /*** XFREE info area of GENDA ***/
    
    if (action == ALL && sqlGen != NULL)
    { 
        
        /*** XFREE descriptors ***/
        if (sqlGen->stmt_handle != 0)
        {
            sql_dealloc_descriptors(sqlGen->stmt_handle, SELECT) ;
            sql_dealloc_descriptors(sqlGen->stmt_handle, BIND) ;
        }
 
        if (debug & DBG6) iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("- info"));
        
        /* the cursor MUST be closed and the stmt MUST be
        released in order to reuse the cursor name */
        
        if (sqlGen->cursor_name != NULL)
        {
            sql_close_cursor(sqlGen->cursor_name, sqlGen->stmt_handle, TRUE) ;
            sql_release(&sqlGen->stmt_id) ;
        }
        
        /*** XFREE genStat buffers ***/
        if (sqlGen->genStat.msg != NULL)
        {
            XFREE (sqlGen->genStat.msg) ;
            sqlGen->genStat.msg = NULL ;
        }
        
        /*** XFREE id info ***/
        get_stmt_handle(&sqlGen->stmt_handle, HDL_FREE) ;
        if (sqlGen->cursor_name != NULL)
        {
            XFREE ((char *)sqlGen->cursor_name) ;
            sqlGen->cursor_name = NULL ;
        }
        
        /*** XFREE decimal flags ***/
        if (sqlGen->decimal_flags != NULL)
        {
            XFREE(sqlGen->decimal_flags) ;
            sqlGen->decimal_flags = NULL ;
        }
        
        if (sqlGen != NULL)
        {
            XFREE (sqlGen) ;
            sqlGen = NULL ;
        }
    }
    else
        return GDB_ERROR ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  alloc_genda
    - allocate the internal elements of the GENDA structure
    - may only be called after INIT_GENDA
    - may only be called after DESCRIBE
    - utilizes elements from SQLDA to alloc GENDA

    Arguments:
    - sqlGen: pointer to GENDA created by 'init_genda'
    - if flag==1, alloc only 1 data row (funct calls)
 ======================================================================*/
long alloc_genda(GENDA *sqlGen, long flag )
{
    long    max_rows ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("ALLOC_GENDA"));
    }
    
    /*** make sure GENDA exists ***/
    if (sqlGen == (GENDA *)NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADSEQ) ;
        return GDB_ERROR ;
    }
    
    /*** make sure stmt has been processed ***/
    if (!sqlGen->stmt_id) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ESQLPRO) ;
        return GDB_ERROR ;
    }
    
    /*** allocate GENDA (DATA) area ***/
    if (sqlGen->da_col_ptr != (COL_DATA *)NULL) 
    {
      if (debug & (DBG6|DBG9)) {
	iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("GENDA data area is already allocated, deallocating"));
      }
      free_genda(DATA_ONLY, sqlGen) ;
      if (debug & (DBG6|DBG9)) {
	iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Reallocating GENDA data area"));
      }
    }
    /*** alloc da_col_ptr ***/
    if (sqlGen->ncols)
    { 
        if ((sqlGen->da_col_ptr = (COL_DATA *)XCALLOC(sqlGen->ncols, sizeof(COL_DATA))) == (COL_DATA *)NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
    }
    else
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOCOLS) ;
        return GDB_ERROR ;
    }
    
    /*** only alloc 1 row for sql function calls ***/
    max_rows = context[context_num].genda_rows ;
    if (flag) max_rows = 1 ;
    sqlGen->nrows = max_rows ;
    
    /*** perform GENDA alloc based on DB specific parameters ***/
    if (db_alloc_genda(sqlGen, max_rows))
    {
    /*    if (debug & DBG3)
        set_stat(FATAL_CD, EINSMEM, sqlGen, TRUE, NULL);  */
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ;
}


/*======================================================================
 process_release_stmt
 - close cursor, dealloc descriptors & XFREE resources
 
   Arguments:
   - sqlGen: needed for cursor_name and handle
 ======================================================================*/
long process_release_stmt(GENDA *sqlGen)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_RELEASE_STMT"));
    }

    /*** may need error handling ***/
    if (sqlGen == NULL || sqlGen->cursor_name == NULL)
        return GDB_ERROR ;
    
    if (sqlGen->cursor_name != NULL)
        sql_close_cursor(sqlGen->cursor_name, sqlGen->stmt_handle, FALSE) ;  
    sql_release(&sqlGen->stmt_id) ;
    sql_dealloc_descriptors(sqlGen->stmt_handle, SELECT) ;
    sql_dealloc_descriptors(sqlGen->stmt_handle, BIND) ;
    
    return GDB_SUCCESS ;
}
 

/*======================================================================
 process_query
 - process the sql statment and prepare all structures and cursors
 for fetching data
 - should only be called from 'process_set_query'
 
   Arguments:
   - sqlstr: the sql statement
   - sqlGen: the GENDA that will receive the data
   - query-type: 
   * SELECT = standard sql select statement
   * STORED_PROC = stored procedure (currently not supported)
 ======================================================================*/
long process_query(GDB_CHAR *sql_str, GENDA *sqlGen, long query_type )
{
    long    status = 0 ;
    long    shandle ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_QUERY"));
    }

    if (sqlGen == NULL) return GDB_ERROR ;
    
    if (sql_str == NULL || *sql_str == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINVSQL) ;
        status = 1 ;
    }
    
    /*** process the select statement ***/
    if (!status)
    {
        if (query_type == SELECT)
        {
            /* only support select statments */
            if (wstrstrci(sql_str, _T("SELECT")) == NULL)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ENONSEL) ;
                status = 1 ;
            }
        }
        else
        {
            /* do not support select statments - for future stored-proc support */
            if (wstrstrci(sql_str, _T("SELECT")) != NULL)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ENOSUPS) ;
                status = 1 ;
            }
        }
    }
    
    /*** get a new stmt handle (only if one has not already been assigned) ***/
    if (!status)
    {
        shandle = sqlGen->stmt_handle ;
        if (shandle == 0)
        {
            get_stmt_handle(&shandle, HDL_GET) ;
            sqlGen->stmt_handle = shandle ;
        }
        if (!shandle) status = 1 ;
    }
    
    /*** create a cursor name if one has not been provided ***/
    if (!status)
    {
        if (sqlGen->cursor_name == NULL)
        { 
            if ((sqlGen->cursor_name = (GDB_CHAR *)XCALLOC(MAX_DCURS_LEN+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                status = 1 ;
            }
            else {
                _snwprintf(sqlGen->cursor_name, MAX_DCURS_LEN,_T("CURSOR%d_%d"), context_num, shandle);
	    }
        }
    }
    
    /*** allocate descriptors ***/
    if (!status)
    {
        status = sql_alloc_descriptors(shandle, BIND) ;
        if (status) 
            sql_dealloc_descriptors(shandle, BIND) ;
    }
    if (!status) 
    {
        status = sql_alloc_descriptors(shandle, SELECT) ;
        if (status) 
            sql_dealloc_descriptors(shandle, SELECT) ;
    }
    
    /*** prepare ***/
    if (!status)
        status = sql_prepare(shandle, &sqlGen->stmt_id, sql_str) ;
    
    /*** describe input ***/
    /* Must use 'process_dynamic_query' if input variables are supplied. Doing this
    here because opening cursor with bind_ptr (rather than having 2 sets of cursor
    definitions) to support the dynamic approach */
    if (!status)
    {
        status = sql_describe_input(shandle, NULL, &sqlGen->stmt_id, &sqlGen->bind_processed, GDB_INIT) ;
        if (status) 
        {
            sql_dealloc_descriptors(shandle, BIND) ;
            sql_release (&shandle) ;
        }
    }
    
    /*** describe output ***/
    if (!status)
    {
        status = sql_describe_output(sqlGen, query_type) ;
        if (status)
        {
            sql_dealloc_descriptors(shandle, SELECT) ;
            sql_dealloc_descriptors(shandle, BIND) ;
            sql_release (&shandle) ;
        }
    }
    
    /*** declare cursor ***/
    if (!status)
        status = sql_declare_cursor(sqlGen->cursor_name, shandle, &sqlGen->stmt_id) ;
    
    if (!status)
    {
        iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
        return GDB_SUCCESS ;
    }
    
    if (status == GDB_ERROR)
    {
        /*   iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg);*/
    }
    else
    {
        get_stat(sqlGen) ;
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
    }
    
    sqlGen->stmt_id = 0 ;
    free_genda(DATA_ONLY, sqlGen) ;
    
    return GDB_ERROR ;
}


/*======================================================================
process_set_query
- release all resources allocated by a 'process_query'
- cleans-up the query if it still exists (via repeated set_query calls)
- XFREE & init the GENDA if it still exists
- call to setup new query

  Arguments:
  - sql_stmt: the sql statement
  - sqlGen: GENDA structure
  - query-type: 
  * SELECT = standard sql select statement
  * STORED_PROC = stored procedure (currently not supported)
  ======================================================================*/
long process_set_query(GDB_CHAR *sql_stmt, GENDA *sqlGen, long query_type )
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_SET_QUERY")) ;
    
    if (sqlGen == NULL) return GDB_ERROR ;
    
    if (sql_stmt == NULL || *sql_stmt == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINVSQL) ;
        return GDB_ERROR ;
    }
    
    /*** release the query ***/
    if (sqlGen->cursor_name != NULL)
        process_release_stmt(sqlGen) ;
    
    /*** XFREE & reinitialize GENDA ***/
    free_genda(DATA_ONLY, sqlGen) ;
    sqlGen->more_rows = 0 ;
    sqlGen->ncols = 0 ;
    sqlGen->array_size = 0 ;
    sqlGen->bind_processed = FALSE ;
    sqlGen->genStat.rows_processed = 0 ;
    sqlGen->genda_num = 0 ;
    sqlGen->genda_pos = 0 ;
    
    /*** setup the new query ***/
    if (process_query(sql_stmt, sqlGen, query_type))
        return GDB_ERROR ;
    
    return GDB_SUCCESS ; 
}

  
/*======================================================================
  process_dynamic_query
  - process the sql statment and prepare all structures and cursors
  for fetching data
  - should only be called from 'process_set_dynamic_query'
  
    Arguments:
    - sqlstr: the sql statement
    - bind_vars: array of bind variables which will be substituted into 
    'sqlstr'
    - sqlGen: the GENDA that will receive the data
    - query-type: 
    * GDB_INIT = fully setup the query which contains bind vars.
    * GDB_UPDATE = only update the bind descriptor with new bind vars.
  ======================================================================*/
long process_dynamic_query(GDB_CHAR *sql_str, BIND_STRUCT *bind_vars, GENDA *sqlGen, long query_type )
{
    long    status = 0 ;
    long    shandle ;
    long    preBind = FALSE ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_DYNAMIC_QUERY")) ;
    
    if (sqlGen == NULL) return GDB_ERROR ;
    
    if (sql_str == NULL || *sql_str == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINVSQL) ;
        status = 1 ;
    }
    
    /* bind vars must be supplied on a dynamic-update */
    if (bind_vars->bind_array == NULL || bind_vars->nBind == 0)
    {
        if (query_type == GDB_UPDATE)
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ENOINPT) ;
            status = 1 ;
        }
        else 
            preBind = TRUE;  /* ????? added for NULL bind vars at define time */
    }
    else 
        preBind = TRUE ;
    
    /*** process the select statement ***/
    if (!status)
    {
        /* only support SELECT statments and EXECs of stored procedures */
        /* ------------------------------------------------------------ */

      if (wstrstrci(sql_str, _T("SELECT")) == NULL)
#ifdef ODBC
	if (wstrstrci(sql_str, _T("EXEC")) == NULL) {
	  iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ESLEXRQ) ;
	  status = 1 ;
	}
#else
      {
	iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ENONSEL) ;
	status = 1 ;
      }
#endif

    }
                        
    /*** get a new stmt handle (only if one has not already been assigned) ***/
    if (!status)
    {
        shandle = sqlGen->stmt_handle ;
        if (shandle == 0)
        {
            get_stmt_handle(&shandle, HDL_GET) ;
            sqlGen->stmt_handle = shandle ;
        }
        if (!shandle) status = 1 ;
    }
            
    /*** create a cursor name if one has not been provided ***/
    if (!status)
    {
        if (sqlGen->cursor_name == NULL)
        { 
            if ((sqlGen->cursor_name = (GDB_CHAR *)XCALLOC(MAX_DCURS_LEN+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                status = 1 ;
            }
            else {
                _snwprintf(sqlGen->cursor_name, MAX_DCURS_LEN, _T("CURSOR%d_%d"), context_num, shandle);
	    }
        }
    }
            
    /* Only setup the query if it is 'new' (INIT). If the only thing changing is the
    bind variables, don't re-initialize the query (UPDATE) */ 
    
    if (query_type == GDB_INIT)
    {  /* create a NEW query */
        /*** allocate descriptors ***/
        if (!status)
        {
            status = sql_alloc_descriptors(shandle, BIND) ;
            if (status) 
                sql_dealloc_descriptors(shandle, BIND) ;
        }
        if (!status)
        {
            status = sql_alloc_descriptors(shandle, SELECT) ;
            if (status) 
                sql_dealloc_descriptors(shandle, SELECT) ;
        }
        
        /*** prepare ***/
        if (!status)
            status = sql_prepare(shandle, &sqlGen->stmt_id, sql_str) ;
        
        /*** declare cursor ***/
        if (!status)
            status = sql_declare_cursor(sqlGen->cursor_name, shandle, &sqlGen->stmt_id) ;
    }
    else
    {  /* update bind vars for EXISTING query */
       /* must XFREE the SQLDA data area since it was allocated via previous call to
        describe_output */
        sql_release_bind(shandle, SELECT) ;
        sql_release_bind(shandle, BIND) ;
    }
            
    if (query_type == GDB_UPDATE || (query_type == GDB_INIT && preBind)) 
    {
        /*** describe input ***/
        if (!status) 
        {
            status = sql_describe_input(shandle, bind_vars, &sqlGen->stmt_id, &sqlGen->bind_processed, query_type) ;
            if (status) 
            {
                sql_dealloc_descriptors(shandle, BIND) ;
                sql_release (&shandle) ;
            }
        }  
        
        /*** describe output ***/
        if (!status)
        {
            status = sql_describe_output(sqlGen, query_type) ;
            if (status)
            {
                sql_dealloc_descriptors(shandle, BIND) ;
                sql_dealloc_descriptors(shandle, SELECT) ;
                sql_release (&shandle) ;
            }
        }
    }
            
    if (!status)
    {
        /*** check for null column names ***/
        /* NOTE: CHECK HOW THIS IS HANDLED NOW !!!!!!??????????? */
        /*   check_column_names(sql_str, sqlGen);  ??? need to check for names with special chars ?>???????? */
        
        iomsg(DBG0, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", NULL_MSG) ;
        return (GDB_SUCCESS) ;
    }
    
    if (status == GDB_ERROR)
    {
        /*   iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg);*/
    }
    else 
    {
        get_stat(sqlGen) ;
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
    }
    
    sqlGen->stmt_id = 0 ;
    free_genda(DATA_ONLY, sqlGen) ;
    
    return GDB_ERROR ;
}


/*======================================================================
  process_set_dynamic_query
    - release all resources allocated by a 'process_query'
    - cleans-up the query if it still exists (via repeated set_query calls)
    - XFREE & init the GENDA if it still exists
    - call to setup new query

    Arguments:
    - sql_stmt: the sql statement
    - bind_vars: array of bind variables which will be substituted into 
      'sql_stmt'
    - sqlGen: GENDA structure
    - query_type: 
        * GDB_INIT = fully setup the query which contains bind vars.
        * GDB_UPDATE = only update the bind descriptor with new bind vars.
 ======================================================================*/
long process_set_dynamic_query(GDB_CHAR *sql_stmt, BIND_STRUCT *bind_vars, GENDA *sqlGen, long query_type )
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_SET_DYNAMIC_QUERY"));
    }

    if (sqlGen == NULL) return GDB_ERROR ;
    
    if (sql_stmt == NULL || *sql_stmt == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", EINVSQL) ;
        return GDB_ERROR ;
    }
    
    if ((bind_vars->bind_array == NULL || bind_vars->nBind == 0) && query_type != GDB_INIT)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ENOINPT) ;
        return GDB_ERROR ;
    }
    
    if (query_type != GDB_UPDATE) 
    {
        /*** release the query ***/
        if (sqlGen->cursor_name != NULL)
            process_release_stmt(sqlGen) ;
    }
    
    /*** XFREE & reinitialize GENDA ***/
    free_genda( DATA_ONLY, sqlGen) ;
    sqlGen->more_rows = 0 ;
    sqlGen->ncols = 0 ;
    sqlGen->array_size = 0 ;
    sqlGen->genStat.rows_processed = 0 ;
    sqlGen->genda_num = 0 ;
    sqlGen->genda_pos = 0 ;
    
    /*** setup the new dynamic query ***/
    if (process_dynamic_query(sql_stmt, bind_vars, sqlGen, query_type))
        return GDB_ERROR ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  execute_stored_proc
    - execute a database stored procedure that does not return any 
      arguments.

    Arguments:
    - sql_stmt: call to database stored procedure
 ======================================================================*/
long execute_stored_proc(GDB_CHAR *sql_stmt)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("EXECUTE_STORED_PROC"));
    }

    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    if (sql_exec_stored_proc(sql_stmt) == GDB_EXT_ERROR)
    {
        get_stat(NULL) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ; 
}


/*======================================================================
  execute_stored_proc_return
 ======================================================================*/
long execute_stored_proc_return(GDB_CHAR *a, GDB_CHAR *b, GDB_CHAR *c )
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("EXECUTE_STORED_PROC_RETURN"));
    }

    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    if (sql_exec_stored_proc_return(a, b, c) == GDB_EXT_ERROR)
    {
        get_stat(NULL) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ; 
}


/*======================================================================
  process_connect
    - initiate connection to database

    Arguments:
    - db_user: database username
    - db_pass: database password
    - c_str: database connection string
	- gsi_connection_str: gsi connection string
 ======================================================================*/
 long process_connect(GDB_CHAR *db_user, GDB_CHAR *db_pass, GDB_CHAR *c_str, GDB_CHAR *gsi_connection_str )/* add gsi-connection-string. modified for project 28544 Gensym-2012 */
 {
     GDB_CHAR    *tuser, *tpass, *tcstr, *tgsiconnstr ; /* add tgsiconnstr. for project 28544 Gensym-2012 */

     context_num = gsi_current_context() ;
     
     if (debug & DBG1) {
         iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_CONNECT")) ;
     }

	 /*{{{ if gsi_connection_str supplied, then use it to connect db. for project 28544 Gensym-2012 */
#ifdef SUPPORT_GSI_CONNECTION_STR
	 if ((gsi_connection_str != NULL) && (*gsi_connection_str != 0))
	 {
		 if (sql_connect_ex(gsi_connection_str))
		 {
			 get_stat(NULL) ;
			 iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
			 return GDB_ERROR ;
		 }
	 }
	 else
	 {
#endif
	 /*}}}*/
     if (c_str == NULL)
     {
		 if (debug & DBG3) 
			 iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOCONS) ;
		 return GDB_ERROR ;
	 }

     /*** sub the username USER if no username provided (for display only) ***/
     if (!db_user[0])  
         iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, "%s%s", _T("'USER' Attempting % database connection via:"), wDB_TYPE);
     else
         iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, "%s%s%s", _T("'%' Attempting % database connection via:"), db_user, wDB_TYPE);

     iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, "%s", c_str) ;
     
     if (sql_connect(db_user, db_pass, c_str))
     {
         get_stat(NULL) ;
         iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
         return GDB_ERROR ;
     }
	 /*{{{ for project 28544 Gensym-2012 */
#ifdef SUPPORT_GSI_CONNECTION_STR
	 }
#endif
	 /*}}}*/
     
     /* change status of INFO_CD to SUCCESS_CD for connect only */
     context[context_num].connected_to_db = FALSE ;
     if (context[context_num].gbl_status.status == INFO_CD)
     {
         context[context_num].gbl_status.status = SUCCESS_CD ;
         context[context_num].connected_to_db = TRUE ;
     }
     
     /*** need to store connect info for auto_db_reconnect ***/
     if (context[context_num].auto_db_reconnect)
     {
         
     /* upon reconnect, the db_user,db_pass, c_str & gsi_connection_str args to this function MAY be coming
        from context[context_num].db_connect_info depending upon the situation.
        Therefore, need to temp store this info as we are about to XFREE context[context_num]. */
         
         tuser = (GDB_CHAR *)XCALLOC(wcslen(db_user)+1, sizeof(GDB_CHAR)) ;
         tpass = (GDB_CHAR *)XCALLOC(wcslen(db_pass)+1, sizeof(GDB_CHAR)) ;
         tcstr = (GDB_CHAR *)XCALLOC(wcslen(c_str)+1,  sizeof(GDB_CHAR)) ;
		 tgsiconnstr = (GDB_CHAR *)XCALLOC(wcslen(gsi_connection_str)+1,  sizeof(GDB_CHAR)) ; /* tgsiconnstr. for project 28544 Gensym-2012 */
         if (tuser == NULL || tpass == NULL || tcstr == NULL || tgsiconnstr == NULL) /* tgsiconnstr. for project 28544 Gensym-2012 */
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
             return (GDB_SUCCESS) ;
         }
         wcscpy(tuser, db_user) ;
         wcscpy(tpass, db_pass) ;
         wcscpy(tcstr, c_str) ;
		 wcscpy(tgsiconnstr, gsi_connection_str); /* gsi_connection_str. for project 28544 Gensym-2012 */
         
         /* set it to false until all settings have been stored */
         context[context_num].auto_db_reconnect = FALSE ;
         if (context[context_num].db_connect_info.username != NULL)
         {
             XFREE(context[context_num].db_connect_info.username) ;
             context[context_num].db_connect_info.username = NULL ;
         }
         if ((context[context_num].db_connect_info.username = (GDB_CHAR *)XCALLOC(wcslen(tuser)+1, sizeof(GDB_CHAR))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
             return GDB_SUCCESS ;
         }
         if (context[context_num].db_connect_info.password != NULL)
         {
             XFREE(context[context_num].db_connect_info.password) ;
             context[context_num].db_connect_info.password = NULL ;
         }
         if ((context[context_num].db_connect_info.password = (GDB_CHAR*)XCALLOC(wcslen(tpass)+1, sizeof(GDB_CHAR))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
             XFREE(context[context_num].db_connect_info.username) ;
             return GDB_SUCCESS ;
         }
         if (context[context_num].db_connect_info.connection != NULL)
         {
             XFREE(context[context_num].db_connect_info.connection) ;
             context[context_num].db_connect_info.connection = NULL ;
         }
         if ((context[context_num].db_connect_info.connection = (GDB_CHAR *)XCALLOC(wcslen(tcstr)+1, sizeof(GDB_CHAR))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
             XFREE(context[context_num].db_connect_info.username) ;
             XFREE(context[context_num].db_connect_info.password) ;
             return GDB_SUCCESS ;
         }
		 /*{{{ gsi_connection_str. for project 28544 Gensym-2012 */
         if (context[context_num].db_connect_info.gsi_connection_str != NULL)
         {
             XFREE(context[context_num].db_connect_info.gsi_connection_str) ;
             context[context_num].db_connect_info.gsi_connection_str = NULL ;
         }
         if ((context[context_num].db_connect_info.gsi_connection_str = (GDB_CHAR *)XCALLOC(wcslen(tgsiconnstr)+1, sizeof(GDB_CHAR))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
             XFREE(context[context_num].db_connect_info.username) ;
             XFREE(context[context_num].db_connect_info.password) ;
             XFREE(context[context_num].db_connect_info.connection) ;
             return GDB_SUCCESS ;
         }
		 /*}}}*/
         wcscpy(context[context_num].db_connect_info.username, tuser) ;
         wcscpy(context[context_num].db_connect_info.password, tpass) ;
         wcscpy(context[context_num].db_connect_info.connection, tcstr) ;
		 wcscpy(context[context_num].db_connect_info.gsi_connection_str, tgsiconnstr); /* gsi_connection_str. for project 28544 Gensym-2012 */
         
         context[context_num].auto_db_reconnect = TRUE ;
         
         XFREE(tuser) ;
         XFREE(tpass) ;
         XFREE(tcstr) ;
		 XFREE(tgsiconnstr); /* free tgsiconnstr. for project 28544 Gensym-2012 */
     }
     
     return GDB_SUCCESS ;
 }


/*======================================================================
  set_init_params
    - setup the variables and defaults for the context
    - called during 'initialize_context'

    Arguments:
    - action: ALL=standard init
    - init_str: string containing the following qualifiers (note:
      the '-' is required)
        -a = array passing
        -A = auto-commit ON
        -b = max # bind variables
        -consoleoff = console_messages off
        -d = debug
        -D = layer_debug
        -f = logfile filter
        -F = smart fetch
        -g = enable messaging
        -m = enable GSI memory messages
        -M = fixed length logfile messages
        -n = max bind name length
        -o = display output to console
        -p = poll interval (in sec) for trigger checking
        -r = max registered items
        -S = G2 batch fetch limit
        -t = turn logfile time-stamping OFF
        -T = turn iomsg time-stamping OFF
        -x = max text length
        -w = use Windows integrated security for authenticating connection

      Specifying -<char>*<text> will override configuration_rp
      defaults (e.g. -C*20 will set max cursors to 20)
 ======================================================================*/
long set_init_params(GDB_CHAR *init_str, long action )
{
    GDB_CHAR *ptr, *fptr ;
    GDB_CHAR *field ;
    GDB_CHAR flag ;
    GDB_CHAR *wideSpace = _T(" ");

    long    value ;
    long    field_len ;
    long    status = GDB_SUCCESS ;
    GDB_CHAR t_stamp[MAX_TIMESTAMP_LEN] ;
    long    override ;
    long    tmp_debug ;
     
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SET_INIT_PARAMS"));
    }
    
    /* must initialize all CONSTANTS by default */
    if (action == ALL) 
    {
        context[context_num].genda_rows             = DFLT_VALUE_ARRAY_SZ ;
        context[context_num].max_cursors            = MAX_CURSORS ;
        context[context_num].max_bind_vars          = DFLT_BIND_VARS ;
        context[context_num].max_bind_name_len      = DFLT_BIND_NAME_LEN ;
        context[context_num].max_text_len           = PR_MAX_GSI_STRING_LEN ;
        context[context_num].need_textsize          = FALSE ;
        context[context_num].iomsg_ts               = FALSE ;
        context[context_num].logfile_ts             = TRUE ;
        context[context_num].logfile_active         = FALSE ;
        context[context_num].logfile_name           = NULL ;
        context[context_num].null_number            = DFLT_NULL_NUM ;
        context[context_num].set_null_string        = NULL ;
        context[context_num].set_null_number        = DFLT_SET_NULL_NUM ;
        context[context_num].set_null_options       = DFLT_SET_NULL_OPTIONS ;
        context[context_num].logfile_filter         = LOGFILE_FILTER_DEF ;
        context[context_num].enable_messaging       = DFLT_ENABLE_MESSAGES ;
        context[context_num].auto_db_reconnect      = DFLT_DB_RECONNECT;
        context[context_num].console_output         = DFLT_CONSOLE_OUTPUT;
        context[context_num].db_reconnecting        = FALSE ;
        context[context_num].name                   = NULL ;
        context[context_num].array_fetch            = TRUE; /* changed from FALSE to TRUE by default */
        context[context_num].max_reg_items          = DFLT_REGISTERED_ITEMS ;
        context[context_num].auto_commit            = DFLT_AUTO_COMMIT;
        context[context_num].smart_fetch            = DFLT_SMART_FETCH ;
#if defined(WIN32)
        context[context_num].integrated_security    = SQL_IS_DEFAULT; // odbcss.h
#endif
        debug                                       = DBG_DEFAULT;
        layer_debug                                 = DBGALL ;
        tmp_debug                                   = debug ;
        gbl_float_flag                              = DFLT_FLOAT_FLAG ;
        trim_log_msgs                               = FALSE ;
        
        /*** initialize global status structure ***/
        if ((context[context_num].gbl_status.msg = (GDB_CHAR *)XCALLOC(STATUS_MSG_LEN+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, FALSE, NULL, TRUE, "%d", EINMEMM) ;
            return GDB_ERROR ;
        }
        context[context_num].gbl_status.code = 0 ;
        context[context_num].gbl_status.status = 0 ;
        context[context_num].gbl_status.rows_processed = 0 ;
        
        /*** allocate registered_item address ***/
        context[context_num].reg_item.hcount = 0 ;
        if ((context[context_num].reg_item.addr = (GENDA **)XCALLOC(DFLT_REGISTERED_ITEMS+1, sizeof(GENDA *))) == (GENDA **)NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }       
        if ((context[context_num].reg_item.gsi_handle = (long *)XCALLOC(DFLT_REGISTERED_ITEMS+1, sizeof(long))) == (long *)NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        
        /*** initialize auto-reconnect ***/
        context[context_num].db_connect_info.username   = NULL ;
        context[context_num].db_connect_info.password   = NULL ;
        context[context_num].db_connect_info.connection = NULL ;
        context[context_num].db_connect_info.gsi_connection_str = NULL; /* add gsi_connection_string. for project 28544 Gensym-2012 */
        
        /*** initialize esql environment ***/
        sql_setup() ;
        
        /*** initialize null string array ***/
        if (context[context_num].null_string != NULL)
        {
            free(context[context_num].null_string) ;
            context[context_num].null_string = NULL ;
        }
        if ((context[context_num].null_string = (GDB_CHAR*)XCALLOC(wcslen(DFLT_NULL_STR)+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        wcscpy(context[context_num].null_string, DFLT_NULL_STR) ;

        /*** initialize set null string array ***/
        if (context[context_num].set_null_string != NULL)
        {
            free(context[context_num].set_null_string) ;
            context[context_num].set_null_string = NULL ;
        }
        if ((context[context_num].set_null_string = (GDB_CHAR*)XCALLOC(wcslen(DFLT_SET_NULL_STR)+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        wcscpy(context[context_num].set_null_string, DFLT_SET_NULL_STR) ;
        
        /*** initialize context_name string ***/
        if ((context[context_num].name = (GDB_CHAR *)XCALLOC(MAX_CONTEXT_NAME_LEN+1, sizeof(GDB_CHAR))) == NULL) 
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return GDB_ERROR ;
        }
        /* set the default context name */
        _snwprintf(context[context_num].name, MAX_CONTEXT_NAME_LEN, _T("Context-%d"), context_num);
    }
    else
        tmp_debug = debug |= DBG8 ;
    
    /*** override constants if instructed ***/
    if ((field = (GDB_CHAR*)XCALLOC(MAXDEFPARAMLEN, sizeof(GDB_CHAR))) == NULL) 
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    
    ptr = init_str ;
    fptr = field ;
    while (*ptr != 0) 
    {
        if (*ptr == DELIM) 
        {
            ptr++ ;
            flag = *ptr ;
            ptr++ ;
            field_len = 0 ;
            override = FALSE ;
            while (*ptr != 0 && *ptr != DELIM)
            {
                if (*ptr == '*') 
                {
                    override = TRUE ;
                    *ptr++ ;
                    continue ;
                }
                *fptr++ = *ptr++ ;  
                field_len++ ;
            }
            if (field_len > 0 && field[field_len-1] == ' ')
            {
                field[field_len-1] = 0 ;
                field_len-- ;  
            }
            else
                *fptr = 0 ;
             
            switch (flag)
            {
            case 'a' :  /* disable array fetch */
                context[context_num].array_fetch = FALSE ;
                if (tmp_debug & (DBG6|DBG8)) {
                    wprintf(_T("Config Param: ARRAY_FETCH set to: %s\n"), WSBOOLEAN(context[context_num].array_fetch)) ;
		}
                break ;
                
            case 'A' :  /* enable auto-commit */
                context[context_num].auto_commit = TRUE ;
                if (tmp_debug & (DBG6|DBG8)) {
                    wprintf(_T("Config Param: AUTO_COMMIT set to: %s\n"), WSBOOLEAN(context[context_num].auto_commit)) ;
		}
                break ;
                
            case 'b' : /* maximum bind variables */
                value = wcstol(field, &wideSpace, 10);
                if (value > MAX_BIND_VARS && !override)
                {
                    if (tmp_debug & DBG3) 
                        printf("Config Param: MAX_BIND_VARS %d exceeds max %d\n", value, MAX_BIND_VARS) ;
                    /*status = GDB_ERROR;  */
                    break ;
                }
                context[context_num].max_bind_vars = value ; 
                if (tmp_debug & (DBG6|DBG8)) 
                    printf("Config Param: MAX_BIND_VARS set to: %d\n", value) ;
                break ;
#if defined(WIN32)
            case 'w': /* enable integrated security */
                context[context_num].integrated_security = SQL_IS_ON ;
                if (tmp_debug & (DBG6|DBG8)) 
                    printf("Config Param: INTEGRATED_SECURITY enabled\n") ;
                break ;
#endif
            case 'c' :  /* console output off */
            case 'C' :
            case 'o' :
                context[context_num].console_output = FALSE ;
                break ;
                
            case 'd' :  /* debug */
                debug = DBGALL ;
                if (field[0] != ' ' && *field != 0)
                {
                    debug = DBG0;

                    if ((GDB_CHAR*)wcsstr(field, _T("DBG1")) != NULL) debug |= DBG1;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG2")) != NULL) debug |= DBG2;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG3")) != NULL) debug |= DBG3;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG4")) != NULL) debug |= DBG4;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG5")) != NULL) debug |= DBG5;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG6")) != NULL) debug |= DBG6;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG7")) != NULL) debug |= DBG7;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG8")) != NULL) debug |= DBG8;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG9")) != NULL) debug |= DBG9;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGM")) != NULL) debug |= DBGM;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGC")) != NULL) debug |= DBGC;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGALL")) != NULL) debug = DBGALL;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGDFLT")) != NULL) debug = DBG_DEFAULT;
                }
                if (tmp_debug & (DBG6|DBG8)) {
		    wprintf(_T("Config Param: DEBUG set to: %s\n"), field) ;
		}
                break ;               
                
            case 'D' :  /* layer-debug */
                if (field[0] != ' ' && *field != 0)
                {
                    layer_debug = DBG0;

                    if ((GDB_CHAR*)wcsstr(field, _T("DBG1")) != NULL) layer_debug |= DBG1;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG2")) != NULL) layer_debug |= DBG2;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG3")) != NULL) layer_debug |= DBG3;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGALL")) != NULL) layer_debug = DBGALL;
                    wprintf(_T("Config Param: LAYER_DEBUG set to: %s\n"), field);
                }
                break ;               
                
            case 'f' :  /* logfile filter */
                if (field[0] != ' ' && *field != 0)
                {
                    context[context_num].logfile_filter = DBG0;

                    if ((GDB_CHAR*)wcsstr(field, _T("DBG2")) != NULL) context[context_num].logfile_filter |= DBG2;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG3")) != NULL) context[context_num].logfile_filter |= DBG3;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBG4")) != NULL) context[context_num].logfile_filter |= DBG4;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGM")) != NULL) context[context_num].logfile_filter |= DBGM;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGALL")) != NULL) context[context_num].logfile_filter |= DBGALL;
                    if ((GDB_CHAR*)wcsstr(field, _T("DBGDFLT")) != NULL) context[context_num].logfile_filter = LOGFILE_FILTER_DEF;
                }

                wprintf(_T("Config Param: LOGFILE_FILTER set to: %s\n"), field);

                break ;               
                
            case 'F':
                context[context_num].smart_fetch = TRUE ;
                break ;
                
            case 'g' :  /* enable messaging */
                context[context_num].enable_messaging = TRUE ;
                if (tmp_debug & (DBG6|DBG8)) {
                    wprintf(_T("Config Param: ENABLE_MESSAGING set to: %s\n"), WSBOOLEAN(context[context_num].enable_messaging)) ;
		}
                break ;
                
            case 'm' :  /* gsi memory messages */
                g2rtl_Gc_silence = (void *)0 ;
                break ;
                
            case 'M' :  /* fixed length logfile messages */
                trim_log_msgs = TRUE ;
                if (tmp_debug & (DBG6|DBG8)) {
                    wprintf(_T("Config Param: TRIM_LOGFILE_MESSAGES set to: %s\n"), WSBOOLEAN(trim_log_msgs)) ;
		}
                break ;
                
            case 'n' : /* maximum bind variable name length */
                value = wcstol(field, &wideSpace, 10) ;
                if (value < DFLT_BIND_NAME_LEN) 
                {
                    if (tmp_debug & DBG3) 
                        printf("Config Param: MAX_BIND_NAME_LEN %d is less than minimum %d\n", value, DFLT_BIND_NAME_LEN) ;
                    /* status = GDB_ERROR;  */
                    break ;
                }
                context[context_num].max_bind_name_len = value ; 
                if (tmp_debug & (DBG6|DBG8)) 
                    printf("Config Param: MAX_BIND_NAME_LEN set to: %d\n", value) ;
                break ;

            case 'p' :  /* poll interval for trigger checking */
                value = wcstol(field, &wideSpace, 10) ;
                if (value < 0) value = 0 ;
                trigger.checkInterval = value ;
                if (tmp_debug & (DBG6|DBG8)) 
                    printf("Config Param: TRIGGER_POLL_INTERVAL set to: %d\n", value) ;
                break ;
                
            case 'r' :  /* max registration items */
                value = wcstol(field, &wideSpace, 10) ;
                if (value > MAX_REGISTERED_ITEMS && !override)
                {
		  if (tmp_debug & DBG3)
                    printf("Config Param: MAX_REGISTERED_ITEMS %d exceeds max %d\n", value, MAX_REGISTERED_ITEMS) ;
                    /* status = GDB_ERROR;  */
                    break ;
                }
                if (context[context_num].reg_item.addr != NULL)
                    XFREE (context[context_num].reg_item.addr) ;
                if (context[context_num].reg_item.gsi_handle != NULL)
                    XFREE (context[context_num].reg_item.gsi_handle) ;
                
                context[context_num].reg_item.hcount = 0 ;
                if ((context[context_num].reg_item.addr = (GENDA **)XCALLOC(value+1, sizeof(GENDA *))) == (GENDA **)NULL)
                {
                    iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                    return GDB_ERROR ;
                }       
                if ((context[context_num].reg_item.gsi_handle = (long *)XCALLOC(value+1, sizeof(long))) == (long *)NULL)
                {
                    iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                    return GDB_ERROR ;
                }
                
                context[context_num].max_reg_items = value ;
                if (tmp_debug & (DBG6|DBG8)) 
                    printf("Config Param: MAX_REGISTERED_ITEMS set to: %d\n", value);
                break ;
                
            case 't' :  /* logfile time-stamp OFF */
                context[context_num].logfile_ts = FALSE ; 
                if (tmp_debug & (DBG6|DBG8)) printf("Config Param: LOGFILE_TIMESTAMP set to: OFF\n");
                break ;
                
            case 'T' :  /* iomsg time-stamp ON */
                context[context_num].iomsg_ts = TRUE ;
                if (tmp_debug & (DBG6|DBG8)) printf("Config Param: IOMSG_TIMESTAMP set to: OFF\n");
                break ;
                
            case 'x':  /* max_text_len */
                value = wcstol(field, &wideSpace, 10);
                if (value <= 0) value = PR_MAX_GSI_STRING_LEN ;
                if (value > MAX_GSI_STRING_LEN) value = MAX_GSI_STRING_LEN ;
                context[context_num].max_text_len = value ;
                context[context_num].need_textsize = TRUE ;
                if (tmp_debug & (DBG6|DBG8)) 
                    printf("Config Param: MAX_TEXT_LEN set to: %ld\nNEED_TEXTSIZE set to TRUE", value);
                break ;
                
            default:
                if (tmp_debug & DBG3) printf("Unknown config parameter: %c\n", flag);
                break ;
            }
            *field = 0 ;
            fptr = field ;
            continue ;
        }
        ptr++ ;
    }
    if (field != NULL) 
        XFREE(field) ;
    field = NULL ;
  
    if (context[context_num].console_output)
    {
        printf("\nG2-%s Context Initialization (%d): ", DB_TYPE, context_num);
        wprintf(_T("%s\n"), TIME_STAMP(DFLT_TS_FMT, t_stamp));

        printf("--------------------------------------------------------\n");
    }
  
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    return status ;
}


/*======================================================================
  process_disconnect
    - initiate database disconnect

    Arguments:
    - cleanup_reconnect: TRUE=trash the stored connect info
    - context_num: the context whose DB connection you wish to disconnect
 ======================================================================*/
long process_disconnect(long  cleanup_reconnect, gsi_int context_num)
{
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_DISCONNECT")) ;
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return GDB_ERROR ;
    }
    
    /* db_reconnecting eliminates the possibility of recursive process_
    reconnect calls (infinite loop) */
    
    context[context_num].db_reconnecting = FALSE ;
    
    sql_disconnect(context_num) ;
    
    if (cleanup_reconnect) 
    {
        /* cleanup the database reconnect info */
        if (context[context_num].auto_db_reconnect) 
        {
            if (context[context_num].db_connect_info.username != NULL) 
            {
                XFREE((char *)context[context_num].db_connect_info.username) ;
                context[context_num].db_connect_info.username = NULL ;
            }
            if (context[context_num].db_connect_info.password != NULL) 
            {
                XFREE((char *)context[context_num].db_connect_info.password) ;
                context[context_num].db_connect_info.password = NULL ;
            }
            if (context[context_num].db_connect_info.connection != NULL)
            {
                XFREE((char *)context[context_num].db_connect_info.connection) ;
                context[context_num].db_connect_info.connection = NULL ;
            }
			/*{{{ gsi_connection_string. for project 28544 Gensym-2012 */
			if (context[context_num].db_connect_info.gsi_connection_str != NULL)
			{
				XFREE((char *)context[context_num].db_connect_info.gsi_connection_str);
				context[context_num].db_connect_info.gsi_connection_str = NULL;
			}
			/*}}}*/
        }
    }
    
    if (get_stat(NULL))
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    else 
    {
      if (context[context_num].name != NULL)
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%s", IDBDISC, context_num, context[context_num].name);
      else
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%s", IDBDISC, context_num, "");
    }
    
    /* change status of INFO_CD to SUCCESS_CD for disconnect only */
    if (context[context_num].gbl_status.status == INFO_CD)
        context[context_num].gbl_status.status = SUCCESS_CD ;
    
    return (GDB_SUCCESS) ;
}


/*======================================================================
  process_sql_function 
    - allow any valid 'select' statement and return
      row #1 column #1 only
    - returns either double or string, the non-returned
      value is set to 'null_string' or 'null_number'

    Arguments:
    - str: sql statement
 ======================================================================*/
GENDA *process_sql_function(GDB_CHAR *str)
{
    GENDA  *sqlGen ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_SQL_FUNCTION"));
    }

    /*** check for null string ***/
    if (*str == 0) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINVFCT) ;
        return NULL ;
    }
    
    /*** only support select statements ***/
    if (wstrstrci(str, _T("SELECT")) == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINVFCT) ;
        sqlGen = NULL ;
        return NULL ;
    }
    
    /*** init & assign GENDA ***/
    if ((sqlGen = init_genda(0)) == NULL)
        return NULL ;
    
    if (!process_set_query(str, sqlGen, SELECT)) 
        return (sqlGen) ;
    else 
    {    
        if (sqlGen != NULL)
            free_genda(ALL, sqlGen) ;
        return NULL ;
    }
    
}
 

/*======================================================================
  process_immediate (formerly process_non_query)
    - submit any sql statement to db
    - performs no statement or data processing
    - does not return any db data
    - returns status info only

    Arguments:
    - stmt: sql statement
 ======================================================================*/
long process_immediate(GDB_CHAR *stmt)
{
    context_num = gsi_current_context() ;
     
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_IMMEDIATE")) ;
    }

    if (stmt == NULL || *stmt == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINVSQL) ;
        return GDB_ERROR ;
    }
    
    sql_exec_sql(stmt) ;
    if (get_stat(NULL))
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ;
 }
 

/*======================================================================
  process_set_exec_sql
    - process the non-query sql statment and prepare all structures
    - cleans-up the dynamic exec if it still exists (via repeated
      process_set_exec_sql calls)
    - XFREE & init the GENDA if it still exists
    - setup new dynamic exec

    Arguments:
    - sql_stmt: the non-query sql statement
    - bind_vars: array of bind variables which will be substituted into
      'sql_stmt'
    - sqlGen: GENDA structure
    - query_type: 
        * GDB_INIT = fully setup the exec which contains bind vars.
        * GDB_UPDATE = only update the bind descriptor with new bind vars.
 ======================================================================*/
long process_set_exec_sql(GDB_CHAR *sql_stmt, BIND_STRUCT *bind_vars, GENDA *sqlGen, long exec_type )
{
    long    status = 0 ;
    long    shandle ;
    long    preBind = FALSE ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_SET_EXEC_SQL")) ;
    }

    if (sqlGen == (GENDA *)NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
        return GDB_ERROR ;
    }
    
    if (sql_stmt == NULL || *sql_stmt == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINVSQL) ;
        return GDB_ERROR ;
    }
    
    /* bind vars must be supplied on a dynamic-update */
    if (bind_vars->bind_array == NULL || bind_vars->nBind == 0) 
    {
        sqlGen->bind_processed = FALSE ;
        if (exec_type == GDB_UPDATE)
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ENOINPT) ;
            return GDB_ERROR ;
        }
    }
    else 
        preBind = TRUE ;
    
    if (exec_type != GDB_UPDATE) 
    {
        /*** release the query ***/
        if (sqlGen->cursor_name != NULL)
            process_release_stmt(sqlGen) ;
    }
    
    /* release bind variables */
    process_release_bind(BIND, sqlGen) ;
    
    /*** XFREE & reinitialize GENDA ***/
    free_genda(DATA_ONLY, sqlGen) ;
    sqlGen->more_rows = 0 ;
    sqlGen->ncols = 0 ;
    sqlGen->array_size = 0 ;
    sqlGen->genStat.rows_processed = 0 ;
    sqlGen->genda_num = 0 ;
    sqlGen->genda_pos = 0 ;
    
    /*** setup the new dynamic query ***/
    
    /*** get a new stmt handle (only if one has not already been assigned) ***/
    shandle = sqlGen->stmt_handle ;
    if (shandle == 0) 
    {
        get_stmt_handle(&shandle, HDL_GET) ;
        sqlGen->stmt_handle = shandle ;
    }
    if (!shandle) status = 1 ;
    
    /* although cursor is not used for dynamic exec, the cursor name is used to
    determine if the descriptors have been allocated and therefore must be
    released -- therefore the cursor name must be defined */
    if (!status) 
    {
        if (sqlGen->cursor_name == NULL) 
        { 
            if ((sqlGen->cursor_name = (GDB_CHAR *)XCALLOC(MAX_DCURS_LEN+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                status = 1 ;
            }
            else {
                _snwprintf(sqlGen->cursor_name, MAX_DCURS_LEN, _T("CURSOR%d_%d"), context_num, shandle);
	    }
        }
    }
    
    /* Only setup the exec if it is 'new' (INIT). If the only thing changing is the
    bind variables, don't re-initialize the exec (UPDATE) */ 
    
    if (exec_type == GDB_INIT) 
    {
        /*** allocate descriptors ***/
        if (!status)
        {
            status = sql_alloc_descriptors(shandle, BIND) ;
            if (status) 
                sql_dealloc_descriptors(shandle, BIND) ;
        }
        
        /*** prepare ***/
        if (!status)
            status = sql_prepare(shandle, &sqlGen->stmt_id, sql_stmt) ;
    }
    
    /*** describe input ***/
    if (!status) 
    {
        status = sql_describe_input(shandle, bind_vars, &sqlGen->stmt_id, &sqlGen->bind_processed, exec_type) ;
        if (status) 
        {
            sql_dealloc_descriptors(shandle, BIND) ;
            sql_release (&shandle) ;
        }
        else if (bind_vars->bind_array != NULL && bind_vars->nBind > 0)
            sqlGen->bind_processed = TRUE ;
    }  
    
    if (status != GDB_ERROR) 
    {
        get_stat(sqlGen) ;
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
    }
    
    return GDB_SUCCESS ;
}


/*======================================================================
  process_exec_sql
    - submit any non-query sql statement to db  
    - performs no statement or data processing
    - does not return any db data
    - returns status info only

    Arguments:
    - sqlGen: GENDA descriptor
 ======================================================================*/
long process_exec_sql(GENDA *sqlGen)
{
    context_num = gsi_current_context() ;
     
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_EXEC_SQL")) ;
    }

    if (sqlGen == NULL) return GDB_ERROR ;
    
    if (!sqlGen->bind_processed)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", ENOINPT) ;
        return GDB_ERROR ;
    }
    
    sql_exec_dynamic_sql(sqlGen->stmt_handle, sqlGen->stmt_id) ;
    if (get_stat(NULL))
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    
    /* added this to handle EOCURSOR return when no data found via delete or update */
    if (context[context_num].gbl_status.status != SUCCESS_CD)
        return GDB_ERROR ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  process_commit
    - commit transaction
  ======================================================================*/
long process_commit()
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_COMMIT")) ;
    }

    sql_commit() ;
    if (get_stat(NULL))
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ;
}
 

/*======================================================================
  process_rollback
    - rollback transaction
  ======================================================================*/
long process_rollback()
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_ROLLBACK")) ;
    }

    sql_rollback() ;
    if (get_stat(NULL)) 
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ;
}


/*======================================================================
    show_results (for debugging only)
  ======================================================================*/
long show_results(GENDA *sqlGen )
{
    long    row, col ;
     
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("SHOW_RESULTS")) ;
    }
    if (sqlGen != (GENDA *)NULL)
    {
        printf("  GENDA STRUCTURE\n") ;
        printf("  ---------------\n\n") ;
        printf("  Contents of GENDA (INFO)\n\n") ;
        printf("  genda_num   : %d\n", sqlGen->genda_num) ;
        printf("  obj_handle  : %d\n", sqlGen->obj_handle) ;
        printf("  stmt_id     : %d\n", sqlGen->stmt_id) ;
        printf("  stmt_handle : %d\n", sqlGen->stmt_handle) ;

        wprintf(_T("  cursor_name : %s\n"), sqlGen->cursor_name) ;

        printf("  ncols       : %d\n", sqlGen->ncols) ;
        printf("  nrows       : %d\n", sqlGen->nrows) ;
        printf("  array_size  : %d\n", sqlGen->array_size) ;
        printf("  more_rows   : %d\n", sqlGen->more_rows) ;
        printf("  genda_pos   : %d\n", sqlGen->genda_pos) ;
    }
    printf("  code        : %d\n", context[context_num].gbl_status.code) ;

    wprintf(_T("  msg         : %s\n"), context[context_num].gbl_status.msg) ;

    printf("  rows_proc'd : %d\n", context[context_num].gbl_status.rows_processed) ;
    printf("  status      : %d\n\n", context[context_num].gbl_status.status) ;
    
    if (sqlGen == NULL) return GDB_SUCCESS ;
    if (context[context_num].gbl_status.status < 0 || !sqlGen->more_rows) return GDB_SUCCESS ; 
    
    printf("  Contents of GENDA (DATA)\n\n");
    printf("\n       ");
    for (col=0;col<sqlGen->ncols;col++) 
    {
        wprintf(_T("%9s="), sqlGen->da_col_ptr[col].col_name) ;

        switch (sqlGen->da_col_ptr[col].data_type)
        {
        case GDB_STRING_TYPE :
                                printf("%s", "STR");
                                break ;
        case GDB_BYTE_TYPE :
                                printf("%s", "BYTE");
                                break ;
        case GDB_SHORT_TYPE :         
                                printf("%s", "SHORT");
                                break ;
        case GDB_INT_TYPE :         
                                printf("%s", "INT");
                                break ;
        case GDB_LONG_TYPE :         
                                printf("%s", "LONG");
                                break ;
        case GDB_FLOAT_TYPE :
                                printf("%s", "FLT");
                                break ;
        case GDB_DBL_TYPE :
                                printf("%s", "DBL");
                                break ;
        }
    }
    printf("\n\n") ;
    
    for (row=0; row<sqlGen->nrows; row++)
    {
        if (row >= sqlGen->more_rows)
            break ;
        printf("%3d>  |", row);
        for (col=0;col<sqlGen->ncols;col++)
        {
            switch (sqlGen->da_col_ptr[col].data_type)
            {
            case GDB_STRING_TYPE :
                                    wprintf(_T("%10s,%2d|"), sqlGen->da_col_ptr[col].val[row].gdb_str,
                                                sqlGen->da_col_ptr[col].ind[row]) ;

                                    break ;
            case GDB_BYTE_TYPE :
                                    printf("%10d,%2d|", sqlGen->da_col_ptr[col].val[row].gdb_byte,
                                                sqlGen->da_col_ptr[col].ind[row]) ;
                                    break ;
            case GDB_SHORT_TYPE :
                                    printf("%10d,%2d|", sqlGen->da_col_ptr[col].val[row].gdb_short,
                                                sqlGen->da_col_ptr[col].ind[row]) ;
                                    break ;
            case GDB_INT_TYPE :
                                    printf("%10d,%2d|", sqlGen->da_col_ptr[col].val[row].gdb_int,
                                                sqlGen->da_col_ptr[col].ind[row]) ;
                                    break ;
            case GDB_LONG_TYPE :         
                                    printf("%10d,%2d|", sqlGen->da_col_ptr[col].val[row].gdb_long,
                                                sqlGen->da_col_ptr[col].ind[row]) ;
                                    break ;
            case GDB_FLOAT_TYPE :
                                    printf("%10f,%2d|", sqlGen->da_col_ptr[col].val[row].gdb_float,
                                                sqlGen->da_col_ptr[col].ind[row]) ;
                                    break ;
            case GDB_DBL_TYPE :
                                    printf("%10f,%2d|", sqlGen->da_col_ptr[col].val[row].gdb_dbl,
                                                sqlGen->da_col_ptr[col].ind[row]) ;
                                    break ;
            }
        }
        printf("\n") ;
    }
    printf("\n") ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  update_genda 
    - fetches 'sqlGen->nrows' rows into GENDA
    - returns fetch transaction status
    - must issue a process_refresh_cursor after calling this
      or a set_query in order to reset cursor ptr to beginning

    Arguments:
    - sqlGen: GENDA that will be populated with data
  ======================================================================*/
long update_genda(GENDA *sqlGen )
{
    long    shandle ;
    long    status ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("UPDATE_GENDA")) ;
    
    if (sqlGen == NULL) return GDB_ERROR ;
    
    if (!sqlGen->stmt_id)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, sqlGen, TRUE, "%d", ESQLPRO) ;
        return GDB_ERROR ;
    }
    
    shandle = sqlGen->stmt_handle ;
    if (!shandle) 
        return GDB_ERROR ;
    
    if (sqlGen->ncols < 1) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ESQLBDP) ;
        return GDB_ERROR ;
    }
    
    if (sqlGen->da_col_ptr == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return GDB_ERROR ;  
    }
    
    if (!sqlGen->bind_processed)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOINPT) ;
        return GDB_ERROR ;
    }
    
    /*** start fetching the data ***/
    sqlGen->more_rows = FALSE ;
    do
    {
        sql_fetch(sqlGen->cursor_name, shandle) ;
        get_stat(sqlGen) ;
        
        if (sqlGen->genStat.code >= 0)
        {
            status = get_genda_data(sqlGen) ;
            if (status)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EFETDAT) ;
                return GDB_ERROR ;  
            }
        }
    } while (sqlGen->more_rows < sqlGen->nrows && sqlGen->genStat.code != end_of_cursor &&
        sqlGen->genStat.code >= 0) ;
    
    sqlGen->genda_num = (sqlGen->genStat.rows_processed - 1)/ sqlGen->nrows ; 
    
    if (debug & DBG6) 
    {
        iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("Number of rows processed: %"), sqlGen->genStat.rows_processed);
        iomsg(DBG6, LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("Done Fetching"));
    }
    
    status = sqlGen->genStat.status ;
    
    if (debug & DBG5) show_results(sqlGen) ;
    
    return (status < 0 ? GDB_ERROR : GDB_SUCCESS) ;
}
  

/*======================================================================
  process_refresh_cursor
    - reposition cursor ptr to first row

    Arguments:
    - sqlGen: GENDA
  ======================================================================*/
long process_refresh_cursor(GENDA *sqlGen)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_REFRESH_CURSOR")) ;
    
    if (sqlGen == NULL) return GDB_ERROR ;
    
    if (sqlGen->cursor_name == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EREFCUR) ;
        return GDB_ERROR ;
    }
    
    sql_refresh_cursor(sqlGen->cursor_name, sqlGen->stmt_handle) ;
    if (get_stat(sqlGen))
        return GDB_ERROR ;
    
    /* reset GENDA - this should force an update */
    sqlGen->more_rows = 0 ;
    sqlGen->genStat.status = 0 ;
    sqlGen->genStat.code = 0 ;
    *sqlGen->genStat.msg = 0 ;
    sqlGen->genStat.rows_processed = 0 ;
    sqlGen->genda_num = 0 ;
    sqlGen->genda_pos = 0 ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  process_reconnect
    - reconnect to database

    Arguments:
    - none.
  ======================================================================*/
long process_reconnect()
{
    long    status ;
      
    context_num = gsi_current_context() ;
    
    if ( !context[context_num].auto_db_reconnect || 
            context[context_num].db_connect_info.connection == NULL || 
            context[context_num].db_reconnecting )
        return (GDB_SUCCESS) ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_RECONNECT")) ;
    
    /* db_reconnecting eliminates the possibility of recursive process_
    reconnect calls (infinite loop) */
    
    iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, "%d", IADBREC) ;
    
    sql_disconnect(context_num) ; /* bug HQ-4203852 */
    
    context[context_num].db_reconnecting = TRUE ;
    status = process_connect(context[context_num].db_connect_info.username,
                    context[context_num].db_connect_info.password,
                    context[context_num].db_connect_info.connection,
					context[context_num].db_connect_info.gsi_connection_str) ; /* add gsi-connection-string. for project 28544 Gensym-2012 */
    
    context[context_num].db_reconnecting = FALSE ;
    
    if (!status)
        iomsg(DBG4, LAYER, TRUE, TRUE, NULL, TRUE, "%d", WDBRECN) ;
    
    /* change status of INFO_CD to SUCCESS_CD for reconnect only */
    if (context[context_num].gbl_status.status == INFO_CD)
        context[context_num].gbl_status.status = SUCCESS_CD ;
    
    return (GDB_SUCCESS) ;
}


/*======================================================================
  process_stored_proc

    Arguments:
    - sql_stmt: stored procedure call
 ======================================================================*/
long process_stored_proc(GDB_CHAR *sql_stmt, GENDA *sqlGen)
{
    context_num = gsi_current_context() ;
  
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_STORED_PROC")) ;
  
    /*** check for null string ***/
    if (*sql_stmt == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINVSQL) ;
        return GDB_ERROR ;
    }
    
    if (!process_set_query(sql_stmt, sqlGen, STORED_PROC))
        return (GDB_SUCCESS) ;
    
    return GDB_ERROR ;
}


/*======================================================================
  process_ping_db
    - ping the database connection
 ======================================================================*/
long process_ping_db (void)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_PING_DB")) ;
    
    sql_ping_db() ;
    
    if (get_stat(NULL)) 
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    
    return GDB_SUCCESS ;
}


/*======================================================================
  process_trigger
 ======================================================================*/
long process_trigger (GDB_CHAR *trig_name, long trig_timeout, GDB_CHAR *trig_ret_msg, gsi_int context_num)
{
    long   status ;
    
    /* NOTE: context_num is passed from L1 as we are outside of
    run-loop during check (i.e. not within a context) */
    status = sql_trigger(trig_name, trig_timeout, trig_ret_msg, context_num) ;
    
    if (status != GDB_SUCCESS /* && get_stat(NULL)*/)
        return GDB_ERROR ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  process_set_exec_sql_obj
    - front end to 'load_bind_vars'
    - loads bind variables into 'bind' SQLDA
    - may be called multiple times to load different bind variables

    Arguments:
      + bind_vars - array of bind variable values
      + sqlGen - Gensym descriptor area
      + index - index of the SQLDA data value (e.g. V[index])
      + datatype - datatype of the values in bind_vars
      + array_size - number of elements in bind_vars 
 ======================================================================*/
long process_set_exec_sql_obj(void **bind_vars, GENDA *sqlGen, long index,
                              long datatype, long array_size )
{
    long    status = 0 ;
    long    shandle ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", "PROCESS_SET_EXEC_SQL_OBJ") ;
    
    shandle = sqlGen->stmt_handle ;
    
    /* process_release_stmt(sqlGen); */
    status = load_bind_vars(shandle, bind_vars, index, datatype, array_size) ;
    
    return (!status ? GDB_SUCCESS : GDB_ERROR) ;
}


/*======================================================================
  process_exec_sql_obj
 ======================================================================*/
long process_exec_sql_obj(GENDA *sqlGen, long array_size)
{
    long   shandle ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_EXEC_SQL_OBJ")) ;
    
    if (sqlGen == NULL) return GDB_ERROR ;
    
    shandle = sqlGen->stmt_handle ;
    sql_exec_sql_obj (shandle, array_size, sqlGen->stmt_id) ;
    if (get_stat(NULL)) 
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    
    /* added this to handle EOCURSOR return when no data found via delete or update */
    if (context[context_num].gbl_status.status != SUCCESS_CD)
        return GDB_ERROR ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  process_poll_check
    - called each time GSI cycles through run-loop
    - called outside of a context
 ======================================================================*/

long process_poll_check ()
{
    long   status ;
    
    if (!gdb_poll_check)
        return GDB_SUCCESS ;
    
    /* NOTE: context_num is passed from L1 as we are outside of
                    run-loop during check (i.e. not within a context) */
    
    status = sql_poll_check() ;
    
    if (status != GDB_SUCCESS)
        return GDB_ERROR ;
    
    return GDB_SUCCESS ;
}


/*======================================================================
  process_release_bind
 ======================================================================*/
long process_release_bind(long action, GENDA *sqlGen)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_RELEASE_BIND")) ;
    
    sql_release_bind(sqlGen->stmt_handle, action) ;
    
    return (GDB_SUCCESS) ;
}


/*======================================================================
  process_count_bind_vars
 ======================================================================*/
long process_count_bind_vars(GENDA *sqlGen, GDB_CHAR *bind_vars)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("PROCESS_COUNT_BIND_VARS")) ;
    
    if (count_bind_vars(sqlGen->stmt_handle, bind_vars))
        return GDB_ERROR ;
    
    return GDB_SUCCESS ;
}


/* ========================================================================== */
/*                                                                            */
/*         Ask Database-specific code whether this bridge uses DSNs.          */
/*                                                                            */
/* ========================================================================== */
long uses_DSN()
{
    return sql_uses_DSNs() ;
}


/* ========================================================================== */
/*                                                                            */
/*                       Add, Modify, or Delete a DSN                         */
/*                                                                            */
/* ========================================================================== */
long configure_DSN(gsi_int action, gsi_char* DrvrName, gsi_item* pStruct)
{
    gsi_int     iCode ;
    gsi_char    *pDSNName ;
    long        rv ;

    rv = sql_configure_DSN(action, DrvrName, pStruct, &iCode, &pDSNName) ;
    if (rv)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", rv) ;
        return GDB_ERROR ;
    }
    if (get_stat(NULL))
    {
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    else
    {
        iomsg(DBG2, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", iCode,
            iCode==IDSNDEL ? _T("") : (GDB_CHAR*)DrvrName, !pDSNName ? _T("") : (GDB_CHAR*)pDSNName);
        return GDB_SUCCESS ;
    }
}
