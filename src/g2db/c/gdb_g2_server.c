/*===========================================================================*
 * GDB_G2_SERVER.C  - GDB Layer-1                                     [source]
 *===========================================================================*
 *
 * Author: Robert J. Franceschini
 *
 *    - LAYER-1 = gdb_g2_server.c + gdb_main.c
 *    - G2<->Bridge interface layer
 *    - receive and send transactions to G2
 *    - call processing routines in LAYER-2
 *    - perform context management
 *    - invoke bridge/context init/shutdown/cleanup
 *===========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gsi_main.h"
#include "gdb_globals.h"
#include "gdb_genda.h"
#include "gdb_g2_server.h"
#include "gdb_messages.h"
#include "gdb_context.h"
#include "gdb_utils.h"
#include "gdb_common.h"
#ifdef WIN32
#include <crtdbg.h>
#endif

#define TCPIP_PORT_NUMBER   0
#define LAYER               LAYER1

/* KB_VER is defined in Makefiles */
#ifndef KB_VER
#define KB_VER    843
#endif

#define SQL_EXISTS   _T("EXISTS")
#define SQL_DELETE   _T("DELETE")
#define SQL_OPEN     _T("OPEN")
#define SQL_IDENTIFY _T("IDENTIFY")
#define SQL_NAME     _T("NAME")
#define SQL_VERSION  _T("VERSION")
#define SQL_PLATFORM _T("PLATFORM")
#define SQL_EXEC     _T("EXEC")
#define SQL_QUERY    _T("QUERY")

/* extern globals */
extern CONTEXT_INFO  context[MAX_GDB_CONTEXTS] ;
extern BRIDGE_INFO   bridge_info ;
extern long   max_value_array_size ;
extern long   max_col_array_size ;
extern long   gdb_charset ;
extern long   debug ;

extern unsigned int tmem ;

/* gsi->g2 procedure handles */   
gsi_int context_event_msg_hdl[MAX_GDB_CONTEXTS] ;
gsi_int context_trigger_msg_hdl[MAX_GDB_CONTEXTS] ;

/* globals */
gsi_registered_item *gdb_registered_item_array ;
gsi_registered_item *gdb_trigger_reg ;
gsi_attr      *gdb_attr_item_array ;
gsi_item      *gdb_item_array ;
gsi_item      *gdb_trigger_item ;
gsi_attr      *gdb_trigger_attr ;
gsi_item      *gdb_value_array ;
gsi_item      *gdb_object_array ;
gsi_item      *gdb_column_array ;
gsi_item      *gdb_status_items ;
gsi_attr      *gdb_status_attr_items ;
gsi_attr     **list_attrs ;
gsi_int        gdb_context_count = 0; /* # of active contexts */
extern gsi_int context_num ;
trig_struct    trigger ;
short         *gdb_unicode ;
GDB_CHAR        gsi_type_as_text[MAX_GSI_CLASS_LEN] ;

/* temp hack used to disable GSI memory messages */
extern void *g2rtl_Gc_silence ;

/*===========================================================================*
    return_event_msg
      - 'starts' the G2 procedure identified by G2_EVENT_MSG_PROC and passes
        it the following arguments: (see below for details)
          + the contents of the gbl_status or GENDA structure
          + the source (facility) of the message
          + timestamp for the event
 *===========================================================================*/
static long return_event_msg(GENDA *genda_ptr)
{
    gsi_item  *rargs ;
    GDB_CHAR   t_stamp[MAX_TIMESTAMP_LEN] ;
    
    context_num = gsi_current_context() ;
    
    if (!context[context_num].enable_messaging)
        return GDB_SUCCESS ;
    
        /* arg0 - status
           arg1 - code
           arg2 - message
           arg3 - facility code
           arg4 - timestamp */
    
    rargs = gdb_status_items ;
    
    /* load the status info - if genda_ptr is not null then get status info
    from GENDA otherwise use the context gbl_status structure */
    update_object_status(rargs, genda_ptr, UPDATE_ITEMS, 0) ;
    
    /* determine the facility from status code */
    if (context[context_num].gbl_status.code <= -GDB_MSG_BASE ||
            context[context_num].gbl_status.code >= GDB_MSG_BASE ||
            !context[context_num].gbl_status.code)
        gsi_set_sym(rargs[FACILITY_POS], gsi_make_symbol((gsi_char*)FACILITY_INTERNAL)) ;
    else
        gsi_set_sym(rargs[FACILITY_POS], gsi_make_symbol((gsi_char*)FACILITY_EXTERNAL)) ;
    
    /* get the current timestamp */
    TIME_STAMP(DFLT_TS_FMT, t_stamp) ;
    gsi_set_str(rargs[TIMESTAMP_POS], (gsi_char*)t_stamp) ;
    
    gsi_rpc_start(context_event_msg_hdl[context_num], rargs, context_num) ;
    
    return GDB_SUCCESS ;
}


/*===========================================================================*
    clear_g2_obj_status
      - reset the status fields (status,code,msg,rows-processed,cursor-pos)
        of a G2 object
      - arguments:
         + item_ptr = the object in which the status attribs are to be
           cleared. 
 *===========================================================================*/
static long clear_g2_obj_status(void* item_ptr)
{
    gsi_registered_item *object ;
    gsi_attr            *ret_record ;
    
    context_num = gsi_current_context() ;
    
    ret_record = gdb_status_attr_items ;
    object = item_ptr ;
    
    /*
    removed this to allow non parameter & variables
    gsi_set_sym(object,SUCC_SYM) ;
    */
    
    gsi_set_attr_name(ret_record[STAT_POS], gsi_make_symbol((gsi_char*)STAT_ATT)) ;    /* status */
    gsi_set_sym(ret_record[STAT_POS], gsi_make_symbol((gsi_char*)SUCC_SYM)) ;
    gsi_set_attr_name(ret_record[CODE_POS], gsi_make_symbol((gsi_char*)CODE_ATT)) ;    /* code */
    gsi_set_int(ret_record[CODE_POS], 0) ;
    gsi_set_attr_name(ret_record[MSG_POS], gsi_make_symbol((gsi_char*)MSG_ATT)) ;      /* message */
    gsi_set_str(ret_record[MSG_POS], (gsi_char*)_T("")) ;
    gsi_set_attr_name(ret_record[NROWS_POS], gsi_make_symbol((gsi_char*)NROWS_ATT));   /* rows processed */
    gsi_set_int(ret_record[NROWS_POS], 0) ;
    gsi_set_attr_name(ret_record[CURSOR_POS], gsi_make_symbol((gsi_char*)CURSOR_ATT)); /* cursor postion */
    gsi_set_int(ret_record[CURSOR_POS], 0) ;
    
    gsi_return_attrs(object, ret_record, NUM_STATUS_ARGS, context_num) ;
    
    return GDB_SUCCESS ;
}


/*===========================================================================*
    return_rpc_status
      - Set the RPC status return fields for all RPC's and return the 
        structure. Status values taken from gbl_status structure unless
        a non-null GENDA is provided in which case the status values are
        taken from the GENDA status area. If sargs is NOT null then sargs
        is directly returned to the RPC.
      - perform a return_event_msg if applicable
      - arguments:
         + sargs = status args; (gsi_item array)
         + num_sargs = # of items in sargs
         + genda_ptr = an allocated GENDA structure
         + call_index = supplied from GSI RPC call
 *===========================================================================*/
static long return_rpc_status(gsi_item *sargs, long num_sargs, GENDA *genda_ptr, gsi_int call_index)
{
    gsi_item  *status_args ;
    
    context_num = gsi_current_context() ;
    if (context_num < 0 || context[context_num].no_rpc_return || call_index == 0) 
        return GDB_SUCCESS ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("RETURN_RPC_STATUS: %"), context_num);
    }

    if (sargs == NULL) 
    {
        /* return contents of gbl_status structure or GENDA if provided */
        status_args = gdb_status_items ;
        update_object_status(status_args, genda_ptr, UPDATE_ITEMS, 0) ;
        gsi_rpc_return_values(status_args, NUM_STATUS_ARGS, call_index, context_num) ;
    }
    else 
    {
        /* return num_args status args provided in sargs */
        gsi_rpc_return_values(sargs, num_sargs, call_index, context_num) ;
    }
    return_event_msg(genda_ptr);  /* returning to rpc generates an event msg */
    return GDB_SUCCESS ;
}


/*===========================================================================*
    check_triggers   
      - check all triggers that have been activated via 'set_trigger_rp'
        and notify if a trigger message exists. 
      - if trigger refers to a trigger-object then update the object
      - if trigger refers to G2_TRIGGER_MSG_PROC then start the procedure                                          
 *===========================================================================*/
void check_triggers()
{
    register long   n, i ;
    gsi_item    *rargs ;
    gsi_item    *object ;
    gsi_attr    *arg ;
    GDB_CHAR     ret_msg[MAX_TRIGGER_MSG_LEN] ;
    GDB_CHAR     t_stamp[MAX_TIMESTAMP_LEN] ;
    long        status = 0 ;
    
    if (!trigger.count)
        return ;
    
    if (get_time() < trigger.timeLastChecked + trigger.checkInterval) 
        return ;
    
    ret_msg[0] = 0 ;
    rargs = gdb_trigger_item ;
    i = 0 ;
    for (n=1; n<MAX_TRIGGERS; n++)
    {
        if (trigger.names[n] != NULL)
        {
            do 
            {
                context_num = trigger.context[n] ;
                
                if (!context[context_num].available || !context[context_num].connected_to_db)
                    continue ;
                
                status = process_trigger((GDB_CHAR*)trigger.names[n], 0L, ret_msg, context_num) ;
                if (*ret_msg != 0)
                {
                    if (trigger.obj_handle[n] > 0) 
                    {
                        /* return to trigger-object */
                        object = gdb_trigger_reg ;
                        gsi_clear_item(object[0]) ;
                        gsi_set_handle(object[0], trigger.obj_handle[n]) ;

                        /* set the trigger message */
                        gsi_set_str(object[0], (gsi_char*)ret_msg) ;

                        /* set the timestamp attribute */
                        arg = gdb_trigger_attr ;
                        TIME_STAMP(DFLT_TS_FMT, t_stamp) ;

                        gsi_set_attr_name(arg[0], gsi_make_symbol((gsi_char*)TIME_STAMP_NAME)) ;
                        gsi_set_str(arg[0], (gsi_char*)t_stamp) ;
                        gsi_return_attrs(object[0], arg, 1, context_num) ;
                    }
                    else 
                    {
                        /*** return to trigger-event procedure in G2 ***/
                        gsi_set_sym(rargs[0], gsi_make_symbol((gsi_char*)trigger.names[n])) ;

                        /* convert trigger msg if not iso-646 */
                        gsi_set_str(rargs[1], (gsi_char*)ret_msg) ;
                        TIME_STAMP(DFLT_TS_FMT, t_stamp) ;
                        gsi_set_str(rargs[2], (gsi_char*)t_stamp) ;
                        gsi_rpc_start(context_trigger_msg_hdl[context_num], rargs, context_num) ;
                    }
                }
            } while (!status && *ret_msg != 0) ;
            
            if (++i >= trigger.count)
                break ;
        }
    }
    
    trigger.timeLastChecked = get_time() ;
    return ;
}


/*===========================================================================*
    poll_check
      - called each time GSI cycles through run-loop
      - called outside of a context
 *===========================================================================*/
void poll_check ()
{
    process_poll_check() ;
    return ;
}


/*---------------------------------------------------------------------------*
                       Remote Procedures
 *---------------------------------------------------------------------------*/

/*===========================================================================*
    log_file_rp                                                       GDB-RPC
      - perform log file management (open,close,modify filter settings)
      - args
          [0]=open/close 
          [1]=filter (ERROR,WARN,INFO,FATAL,ALL) "" = default (any delimiter ok)
          [2]=existing or new logfile path+name  "" = close current
              (may contain filter args too)
 *===========================================================================*/
static void log_file_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    GDB_CHAR       *ptr1, *ptr2 ;
    unsigned int  len ;
    int           fSpaceOK = FALSE ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("LOG_FILE_RP: %"), context_num) ;
    }

    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 3)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = the action: open, close */
    if (*gsi_symbol_name(gsi_sym_of(arg[0])) == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-2 = the logfile name (may contain filter args too) */
    if (*gsi_str_of(arg[2]) == 0) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOLOGN) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    
    /* for debugging purposes */
    if (!_wcsicmp(gsi_symbol_name(gsi_sym_of(arg[0])), SQL_EXISTS))
    {
        if (logfileio(F_EXISTS, context[context_num].logfile_name))
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    if (!_wcsicmp(gsi_symbol_name(gsi_sym_of(arg[0])), SQL_DELETE))
    {
        if (*context[context_num].logfile_name != 0)
            logfileio(F_CLOSE, context[context_num].logfile_name) ;
        if (logfileio(F_DELETE, context[context_num].logfile_name)) {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%s%s", 
                    _T("Could not delete logfile %"), context[context_num].logfile_name);
	}
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* allocate or reallocate logfile name buffer */
    len = wcslen(gsi_str_of(arg[2])) ;
    if (context[context_num].logfile_name == NULL)
    {
        if ((context[context_num].logfile_name = (GDB_CHAR*)XCALLOC(len+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            context[context_num].logfile_name = NULL ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        *context[context_num].logfile_name = 0 ;
    }
    else 
    {
        if (wcslen(context[context_num].logfile_name) < len)
        {
            if ((context[context_num].logfile_name = (GDB_CHAR*)realloc(context[context_num].logfile_name,
                sizeof(GDB_CHAR)*(len+1))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINMEMR) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                return ;
            }
        }
    }
    
    /* must close 'existing' log to avoid non-share error */
    if (*context[context_num].logfile_name != 0)
        logfileio(F_CLOSE, context[context_num].logfile_name) ;
    
    /* Extract the 'new' logfile name.  Everything up to the first comma or     */
    /* space not contained with a leading and closing quotation mark is         */
    /* considered to be part of the log file name.  Everything afterwards is    */
    /* treated as a filter condition.  For example:                             */
    /*                                                                          */
    /* "Log File.txt" all   --> Log file name: Log File.txt   Filter: all       */
    /* Gensym.log           --> Log file name: Gensym.log     Filter: default   */
    /* x,Fatal              --> Log file name: x              Filter: fatal     */
    /* ------------------------------------------------------------------------ */
    ptr1 = context[context_num].logfile_name ;
    ptr2 = (GDB_CHAR*)gsi_str_of(arg[2]) ;
    
    if (*ptr2 == '"')
    {
        fSpaceOK = TRUE ;
        ptr2++ ;
    }
    while (*ptr2 != 0 && (fSpaceOK || (*ptr2 != ',' && *ptr2 != ' ')))
    {
        if (*ptr2 == '"' && fSpaceOK)
        {
            fSpaceOK = FALSE ;
            ptr2++ ;
            continue ;
        }
        if (*ptr2 != '~')
            *ptr1++ = *ptr2 ;
        ptr2++ ;
    }
    *ptr1 = 0 ;
    if (context[context_num].console_output) {
        wprintf(_T("Config Param: LOGFILE_NAME is: '%s'\n"), context[context_num].logfile_name);
    }

        /* extract logfile filters from name field (if they exist) and set the appropriate
    logfile filter flags */ 
    context[context_num].logfile_filter = DBG0;

    if (wstrstrci(ptr2, _T("INFO"))  != NULL) context[context_num].logfile_filter |= DBG2 ;
    if (wstrstrci(ptr2, _T("ERROR")) != NULL) context[context_num].logfile_filter |= DBG3 ;
    if (wstrstrci(ptr2, _T("WARN"))  != NULL) context[context_num].logfile_filter |= DBG4 ;
    if (wstrstrci(ptr2, _T("FATAL")) != NULL) context[context_num].logfile_filter |= DBGM ;
    if (wstrstrci(ptr2, _T("ALL"))   != NULL) context[context_num].logfile_filter  = LOGFILE_FILTER_ALL ;

    if (context[context_num].logfile_filter == DBG0) 
        context[context_num].logfile_filter = LOGFILE_FILTER_DEF ;
    
    if (!_wcsicmp(gsi_symbol_name(gsi_sym_of(arg[0])), SQL_OPEN))
        logfileio(F_OPEN, context[context_num].logfile_name) ;
    else
        logfileio(F_CLOSE, context[context_num].logfile_name) ;
    
    /* set logfile filter if supplied in filter argument */
    if (*gsi_str_of(arg[1]) != 0)
    {
        context[context_num].logfile_filter = DBG0;

        if (wstrstrci((GDB_CHAR*)gsi_str_of(arg[1]), (GDB_CHAR*)_T("INFO"))  != NULL) context[context_num].logfile_filter |= DBG2 ;
        if (wstrstrci((GDB_CHAR*)gsi_str_of(arg[1]), (GDB_CHAR*)_T("ERROR")) != NULL) context[context_num].logfile_filter |= DBG3 ;
        if (wstrstrci((GDB_CHAR*)gsi_str_of(arg[1]), (GDB_CHAR*)_T("WARN"))  != NULL) context[context_num].logfile_filter |= DBG4 ;
        if (wstrstrci((GDB_CHAR*)gsi_str_of(arg[1]), (GDB_CHAR*)_T("FATAL")) != NULL) context[context_num].logfile_filter |= DBGM ;
        if (wstrstrci((GDB_CHAR*)gsi_str_of(arg[1]), (GDB_CHAR*)_T("ALL"))   != NULL) context[context_num].logfile_filter  = LOGFILE_FILTER_ALL ;

        if (context[context_num].logfile_filter == DBG0) 
            context[context_num].logfile_filter = LOGFILE_FILTER_DEF ;
    }
    
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    configuration_rp                                                  GDB-RPC
      - configure the G2-to-bridge connection for this context and open
        logfile if name is supplied.
      - sets context[].available flag to TRUE upon SUCCESS_CD 
      - args: 
          [0]=kb-version,[1]=context-name,[2]=logfile-name,
          [3]=auto-db-reconnect,[4]=max-cursors,[5]=enable-messaging,
          [6]=null-string,[7]=null-number,[8]=set-null-string,
          [9]=set-null-number,[10]=set-null-options
 *===========================================================================*/
static void configuration_rp(gsi_item *arguments, gsi_int count, gsi_int call_index)
{
    gsi_item*   largs ;
    long        tmp_int ;
    long        warn_flag ;
    long        arg ;
    long        logArg ;
    long        len ;
    long        lX ;
    int         snNum, snTxt, snNull ;

    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("CONFIGURATION_RP: %"), context_num);
    }

    /* Disallow configuration if context is not active */
    if (!context[context_num].active) 
    {
        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, FALSE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_kill_context(context_num) ;
        return ;
    }
    
    /* Disallow multiple calls to this function */
    if (context[context_num].available)
    {
        iomsg(DBG4, LAYER, FALSE, TRUE, NULL, FALSE, "%d", WALCONF) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 8)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_kill_context(context_num) ;
        return ;
    }
    
    context[context_num].available = FALSE ;
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    arg = 0 ;
    
    /*-------------------------
    arg-0 = KB version
    -------------------------*/
    if (gsi_type_of(arguments[arg]) != GSI_INTEGER_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EUNEXDA, gsi_type_of(arguments[arg]), arg+1) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }

	if(!compare_kb_ver(gsi_int_of(arguments[arg])))
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", EWRNGKB, gsi_int_of(arguments[arg]), KB_VER) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_kill_context(context_num) ;
        return ;
    }
    arg++ ;
    
    /*-------------------------
    arg-1 = context name
    -------------------------*/
    if (*gsi_str_of(arguments[arg]) != 0)
    {
        warn_flag = FALSE ;
        len = wcslen(gsi_str_of(arguments[arg])) ;
        if (len > MAX_CONTEXT_NAME_LEN)
        {
            len = MAX_CONTEXT_NAME_LEN ;
            warn_flag = TRUE ;
        }
        if (context[context_num].name == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOSTRA) ;
            return_event_msg(NULL) ;
        }
        else 
        {
            wcsncpy(context[context_num].name, gsi_str_of(arguments[arg]), len) ;
            context[context_num].name[len] = 0 ;
            if (warn_flag)
            {
                printf("Config WARN : CONTEXT_NAME Exceeds max length of %d and has been truncated.\n", MAX_CONTEXT_NAME_LEN);
                set_stat(WARN_CD, WCTRUNC, NULL, FALSE, NULL) ;
                return_event_msg(NULL) ;
            }
            if (context[context_num].console_output || warn_flag) {

                wprintf(_T("Config OK   : CONTEXT_NAME set to: '%s' for context %d\n"), context[context_num].name, context_num);
	    }
        }
    }
    arg++ ;

    /*-------------------------------------------------------
    arg-2 = logfile name (Will be processed by log_file_rp)
    --------------------------------------------------------*/
    logArg = arg ;
    arg++ ;
    
    /*-------------------------
    arg-3 = auto db reconnect
    -------------------------*/
    context[context_num].auto_db_reconnect = FALSE ;
    if (gsi_log_of(arguments[arg]) == GSI_TRUE)
    {
        context[context_num].auto_db_reconnect = TRUE ;
        if (context[context_num].console_output) {

            wprintf(_T("Config OK   : AUTO_DB_RECONNECT set to: %s\n"), WSBOOLEAN(context[context_num].auto_db_reconnect));
	}
    }
    arg++ ;

    /*-------------------------
    arg-4 = max cursors   
    -------------------------*/
    if (gsi_int_of(arguments[arg]) > 0)
    {
        tmp_int = gsi_int_of(arguments[arg]) ;
        if (tmp_int > MAX_CURSORS) 
        {
            wprintf(_T("Config ERROR: MAX_CURSORS %d exceeds maximum %d\n"), tmp_int, MAX_CURSORS) ;
            wprintf(_T("Config OK   : MAX_CURSORS set to DEFAULT: %d\n"), context[context_num].max_cursors) ;
            set_stat(ERROR_CD, NULL_MSG, NULL, FALSE, _T("MAX_CURSORS exceeds maximum value.")) ;

            return_event_msg(NULL) ;
        }
        else
        {
            context[context_num].max_cursors = tmp_int ;
            if (context[context_num].console_output) {
                wprintf(_T("Config OK   : MAX_CURSORS set to: %d\n"), context[context_num].max_cursors);
	    }
        }
    }
    else {
        wprintf(_T("Config OK   : MAX_CURSORS set to DEFAULT: %d\n"), context[context_num].max_cursors);
    }
    arg++ ;

    /*-------------------------
    arg-5 = enable messaging
    -------------------------*/
    context[context_num].enable_messaging = FALSE ;
    if (gsi_log_of(arguments[arg]) == GSI_TRUE)
    {
        context[context_num].enable_messaging = TRUE ;
        if (context[context_num].console_output) {
            wprintf(_T("Config OK   : ENABLE_MESSAGING set to: %s\n"), WSBOOLEAN(context[context_num].enable_messaging)) ;
	}
    }
    arg++ ;

    /*-------------------------
    arg-6 = null string
    -------------------------*/
    if (*gsi_str_of(arguments[arg]) != 0)
    {
        if (context[context_num].null_string == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOSTRA) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        len = wcslen(gsi_str_of(arguments[arg])) ;
        if ((context[context_num].null_string  
            = (GDB_CHAR*)realloc(context[context_num].null_string, (len+1)*sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        wcsncpy(context[context_num].null_string, gsi_str_of(arguments[arg]), len) ;
        context[context_num].null_string[len] = 0 ;
        if (context[context_num].console_output) {
            wprintf(_T("Config OK   : NULL_STRING set to: '%s'\n"), context[context_num].null_string);
	}
    }
    arg++ ;
    
    /*-------------------------
    arg-7 = null number
    -------------------------*/
    if (gsi_int_of((arguments[arg])) != 0)
    {
        context[context_num].null_number = gsi_int_of((arguments[arg])) ;
        if (context[context_num].console_output) {
            wprintf(_T("Config OK   : NULL_NUMBER set to: %d\n"), context[context_num].null_number);
	}
    }
    arg++ ;
    
    /*-------------------------
    arg-8 = set null text
    -------------------------*/
    if (*gsi_str_of(arguments[arg]) != 0)
    {
        if (context[context_num].set_null_string == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOSTRA) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        len = wcslen(gsi_str_of(arguments[arg]));
        if ((context[context_num].set_null_string 
            = (GDB_CHAR*)realloc(context[context_num].set_null_string, (len+1)*sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        wcsncpy(context[context_num].set_null_string, gsi_str_of(arguments[arg]), len) ;
        context[context_num].set_null_string[len] = 0 ;
        if (context[context_num].console_output) {
            wprintf(_T("Config OK   : SET_NULL_STRING set to: '%s'\n"), context[context_num].set_null_string);
	}
    }
    arg++ ;
    
    /*-------------------------
    arg-9 = set null number
    -------------------------*/
    if (gsi_int_of((arguments[arg])) != 0)
    {
        context[context_num].set_null_number = gsi_int_of((arguments[arg])) ;
        if (context[context_num].console_output) {
            wprintf(_T("Config OK   : SET_NULL_NUMBER set to: %d\n"), context[context_num].set_null_number);
	}
    }
    arg++ ;

    /*---------------------------
    arg-10 = set null options
    ---------------------------*/
    lX = gsi_int_of(arguments[arg]) ;
    if (lX < 0)
        lX = -lX ;
    snNum = lX % 10 ;
    lX /= 10 ;
    snTxt = lX % 10 ;
    lX /= 10 ;
    snNull = lX % 10 ;
    
    /*  Make sure that a set-null-string has been specified if the set-null-string option is on. */
    /* ----------------------------------------------------------------------------------------- */
    if (snTxt &&  
        (context[context_num].set_null_string==NULL || !wcslen(context[context_num].set_null_string)))
    {
        snTxt = 0 ;
        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, FALSE, "%d", ESNUSDS) ;
    }
    
    context[context_num].set_null_options = ((snNull ? 0x4 : 0) | (snTxt ? 0x2 : 0) | (snNum ? 0x1 : 0)) ;
    arg++ ;
    
    
    
    /*-------------------------
    Finish-up configuration
    -------------------------*/
    
    /* display items modified via remote-process-initialization string */
    if (context[context_num].console_output && (context[context_num].max_reg_items != DFLT_REGISTERED_ITEMS))
      printf("Config OK   : MAX_REGISTERED_ITEMS set to: %d\n", context[context_num].max_reg_items);
    
    if (context[context_num].console_output && context[context_num].max_bind_vars != DFLT_BIND_VARS )
      printf("Config OK   : MAX_BIND_VARS set to: %d\n", context[context_num].max_bind_vars);
    
    if (context[context_num].console_output) printf("\n");
    
    /* make this context available for transactions */
    context[context_num].available = TRUE ;
    
    /* open the logfile if designated */
    if (wcslen(gsi_str_of(arguments[logArg])))
    {
        largs = gdb_item_array ;
        gsi_set_sym(largs[0], gsi_make_symbol((gsi_char*)SQL_OPEN)) ;
        gsi_set_str(largs[1], (gsi_char*)_T("")) ;
        gsi_set_str(largs[2], gsi_str_of(arguments[logArg])) ;
        context[context_num].no_rpc_return = TRUE ;
        log_file_rp(largs, 3, 0) ;
        context[context_num].no_rpc_return = FALSE ;
    }
    
    if (context[context_num].console_output) printf("\n") ;

    if (context[context_num].name != NULL) {
        iomsg(DBGALL, LAYER, TRUE, FALSE, NULL, FALSE, "%s%s%s", _T("G2-% Context Ready: %"),
	      wDB_TYPE, context[context_num].name);
    } else {
        iomsg(DBGALL, LAYER, TRUE, FALSE, NULL, FALSE, "%s%s%d", _T("G2-% Context Ready: %"),
	      wDB_TYPE, context_num);
    }

        /* reset status info - this function should have returned on a fatal configuration error
    prior to this point */
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    connect_rp                                                        GDB-RPC
      - connect 'this context' to the database
      - args: [0]=username,[1]=password,[2]=connect-string, [3]=gsi-connection-string
 *===========================================================================*/
static void connect_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    GDB_CHAR   *db_username = NULL ;
    GDB_CHAR   *db_password = NULL ;
    GDB_CHAR   *db_connect_str = NULL ;
    GDB_CHAR   *db_gsi_connection_str = NULL; /* gsi-connection-string. added for project 28544 Gensym-2012 */
    GDB_CHAR   *tmp ;
    long      status ;
    long      len ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("CONNECT_RP: %"), context_num);
    }

    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 3) /* added a new arg gsi-connection-string and increased the desired arg num. for project 28544 Gensym-2012 */
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = db username */
    tmp = (GDB_CHAR*)gsi_str_of(arg[0]) ;
    if (*tmp != 0)
    {
        len = wcslen(tmp) ;
        if ((db_username = (GDB_CHAR *)XCALLOC(len+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        wcscpy(db_username, tmp) ;
    }
    else 
    {  /* if username not supplied generate a null username */
        if ((db_username = (GDB_CHAR*)XCALLOC(1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        db_username[0] = 0 ;
    }
    
    /* arg-1 = db password */
    tmp = (GDB_CHAR*)gsi_str_of(arg[1]) ;
    if (*tmp != 0)
    {
        len = wcslen(tmp) ;
        if ((db_password = (GDB_CHAR*)XCALLOC(len+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            XFREE (db_username) ;
            return ;
        }
        wcscpy(db_password, tmp) ;
    }
    else 
    {
        if ((db_password = (GDB_CHAR*)XCALLOC(1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return_event_msg(NULL) ;
            XFREE (db_username) ;
            return ;
        }
        db_password[0] = 0 ;
    }
    
    /* arg-2 = db connect-string */
    tmp = (GDB_CHAR*)gsi_str_of(arg[2]) ;
	/*{{{ allow it not supplied since the gsi-connection-string may be supplied. Modified for project 28544 Gensym-2012 */
	if (*tmp != 0)
	{
		len = wcslen(tmp) ;
		if ((db_connect_str = (GDB_CHAR*)XCALLOC(len+1, sizeof(GDB_CHAR))) == NULL)
		{
			iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
			return_rpc_status(NULL, 0, NULL, call_index) ;
			XFREE(db_username) ;
			XFREE(db_password) ;
			return ;
		}
		wcscpy(db_connect_str, tmp) ;
	}
    else 
    {
        if ((db_connect_str = (GDB_CHAR*)XCALLOC(1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            return_event_msg(NULL) ;
            XFREE (db_username) ;
			XFREE(db_password) ;
            return ;
        }
        db_connect_str[0] = 0 ;
    }
	/*}}}*/

	if(count == 3)
	{
		if ((db_gsi_connection_str = (GDB_CHAR*)XCALLOC(1, sizeof(GDB_CHAR))) == NULL)
		{
			iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM);
			return_rpc_status(NULL, 0, NULL, call_index);
			XFREE(db_username);
			XFREE(db_password);
			XFREE(db_connect_str);
			return;
		}
		db_gsi_connection_str[0] = 0 ;

	}
	else
	{
		
		/*{{{ added for project 28544 Gensym-2012 */
		/* arg-3 = gsi-connection-string */
		tmp = (GDB_CHAR*)gsi_str_of(arg[3]);
		if ((tmp != NULL) && (*tmp != 0))
		{
			len = wcslen(tmp);
			if ((db_gsi_connection_str = (GDB_CHAR*)XCALLOC(len + 1, sizeof(GDB_CHAR))) == NULL)
			{
				iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM);
				return_rpc_status(NULL, 0, NULL, call_index);
				XFREE(db_username);
				XFREE(db_password);
				XFREE(db_connect_str);
				return;
			}
			wcscpy(db_gsi_connection_str, tmp);
		}
		else 
		{  /* if gsi-connection-string parameter not supported or supplied, generate a null string */
			if ((db_gsi_connection_str = (GDB_CHAR*)XCALLOC(1, sizeof(GDB_CHAR))) == NULL)
			{
				iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM);
				return_rpc_status(NULL, 0, NULL, call_index);
				XFREE(db_username);
				XFREE(db_password);
				XFREE(db_connect_str);
				return;
			}
			db_gsi_connection_str[0] = 0 ;
		}
	}
	/*}}}*/

    /* attempt to connect */
    status = process_connect(db_username, db_password, db_connect_str, db_gsi_connection_str) ;/* add gsi-connection-string. modified for project 28544 Gensym-2012 */
    
    /* return status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    
    XFREE(db_username) ;
    XFREE(db_password) ;
    XFREE(db_connect_str) ;
    XFREE(db_gsi_connection_str) ; /* free gsi-connection-string. added for project 28544 Gensym-2012 */
    
    return ;
}


/*===========================================================================*
    disconnect_rp                                                     GDB-RPC
      - disconnect 'this context' from the database
      - no arguments
 *===========================================================================*/
static void disconnect_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("DISCONNECT_RP: %"), context_num);
    }

    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    process_disconnect(TRUE, context_num) ;
    
    /* return disconnect status information from global status struct */ 
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    exec_immediate_rp                                                 GDB-RPC
      - Executes non-select sql statements. Does not use or accept 
        bind variables. Does not perform any processing of the SQL
        statement.
      - args: [0]=sql_statement
              [1]=auto-commit (GSI_TRUE,GSI_FALSE)
 *===========================================================================*/
static void exec_immediate_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    GDB_CHAR *sql_stmt ;
    long    status ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("EXEC_IMMEDIATE_RP: %"), context_num);
    }

    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 2)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = (non-select) SQL statement */
    sql_stmt = (GDB_CHAR*)gsi_str_of(arg[0]) ;
    if (debug & DBG6) {
      wprintf(_T("-----\nSQL: %s\n-----\n"), sql_stmt);
    }
    
    status = process_immediate(sql_stmt) ;
    
    /* only commit if process_immdediate succeeds and auto_commit is on */
    if (gsi_log_of(arg[1]) == GSI_TRUE && !status)
        process_commit() ;
    
    /* return status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    exec_sql_obj_rp                                                   GDB-RPC
      - Update or execute a SQL statement (containing bind vars), 
        prepared via 'exec_sql_rp'. Uses an object for bind vars.
      - sql-object must be defined () prior to calling
      - non-select sql statements
      - args: [0]=sql-object (passed as handle) - for object index
              [1]=bind variable names (map to object attribute names)
              [2]=GDB_UPDATE,GDB_EXECUTE 
              [3]=data-object (passed as item, defined by user)
              [4]=auto-commit
 *===========================================================================*/
static void exec_sql_obj_rp(gsi_item *arg, gsi_int count, gsi_int call_index )
{
    GENDA*                  genda_ptr ;
    gsi_attr*               attr ;
    gsi_int                 attr_type ;
    gsi_int                 nr_symbols ;
    gsi_int                 exec_mode ;
    gsi_int                 obj_handle ;
    gsi_int                 option_flag ;
    gsi_registered_item*    object ;
    int                     bind_flag = 0 ;
    long                    datatype ;
    long                    lngX ;
    long                    n, alen ;
    long                    status ;
    void**                  bind_array = NULL ;

    GDB_CHAR                action[3][8] = {_T("INIT"), _T("UPDATE"), _T("EXECUTE")};
    GDB_CHAR                bind_name[256];  /* ~~ if bind name > this then crash */
    GDB_CHAR*               bind_vars ;
    GDB_CHAR*               do_name = _T("UNNAMED");
    GDB_CHAR*               tmp_bind_vars = NULL;
    GDB_CHAR**              unpacked_symbols =NULL;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("EXEC_SQL_OBJ_RP: %"), context_num) ;
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 5 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
#ifdef _DEBUG
    wprintf(_T("\ncount = %d\n"), count) ;
    wprintf(_T("-------------------------------------------------------\n")) ;
    wprintf(_T(" SQL-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0])) ;
    wprintf(_T("    Handle:      %d\n"), gsi_handle_of(arg[0])) ;
    get_attrib_info(arg[0]) ;
    
    wprintf(_T("\n-------------------------------------------------------\n")) ;
    wprintf(_T(" Data-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[3]), gsi_type_to_string(arg[3])) ;
    wprintf(_T("    Class Name:  %s\n"), gsi_symbol_name(gsi_class_name_of(arg[3]))) ;
    if (gsi_name_of(arg[3]) == NULL)
        wprintf(_T("    Object Name: (null)\n")) ;
    else
        wprintf(_T("    Object Name: %s\n"), gsi_symbol_name(gsi_name_of(arg[3]))) ;
    get_attrib_info(arg[3]) ;
#endif
    
    /* arg-0 = object handle of sql-object */
    obj_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (obj_handle < MIN_ITEM_HANDLE )
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* identify the genda pointer from the user ptr */
    genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
    
    if (genda_ptr == NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
        update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* make sure SQL statement has been previously processed */
    if (genda_ptr->stmt_id <= 0) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ESQLPRO) ;
        update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* clear out the status attribs of the object */
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], obj_handle) ;
    clear_g2_obj_status(object[0]) ;
    
    /* arg-2 is the mode (GDB_UPDATE,GDB_EXECUTE) */
    exec_mode = gsi_int_of(arg[2]) ;
    
    if (debug & DBG6) {
        wprintf(_T("    Mode: %s\n"), action[exec_mode - 1]) ;
    }
    
    if (exec_mode == GDB_EXECUTE)
    {
        if (!genda_ptr->array_size || !genda_ptr->bind_processed)
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOINPT) ;
            update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        /* execute the SQL (array_size of GENDA set to bind array size during UPDATE) */
        status = process_exec_sql_obj(genda_ptr, genda_ptr->array_size) ;
        
        /* arg-4 = auto-commit - only commit if process_exec_sql_obj succeeds and auto_commit is on */
        if (gsi_log_of(arg[4]) == GSI_TRUE && !status)
            process_commit() ;
        
        /* bind vars will be released (following an execute) if the sql-object is either
           update'd or the sql-object is deleted/disabled via receive_deregistrations */
    }
    else if (exec_mode == GDB_UPDATE)
    {
        /* Since we're not acutally acessing the DB on a bind var update,
           'ping' the connection to see if it's still there. If not, abort
           the update and return DISCONNECTED. This will also cause the IO
           to db-connection-status to be set to DISCONNECTED via KB logic */
        if (process_ping_db())
        {
            update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
        }
        
        /* arg-1 has the bind variable names (and must be supplied) */
        bind_vars = (GDB_CHAR*)gsi_str_of(arg[1]) ;
        
        if (*bind_vars == 0)
        {
            if (debug & DBG6) printf("-----\nBIND: \n-----\n") ;
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOINPT) ;
            update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        
        if ((tmp_bind_vars = (GDB_CHAR*)XCALLOC(wcslen(bind_vars)+1, sizeof(GDB_CHAR))) == NULL)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        
        wcscpy(tmp_bind_vars, bind_vars) ;
        upper_case(tmp_bind_vars) ;
        if (debug & DBG6) {
	    wprintf(_T("-----\nBIND: %s\n-----\n"), tmp_bind_vars) ;
	}
        
        /* release bind vars if previously allocated */
        process_release_bind(BIND, genda_ptr) ;
        
        /* arg-3 = the user-defined input data object */
        if (gsi_name_of(arg[3]) != NULL)
            do_name = (GDB_CHAR*)gsi_symbol_name(gsi_name_of(arg[3])) ;
        
        /* reset status */
        iomsg(DBG0, LAYER, TRUE, TRUE, NULL, FALSE, "%d", NULL_MSG) ;
        
        /* verify that # of bind vars 'described' equals # bind vars
        supplied in 'tmp_bind_vars' */
        if (process_count_bind_vars(genda_ptr, tmp_bind_vars))
        {
            update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            XFREE(tmp_bind_vars) ;
            return ;
        }
        
        /* look at each bind var name and get the data from the corresponding 
        attribute of the user-defined object */
        genda_ptr->array_size = 0 ;
        n = 0 ;
        alen = 0 ;
        while (strgettoken(tmp_bind_vars, bind_name, ',', n) != NULL)
        {
            option_flag = gsi_option_is_set(GSI_SUPPRESS_OUTPUT) ;
            gsi_set_option(GSI_SUPPRESS_OUTPUT) ;
            
            attr = gsi_attr_by_name(arg[3], gsi_make_symbol((gsi_char*)bind_name)) ;
            if (!option_flag)
                gsi_reset_option(GSI_SUPPRESS_OUTPUT) ;
            if (attr == NULL)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s%s", ENOATTR, bind_name, do_name) ;
                update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                XFREE(tmp_bind_vars) ;
                return ;
            } 
            alen = gsi_element_count_of(attr) ;
            if (!alen)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s%s", ENOATTR, bind_name, do_name) ;
                update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                XFREE(tmp_bind_vars) ;
                return ;
            } 
            
            if (alen != genda_ptr->array_size && genda_ptr->array_size != 0)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBNDLEN) ;
                update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                XFREE(tmp_bind_vars) ;
                return ;
            }
            genda_ptr->array_size = alen ;
            
            bind_flag = 0 ;
            datatype = 0 ;
            status = 0 ;
            
            attr_type = gsi_type_of(attr) ;
            if (attr_type == GSI_SYMBOL_ARRAY_TAG || attr_type == GSI_SYMBOL_LIST_TAG)
            {
                nr_symbols =  gsi_element_count_of(attr) ;
                if (nr_symbols)
                {
                    unpacked_symbols = (GDB_CHAR**)XCALLOC(nr_symbols, sizeof(GDB_CHAR*))  ;
                    if (unpacked_symbols == NULL)
                    {
                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                        update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
                        return_rpc_status(NULL, 0, NULL, call_index) ;
                        return ;
                    }
                    bind_array = (attr_type == GSI_SYMBOL_ARRAY_TAG) ? (void **)gsi_sym_array_of(attr) : 
                                                                       (void**)gsi_sym_list_of(attr) ;
                    for (lngX = 0 ; lngX < nr_symbols ; lngX++)
                        unpacked_symbols[lngX] = (GDB_CHAR*)gsi_symbol_name(bind_array[lngX]) ;
                    bind_array = (void**)unpacked_symbols ;
                }
            }
            switch (attr_type)
            {
            case GSI_INTEGER_ARRAY_TAG: 
                                        bind_array = (void **)gsi_int_array_of(attr) ;
                                        datatype = GDB_INT_TYPE ;
                                        break ;
            case GSI_SYMBOL_ARRAY_TAG:
                                        /* bind_array was prepared before this switch */
                                        datatype = GDB_STRING_TYPE ;
                                        break ;
            case GSI_STRING_ARRAY_TAG:
                                        bind_array = (void **)gsi_str_array_of(attr) ;
                                        datatype = GDB_STRING_TYPE ;
                                        break ;
            case GSI_LOGICAL_ARRAY_TAG:
                                        bind_array = (void **)gsi_log_array_of(attr) ;
                                        datatype = GDB_STRING_TYPE ;
                                        break ;
            case GSI_FLOAT64_ARRAY_TAG:
                                        bind_array = (void **)gsi_flt_array_of(attr) ;
                                        datatype = GDB_FLOAT_TYPE ;
                                        break ;
                
            case GSI_INTEGER_LIST_TAG: 
                                        bind_array = (void **)gsi_int_list_of(attr) ;
                                        datatype = GDB_INT_TYPE ;
                                        break ;
            case GSI_SYMBOL_LIST_TAG:
                                        /* bind_array was prepared before this switch */
                                        datatype = GDB_STRING_TYPE ;
                                        break ;
            case GSI_STRING_LIST_TAG:
                                        bind_array = (void **)gsi_str_list_of(attr) ;
                                        datatype = GDB_STRING_TYPE ;
                                        break ;
            case GSI_LOGICAL_LIST_TAG:
                                        bind_array = (void **)gsi_log_list_of(attr) ;
                                        datatype = GDB_STRING_TYPE ;
                                        break ;
            case GSI_FLOAT64_LIST_TAG:
                                        bind_array = (void **)gsi_flt_list_of(attr) ;
                                        datatype = GDB_FLOAT_TYPE ;
                                        break ;
                
            default:
                                        datatype = 0 ;
                                        bind_array = NULL ;
                                        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s%s", EUNSPDT, 
                                                        gsi_type_to_string(attr), bind_name) ;
                                        break ;
                
            } /* switch */
            
            /* load the bind variable values for each bind variable */
            if (datatype != 0)
                status = process_set_exec_sql_obj(bind_array, genda_ptr, n, datatype, genda_ptr->array_size) ;
            if (unpacked_symbols)
            {
                XFREE(unpacked_symbols) ;
                unpacked_symbols = NULL ;
            }
            if (status || !datatype)
            {
                genda_ptr->array_size = 0 ; /* causes execute to fail with 'bind not processed' */
                genda_ptr->bind_processed = FALSE ;
                update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                XFREE(tmp_bind_vars) ;
                return ;
            }
            else
                genda_ptr->bind_processed = TRUE ;
            
            n++ ;
            
        } /* while */
    
        if (tmp_bind_vars != NULL)
            XFREE(tmp_bind_vars) ;
    
    } /* gdb_update */
  
    /* set the status attributes */
    update_object_status(arg[0], NULL, RETURN_TO_OBJECT, 0) ;
  
    /* return status information from global status struct */
    return_rpc_status(NULL, 0, NULL, call_index) ;
  
    return ;
}


/*===========================================================================*
    set_cursor_rp                                                     GDB-RPC
      - initialize a SQL query statement that contains 'input' variables
        (or placeholders i.e. :xyz)
      - INIT=initializes the query and sets the input variables
      - UPDATE=sets the input variables only
      - args: [0]=cursor-object (passed as handle)
              [1]=sql_stmt
              [2]=GDB_INIT,GDB_UPDATE 
              [3]=input vars
 *===========================================================================*/
static void set_cursor_rp(gsi_item *arg, gsi_int count, gsi_int call_index )
{
    gsi_registered_item *object ;
    BIND_STRUCT         bind ;
    gsi_attr            *attrs ;
    GENDA               *genda_ptr ;
    GDB_CHAR             *select_string ;
    gsi_int             select_mode ;
    gsi_int             obj_handle ;
    long                status ;
    long                bind_flag = 0 ;
    long                n ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("SET_CURSOR_RP: %"), context_num) ;
    }

    if (!context[context_num].available || !context[context_num].connected_to_db)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 4 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = object handle */
    obj_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (obj_handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* point to the object identified by obj_handle */
    object = gdb_registered_item_array ;
    gsi_clear_item(object[0]) ;
    gsi_set_handle(object[0], obj_handle) ;
    
    /* arg-1 is the select_statement */
    select_string = (GDB_CHAR*)gsi_str_of(arg[1]) ;
    
    if (debug & DBG6) {
      wprintf(_T("-----\nSQL: %s\n-----\n"), select_string) ;
    }
    
    /* arg-2 is the mode (GDB_INIT,GDB_UPDATE) */
    select_mode = gsi_int_of(arg[2]) ;
    
    /* arg-3 is the input variables */
    bind.nBind = gsi_element_count_of(arg[3]) ; /* copied to descriptor in L3 */
    if (bind.nBind > 0)
    {
        bind.bind_array = (GDB_CHAR**)gsi_str_list_of(arg[3]) ;
        if (debug & DBG6) 
        {
            printf("-----\nBIND: ");
            for (n=0;n<bind.nBind;n++) {
                wprintf(_T("(%d)%s "), n+1, bind. bind_array[n]);
	    }
            printf("\n-----\n") ;
        }
    }
    else
        bind.bind_array = NULL ;
    
    /* identify the genda pointer from the user ptr */
    genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
    
    if (genda_ptr == (GENDA *)NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
        update_object_status(object[0], NULL, RETURN_TO_OBJECT, 0) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    clear_g2_obj_status(object[0]) ;
    
    if (select_mode == GDB_INIT)
    {
        status = process_set_dynamic_query(select_string, &bind, genda_ptr, GDB_INIT) ;
        if (!status && bind.bind_array != NULL && bind.nBind > 0)
            status = process_refresh_cursor(genda_ptr) ;
    }
    else if (select_mode == GDB_UPDATE)
    {
        /* make sure the SQL statement has been previously processed */
        if (genda_ptr->stmt_id <= 0)
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ESQLPRO) ;
            update_object_status(object[0], NULL, RETURN_TO_OBJECT, 0) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        status = process_set_dynamic_query(select_string, &bind, genda_ptr, GDB_UPDATE) ;
        if (!status)
            status = process_refresh_cursor(genda_ptr) ;
    }
    
    /* reset the cursor status */
    attrs = gdb_attr_item_array ;
    update_object_status(attrs, NULL, UPDATE_ATTRS, 0) ;
    gsi_set_int(attrs[CURSOR_POS], 0) ;
    gsi_return_attrs(object[0], attrs, NUM_STATUS_ARGS, context_num) ;
    
    /* return rpc status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    
    return ;
}


/*===========================================================================*
    release_cursor                                                    GDB-RPC
 *===========================================================================*/
long release_cursor()
{
    /* release resources for the current object being destroyed */
    return GDB_SUCCESS ;
}


/*===========================================================================*
    exec_sql_rp                                                       GDB-RPC
      - initialize a SQL non-query statement that contains 'input' variables
        (or placeholders i.e. :xyz)
      - GDB_INIT=initializes the SQL stmt and sets the input variables
      - GDB_UPDATE=sets/resets the input variables only
      - GDB_EXECUTE=executes the non-query stmt via bind descriptor
      - args: [0]=sql-object (passed as handle)
              [1]=sql_stmt
              [2]=GDB_INIT,GDB_UPDATE,GDB_EXECUTE 
              [3]=input vars
              [4]=auto-commit
 *===========================================================================*/
static void exec_sql_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    gsi_registered_item *object ;
    BIND_STRUCT         bind ;
    GENDA               *genda_ptr ;
    GDB_CHAR            *exec_string ;
    gsi_int             exec_mode ;
    gsi_int             obj_handle ;
    long                status, n ;

	GDB_CHAR            action[3][8] = {_T("INIT"), _T("UPDATE"), _T("EXECUTE")};

    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("EXEC_SQL_RP: %"), context_num);
    }
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 5 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
#ifdef _DEBUG
    printf("\ncount = %d\n", count);
    printf("-------------------------------------------------------\n");
    printf(" SQL-Object Information\n");
    printf("-------------------------------------------------------\n\n");

    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0]));

    printf("    Handle:      %d\n", gsi_handle_of(arg[0]));
    get_attrib_info(arg[0]);
#endif
    
    /* arg-0 = object handle */
    obj_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (obj_handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* point to the object identified by obj_handle */
    object = gdb_registered_item_array ;
    gsi_clear_item(object[0]) ;
    gsi_set_handle(object[0], obj_handle) ;
    
    /* arg-1 is the SQL statement */
    exec_string = (GDB_CHAR*)gsi_str_of(arg[1]) ;
    if (debug & DBG6) {
      wprintf(_T("-----\nSQL: %s\n-----\n"), exec_string);

    }
    
    /* arg-2 is the mode (GDB_INIT,GDB_UPDATE,GDB_EXECUTE) */
    exec_mode = gsi_int_of(arg[2]) ;
    
    if (debug & DBG6) {
        wprintf(_T("    Mode: %s\n"), action[exec_mode - 1]) ;
    }

    /* arg-3 is the input variables */
    bind.nBind = gsi_element_count_of(arg[3]) ; /* copied to descriptor in L3 */
    if (bind.nBind > 0) 
    {
        bind.bind_array = (GDB_CHAR**)gsi_str_list_of(arg[3]) ;
        if (debug & DBG6) 
        {
            printf("-----\nBIND: ");
            for (n=0; n<bind.nBind; n++) {
                wprintf(_T("(%d)%s "), n+1, bind.bind_array[n]);
	    }
            printf("\n-----\n");
        }
    }
    else
        bind.bind_array = NULL ;
    
    /* identify the genda pointer from the user ptr */
    genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
    
    if (genda_ptr == NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
        update_object_status(object[0], NULL, RETURN_TO_OBJECT, 0) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* clear out the status attribs of the object */
    clear_g2_obj_status(object[0]) ;
    
    if (exec_mode == GDB_INIT)
    {
        status = process_set_exec_sql(exec_string, &bind, genda_ptr, GDB_INIT) ;
    }
    else if (exec_mode == GDB_UPDATE) 
    {
        /* Since we're not acutally acessing the DB on a bind var update,
           'ping' the connection to see if it's still there. If not, abort
           the update and return DISCONNECTED. This will also cause the IO
           to db-connection-status to be set to DISCONNECTED via KB logic */
        if (process_ping_db())
        {
            update_object_status(object[0], NULL, RETURN_TO_OBJECT, 0) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        status = process_set_exec_sql(exec_string, &bind, genda_ptr, GDB_UPDATE) ;
    }
    else if (exec_mode == GDB_EXECUTE)
    {
        status = process_exec_sql(genda_ptr) ;
        if (gsi_log_of(arg[4]) == GSI_TRUE && !status)
            process_commit() ;
    }
    
    update_object_status(object[0], NULL, RETURN_TO_OBJECT, 0) ;
    
    /* return rpc status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    refresh_cursor_rp                                                 GDB-RPC
      - close & reopen cursor
      - args: [0]=cursor-object (passed as handle)
 *===========================================================================*/
static void refresh_cursor_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    GENDA     *genda_ptr ;
    gsi_registered_item  *object ;
    long       handle ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("REFRESH_CURSOR_RP: %"), context_num);
    }
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 1 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = the object handle */
    handle = gsi_handle_of(arg[0]) ;
    if (handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* Get the genda from the object handle */
    genda_ptr = storage_area(GET, context_num, handle, NULL) ;
    
    if (genda_ptr == NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    process_refresh_cursor(genda_ptr) ;
    
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], handle) ;
    
    clear_g2_obj_status(object[0]) ;
    
    /* return status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    sql_function_rp                                                   GDB-RPC
      - This procedure accepts any valid SQL query statement and returns the
        row1,col1 value. Originally designed to support SQL functions such as
        SUM, MIN, MAX, AVG, etc.
      - returns either a string or a float depending upon the datatype of the
        row1,col1 value.
      - args: [0]=sql_statement
 *===========================================================================*/
static void sql_function_rp(gsi_item *arg, gsi_int count, gsi_int call_index )
{
    gsi_item     *ret_args ;
    GENDA        *genda_ptr ;
    GDB_CHAR      *sql_stmt ;
    long          status ;
    double        float_val ;
    
    context_num = gsi_current_context() ;
    
    if (context_num < 0 || context[context_num].no_rpc_return) 
        return ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("SQL_FUNCTION_RP: %"), context_num);
    }
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 1) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    ret_args = gdb_item_array ;
    
    /* initialize both return values to null */ 
    float_val = (double)context[context_num].null_number ;
    GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
    gsi_set_flt( ret_args[STAT_POS], float_val) ;
    gsi_set_str(ret_args[STAT_POS+1], (gsi_char*)context[context_num].null_string) ;
    
    sql_stmt = (GDB_CHAR*)gsi_str_of(arg[0]) ;
    if (debug & DBG6) {
      wprintf(_T("-----\nSQL: %s\n-----\n"), sql_stmt);
    }
    
    genda_ptr = process_sql_function(sql_stmt) ;
    
    if (genda_ptr != (GENDA *)NULL)
    {
        status = alloc_genda(genda_ptr, ALLOC_ONE) ;
        if (!status) 
        {
            status = update_genda(genda_ptr) ;
            if (genda_ptr->ncols > 0 && genda_ptr->da_col_ptr[0].ind[0] >= 0 && genda_ptr->genStat.rows_processed > 0)
            {
                if (!status) 
                {
                    switch(genda_ptr->da_col_ptr[0].data_type)
                    {
                    case GDB_BYTE_TYPE :
                                        float_val = (GDB_DBL)genda_ptr->da_col_ptr[0].val[0].gdb_byte ;
                                        GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
                                        gsi_set_flt(ret_args[STAT_POS], float_val) ;
                                        break ;
                    case GDB_SHORT_TYPE :
                                        float_val = (GDB_DBL)genda_ptr->da_col_ptr[0].val[0].gdb_short ;
                                        GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
                                        gsi_set_flt(ret_args[STAT_POS], float_val) ;
                                        break ;
                    case GDB_INT_TYPE :
                                        float_val = (GDB_DBL)genda_ptr->da_col_ptr[0].val[0].gdb_int ;
                                        GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
                                        gsi_set_flt(ret_args[STAT_POS], float_val) ;
                                        break ;
                    case GDB_LONG_TYPE :
                                        float_val = (GDB_DBL)genda_ptr->da_col_ptr[0].val[0].gdb_long ;
                                        GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
                                        /* No need to check for MAX_G2_INTEGER as converting to float anyway */
                                        gsi_set_flt( ret_args[STAT_POS], float_val) ;
                                        break ;
                    case GDB_FLOAT_TYPE :
                                        float_val = (GDB_DBL)genda_ptr->da_col_ptr[0].val[0].gdb_float ;
                                        GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
                                        gsi_set_flt(ret_args[STAT_POS], float_val) ;
                                        break ;
                    case GDB_DBL_TYPE :
                                        float_val = genda_ptr->da_col_ptr[0].val[0].gdb_dbl ;
                                        GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
                                        gsi_set_flt(ret_args[STAT_POS], float_val) ;
                                        break ;
                    case GDB_STRING_TYPE :
                                        gsi_set_str(ret_args[STAT_POS+1], (gsi_char*)genda_ptr->da_col_ptr[0].val[0].gdb_str) ;
                                        break ;
                    default :
                                        break ;
                    }
                }
            }
        }
    }
    
    if (context[context_num].gbl_status.status == EOCURSOR_CD)
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
    
    update_object_status(ret_args, NULL, UPDATE_ITEMS, 2) ;
    return_rpc_status(ret_args, 2+NUM_STATUS_ARGS, NULL, call_index) ;
    
    if (genda_ptr != NULL)
        free_genda(ALL, genda_ptr) ;
    
    return ;
}


/*===========================================================================*
    commit_rp                                                         GDB-RPC
      - make a transaction permanent in the database
      - no arguments
 *===========================================================================*/
static void commit_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("COMMIT_RP: %"), context_num);
    }
    
    if (!context[context_num].available) {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    process_commit() ;
    if (debug & DBG5) show_results(NULL) ;
    
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    rollback_rp                                                       GDB-RPC
      - undo a 'non-committed' transaction in the database
      - no arguments
 *===========================================================================*/
static void rollback_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("ROLLBACK_RP: %"), context_num);
    }
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    process_rollback() ;

    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    kill_bridge_rp                                                    GDB-RPC
      - disconnect from database, close logfiles
      - terminate the current bridge process
      - no arguments
 *===========================================================================*/
static void kill_bridge_rp(gsi_item *arg_list, gsi_int count, gsi_int call_index)
{
    register gsi_int    this_context ;
    GDB_CHAR            t_stamp[MAX_TIMESTAMP_LEN] ;

    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s", _T("KILL_BRIDGE_RP"));
    }
    
    if (context[context_num].console_output) 
    {
        printf("\n\nShutting down G2-%s Bridge: ", DB_TYPE);
	wprintf(_T("%s\n"), TIME_STAMP(DFLT_TS_FMT, t_stamp));
        printf("-----------------------------------------------------\n") ;
    }
    
    for (this_context=0; this_context < MAX_GDB_CONTEXTS; this_context++)
    {
        if (!context[this_context].active)
            continue ;
        
        context[this_context].no_rpc_return = TRUE ;
        
        /* disconnect from database */
        if (context[this_context].connected_to_db) 
        {
            process_disconnect(FALSE, this_context) ;
            return_event_msg(NULL) ;
        }
        
        /* close the logfile if designated */
        if (context[this_context].logfile_name != NULL)
        {
            logfileio(F_CLOSE, context[this_context].logfile_name) ;
            XFREE(context[this_context].logfile_name) ;
            context[this_context].logfile_name = NULL ;
            return_event_msg(NULL) ;
        }
    }
    
    if (context[context_num].console_output) printf("\n") ;
    
    printf("\n");

    printf("   === G2-%s ", DB_TYPE);
    wprintf(_T("%s @ %s ===\n"), MSG_INFO[IBRTERM], TIME_STAMP(DFLT_TS_FMT, t_stamp));

    printf("\n");
    
    exit(0) ;
} 


/*===========================================================================*
    exec_stored_proc_rp                                               GDB-RPC
      - execute a database stored procedure.
      - args: [0]=stored procedure call              
              [1]=action: EXEC=execute,no return args,QUERY = return values
              [2]=object handle
 *===========================================================================*/
static void exec_stored_proc_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    gsi_registered_item *object ;
    GENDA               *genda_ptr ;
    GDB_CHAR             *sql_stmt ;
    GDB_CHAR             *action ;
    gsi_int             obj_handle ;
    long                status = 0 ;
    long                len ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("EXEC_STORED_PROC_RP: %"), context_num);
    }
    
    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 2) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = stored-procedure call */
    len = wcslen(gsi_str_of(arg[0])) ;
    if ((sql_stmt = (GDB_CHAR*)XCALLOC(len+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    wcscpy(sql_stmt, gsi_str_of(arg[0])) ;
    if (debug & DBG6) {
      wprintf(_T("-----\nSQL: %s\n-----\n"), sql_stmt);
    }
    
    /* arg-1 = action */
    action = (GDB_CHAR*)gsi_str_of(arg[1]) ;
    
    if (!_wcsicmp(action, SQL_QUERY))
    {
        /* arg-2 = object handle */
        obj_handle = gsi_int_of(arg[2]) ;
        
        /* Check for ok handle, and object */
        if (obj_handle < MIN_ITEM_HANDLE)
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        object = gdb_registered_item_array ;
        gsi_clear_item(object[0]) ;
        gsi_set_handle(object[0], obj_handle) ;
    }
    
    if (!_wcsicmp(action, SQL_EXEC))
        status = execute_stored_proc(sql_stmt) ;
    else
    {
        if (!_wcsicmp(action, SQL_QUERY))
        {
            /* identify the genda pointer from the user ptr */
            genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
            
            if (genda_ptr == NULL)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
                update_object_status(object[0], NULL, RETURN_TO_OBJECT, 0) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                return ;
            }
            process_stored_proc(sql_stmt, genda_ptr) ;
        }
    }
    
    /* return status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    
    XFREE(sql_stmt) ;

    return ;
}


/*===========================================================================*
    exec_stored_proc_return_rp
      - execute a database stored procedure & return values
      - args: [0]=stored procedure name             
              [1]=stored procedure arguments
      - returns a string that is generated by the user. The string can be
        delimited in any way and decoded back in G2. NOTE: This proc requires
        the sql script 'sp_example.sql' or equivalent. The stored procedure
        MUST be called 'sp_handler'.
 *===========================================================================*/ 
static void exec_stored_proc_return_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    GDB_CHAR    *sp_name, *sp_args ;
    gsi_item   *ret_args ;
    GDB_CHAR    sp_ret_val[EXSPRET_SZ+1];  /* this size must match the size in gdb_client_xxx.yy */
    long       status=0 ;
    long       len ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("EXEC_STORED_PROC_RETURN_RP: %"), context_num);
    }
    
    ret_args = gdb_item_array ;
    gsi_set_str(ret_args[STAT_POS+1], (gsi_char*)context[context_num].null_string) ;
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 2) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = sp name */
    len = wcslen(gsi_str_of(arg[0])) ;
    if ((sp_name = (GDB_CHAR*)XCALLOC(len+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    wcscpy(sp_name, gsi_str_of(arg[0])) ;
    
    /* arg-1 = sp args */
    len = wcslen(gsi_str_of(arg[1])) ;
    if ((sp_args = (GDB_CHAR*)XCALLOC(len+1, sizeof(GDB_CHAR))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    wcscpy(sp_args, gsi_str_of(arg[1])) ;
    
    status = execute_stored_proc_return(sp_name, sp_args, sp_ret_val) ;
    
    /* return status information from global status struct */   
    gsi_set_str(ret_args[STAT_POS], (gsi_char*)sp_ret_val) ;
    update_object_status(ret_args, NULL, UPDATE_ITEMS, 1) ;
    return_rpc_status(ret_args, 1+NUM_STATUS_ARGS, NULL, call_index) ;
    
    XFREE (sp_name) ;
    XFREE (sp_args) ;
    return ;
}


/*===========================================================================*
    ping_db_rp                                                        GDB-RPC
      - ping the database to verify connection
      - no arguments
 *===========================================================================*/
static void ping_db_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("PING_DB_RP: %"), context_num);
    }

    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    process_ping_db() ;
    
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}


/*===========================================================================*
    fetch_records_rp                                       (AAA)      GDB-RPC
      - fetches records from a cursor defined via 'set_cursor_rp'.
        Data value are returned directly to the attributes of a query
        object. 
      - args: [0]=cursor-object (passed as handle)
              [1]=query-object  (passed as handle)
              [2]=fetch_batch
              [3]=sequence of attribute names
              [4]=sequence of attribute types
 *===========================================================================*/
static void fetch_records_rp(gsi_item *arg, gsi_int count, gsi_int call_index )
{
    double                  dblX ;
    GENDA*                  genda_ptr ;
    gsi_item*               status_args ;
    gsi_attr*               ret_record;         /* Row vector pointer */
    gsi_int                 cursor_obj_handle ;
    gsi_int                 query_obj_handle ;
    gsi_registered_item*    object ;
    gsi_symbol              symX ;
    register long           col_count ;
    long                    fetch_batch;        /* default batch is ALL records (0) */
    long                    batch_count;        /* fetch_batch row counter */
    long                    status;             /* local status */
    long                    num_ret_atts;       /* number of total attrs returned */
    long                    num_status_args ;
    long                    rcd=0;              /* local record (row) counter */
    long                    smart_fetch ;
    long                    selectColumnType ;
    long*                   column_receptacle_type ;
    long                    attr_type ;
    long                    lngX ;
    long                    idX ;
    short                   incompat_attr_err ;
    short                   int_ovf ;
    short                   int_ovf_err ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("FETCH_RECORDS_RP: %"), context_num) ;
    
    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }

    smart_fetch = context[context_num].smart_fetch ;
    
    if (count < 5 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG || gsi_type_of(arg[1]) != GSI_HANDLE_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = cursor object handle */
    cursor_obj_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (cursor_obj_handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-1 = query object handle */
    object = gdb_registered_item_array ;
    query_obj_handle = gsi_handle_of(arg[1]) ;
    gsi_clear_item(object[0]) ;
    gsi_set_handle(object[0], query_obj_handle) ;
    
    /* Check for ok handle, and object */
    if (query_obj_handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-2 is fetch_batch size */
    fetch_batch = gsi_int_of(arg[2]) ;

    /* identify the genda pointer from the user ptr */
    genda_ptr = storage_area(GET, context_num, cursor_obj_handle, NULL) ;
    
    if (genda_ptr == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (genda_ptr->genStat.rows_processed != 0 && genda_ptr->genda_pos == 0 &&
        genda_ptr->more_rows != genda_ptr->nrows )
    {
    /* If positioned at EOCURSOR simply return EOCURSOR message until user
       either performs SET_QUERY or REFRESH_CURSOR: This check is provided
       because Oracle will automatically refresh the cursor. Performing a
       'ping' here so EOCURSOR message is not returned while disconnected.
       This will also cause the G2 IO db-connection-status to be set to 
       disconnected via KB logic */   
        
        if (!process_ping_db())    
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        else
        {
            status_args = gsi_make_items(NUM_STATUS_ARGS) ;
            update_object_status(status_args, NULL, UPDATE_ITEMS, 0) ;
            return_rpc_status(status_args, NUM_STATUS_ARGS, NULL, call_index) ;
            gsi_reclaim_items(status_args) ;
            genda_ptr->more_rows = 0 ; /* make sure its 0 */
                                       /* this will prevent EOCURSOR message from being returned
                                          following a reconnect */
            genda_ptr->genStat.rows_processed = 0 ;
            return ;
        }
        genda_ptr->more_rows = 0 ; /* make sure its 0 */
        return_rpc_status(NULL, 0, genda_ptr, call_index) ;
        return ;
    }
    
    /* clear out the status attribs of the object */
    if (genda_ptr->genda_pos == 0 && genda_ptr->genStat.status != EOCURSOR_CD)
        clear_g2_obj_status(object[0]) ;
    
    /* Initially Allocate, then Update (populate) the GENDA with db data */
    if (genda_ptr->genda_pos == 0) 
    {
        status = alloc_genda(genda_ptr, ALLOC_ALL) ;
        if (!status)
            status = update_genda(genda_ptr) ;
        if (status)
        {
            update_object_status(object[0], genda_ptr, RETURN_TO_OBJECT, 0) ;
            /* Errors, no data, return error info */
            return_rpc_status(NULL, 0, NULL, call_index) ;
            free_genda(DATA_ONLY, genda_ptr) ;
            return ;
        }
    }
    if (genda_ptr->genda_pos == -1)     /* First rows have already been loaded */
        genda_ptr->genda_pos = 0 ;
    
    /* Calculate the correct number of return attributes */
    num_ret_atts = 0 ;
    num_status_args = 0 ;
    
    /* Establish the vector to return the record of data/status */
    ret_record = gdb_attr_item_array ;   /* gdb_attr_item_array */

    column_receptacle_type = build_receptacle_type_list(genda_ptr, arg[3], arg[4]) ;
    if (column_receptacle_type == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ERATYEF) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /******************
     * START FETCHING *
     ******************/
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, FALSE, "%d", NULL_MSG) ;
    batch_count = 0 ;
    
    while ((batch_count < fetch_batch || fetch_batch == 0) && context_num >= 0)
    {
        /* Test for fetched last row in GENDA XFREE & realloc */
        if (genda_ptr->genStat.status != EOCURSOR_CD) 
        {
            if (genda_ptr->genda_pos >= genda_ptr->more_rows) 
            {
                free_genda(DATA_ONLY, genda_ptr) ;
                status = alloc_genda(genda_ptr, ALLOC_ALL) ;
                if (!status)
                {
                    status = update_genda(genda_ptr) ;
                    if (status)
                    {
                        return_rpc_status(NULL, 0, NULL, call_index) ;
                        free_genda(DATA_ONLY, genda_ptr) ;
                        return ;
                    }
                }
                else /* error allocating genda */
                {
                    return_rpc_status(NULL, 0, NULL, call_index) ;
                    free_genda(DATA_ONLY, genda_ptr) ;
                    return ;
                }
                genda_ptr->genda_pos = 0 ;
            }
        }
        
        /* Calculate actual record count currently on.
           genda_pos is reset for each batch, and rows_processed is    
           the number of the last row in that genda (updated during fetch).*/
        
        rcd = (genda_ptr->genda_num * genda_ptr->nrows) + genda_ptr->genda_pos ;
        
        int_ovf_err = FALSE ;
        incompat_attr_err = FALSE ;
        num_ret_atts = 0 ;

        /* pack row into attrib list */           
        for (col_count=0; col_count < genda_ptr->ncols; col_count++)
        {
            attr_type = column_receptacle_type[col_count] ;
            if (attr_type == GSI_NULL_TAG)
                continue ;
            idX = num_ret_atts++ ;

            /* Set the column name */ 
            gsi_set_attr_name( ret_record[num_status_args+idX],
                gsi_make_symbol((gsi_char*)genda_ptr->da_col_ptr[col_count].col_name)) ;
            if (debug & DBG6) {
	      wprintf (_T("R:%d,C:%d Attr: %s  "), genda_ptr->genda_pos, col_count, 
		       gsi_symbol_name(gsi_attr_name_of(ret_record[num_status_args+col_count])));
            }

            /* Set the data value based on type - formerly via function get_genda_col_data */
            selectColumnType = genda_ptr->da_col_ptr[col_count].data_type ;
            switch(selectColumnType)
            {
            case GDB_STRING_TYPE:
                if (attr_type == GSI_STRING_TAG || attr_type == GSI_VALUE_TAG )
                {
                    gsi_set_str( ret_record[num_status_args+idX], 
                        (gsi_char*)genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_str) ;
                    if (debug & DBG6) printf("%s\n",gsi_str_of(gsi_item_of_attr(ret_record[num_status_args+idX])));
                }
                else if (attr_type == GSI_SYMBOL_TAG)
                {
                    symX = gsi_make_symbol((gsi_char*)genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_str) ;
                    gsi_set_sym(ret_record[num_status_args+idX], symX) ;
                    if (debug & DBG6) printf("%s\n",gsi_symbol_name(gsi_sym_of(gsi_item_of_attr(ret_record[num_status_args+idX]))));
                }
                else
                {
                    incompat_attr_err = TRUE ;
                }
                break ;
                
            case GDB_BYTE_TYPE:
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:
                if (genda_ptr->da_col_ptr[col_count].ind[genda_ptr->genda_pos] < 0 || selectColumnType == GDB_LONG_TYPE)
                    lngX = genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_long ;
                else if (selectColumnType == GDB_BYTE_TYPE)
                    lngX = genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_byte ;
                else if (selectColumnType == GDB_SHORT_TYPE)
                    lngX = genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_short ;
                else if (selectColumnType == GDB_INT_TYPE)
                    lngX = genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_int ;
                int_ovf = (lngX > MAX_G2_INTEGER || lngX < MIN_G2_INTEGER) ;

                /* Determine which of 4 cases apply: return the value as an   */
                /* integer, return the minimum or maximum integer as an       */
                /* integer, return it as a float, or report an error.         */
                /* ---------------------------------------------------------- */
                if (!int_ovf && (attr_type == GSI_INTEGER_TAG || attr_type == GSI_VALUE_TAG ||
                     attr_type == GSI_QUANTITY_TAG ))
                {
                    gsi_set_int( ret_record[num_status_args+idX], lngX );
                    if (debug & DBG6) printf ("%d\n",gsi_int_of(gsi_item_of_attr(ret_record[num_status_args+idX])));
                }

                else if (int_ovf && attr_type == GSI_INTEGER_TAG)
                {
                    int_ovf_err = TRUE ;
                    iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINTOVF) ;
                    if (smart_fetch)
                        gsi_set_int( ret_record[num_status_args+idX], lngX < 0 ? MIN_G2_INTEGER : MAX_G2_INTEGER );
                    if (debug & DBG6) printf ("overflow: %d\n",gsi_int_of(gsi_item_of_attr(ret_record[num_status_args+idX])));
                }

                else if (attr_type == GSI_FLOAT64_TAG || attr_type == GSI_VALUE_TAG || attr_type == GSI_QUANTITY_TAG)
                {
                    dblX = (GDB_DBL)lngX ;
                    GFLOAT_TO_IEEE(dblX, &dblX, TRUE) ;
                    gsi_set_flt( ret_record[num_status_args+idX], dblX );
                    /* note: arg4 must be FALSE to prevent infinite loop */
                    iomsg(DBG4, LAYER, FALSE, FALSE, NULL, FALSE, "%d%s%s%s", WTYPCHG, 
                        gsi_symbol_name(gsi_attr_name_of(ret_record[num_status_args+idX])), 
                        _T("INTEGER"), _T("FLOAT"));

                    if (debug & DBG6)
		      printf("conversion: %f\n",
			     gsi_flt_of(gsi_item_of_attr(ret_record[num_status_args+idX])));
                    break ;
                }

                else
                    incompat_attr_err = TRUE ;

                break ;
                
            case GDB_FLOAT_TYPE:
            case GDB_DBL_TYPE:
                if (genda_ptr->da_col_ptr[col_count].ind[genda_ptr->genda_pos] < 0 || selectColumnType == GDB_DBL_TYPE)
                    dblX = genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_dbl ;
                else
                    dblX = (GDB_DBL)genda_ptr->da_col_ptr[col_count].val[genda_ptr->genda_pos].gdb_float ;
                GFLOAT_TO_IEEE(dblX, &dblX, TRUE) ;
                int_ovf = (dblX < MIN_G2_INTEGER - 0.1 || dblX > MAX_G2_INTEGER + 0.1) ;

                /* Determine which of 4 cases apply: return the value as a    */
                /* float, return the value as an integer, return the minimum  */
                /* or maximum integer as an integer, or report an error.      */
                /* ---------------------------------------------------------- */
                if (attr_type == GSI_FLOAT64_TAG || ((attr_type == GSI_VALUE_TAG || attr_type == GSI_QUANTITY_TAG) 
                    && (!smart_fetch || !genda_ptr->decimal_flags[col_count] || int_ovf)))
                {
                    gsi_set_flt( ret_record[num_status_args+idX], dblX );
                    if (debug & DBG6)
		      printf ("%f\n", gsi_flt_of(gsi_item_of_attr(ret_record[num_status_args+idX])));
                }

                else if (genda_ptr->decimal_flags[col_count] && !int_ovf && (attr_type == GSI_INTEGER_TAG ||
                                    (smart_fetch && (attr_type == GSI_VALUE_TAG || attr_type == GSI_QUANTITY_TAG))))
                {
                    gsi_set_int( ret_record[num_status_args+idX], (long)dblX );
                    if (debug & DBG6)
		      printf("%d\n", gsi_int_of(gsi_item_of_attr(ret_record[num_status_args+idX])));
                }

                else if (genda_ptr->decimal_flags[col_count] && int_ovf && attr_type == GSI_INTEGER_TAG)
                {
                    int_ovf_err = TRUE ;
                    if (smart_fetch)
                        gsi_set_int( ret_record[num_status_args+idX], dblX < 0 ? MIN_G2_INTEGER : MAX_G2_INTEGER);
                    if (debug & DBG6)
		      printf("overflow: %ld\n", gsi_int_of(gsi_item_of_attr(ret_record[num_status_args+idX])));
                }
                
                else
                    incompat_attr_err = TRUE ;
                break ;
                
            default:
                iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s%s", EINVDTY, "na", "na");
                if (debug & DBG6) printf("\n");
                update_object_status(object[0], genda_ptr, RETURN_TO_OBJECT, 0) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                free_genda(DATA_ONLY, genda_ptr) ;
                return ;
            } /* end switch */


            if (incompat_attr_err)
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s%s", EINCRAT,
                       genda_ptr->da_col_ptr[col_count].col_name, column_type_name(col_count, genda_ptr, arg[3], arg[4])) ;
                break ;
            }
        }
        
        /* return a row */ 
        if (!incompat_attr_err && (smart_fetch || !(int_ovf && attr_type == GSI_INTEGER_TAG)) && genda_ptr->genda_pos != genda_ptr->more_rows || genda_ptr->genStat.status != EOCURSOR_CD) 
        {
            /* Return the complete Record (row) with status info to G2 */
            gsi_return_attrs(object[0], ret_record, num_status_args+num_ret_atts, context_num) ;
        }
        else
            break ;
        
        /* Update row count */
        if (!incompat_attr_err)
        {
            (genda_ptr->genda_pos)++ ;
            batch_count++ ;
        }

        if (incompat_attr_err || (int_ovf_err && !smart_fetch))
            break ;
        
    } /* end while not last row in fetch batch */

    if (incompat_attr_err || int_ovf_err)
    {
        if (int_ovf_err)
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINTOVF) ;
        update_object_status(ret_record, NULL, UPDATE_ATTRS, 0) ;
        gsi_set_attr_name(ret_record[NROWS_POS], gsi_make_symbol((gsi_char*)NROWS_ATT)) ;
        gsi_set_int(ret_record[NROWS_POS], batch_count) ;
        gsi_set_attr_name(ret_record[CURSOR_POS], gsi_make_symbol((gsi_char*)CURSOR_ATT)) ;
        gsi_set_int(ret_record[CURSOR_POS], rcd+1) ;
        gsi_return_attrs(object[0], ret_record, NUM_STATUS_ARGS, context_num) ;
        gsi_clear_item(object[1]) ;
        gsi_set_handle(object[1], gsi_handle_of(arg[0])) ;
        gsi_return_attrs(object[1], ret_record, NUM_STATUS_ARGS, context_num) ;
    }

    /* update object & RPC status */
    /* at end of cursor and all rows have been returned so return EOCURSOR and release
       GENDA, etc. */
    else if ((genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_pos == genda_ptr->genStat.rows_processed) ||
             (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_pos == 0) || 
             (genda_ptr->genStat.status == EOCURSOR_CD && rcd+1 == genda_ptr->genStat.rows_processed) ||
             (genda_ptr->genStat.status == EOCURSOR_CD && rcd == genda_ptr->genStat.rows_processed)) 
    {
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        update_object_status(ret_record, genda_ptr, UPDATE_ATTRS, 0) ;
        gsi_set_attr_name(ret_record[NROWS_POS], gsi_make_symbol((gsi_char*)NROWS_ATT)) ;
        gsi_set_int(ret_record[NROWS_POS], batch_count) ;
        gsi_set_attr_name(ret_record[CURSOR_POS], gsi_make_symbol((gsi_char*)CURSOR_ATT)) ;
        gsi_set_int(ret_record[CURSOR_POS], genda_ptr->genStat.rows_processed) ;
        gsi_return_attrs(object[0], ret_record, NUM_STATUS_ARGS, context_num) ;
        /* update the cursor object status */
        gsi_clear_item(object[1]) ;
        gsi_set_handle(object[1], gsi_handle_of(arg[0])) ;
        gsi_return_attrs(object[1], ret_record, NUM_STATUS_ARGS, context_num) ;
        genda_ptr->genda_pos = 0 ;
        /* end of genda so XFREE it */
        free_genda(DATA_ONLY, genda_ptr); /* must be within while loop */
    }
    else 
    {
        iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WNOTEOC) ;
        update_object_status(ret_record, NULL, UPDATE_ATTRS, 0) ;
        gsi_set_attr_name(ret_record[NROWS_POS], gsi_make_symbol((gsi_char*)NROWS_ATT)) ;
        gsi_set_int(ret_record[NROWS_POS], batch_count) ;
        gsi_set_attr_name(ret_record[CURSOR_POS], gsi_make_symbol((gsi_char*)CURSOR_ATT)) ;
        gsi_set_int(ret_record[CURSOR_POS], rcd+1) ;
        gsi_return_attrs(object[0], ret_record, NUM_STATUS_ARGS, context_num) ;
        /* update the cursor object cursor-pos */
        gsi_clear_item(object[1]) ;
        gsi_set_handle(object[1], gsi_handle_of( arg[0] )) ;
        gsi_return_attrs(object[1], ret_record, NUM_STATUS_ARGS, context_num) ;
    }
    
    /* generate error if context shutdown occured during data return */
    /* This will not work as context_num is set at top of this function. I've also
    noticed that gsi_current_context() is not being set to -1 as pre 4.1 when
    IO is disabled during data return. This needs to be revisited ????????? */ 
    if (context_num < 0)
        iomsg(DBG3, LAYER, FALSE, FALSE, NULL, FALSE, "%d", ECONACT) ;
    
    /* return status information from global status struct -- to RPC */ 
    status_args = gsi_make_items(NUM_STATUS_ARGS) ;
    update_object_status(status_args, NULL, UPDATE_ITEMS, 0) ;
    gsi_set_int(status_args[NROWS_POS], batch_count) ;
    if (!genda_ptr->genda_pos) /* if EOCURSOR - return total rows processed */
        gsi_set_int(status_args[CURSOR_POS], genda_ptr->genStat.rows_processed) ;
    else
        gsi_set_int(status_args[CURSOR_POS], rcd+1) ;
    
    /* return status values to G2 RPC */
    return_rpc_status(status_args, NUM_STATUS_ARGS, NULL, call_index) ;
    gsi_reclaim_items(status_args) ;
    if (column_receptacle_type != NULL)
        XFREE(column_receptacle_type) ;
    
    return ;
}



/*===========================================================================*
    fetch_query_item_rp                                   (III)       GDB-RPC
      - fetches records from a cursor defined via 'set_cursor_rp'.
        Data value are returned within a 'query-item' template object.
      - input: [0]=cursor-object
               [1]=format (LIST_TYPE,ARRAY_TYPE)
               [2]=batch-size
 *===========================================================================*/
 
static void fetch_query_item_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    double                  dblX ;
    double*                 dblval ;
    GENDA*                  genda_ptr ;
    gsi_attr*               theAttrs ;
    gsi_int                 obj_handle ;
    gsi_item*               new_items ;
    gsi_item*               query_items = NULL ;
    gsi_item*               theAttrs2 ;
    gsi_item**              itmval ;
    gsi_registered_item*    object ;
    gsi_symbol*             symval = NULL ;
    int                     iidx, i ;
    int                     quantityCt = 0 ;
    register long           col, row ;
    long                    cursor_pos = 0 ;
    long                    fetch_batch ;
    long                    float_flag = FALSE ;
    long                    format ;
    long                    max_rows ;
    long                    rcd = 0 ;   /* local record (row) counter - for batch-fetch */
    long                    selectColumnType ;
    long                    smart_fetch ;
    long                    status ;
    long*                   longval ;
    short                   retType ;
    GDB_CHAR**              col_names ;
    GDB_CHAR**              strval ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("FETCH_QUERY_ITEM_RP: %"), context_num) ;
    
    /* Build a query-object */
    query_items = gdb_item_array ;
    gsi_set_class_name(query_items[0], gsi_make_symbol((gsi_char*)LIST_OBJECT_NAME)) ;
    gsi_set_type(query_items[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(query_items[0]) ;
        return ;
    }
    
    smart_fetch = context[context_num].smart_fetch ;
    
    if (count < 3 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(query_items[0]) ;
        return ;
    }
    
#ifdef _DEBUG
    wprintf(_T("\ncount = %d\n"), count) ;
    wprintf(_T("-------------------------------------------------------\n")) ;
    wprintf(_T(" Cursor-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0]) ) ;
    wprintf(_T("    Handle:      %d\n"), gsi_handle_of(arg[0]) ) ;
    get_attrib_info(arg[0]) ;
#endif
    
    /* arg-0 is the cursor-object handle */
    obj_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (obj_handle < MIN_ITEM_HANDLE) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(query_items[0]) ;
        return ;
    }
    
    /* arg-1 is the query-item format (LISTS or ARRAYS) */
    format = gsi_int_of(arg[1]) ;
    if (format != LIST_TYPE && format != ARRAY_TYPE) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(query_items[0]) ;
        return ;
    }
    
    /* do it here to get correct object type if premature return occurs */
    if (format == LIST_TYPE) 
    {
        gsi_set_class_name(query_items[0], gsi_make_symbol((gsi_char*)LIST_OBJECT_NAME)) ;
        gsi_set_type(query_items[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    }
    else 
    {
        gsi_set_class_name(query_items[0], gsi_make_symbol((gsi_char*)ARRAY_OBJECT_NAME)) ;
        gsi_set_type(query_items[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    }
    
    genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
    if (genda_ptr == (GENDA *)NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVITM, CURSOR_OBJECT_NAME) ;
        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(query_items[0]) ;
        return ;
    }
    
    if (genda_ptr->genStat.rows_processed != 0 && genda_ptr->genda_pos == 0 &&
        genda_ptr->more_rows != genda_ptr->nrows )
    {
    /* If positioned at EOCURSOR simply return EOCURSOR message until user
       either performs SET_QUERY or REFRESH_CURSOR: This check is provided
       because Oracle will automatically refresh the cursor. Performing a
       'ping' here so EOCURSOR message is not returned while disconnected.
       This will also cause the G2 IO db-connection-status to be set to 
       disconnected via KB logic */   
        
        if (!process_ping_db())    
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        else
        {
        /* this will prevent EOCURSOR message from being returned following a reconnect */
            genda_ptr->genStat.rows_processed = 0 ;
        }
        
        genda_ptr->more_rows = 0; /* make sure it's 0 */
        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(query_items[0]) ;
        return ;
    }
    
    /* Initially Allocate, then Update (populate) the GENDA with db data */
    if (genda_ptr->genda_pos == 0) 
    {    /* add for fetch-batch */
        status = alloc_genda(genda_ptr, ALLOC_ALL) ;
        if (!status)
            status = update_genda(genda_ptr) ;
        if (status) 
        {
            update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
            return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
            gsi_clear_item(query_items[0]) ;
            free_genda(DATA_ONLY, genda_ptr) ;
            return ;
        }
    }
    if (genda_ptr->genda_pos == -1)     /* First rows have already been loaded */
        genda_ptr->genda_pos = 0 ;
    
    /**********************************
    * Load the Column Name List/Array
    **********************************/
    theAttrs = gdb_attr_item_array ;
    
    if (format == LIST_TYPE)
    {
        gsi_set_attr_name(theAttrs[0], gsi_make_symbol((gsi_char*)COL_NAME_ATTRIB)) ;
        gsi_set_class_name (theAttrs[0], gsi_make_symbol((gsi_char*)_T("SYMBOL-LIST"))) ;
        gsi_set_type(theAttrs[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
        gsi_set_attr_name(theAttrs[1], gsi_make_symbol((gsi_char*)COL_VALUE_ATTRIB)) ;
        gsi_set_class_name (theAttrs[1], gsi_make_symbol((gsi_char*)_T("ITEM-LIST"))) ;
        gsi_set_type(theAttrs[1], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    }
    else 
    {
        gsi_set_attr_name(theAttrs[0], gsi_make_symbol((gsi_char*)COL_NAME_ATTRIB)) ;
        gsi_set_class_name (theAttrs[0], gsi_make_symbol((gsi_char*)_T("SYMBOL-ARRAY"))) ;
        gsi_set_type(theAttrs[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
        gsi_set_attr_name(theAttrs[1], gsi_make_symbol((gsi_char*)COL_VALUE_ATTRIB)) ;
        gsi_set_class_name (theAttrs[1], gsi_make_symbol((gsi_char*)_T("ITEM-ARRAY"))) ;
        gsi_set_type(theAttrs[1], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    }
    
    /* Assign DB col names to 'column name' attribute list/array */  
    if ((col_names = (GDB_CHAR**)XCALLOC(genda_ptr->ncols, sizeof(GDB_CHAR*))) == NULL  ||
        (symval = (gsi_symbol*)XCALLOC(genda_ptr->ncols, sizeof(gsi_symbol))) == NULL )
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(query_items[0]) ;
        gsi_clear_item(theAttrs[0]) ;
        gsi_clear_item(theAttrs[1]) ;
        if (col_names) XFREE(col_names) ;
        return ;
    }
    for (col=0; col < genda_ptr->ncols; col++)
    {
        col_names[col] = genda_ptr->da_col_ptr[col].col_name ;
        symval[col] = gsi_make_symbol((gsi_char*)col_names[col]) ;
    }

    if (format == LIST_TYPE) 
        gsi_set_sym_list(theAttrs[0], symval, genda_ptr->ncols ) ;
    else
        gsi_set_sym_array(theAttrs[0], symval, genda_ptr->ncols ) ;
    
    new_items = gdb_column_array ;
    
    /* initialize temp buffers to NULL */
    strval  = NULL ;
    longval = NULL ;
    dblval  = NULL ;
    itmval  = NULL ;
    
    /* arg-2 is fetch_batch size */
    fetch_batch = gsi_int_of(arg[2]) ;
    rcd = genda_ptr->genda_pos ;
    
    /******************
    * START FETCHING
    ******************/
    max_rows = genda_ptr->more_rows;
    if (fetch_batch > 0 && genda_ptr->more_rows > 0) 
    { /* && fetch_batch <= genda_ptr->more_rows) */ /* don't set max_rows > rows fetched */
        if (fetch_batch + rcd < genda_ptr->more_rows)
            max_rows = fetch_batch ;
        else
            max_rows = genda_ptr->more_rows - genda_ptr->genda_pos ;
    }
    if (max_rows > context[context_num].genda_rows)
        max_rows = context[context_num].genda_rows ;
    
        /* Allocate temp ptrs based on genda_rows for use by 'gsi_set_xxx_list/array. Since 
           the DB data is returned in 1 object, enough space must be allocated for all rows.
           If the number of rows exceeds context[context_num].genda_rows, then return a partially 
           populated object and the message 'end-of-cursor has not been reached' warning. */
    
    for (col=0; col < genda_ptr->ncols; col++)
    {
        switch (genda_ptr->da_col_ptr[col].data_type)
        {
            case GDB_STRING_TYPE:   if (strval != NULL)
                                        break ;
                                    if ((strval = (GDB_CHAR**)XCALLOC(max_rows+1, sizeof(GDB_CHAR*))) == NULL)
                                    {
                                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
                                        goto jumpOut ;
                                    }
                                    break ;

            case GDB_BYTE_TYPE:
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:     if (longval != (long *)NULL)
                                        break ;
                                    if ((longval = (long *)XCALLOC(max_rows+1, sizeof(long))) == (long *)NULL)
                                    {
                                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
                                        goto jumpOut ;
                                    }
                                    if (smart_fetch)
                                        quantityCt++ ;
                                    break ;

            case GDB_FLOAT_TYPE:
            case GDB_DBL_TYPE:      if (genda_ptr->decimal_flags[col] && smart_fetch)
                                    {
                                        quantityCt++ ;
                                        break ;
                                    }
                                    if (dblval != (double *)NULL)
                                        break ;
                                    if ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double))) == (double *)NULL)
                                    {
                                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                        update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
                                        goto jumpOut ;
                                    } 
                                    break ;
        }
    }
    
    /* Allocate the needed arrays of gsi_items for quantity arrays/lists */
    /*  ---------------------------------------------------------------- */
    if (quantityCt)
    {
		if(col > quantityCt)/*Gensym*/
			quantityCt = col;
        i = -1 ; /* So quantityCt check can detect failure to allocate itemval */  
        itmval = (gsi_item**)XCALLOC(quantityCt, sizeof(gsi_item*)) ;
        if (itmval != NULL)
            for (i=0; i < quantityCt ; i++)
            {
                itmval[i] = gsi_make_items(max_rows) ;
                if (itmval[i] == NULL)
                    break ;
            }
        if (i != quantityCt)
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
            goto jumpOut ;
        }           
    }
    
    /* Fetch & associate data with GSI lists/arrays. All data must be loaded into 'new_items'
    and associated with the object via a single set/vector */
#define RET_UNK -2
#define RET_QTY -1
#define RET_INT  0
#define RET_FLT  1

    
    iidx = 0 ;  /* next array of gsi_items to use */
    for (col=0; col < genda_ptr->ncols; col++)
    {
        retType = RET_UNK ; /* control what is executed at start of float/double case */
        
        /* Set the data value based on type */
        selectColumnType = genda_ptr->da_col_ptr[col].data_type ;
        switch(selectColumnType)
        {
            case GDB_STRING_TYPE:   for (row=0;row<max_rows;row++)
                                        strval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_str ;
                                    if (format == LIST_TYPE) 
                                    {
                                        gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("TEXT-LIST"))) ;
                                        gsi_set_str_list(new_items[col], (gsi_char**)strval, max_rows) ;
                                    }
                                    else
                                    {
                                        gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("TEXT-ARRAY"))) ;
                                        gsi_set_str_array(new_items[col], (gsi_char**)strval, max_rows) ;
                                    }
                                    break ;
            
            case GDB_BYTE_TYPE:       
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:     /* We will always return lists or arrays of quantities if smart fetch is on. */
                                    /* This is necessary to guarantee that db-update-query-item will work.       */
                                    /* ------------------------------------------------------------------------- */
                                    retType = smart_fetch ? RET_QTY : RET_INT ;   /* Assume we will return a list or array of integers */
                                    for (row=0;row<max_rows;row++)
                                    {
                                        if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_LONG_TYPE )
                                            longval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                                        else if (selectColumnType == GDB_BYTE_TYPE)
                                            longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_byte ;
                                        else if (selectColumnType == GDB_SHORT_TYPE)
                                            longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_short ;
                                        else
                                            longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_int ;

                
                                        /* If the value we just retrieved would cause G2 integer overflow and smart     */
                                        /* fetch is off, all values will be returned as floats.                         */
                                        /* ---------------------------------------------------------------------------- */
                                        if (!smart_fetch && (longval[row] < MIN_G2_INTEGER || longval[row] > MAX_G2_INTEGER))
                                        {
                                            retType = RET_FLT ;
                                        }
                                    }
                                    switch(retType)
                                    {
                                        case RET_QTY:   /* Return an array or list of quantities */
                

                                                        /* Allocated another array of gsi_items */
                                                        itmval = realloc(itmval, quantityCt * sizeof(gsi_item*)) ;
                                                        if (itmval== NULL || ((itmval[quantityCt-1] = gsi_make_items(max_rows)) == NULL))
                                                        {
                                                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                                            update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
                                                            goto jumpOut ;
                                                        }
                
                                                        /* Fill in the array of gsi_items */
                                                        for (row=0 ; row < max_rows ; row++)
                                                        {
                                                            if (longval[row] >= MIN_G2_INTEGER && longval[row] <= MAX_G2_INTEGER)
                                                                gsi_set_int(itmval[iidx][row], longval[row]) ;
                                                            else
                                                                gsi_set_flt(itmval[iidx][row], (double)longval[row]) ;
                                                        }
                
                                                        break ;
                
                                        case RET_INT:   if (format == LIST_TYPE)
                                                        {
                                                            gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("INTEGER-LIST")));

                                                            gsi_set_int_list(new_items[col], longval, max_rows) ;
                                                        }
                                                        else
                                                        {
                                                            gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("INTEGER-ARRAY")));

                                                            gsi_set_int_array(new_items[col], longval, max_rows) ;
                                                        }
                                                        break ;
                
                                        case RET_FLT :  /* Return a list or array of floats */
                                                        if (!dblval && ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double)) ) == (double *)NULL))
                                                        {
                                                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                                            update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
                                                            goto jumpOut ;
                                                        }
                
                                                        /* Copy the values from the array of longs to the array of doubles */
                                                        for (row=0;row<max_rows;row++)
                                                        {
                                                            dblval[row] = (double)longval[row] ;
                                                            GFLOAT_TO_IEEE(dblval[row], &dblval[row], TRUE) ;
                                                        }
                
                                                        /* note: arg4 must be FALSE to prevent infinite loop */
                                                        iomsg(DBG4, LAYER, FALSE, FALSE, NULL, FALSE, "%d%s%s%s", WTYPCHG, col_names[col], _T("INTEGER"), _T("FLOAT"));

                                                        break ;

                                    } /* end of return-type switch */
                                    if (retType == RET_INT )
                                        break ;
            

                case GDB_FLOAT_TYPE:
                case GDB_DBL_TYPE:      /* Bypass this block of code if we fell through to here from the prior case */
                                        if (retType == RET_UNK)
                                        {
                                            retType = (smart_fetch && genda_ptr->decimal_flags[col] ? RET_QTY : RET_FLT) ;
                                            for (row=0;row<max_rows;row++)
                                            {
                                                if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_DBL_TYPE)
                                                    dblX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_dbl ;
                                                else
                                                    dblX = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_float ;
                                                GFLOAT_TO_IEEE(dblX, &dblX, FALSE) ;
                                                if (retType == RET_QTY)
                                                {
                                                    /* The use of 0.1 below guarantees that that we don't get the wrong answer due    */
                                                    /* to the minute rounding error that occurs when converting between long & double */
                                                    if (dblX > (double)(MIN_G2_INTEGER - 0.1) && dblX < (double)(MAX_G2_INTEGER + 0.1))
                                                        gsi_set_int(itmval[iidx][row], (long)dblX) ;
                                                    else
                                                        gsi_set_flt(itmval[iidx][row], dblX) ;
                                                }
                                                else
                                                    dblval[row] = dblX ;
                                            }
                                        }

                                        if (retType == RET_QTY)  /* list or array of quantity */
                                        {
                                            /* Store the quantity list/array in the attribute */
                                            if (format == LIST_TYPE)
                                            {
                                                gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("QUANTITY-LIST")));

                                                gsi_set_elements(new_items[col], itmval[iidx], max_rows, GSI_QUANTITY_LIST_TAG) ;
                                            }
                                            else
                                            {
                                                gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("QUANTITY-ARRAY")));

                                                gsi_set_elements(new_items[col], itmval[iidx], max_rows, GSI_QUANTITY_ARRAY_TAG) ;
                                            }
                                            iidx++ ; /* Next time, use the next array of gsi_items */
                                        }
                                        else
                                        {
                                            /* Put the list or array of doubles into the attribute */
                                            if (format == LIST_TYPE)
                                            {
                                                gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("FLOAT-LIST")));

                                                gsi_set_flt_list(new_items[col], dblval, max_rows) ;
                                            }
                                            else 
                                            {
                                                gsi_set_class_name (new_items[col], gsi_make_symbol((gsi_char*)_T("FLOAT-ARRAY")));

                                                gsi_set_flt_array(new_items[col], dblval, max_rows) ;
                                            }
                                        }
                                        break ;
                
            default:
	      iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s%s", EINVDTY, _T("na"), _T("na"));
	      if (debug & DBG6) printf("\n");
	      break ;
        } /* end switch */
    } /* end for col */
  
    genda_ptr->genda_pos += max_rows ;
    
    /* update the item-list */
    if (format == LIST_TYPE)
        gsi_set_elements (theAttrs[1], new_items, genda_ptr->ncols, GSI_ITEM_LIST_TAG) ;
    else
        gsi_set_elements (theAttrs[1], new_items, genda_ptr->ncols, GSI_ITEM_ARRAY_TAG) ;
    
    if (genda_ptr->genStat.status == EOCURSOR_CD && (genda_ptr->nrows * genda_ptr->genda_num + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed ||
        genda_ptr->genda_pos == 0))
    {
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, NULL, FALSE, "%d", IEOFETC) ;
        cursor_pos = genda_ptr->genStat.rows_processed ;
    }
    else 
    {
        iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WNOTEOC) ;
        cursor_pos = (((genda_ptr->genStat.rows_processed - 1)/ genda_ptr->nrows) * genda_ptr->nrows) + genda_ptr->genda_pos ;
    }
    
    /* move STATUS info into object attributes */
    update_object_status(query_items, NULL, UPDATE_ITEMS, 1) ;
    gsi_set_int(query_items[1+NROWS_POS], max_rows) ;
    gsi_set_int(query_items[1+CURSOR_POS], cursor_pos) ;
    
    /* Build a query-object */
    query_items = gdb_item_array ;
    if (format == LIST_TYPE) 
    {
        gsi_set_class_name(query_items[0], gsi_make_symbol((gsi_char*)LIST_OBJECT_NAME)) ;
        gsi_set_type(query_items[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    }
    else
    {
        gsi_set_class_name(query_items[0], gsi_make_symbol((gsi_char*)ARRAY_OBJECT_NAME)) ;
        gsi_set_type(query_items[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    }
    
    /* update the cursor object status */
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], gsi_handle_of(arg[0])) ;
    
    theAttrs2 = gdb_status_attr_items ;
    update_object_status(theAttrs2, NULL, UPDATE_ATTRS, 0) ;
    gsi_set_int(theAttrs2[CURSOR_POS], cursor_pos) ;
    gsi_return_attrs(object[0], theAttrs2, NUM_STATUS_ARGS, context_num) ;
    
    /* col_name_list+item_list+status_values */
    gsi_set_attrs(query_items[0], theAttrs, 2) ;
    
jumpOut:    
    /* return the query-item to G2 */
    return_rpc_status(query_items, 1+NUM_STATUS_ARGS, NULL, call_index) ;
    
    /* reset the global structures */
    for (col=0; col < genda_ptr->ncols; col++)
        gsi_clear_item(new_items[col]) ;
    
    gsi_clear_item(query_items[0]) ;
    gsi_clear_item(theAttrs[0]) ;
    gsi_clear_item(theAttrs[1]) ;
    
    /* release the temp buffers */
    if (dblval != NULL)
        XFREE(dblval) ;
    if (longval != NULL)
        XFREE(longval) ;
    if (strval != NULL)
        XFREE(strval) ;
    if (itmval != NULL)
    {
        for (i = 0 ; i < quantityCt ; i++)
            if (itmval[i])
                gsi_reclaim_items(itmval[i]) ;
            XFREE(itmval) ;
            itmval = NULL ;
    }
  
    /* release the column names arrays */
    XFREE(col_names) ;
    XFREE(symval) ;
    
    /* release fetched data */
    if ( (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed) || 
        genda_ptr->genda_pos == genda_ptr->nrows) 
    {
        genda_ptr->genda_pos = 0;     /* add for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
    }
    
    return ;
} /* end fetch_query_item_rp */



/*===========================================================================*
    update_query_item_rp                                   (222)      GDB-RPC
      - fetches records from a cursor defined via 'set_cursor_rp'.
        Data values are returned to an existing 'query-item'.
      - input: [0]=cursor-object (handle only)
               [1]=query-item    (with handle)
               [2]=update-action (OBJECT_REPLACE,OBJECT_APPEND)
               [3]=fetch-batch
 *===========================================================================*/
static void update_query_item_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    double                  dblX ;
    double*                 dblval ;
    GENDA*                  genda_ptr ;
    gsi_attr*               attribs_out ;
    gsi_attr*               qi_attribs_in ;
    gsi_int                 attr_type ;
    gsi_int                 co_handle, qi_handle ;
    gsi_int                 gsintX ;
    gsi_int                 naols ;
    gsi_int                 nattrs = 0 ;
    gsi_int                 nnames ;
    gsi_item*               aols ;
    gsi_item*               new_items ;
    gsi_item*               query_item ;
    gsi_item*               status_args ;
    gsi_item**              itmval = NULL ;
    gsi_registered_item*    object ;
    gsi_symbol*             aol_names ;
    gsi_symbol*             symlist = NULL ;
    int                     i ;
    int                     quantityCt = 0 ;
    register long           col, row ;
    long                    cursor_pos = 0 ;
    long                    fetch_batch ;
    long                    float_flag = FALSE ;
	long					idx ;
    long*                   longval ;
    long                    lX ;
    long                    max_rows ;
    long                    rcd = 0 ;   /* local record (row) counter - for batch-fetch */
    long                    selectColumnType ;
    long                    smart_fetch ;
    long                    status = 0 ;
    long                    update_action ;
    short                   bad_query_item = FALSE ;
    short                   intOvfl ;
    short                   intOvflErr ;
    short                   list_flag ;
    short                   retType ;
    GDB_CHAR*                aol_name ;
    GDB_CHAR**               strval ;

    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("UPDATE_QUERY_ITEM_RP: %"), context_num);
    }
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    smart_fetch = context[context_num].smart_fetch ;
    
    if (count < 4 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
#ifdef _DEBUG
    wprintf(_T("\ncount = %d\n"), count) ;
    wprintf(_T("-------------------------------------------------------\n")) ;
    wprintf(_T(" Cursor-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0]) ) ;
    wprintf(_T("    Handle:      %d\n"), gsi_handle_of(arg[0]) ) ;
    get_attrib_info(arg[0]) ;
    
    wprintf(_T("\n-------------------------------------------------------\n")) ;
    wprintf(_T(" Query-Item Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[1]), gsi_type_to_string(arg[1]) ) ;
    wprintf(_T("    Class Name:  %s\n"), gsi_symbol_name(gsi_class_name_of(arg[1]))) ;
    wprintf(_T("    Handle:      %d\n"), gsi_handle_of(arg[1]) ) ;
    get_attrib_info(arg[1]) ;
#endif

    /* arg-0 is the cursor-object handle */
    co_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (co_handle < MIN_ITEM_HANDLE) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-1 is the query-item handle */
    qi_handle = gsi_handle_of(arg[1]) ;
    
    /* Check for ok handle, and object */
    if (qi_handle < MIN_ITEM_HANDLE) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* associate object we're building with existing object in G2 */
    query_item = gsi_item_of_registered_item(gdb_registered_item_array[0]) ;
    gsi_set_handle(gdb_registered_item_array[0], qi_handle) ;
    gsi_set_class_name(query_item, gsi_class_name_of(arg[1])) ;
    gsi_set_type(query_item, GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    
    /* arg-2 is the query-item update_action (OBJECT_REPLACE or OBJECT_APPEND) */
    update_action = gsi_int_of(arg[2]) ;
    if (update_action != OBJECT_REPLACE && update_action != OBJECT_APPEND) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(query_item) ;
        return ;
    }
    
    genda_ptr = storage_area(GET, context_num, co_handle, NULL) ;
    if (genda_ptr == (GENDA *)NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVITM, CURSOR_OBJECT_NAME) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(query_item) ;
        return ;
    }
    
    qi_attribs_in = gsi_attrs_of(arg[1]) ;
    nattrs = gsi_attr_count_of(arg[1]) ;
    attribs_out = gdb_attr_item_array ;
    
    if (genda_ptr->genStat.rows_processed != 0 && genda_ptr->genda_pos == 0 &&
        genda_ptr->more_rows != genda_ptr->nrows)
    {
    /* If positioned at EOCURSOR simply return EOCURSOR message until user
       either performs SET_QUERY or REFRESH_CURSOR: This check is provided
       because Oracle will automatically refresh the cursor. Performing a
       'ping' here so EOCURSOR message is not returned while disconnected.
       This will also cause the G2 IO db-connection-status to be set to 
       disconnected via KB logic */   
        
        if (!process_ping_db())    
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        else 
        {
        /* this will prevent EOCURSOR message from being returned
           following a reconnect */
            genda_ptr->genStat.rows_processed = 0 ;
        }
        
        genda_ptr->more_rows = 0; /* make sure its 0 */
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(query_item) ;
        return ;
    }
    
    /* Initially, Allocate then Update (populate) the GENDA with db data */
    if (genda_ptr->genda_pos == 0) 
    {    /* add for fetch-batch */
        status = alloc_genda(genda_ptr, ALLOC_ALL) ;
        if (!status)
            status = update_genda(genda_ptr) ;
        if (status) 
        {
            return_rpc_status(NULL, 0, NULL, call_index) ;
            free_genda(DATA_ONLY, genda_ptr) ;
            gsi_clear_item(query_item) ;
            return ;
        }
    }
    if (genda_ptr->genda_pos == -1)     /* First rows have already been loaded */
        genda_ptr->genda_pos = 0 ;

  /**********************************
   * Load the Column Name List/Array
   **********************************/

    /* determine datatype of query-item attributes by looking at the first attribute
      'db-col-names' - options are GSI_SYMBOL_LIST_TAG and GSI_STRING_LIST_TAG */

    if (nattrs >= 2)
    {
        gsintX = gsi_type_of(qi_attribs_in[0]) ;
        list_flag = (gsintX == GSI_SYMBOL_LIST_TAG) ;
    
        if (list_flag) 
        {
            gsi_set_attr_name(attribs_out[0], gsi_make_symbol((gsi_char*)COL_NAME_ATTRIB)) ;
            gsi_set_class_name (attribs_out[0], gsi_make_symbol((gsi_char*)_T("SYMBOL-LIST"))) ;
            gsi_set_type(attribs_out[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
            gsi_set_attr_name(attribs_out[1], gsi_make_symbol((gsi_char*)COL_VALUE_ATTRIB)) ;
            gsi_set_class_name (attribs_out[1], gsi_make_symbol((gsi_char*)_T("ITEM-LIST"))) ;
            gsi_set_type(attribs_out[1], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
            aol_names = gsi_sym_list_of(qi_attribs_in[0]) ;
            nnames = gsi_element_count_of(qi_attribs_in[0]) ;
        }
        else if (gsintX == GSI_SYMBOL_ARRAY_TAG) 
        {
            gsi_set_attr_name(attribs_out[0], gsi_make_symbol((gsi_char*)COL_NAME_ATTRIB)) ;
            gsi_set_class_name (attribs_out[0], gsi_make_symbol((gsi_char*)_T("SYMBOL-ARRAY"))) ;
            gsi_set_type(attribs_out[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
            gsi_set_attr_name(attribs_out[1], gsi_make_symbol((gsi_char*)COL_VALUE_ATTRIB)) ;
            gsi_set_class_name (attribs_out[1], gsi_make_symbol((gsi_char*)_T("ITEM-ARRAY"))) ;
            gsi_set_type(attribs_out[1], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
            aol_names = gsi_sym_array_of(qi_attribs_in[0]) ;
            nnames = gsi_element_count_of(qi_attribs_in[0]) ;
        }
        else
            bad_query_item = TRUE ;
        gsintX = gsi_type_of(qi_attribs_in[1]) ;
        if (gsintX != GSI_ITEM_LIST_TAG && gsintX != GSI_ITEM_ARRAY_TAG) 
            bad_query_item = TRUE ;
    }
    else
        bad_query_item = TRUE ;

    if (!bad_query_item)
    {
        aols = gsi_elements_of(qi_attribs_in[1]) ;
        naols = gsi_element_count_of(qi_attribs_in[1]) ;
        if (update_action == OBJECT_APPEND && nnames != naols)
            bad_query_item = TRUE ;
    }

    /* If we are appending to the query item, the query item should be for    */
    /* same query we are about to execute.  Make sure that the query item is  */
    /* for the number of columns returned by the query and that the names of  */
    /* each column match.                                                     */
    /* ---------------------------------------------------------------------  */
    if (update_action == OBJECT_APPEND && !bad_query_item)
    {
        if (nnames != genda_ptr->ncols)
            bad_query_item = TRUE ;
        else
        {
            for (lX = 0 ; lX < nnames ; lX++)
            {
                aol_name = (GDB_CHAR*)gsi_symbol_name(aol_names[lX]) ;
                if (_wcsicmp(genda_ptr->da_col_ptr[lX].col_name, aol_name))
                {
                    bad_query_item = TRUE ;
                    break ;
                }
            }
        }
    }

    /*  If the query item is invalid or doesn't match the query, exit here.   */
    /* ---------------------------------------------------------------------- */
    if (bad_query_item)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EBADOBJ, _T("valid query item that matches SQL statement"));
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(query_item) ;
        return ;
    }

  
    /* This flag will set the item such that elements of the item will be capable of
       performing an update with append. This flag is only necessary for nested items
       and will not have recursive affects. Note: The actual item that will have the
       update-append must be set with the gsi_set_item_append_flag only ! */
    
    gsi_set_update_items_in_lists_and_arrays_flag(gsi_item_of_attr(attribs_out[1]), 1) ;
    
    if (list_flag)
        gsi_set_sym_list(attribs_out[0], aol_names, nnames);
    else
        gsi_set_sym_array(attribs_out[0], aol_names, nnames);
    
    new_items = gdb_column_array;

    /* If the REPLACE option was chosen, we must create empty lists or arrays for */
    /* each column stored in the query item                                       */
    /* -------------------------------------------------------------------------- */
    if (update_action == OBJECT_REPLACE)
    {
        for (lX = 0 ; lX < naols ; lX++)
        {
            gsintX = gsi_type_of(aols[lX]) ;
            if (list_flag)
                if (gsintX == GSI_INTEGER_LIST_TAG)
                {
                    gsi_set_class_name(new_items[lX], "INTEGER-LIST") ;
                    gsi_set_int_list(new_items[lX], NULL ,0) ;
                }
                else if (gsintX == GSI_FLOAT64_LIST_TAG)
                {
                    gsi_set_class_name(new_items[lX], "FLOAT-LIST") ;
                    gsi_set_flt_list(new_items[lX], NULL, 0) ;
                }
                else if (gsintX == GSI_STRING_LIST_TAG)
                {
                    gsi_set_class_name(new_items[lX], "TEXT-LIST") ;
                    gsi_set_str_list(new_items[lX], NULL, 0) ;
                }
                else if (gsintX == GSI_QUANTITY_LIST_TAG)
                {
                    gsi_set_class_name ( new_items[lX], "QUANTITY-LIST" );
                    gsi_set_elements(new_items[lX], NULL, 0, GSI_QUANTITY_LIST_TAG) ;
                }
                else
                    bad_query_item = TRUE ;
            else
                if (gsintX == GSI_INTEGER_ARRAY_TAG)
                {
                    gsi_set_class_name(new_items[lX], "INTEGER-ARRAY") ;
                    gsi_set_int_array(new_items[lX], NULL, 0) ;
                }
                else if (gsintX == GSI_FLOAT64_ARRAY_TAG)
                {
                    gsi_set_class_name(new_items[lX], "FLOAT-ARRAY") ;
                    gsi_set_flt_array(new_items[lX], NULL, 0) ;
                }
                else if (gsintX == GSI_STRING_ARRAY_TAG)
                {
                    gsi_set_class_name(new_items[lX], "TEXT-ARRAY") ;
                    gsi_set_str_array(new_items[lX], NULL, 0) ;
                }
                else if (gsintX == GSI_QUANTITY_ARRAY_TAG)
                {
                    gsi_set_class_name ( new_items[lX], "QUANTITY-ARRAY" );
                    gsi_set_elements(new_items[lX], NULL, 0, GSI_QUANTITY_ARRAY_TAG) ;
                }
                else
                    bad_query_item = TRUE ;
        }
    }
    
    /*  Exit if the query item had a list or array of values of an unexpected type. */
    /* ---------------------------------------------------------------------------- */
    if (bad_query_item)
    {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%s", EBADOBJ, _T("query item with valid value types"));
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(query_item) ;
        gsi_clear_item(attribs_out[0]) ;
        gsi_clear_item(attribs_out[1]) ;
        return ;
    }

    
    /* initialize temp buffers to NULL */
    strval  = NULL ;
    longval = NULL ;
    dblval  = NULL ;
    itmval  = NULL ;
    
    /* arg-3 is fetch_batch size */
    fetch_batch = gsi_int_of(arg[3]) ;
    rcd = genda_ptr->genda_pos ;


    max_rows = genda_ptr->more_rows;          /* ???? check this is more_rows initialized ? */
    if (fetch_batch > 0 && genda_ptr->more_rows > 0)
    { /* && fetch_batch <= genda_ptr->more_rows) */ /* don't set max_rows > rows fetched */
        if (fetch_batch + rcd < genda_ptr->more_rows)
            max_rows = fetch_batch ;
        else
            max_rows = genda_ptr->more_rows - genda_ptr->genda_pos ;
    }
    if (max_rows > context[context_num].genda_rows)
        max_rows = context[context_num].genda_rows ;
    
    /* ---------------------------------------------------------------------------------- */
    /* Allocate temp ptrs based on genda_rows for use by 'gsi_set_xxx_list/array. Since 
       the DB data is returned in 1 object, enough space must be allocated for all rows.
       If the number of rows exceeds context[context_num].genda_rows, then return a partially 
       populated object and the message 'end-of-cursor has not been reached' warning.     */
    /* ---------------------------------------------------------------------------------- */
    for (col=0; col < genda_ptr->ncols; col++)
    {
        switch (genda_ptr->da_col_ptr[col].data_type) {
        case GDB_STRING_TYPE:
                                if (strval != NULL)
                                    break ;
                                if ((strval = (GDB_CHAR**)XCALLOC(max_rows+1, sizeof(GDB_CHAR*))) == NULL)
                                {
                                    iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                    return_rpc_status(NULL, 0, NULL, call_index) ;
                                    goto jumpOut ;
                                }
                                break ;

        case GDB_BYTE_TYPE:
        case GDB_SHORT_TYPE:
        case GDB_INT_TYPE:
        case GDB_LONG_TYPE:
                                if (longval != NULL)
                                    break ;
                                if ((longval = (long *)XCALLOC(max_rows+1, sizeof(long))) == (long *)NULL) 
                                {
                                    iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                    return_rpc_status(NULL, 0, NULL, call_index) ;
                                    goto jumpOut ;
                                }
                                break ;

        case GDB_FLOAT_TYPE:
        case GDB_DBL_TYPE:
                                if (dblval != NULL)
                                    break ;
                                if ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double))) == (double *)NULL) 
                                {
                                    iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                    return_rpc_status(NULL, 0, NULL, call_index) ;
                                    goto jumpOut ;
                                } 
                                break ;
        }
    }

    /* Allocate a pointer to an array of gsi_items for each column of the query */
    /* ------------------------------------------------------------------------ */
    itmval = (gsi_item**)XCALLOC(genda_ptr->ncols, sizeof(gsi_item*)) ;
    if (itmval == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        goto jumpOut ;
    }            

  /******************
   * START FETCHING
   ******************/

    /* --------------------------------------------------------------------------- */
    /* Fetch & associate data with GSI lists/arrays. All data must be loaded into  */
    /* 'new_items' and associated with the object via a single set..vector         */
    /* --------------------------------------------------------------------------- */   
    intOvflErr = FALSE ;
    for (col=0; col < genda_ptr->ncols; col++)
    {


    /* Activate (1) the append flag on each attrib. This will cause the returned data to
       be "appended" to G2 object attribs that are lists or arrays. If the append flag is
       not set (0) then the returned data will "replace" G2 object attribs. NOTE: This
       has no real meaning for simple types */
        if (update_action == OBJECT_APPEND)
        {
            idx = col ;
            gsi_set_item_append_flag(new_items[idx],1);
        }

        /* If the REPLACE option was chosen, find the column of the original  */
        /* query item that matches this column of the query.                  */
        /* ------------------------------------------------------------------ */
        else
        {
            for (lX = 0 ; lX < nnames ; lX++)
                if (!_wcsicmp(genda_ptr->da_col_ptr[col].col_name,gsi_symbol_name(aol_names[lX])))
                {
                    idx = lX ;
                    break ;
                }
            if (lX >= nnames)
            {
                iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%s", EQINCOL, genda_ptr->da_col_ptr[col].col_name);
                status = 1 ;
                break ;
            }
        }
        
        /* Set the data value based on type */
        selectColumnType = genda_ptr->da_col_ptr[col].data_type ;
        retType = 0 ;
        switch(selectColumnType)
        {
            case GDB_STRING_TYPE:
                for (row=0;row<max_rows;row++)
                    strval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_str ;
                if (list_flag) 
                {
                    gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("TEXT-LIST")));
                    gsi_set_str_list(new_items[idx], (gsi_char **)strval, max_rows);
                }
                else
                {
                    gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("TEXT-ARRAY")));
                    gsi_set_str_array(new_items[idx], strval, max_rows);
                }
                break ;
                
            case GDB_BYTE_TYPE:       
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:
            {
                /* Move the values into the longval array & determine if integer overflow occurs */
                /* ----------------------------------------------------------------------------- */
                intOvfl = FALSE ;
                for (row=0;row<max_rows;row++)
                {
                    if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_LONG_TYPE )
                        longval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                    else if (selectColumnType == GDB_BYTE_TYPE)
                        longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_byte ;
                    else if (selectColumnType == GDB_SHORT_TYPE)
                        longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_short ;
                    else
                        longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_int ;
                    if (longval[row] < MIN_G2_INTEGER || longval[row] > MAX_G2_INTEGER)
                        intOvfl = TRUE ;
                }

                /* Determine the return type */
                /* ------------------------- */
                if (update_action == OBJECT_REPLACE)
                {
                    if (smart_fetch)
                        attr_type = list_flag ? GSI_QUANTITY_LIST_TAG : GSI_QUANTITY_ARRAY_TAG ;
                    else if (intOvfl)
                        attr_type = list_flag ? GSI_FLOAT64_LIST_TAG : GSI_FLOAT64_ARRAY_TAG ;
                    else
                        attr_type = list_flag ? GSI_INTEGER_LIST_TAG : GSI_INTEGER_ARRAY_TAG ;
                }
                else
                    attr_type = gsi_type_of(aols[idx]) ;


                /* What we do now depends upon the type of array or list */
                /* that will hold the values.                            */
                /* ----------------------------------------------------- */
                switch(attr_type)
                {
                    case GSI_QUANTITY_ARRAY_TAG:   /* Return an array or list of quantities */
                    case GSI_QUANTITY_LIST_TAG:
                
                        /* Allocate an array of gsi_items */
                        if ((itmval[col] = gsi_make_items(max_rows)) == NULL)
                        {
                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                            return_rpc_status(NULL, 0, NULL, call_index) ;
                            goto jumpOut ;
                        }
                
                        /* Fill in the array of gsi_items */
                        for (row=0 ; row < max_rows ; row++)
                        {
                            if (longval[row] >= MIN_G2_INTEGER && longval[row] <= MAX_G2_INTEGER && (smart_fetch || !intOvfl))
                                gsi_set_int(itmval[col][row], longval[row]) ;
                            else
                                gsi_set_flt(itmval[col][row], (double)longval[row]) ;
                        }               

                        /* Now store the array of items as a list or array of */
                        /* quantities in the list/array of items              */
                        /* -------------------------------------------------- */
                        if (list_flag)
                        {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("QUANTITY-LIST")));
                        gsi_set_elements( new_items[idx], itmval[col], max_rows, GSI_QUANTITY_LIST_TAG );
                        }
                        else
                        {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("QUANTITY-ARRAY")));
                        gsi_set_elements( new_items[idx], itmval[col], max_rows, GSI_QUANTITY_ARRAY_TAG );
                        }
                        break ;
                
                    case GSI_INTEGER_ARRAY_TAG:
                    case GSI_INTEGER_LIST_TAG:

                        /* If there was overflow and smart fetch is on, the values  */
                        /* would cause overflow are replaced by the minimum or      */
                        /* maximum G2 integer values.  If smart fetch is off, this  */
                        /* call fails.                                              */
                        /* -------------------------------------------------------- */
                        if (intOvfl)
                        {
                            intOvflErr = TRUE ;
                            if (smart_fetch)
                            {
                                for (row=0;row<max_rows;row++)
                                {
                                    if (longval[row] < MIN_G2_INTEGER)
                                        longval[row] = MIN_G2_INTEGER ;
                                    else if (longval[row] > MAX_G2_INTEGER)
                                        longval[row] = MAX_G2_INTEGER ;
                                }
                            }
                            else
                            {
                                status = 1 ;
                                break ;
                            }
                        }

                        if (list_flag)
                        {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("INTEGER-LIST")));
                        gsi_set_int_list( new_items[idx], longval, max_rows );
                        }
                        else
                        {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("INTEGER-ARRAY")));
                        gsi_set_int_array( new_items[idx], longval, max_rows );
                        }
                        break ;
                
                    case GSI_FLOAT64_ARRAY_TAG:    /* Return a list or array of floats */
                    case GSI_FLOAT64_LIST_TAG:

                        if (!dblval && ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double))) == (double *)NULL))
                        {
                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                            return_rpc_status(NULL, 0, NULL, call_index) ;
                            goto jumpOut ;
                        }
                
                        /* Copy the values from the array of longs to the array of doubles */
                        for (row=0;row<max_rows;row++)
                        {
                            dblval[row] = (double)longval[row] ;
                            GFLOAT_TO_IEEE(dblval[row], &dblval[row], TRUE) ;
                        }
                
                        /* note: arg4 must be FALSE to prevent infinite loop */
                        iomsg(DBG4,LAYER,FALSE,FALSE,NULL,FALSE, "%d%s%s%s" , WTYPCHG, gsi_symbol_name(aol_names[idx]), _T("INTEGER"), _T("FLOAT"));

                        if (list_flag)
                        {
                            gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("FLOAT-LIST")));

                            gsi_set_flt_list( new_items[idx], dblval, max_rows );
                        }
                        else 
                        {
                            gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)"FLOAT-ARRAY"));
                            gsi_set_flt_array( new_items[idx], dblval, max_rows );
                        }
                        break ;

                    default:

		      iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s", EBADOBJ, _T("compatible query item"));

		      status = 1;
                }
                break ;
            } /* end of integral column case */          
            
            case GDB_FLOAT_TYPE:
            case GDB_DBL_TYPE:
            {
                /* Move the values into the dblval array & determine if there is */
                /* a DECIMAL(x, 0) value that would cause G2-integer overflow.    */
                /* ------------------------------------------------------------- */
                float_flag = FALSE ;
                intOvfl = FALSE ;
                for (row=0;row<max_rows;row++)
                {
                    if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_DBL_TYPE)
                        dblval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_dbl ;
                    else
                        dblval[row] = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_float ;
                    GFLOAT_TO_IEEE(dblval[row], &dblval[row], FALSE) ;
                    if (genda_ptr->decimal_flags[col] && 
                            ((dblval[row] < (double)MIN_G2_INTEGER - 0.1) || (dblval[row] > (double)MAX_G2_INTEGER + 0.1) ) )
                        intOvfl = TRUE ;
                }

                /* Determine the return type */
                /* ------------------------- */
                if (OBJECT_REPLACE == update_action)
                {
                    if (smart_fetch && genda_ptr->decimal_flags[col])
                        attr_type = list_flag ? GSI_QUANTITY_LIST_TAG : GSI_QUANTITY_ARRAY_TAG ;
                    else
                        attr_type = list_flag ? GSI_FLOAT64_LIST_TAG : GSI_FLOAT64_ARRAY_TAG ;
                }
                else
                    attr_type = gsi_type_of(aols[idx]) ;


                switch(attr_type)
                {
                case GSI_QUANTITY_ARRAY_TAG:   /* Return an array or list of quantities */
                case GSI_QUANTITY_LIST_TAG:

                    /* Allocate an array of gsi_items */
                    if ((itmval[col] = gsi_make_items(max_rows)) == NULL)
                    {
                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                        return_rpc_status(NULL, 0, NULL, call_index) ;
                        goto jumpOut ;
                    }
                
                    /* Fill in the array of gsi_items */
                    for (row=0 ; row < max_rows ; row++)
                    {
                        if (!genda_ptr->decimal_flags[col] || !smart_fetch ||
                                    (dblval[row] < (double)MIN_G2_INTEGER - 0.1) ||
                                    (dblval[row] > (double)MAX_G2_INTEGER + 0.1))
                            gsi_set_flt(itmval[col][row], dblval[row]) ;
                        else
                            gsi_set_int(itmval[col][row], (long)dblval[row]) ;
                    }               

                    /* Store the quantity list/array in the attribute */
                    if (list_flag)
                    {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("QUANTITY-LIST")));

                        gsi_set_elements( new_items[idx], itmval[col], max_rows, GSI_QUANTITY_LIST_TAG );
                    }
                    else
                    {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("QUANTITY-ARRAY")));

                        gsi_set_elements( new_items[idx], itmval[col], max_rows, GSI_QUANTITY_ARRAY_TAG );
                    }
                    break ;

                case GSI_INTEGER_ARRAY_TAG:
                case GSI_INTEGER_LIST_TAG:

                    if (intOvfl)
                    {
                        intOvflErr = TRUE ;
                        /* Overflow of a DECIMAL(x, 0) with smart fetch off is fatal */
                        if (!smart_fetch)
                        {
                            status = 1 ;
                            break ;
                        }
                    }

                    /* Allocate the array of longs, if necessary */
                    if (longval==(long*)NULL && ((longval= (long*)XCALLOC(max_rows+1, sizeof(long)))==NULL) )
                    {
                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                        return_rpc_status(NULL, 0, NULL, call_index) ;
                        goto jumpOut ;
                    }

                    /* Move the values from the array of doubles */
                    /* to the array of longs.                    */
                    for (row=0;row<max_rows;row++)
                    {
                        dblX = dblval[row] ;
                        if (dblX < (double)MIN_G2_INTEGER - 0.1)
                            longval[row] = MIN_G2_INTEGER ;
                        else if (dblX > (double)MAX_G2_INTEGER + 0.1)
                            longval[row] = MAX_G2_INTEGER ;
                        else
                            longval[row] = (long)dblX ;
                    }

                    /* Create the integer list or array */
                    if (list_flag)
                    {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("INTEGER-LIST")));

                        gsi_set_int_list( new_items[idx], longval, max_rows );
                    }
                    else 
                    {
                        gsi_set_class_name ( new_items[idx], gsi_make_symbol((gsi_char*)_T("INTEGER-ARRAY")));

                        gsi_set_int_array( new_items[idx], longval, max_rows );
                    }
                    break ;


                case GSI_FLOAT64_ARRAY_TAG:    /* Return a list or array of floats */
                case GSI_FLOAT64_LIST_TAG:

                    if (list_flag)
                    {
                        gsi_set_class_name (new_items[idx], gsi_make_symbol((gsi_char*)_T("FLOAT-LIST")));

                        gsi_set_flt_list(new_items[idx], dblval, max_rows) ;
                    }
                    else 
                    {
                        gsi_set_class_name (new_items[idx], gsi_make_symbol((gsi_char*)_T("FLOAT-ARRAY")));

                        gsi_set_flt_array( new_items[idx], dblval, max_rows );
                    }
                    break ;

                default:
                    iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s", EBADOBJ, _T("compatible query item")) ;

                    status = 1 ;
                }
                break ;
            } /* end of float/DECIMAL column case */
                
            default:
                iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s%s", EINVDTY, "na", "na");
                if (debug & DBG6) printf("\n");
                break ;
                
        } /* end switch */
        if (status)
            break ;

    } /* end for col */

    /* update the item-list */
    if (!status)
    {
        genda_ptr->genda_pos += max_rows ;
        if (list_flag)
            gsi_set_elements (attribs_out[1], new_items, naols, GSI_ITEM_LIST_TAG); 
        else
            gsi_set_elements (attribs_out[1], new_items, naols, GSI_ITEM_ARRAY_TAG);
    }
    
    if (intOvflErr)
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINTOVF) ;

    if (genda_ptr->genStat.status == EOCURSOR_CD && (genda_ptr->nrows * genda_ptr->genda_num + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed || genda_ptr->genda_pos == 0) && !status)
    {
        if (!intOvflErr)
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, NULL, FALSE, "%d", IEOFETC) ;
        cursor_pos = genda_ptr->genStat.rows_processed ;
    }
    else
    {
        if (!intOvflErr && !status)
            iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WNOTEOC) ;
        cursor_pos = (((genda_ptr->genStat.rows_processed - 1)/ genda_ptr->nrows) * genda_ptr->nrows) + genda_ptr->genda_pos ;
    }
    
    /* move updated attrs into the return object & return the object to G2 */
    if (!status)
    {
        gsi_set_attrs(query_item, attribs_out, 2) ;
        gsi_return_values(gdb_registered_item_array, 1, context_num) ;
    }
    

    /* update the cursor object status */
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], gsi_handle_of(arg[0])) ;
    attribs_out = gdb_attr_item_array ;
    update_object_status(attribs_out, NULL, UPDATE_ATTRS, 0) ;
    gsi_set_int(attribs_out[CURSOR_POS], cursor_pos) ;
    gsi_return_attrs(object[0], attribs_out, NUM_STATUS_ARGS, context_num) ;
    
    /* return the status info to G2 RPC */
    status_args = gdb_status_items ;
    update_object_status(status_args, NULL, UPDATE_ITEMS, 0) ;
    gsi_set_int(status_args[NROWS_POS], status ? 0 : max_rows) ;
    gsi_set_int(status_args[CURSOR_POS], cursor_pos) ;
    return_rpc_status(status_args, NUM_STATUS_ARGS, NULL, call_index) ;
jumpOut:
    gsi_clear_item(query_item) ;
    
    /* reset the global structures */
    for (col=0; col < genda_ptr->ncols; col++) 
    {
        gsi_clear_item(new_items[col]) ;
        /* reset the append flag */
        if (update_action == OBJECT_APPEND)
            gsi_set_item_append_flag(new_items[col], 0) ;
    }
    gsi_set_update_items_in_lists_and_arrays_flag(gsi_item_of_attr(attribs_out[1]), 0) ;
    gsi_clear_item(query_item) ;
    gsi_clear_item(attribs_out[0]) ;
    gsi_clear_item(attribs_out[1]) ;
    
    /* release the temp buffers */
    if (dblval != NULL)
        XFREE(dblval) ;
    if (longval != NULL)
        XFREE(longval) ;
    if (strval != NULL)
        XFREE(strval) ;
    if (itmval != NULL)
    {
        for (i = 0 ; i < quantityCt ; i++)
            if (itmval[i])
                gsi_reclaim_items(itmval[i]) ;
        XFREE(itmval) ;
    }
    
    /* release the column name array */
    XFREE(symlist) ;
    
    /* release fetched data */
    if ( (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed) || 
        genda_ptr->genda_pos == genda_ptr->nrows) 
    {
        genda_ptr->genda_pos = 0;     /* add for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
    }   
    return ;
} /* end update_query_item_rp */


/*===========================================================================*
    fetch_object_copy_rp                                      (XXX)   GDB-RPC
      - input: [0]=cursor-object
               [1]=user-object
               [2]=fetch-batch
               [3]=sequence of attribute names
               [4]=sequence of QUANTITY/VALUE flags
 *===========================================================================*/
static void fetch_object_copy_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    double              *dblval, dblX ;
    GENDA               *genda_ptr ;
    gsi_attr            *theAttrs, *theAttrs2 ;
    gsi_attr            *attribs ;
    gsi_item            *user_object ;
    gsi_item            **cmpd_items = NULL ;
    gsi_int             attr_type ;
    gsi_int             nattrs ;
    gsi_int             obj_handle ;
    gsi_registered_item *object ;
    gsi_symbol*         symval = NULL ;
    long                attr_num ;
    long                cursor_pos = 0 ;
    long                fetch_batch ;
    long                float_flag = FALSE ;
    long                found ;
    long                lngX ;
    long                max_rows ;
    long                ncmpd ;
    long                rcd = 0 ;   /* local record (row) counter - for batch-fetch */
    long                selectColumnType ;
    long                smart_fetch ;
    long                status ;
    long*               longval ;
    register int        col, row ;
    register int        n ;
    short               *qvFlags ;
    short               intOvflErr ;
    short               ret_floats ;
    short               use_items ;
    short               use_ints ;
    GDB_CHAR             **strval ;
    GDB_CHAR             *attr_class ;

    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("FETCH_OBJECT_COPY_RP: %"), context_num) ;

        /* Create user-object (generic type since we don't have user class type yet). Do it
           here in case error causes premature return from this function - need to send 
           status info back. KB procedure will delete the generic object on error and return
           an object of user's type to avoid problems. */
    
    user_object = gdb_object_array ;
    gsi_set_class_name(user_object[0], gsi_make_symbol((gsi_char*)GENERIC_OBJECT_NAME)) ;
    gsi_set_type(user_object[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    
    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }

    smart_fetch = context[context_num].smart_fetch  ;

    if (count < 5 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
#ifdef _DEBUG
    wprintf(_T("\ncount = %d\n"), count) ;
    wprintf(_T("-------------------------------------------------------\n")) ;
    wprintf(_T(" Cursor-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0]) ) ;
    wprintf(_T("    Handle:      %d\n"), gsi_handle_of(arg[0]) ) ;
    get_attrib_info(arg[0]) ;
    
    wprintf(_T("\n-------------------------------------------------------\n")) ;
    wprintf(_T(" User-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[1]), gsi_type_to_string(arg[1]) ) ;
    wprintf(_T("    Class Name:  %s\n"), gsi_symbol_name(gsi_class_name_of(arg[1]))) ;
    if (gsi_name_of(arg[1]) == NULL)
        wprintf(_T("    Object Name: (null)\n" )) ;
    else
        wprintf(_T("    Object Name: %s\n"), gsi_symbol_name(gsi_name_of(arg[1]))) ;
    get_attrib_info(arg[1]) ;
    wprintf(_T("==================\n")) ;
    get_qv_info(arg[3], arg[4]) ;
#endif
    
    /* arg-0 is the cursor-object handle */
    obj_handle = gsi_handle_of(arg[0]) ;
    
    /* arg-1 is the user object: Redefine the user-object to the actual class type */
    gsi_set_class_name(user_object[0], gsi_class_name_of(arg[1])) ;
    gsi_set_type(user_object[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    
    /* Check for ok handle, and object */
    if (obj_handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
    if (genda_ptr == (GENDA *)NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVITM, CURSOR_OBJECT_NAME) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    attribs = gsi_attrs_of(arg[1]) ;
    nattrs = gsi_attr_count_of(arg[1]) ;
    qvFlags = build_qv_list(attribs, nattrs, arg[3], arg[4]) ;
    if (nattrs && qvFlags == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    if (genda_ptr->genStat.rows_processed != 0 && genda_ptr->genda_pos == 0 &&
        genda_ptr->more_rows != genda_ptr->nrows )
    {
        /* If positioned at EOCURSOR simply return EOCURSOR message until user
           either performs SET_QUERY or REFRESH_CURSOR: This check is provided
           because Oracle will automatically refresh the cursor. Performing a
           'ping' here so EOCURSOR message is not returned while disconnected.
           This will also cause the G2 IO db-connection-status to be set to 
           disconnected via KB logic */   
        
        if (!process_ping_db())    
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        else 
        {
        /* this will prevent EOCURSOR message from being returned
            following a reconnect */
            genda_ptr->genStat.rows_processed = 0 ;
        }
        
        genda_ptr->more_rows = 0; /* make sure its 0 */  
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    /* Initially, Allocate then Update (populate) the GENDA with db data */
    if (genda_ptr->genda_pos == 0) 
    {    /* add for fetch-batch */
        status = alloc_genda(genda_ptr, ALLOC_ALL) ;
        if (!status)
            status = update_genda(genda_ptr) ;
        if (status) 
        {
            update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
            return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
            gsi_clear_item(user_object[0]) ;
            free_genda(DATA_ONLY, genda_ptr) ;
            return ;
        }
    }
    if (genda_ptr->genda_pos == -1)     /* First rows have already been loaded */
        genda_ptr->genda_pos = 0 ;
    
    theAttrs = gdb_attr_item_array ;
    
    /* initialize temp buffers to NULL */
    strval  = NULL ;
    longval = NULL ;
    dblval  = NULL ;
    
    /* arg-2 is fetch_batch size */
    fetch_batch = gsi_int_of(arg[2]) ;
    rcd = genda_ptr->genda_pos ;

  /******************
   * START FETCHING
   ******************/

    max_rows = genda_ptr->more_rows ;
    if (fetch_batch > 0 && genda_ptr->more_rows > 0)
    { /* && fetch_batch <= genda_ptr->more_rows) -- don't set max_rows > rows fetched */
        if (fetch_batch + rcd < genda_ptr->more_rows)
            max_rows = fetch_batch ;
        else
            max_rows = genda_ptr->more_rows - genda_ptr->genda_pos ;
    }
    if (max_rows > context[context_num].genda_rows)
        max_rows = context[context_num].genda_rows ;
    
        /* If previous fetch returned all rows but the EOCURSOR marker, then this update will
           only get the EOCURSOR status. Therefore, more_rows will be 0. This should only happen
           when update occurs exactly on a genda->rows boundary */
    if (max_rows <= 0)
    {
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        genda_ptr->genda_pos = 0 ;
        free_genda(DATA_ONLY, genda_ptr) ;
        return ;
    }
    
    /* Allocate temp ptrs based on genda_rows for use by 'gsi_set_xxx_list/array. Since 
       the DB data is returned in 1 object, enough space must be allocated for all rows.
       If the number of rows exceeds context[context_num].genda_rows, then return a partially 
       populated object and the message 'end-of-cursor has not been reached' warning. */
    
    for (col=0; col < genda_ptr->ncols; col++)
    {
        switch (genda_ptr->da_col_ptr[col].data_type)
        {
        case GDB_STRING_TYPE:
            if (strval != NULL)
                break ;
            if ((strval = (GDB_CHAR**)XCALLOC(max_rows+1, sizeof(GDB_CHAR*))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                goto jumpOut_of_fetch_obj_copy ;
            }
            break ;
        case GDB_BYTE_TYPE:
        case GDB_SHORT_TYPE:
        case GDB_INT_TYPE:
        case GDB_LONG_TYPE:
            if (longval != NULL)
                break ;
            if ((longval = (long *)XCALLOC(max_rows+1, sizeof(long))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                goto jumpOut_of_fetch_obj_copy ;
            }
            break ;
        case GDB_FLOAT_TYPE:
        case GDB_DBL_TYPE:
            if (dblval != NULL)
                break ;
            if ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                goto jumpOut_of_fetch_obj_copy ;
            } 
            break ;
        }
    }
    
    /* Fetch & associate data with GSI lists/arrays or simple values */
    
    /* allocate array of ptrs to store items for compound data types */
    if (nattrs < genda_ptr->ncols)
        ncmpd = nattrs ;
    else
        ncmpd = genda_ptr->ncols ;
    
    if ((cmpd_items = (gsi_item **)XCALLOC(ncmpd, sizeof(gsi_item *))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        goto jumpOut_of_fetch_obj_copy ;
    } 
    
    status = 0 ;
    attr_num = 0 ;
    intOvflErr = FALSE ;
    for (col=0; col < genda_ptr->ncols; col++)
    {
        found = FALSE ;
        /* try to match this db column with a user-object attribute */
        for (n=0; n<nattrs; n++)
        {
            if (!wcscmp(gsi_symbol_name(gsi_attr_name_of(attribs[n])), genda_ptr->da_col_ptr[col].col_name))
            {
                gsi_set_attr_name(theAttrs[attr_num], gsi_make_symbol((gsi_char*)genda_ptr->da_col_ptr[col].col_name)) ;
                if (qvFlags && qvFlags[n])
                    attr_type = GSI_QUANTITY_TAG ;
                else
                    attr_type = gsi_type_of(attribs[n]) ;
                attr_class = (GDB_CHAR*)gsi_symbol_name(gsi_class_name_of(attribs[n])) ;
                if (gsi_is_item(attribs[n]) && attr_class != NULL)
                {
                    gsi_set_class_name (theAttrs[attr_num], gsi_make_symbol((gsi_char*)attr_class) ) ;
                    gsi_set_type(theAttrs[attr_num], GSI_NULL_TAG) ; /* hack to correct GSI bug with set_class_name */
                    if (!attr_type)
                        attr_type = type_of_item(attribs[n], GDB_TYPE) ;
                }
                found = TRUE ;
                break ;
            }
        }
        if (!found)
            continue ;
        
        /* Set the data value based on type */
        selectColumnType = genda_ptr->da_col_ptr[col].data_type ;
        switch(selectColumnType)
        {
        case GDB_STRING_TYPE:
            for (row=0; row<max_rows; row++)
            {
                strval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_str ;
                if (attr_type == GSI_SEQUENCE_TAG)
                {
                    if (cmpd_items[attr_num] == NULL)
                        cmpd_items[attr_num] = gsi_make_items(max_rows) ;
                    gsi_set_str(cmpd_items[attr_num][row], (gsi_char*)strval[row]) ;
                }
            }
            
            if (attr_type == GSI_SYMBOL_LIST_TAG || attr_type == GSI_SYMBOL_ARRAY_TAG)
            {
                symval = (gsi_symbol*)XCALLOC(max_rows, sizeof(gsi_symbol)) ;
                if (symval == NULL)
                {
                    iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                    update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                    goto jumpOut_of_fetch_obj_copy ;
                }
                for (lngX = 0 ; lngX < max_rows ; lngX++)
                    symval[lngX] = gsi_make_symbol((gsi_char*)strval[lngX]) ;
            }
            if (is_list_type(attr_type))
            {
                if (attr_type == GSI_SYMBOL_LIST_TAG)
                    gsi_set_sym_list(theAttrs[attr_num], symval, max_rows) ;
                else
                {
                    gsi_set_str_list(theAttrs[attr_num], (gsi_char**)strval, max_rows) ;
                }
            }
            else if (is_array_type(attr_type))
            {
                if (attr_type == GSI_SYMBOL_ARRAY_TAG)
                    gsi_set_sym_array(theAttrs[attr_num], symval, max_rows) ;
                else
                    gsi_set_str_array(theAttrs[attr_num], (gsi_char**)strval, max_rows) ;
            }
            else if (attr_type == GSI_SEQUENCE_TAG)
                gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, GSI_SEQUENCE_TAG) ;
            else if (type_of_item(attribs[n], GDB_CATEGORY) == GDB_SIMPLE_TYPE || type_of_item(attribs[n], GDB_CATEGORY) == GDB_PARAM_OR_VAR_TYPE) 
            { 
                if (attr_type == GSI_STRING_TAG || attr_type == GSI_NULL_TAG)
                    gsi_set_str(theAttrs[attr_num], (gsi_char*)strval[max_rows-1]) ;
                else
                    gsi_set_sym(theAttrs[attr_num], gsi_make_symbol((gsi_char*)strval[max_rows-1])) ;
            }
            else
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                status = 1 ;
                break ;
            }
            if (symval)
            {
                XFREE(symval) ;
                symval = NULL ;
            }
            attr_num++ ;
            break ;
            
        case GDB_BYTE_TYPE:       
        case GDB_SHORT_TYPE:
        case GDB_INT_TYPE:
        case GDB_LONG_TYPE:
            {
                float_flag = FALSE ;
                for (row=0;row<max_rows;row++)
                {
                    if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_LONG_TYPE)
                        longval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                    else if (selectColumnType == GDB_BYTE_TYPE)
                        longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_byte ;
                    else if (selectColumnType == GDB_SHORT_TYPE)
                        longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_short ;
                    else
                        longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_int ;
                    if (longval[row] > MAX_G2_INTEGER || longval[row] < MIN_G2_INTEGER)
                        float_flag = TRUE ;
                }
                
                /* If the receiving attribute is a sequence or an array or list of values,    */
                /* quantities, or item-or-values we must make sure an array of gsi_items      */
                /* has been allocated.                                                        */
                /* -------------------------------------------------------------------------- */
                use_items = attr_type == GSI_SEQUENCE_TAG || 
                    attr_type == GSI_VALUE_LIST_TAG ||    attr_type == GSI_VALUE_ARRAY_TAG || 
                    attr_type == GSI_QUANTITY_LIST_TAG || attr_type == GSI_QUANTITY_ARRAY_TAG ||
                    attr_type == GSI_ITEM_OR_VALUE_LIST_TAG || attr_type == GSI_ITEM_OR_VALUE_ARRAY_TAG ;
                if (use_items)
                {
                    if (cmpd_items[attr_num] == (gsi_item *)NULL)
                    {
                        cmpd_items[attr_num] = gsi_make_items(max_rows) ;
                        if (cmpd_items[attr_num] == NULL)
                        {
                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                            update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                            goto jumpOut_of_fetch_obj_copy ;
                        }
                    }
                }

                /* We now have the values in the longval array.  If the receiving attribute is of a  */
                /* float type, we will return all the values as floats.  Otherwise, we will look at  */
                /* whether or not any of the values would have caused G2-integer overflow to         */
                /* determine if the values should be returned as integers or floats.                 */
                /* --------------------------------------------------------------------------------- */
                ret_floats = (attr_type == GSI_FLOAT64_LIST_TAG || attr_type == GSI_FLOAT64_ARRAY_TAG ||
                              attr_type == GSI_FLOAT64_TAG) ;
                if (!ret_floats && !smart_fetch)
                {
                    if (!float_flag)
                    {
                        if (attr_type==GSI_INTEGER_LIST_TAG)
                            gsi_set_int_list(theAttrs[attr_num], longval, max_rows) ;
                        else if (attr_type==GSI_INTEGER_ARRAY_TAG)
                            gsi_set_int_array(theAttrs[attr_num], longval, max_rows) ;
                        else if (use_items)
                        {
                            for (row = 0 ; row < max_rows ; row++)
                                gsi_set_int(cmpd_items[attr_num][row], longval[row]) ;
                            gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, attr_type) ;
                        }
                        else if (type_of_item(attribs[n], GDB_CATEGORY) == GDB_SIMPLE_TYPE || type_of_item(attribs[n], GDB_CATEGORY) == GDB_PARAM_OR_VAR_TYPE)
                            gsi_set_int(theAttrs[attr_num], longval[max_rows-1]) ;
                        else
                        {
                            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                            status = 1 ;
                        }
                    }
                    else
                        ret_floats = TRUE ;
                }
                
                
                /* If smart fetch is on, we will look at both the receiving attribute type and the  */
                /* individual values to decide how to cast the results.                             */
                /* -------------------------------------------------------------------------------- */
                else if(!ret_floats)
                {
                    /* Case one: Using gsi_items to return values */
                    if (use_items)
                    {
                        for (row = 0 ; row < max_rows ; row++)
                        {
                            lngX = longval[row] ;
                            if (lngX > MAX_G2_INTEGER || lngX < MIN_G2_INTEGER)
                                gsi_set_flt(cmpd_items[attr_num][row], (double)lngX) ;
                            else
                                gsi_set_int(cmpd_items[attr_num][row], lngX) ;
                        }
                        gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, attr_type) ;
                    }
                    
                    /* Case two: attribute is a value or a quantity */
                    else if (attr_type == GSI_QUANTITY_TAG)
                    {
                        lngX = longval[max_rows-1] ;
                        if (lngX > MAX_G2_INTEGER || lngX < MIN_G2_INTEGER)
                            gsi_set_flt(theAttrs[attr_num], (double)lngX) ;
                        else
                            gsi_set_int(theAttrs[attr_num], lngX) ;
                    }
                                     
                    /* Case three: Returning a list or array of integers */
                    else if (attr_type == GSI_INTEGER_LIST_TAG || attr_type == GSI_INTEGER_ARRAY_TAG ||
                        attr_type == GSI_INTEGER_TAG)
                    {
                        if (float_flag)
                        {
                            intOvflErr = TRUE ;  /* Request integer overflow error message */
                            for (row = 0 ; row < max_rows ; row++)
                            {
                                lngX = longval[row] ;
                                if (lngX > MAX_G2_INTEGER)
                                    longval[row] = MAX_G2_INTEGER ;
                                else if (lngX < MIN_G2_INTEGER)
                                    longval[row] = MIN_G2_INTEGER ;
                            }
                        }
                        if (attr_type == GSI_INTEGER_LIST_TAG)
                            gsi_set_int_list(theAttrs[attr_num], longval, max_rows) ;
                        else if (attr_type == GSI_INTEGER_ARRAY_TAG)
                            gsi_set_int_array(theAttrs[attr_num], longval, max_rows) ;
                        else if (attr_type == GSI_INTEGER_TAG)
                            gsi_set_int(theAttrs[attr_num], longval[max_rows-1]) ;
                    }
                    
                    /* Last case: Returning the values as floats */
                    else
                        ret_floats = TRUE ;
                    
                } /* end of smart fetch */
                
                
                /* Here is where we convert all the values to floats. */
                /* -------------------------------------------------- */
                if (ret_floats)
                {
                    if (dblval == (double *)NULL)
                    {
                        if ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double))) == (double *)NULL)
                        {
                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                            update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                            goto jumpOut_of_fetch_obj_copy ;
                        } 
                    }
                    for (row=0;row<max_rows;row++)
                    {
                        dblval[row] = (GDB_DBL)longval[row] ;
                        GFLOAT_TO_IEEE(dblval[row], &dblval[row], TRUE) ;
                    }
                    
                    if (attr_type==GSI_FLOAT64_LIST_TAG)
                        gsi_set_flt_list(theAttrs[attr_num], dblval, max_rows) ;
                    else if (attr_type==GSI_FLOAT64_ARRAY_TAG)
                        gsi_set_flt_array(theAttrs[attr_num], dblval, max_rows) ;
                    else if (use_items)
                    {
                        for (row = 0 ; row < max_rows ; row++)
                            gsi_set_flt(cmpd_items[attr_num][row], dblval[row]) ;
                        gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, attr_type) ;
                    }
                    else if (type_of_item(attribs[n], GDB_CATEGORY) == GDB_SIMPLE_TYPE || type_of_item(attribs[n], GDB_CATEGORY) == GDB_PARAM_OR_VAR_TYPE)
                        gsi_set_flt(theAttrs[attr_num], dblval[max_rows-1]) ;
                    else if (attr_type == GSI_INTEGER_TAG || attr_type == GSI_INTEGER_LIST_TAG ||
                             attr_type == GSI_INTEGER_ARRAY_TAG )
                    {
                        intOvflErr = TRUE ;
                        status = 1 ;
                    }
                    else
                    {
                        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                        status = 1 ;
                    }                   
                }
                
                attr_num++ ;
                break ;
            }
        case GDB_FLOAT_TYPE:
        case GDB_DBL_TYPE:

            use_items = (attr_type == GSI_SEQUENCE_TAG || (smart_fetch &&
                (attr_type == GSI_VALUE_LIST_TAG ||   attr_type == GSI_VALUE_ARRAY_TAG || 
                 attr_type == GSI_QUANTITY_LIST_TAG || attr_type == GSI_QUANTITY_ARRAY_TAG ||
                 attr_type == GSI_ITEM_OR_VALUE_LIST_TAG || attr_type == GSI_ITEM_OR_VALUE_ARRAY_TAG))) ;

            /* Note that smart fetch is not intended to return true floating point value */
            /* (as opposed to DECIMAL(x,0) values) to integer-type attributes.           */
            use_ints = smart_fetch && genda_ptr->decimal_flags[col] && 
                (attr_type == GSI_INTEGER_LIST_TAG || attr_type == GSI_INTEGER_ARRAY_TAG ||
                attr_type == GSI_INTEGER_TAG) ;


            /* If the receiving attribute is a sequence or an array or list of values     */
            /* or quantities, we must make sure an array of gsi_items has been allocated. */
            /* -------------------------------------------------------------------------- */
            if (use_items)
            {
                if (cmpd_items[attr_num] == (gsi_item *)NULL)
                {
                     cmpd_items[attr_num] = gsi_make_items(max_rows) ;
                     if (cmpd_items[attr_num] == NULL)
                     {
                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                        goto jumpOut_of_fetch_obj_copy ;
                    }
                }
            }

            /* If the receiving attribute is some type of integer, we must make sure that */
            /* an array of longs (gsi_ints) has been allocated.                           */
            /* -------------------------------------------------------------------------- */
            if (use_ints)
            {
                if (longval == (long *)NULL)
                    if ((longval = (long *)XCALLOC(max_rows+1, sizeof(long))) == (long *)NULL)
                    {
                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                        goto jumpOut_of_fetch_obj_copy ;
                    }
            }

            for (row=0;row<max_rows;row++)
            {
                if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_DBL_TYPE)
                    dblX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_dbl ;
                else 
                    dblX = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_float ;
                GFLOAT_TO_IEEE(dblX, &dblX, TRUE) ;
                if (use_items)
                    if (!smart_fetch || !genda_ptr->decimal_flags[row] || dblX < MIN_G2_INTEGER - 0.1 ||
                            dblX > MAX_G2_INTEGER + 0.1)
                        gsi_set_flt(cmpd_items[attr_num][row], dblX) ;
                    else
                        gsi_set_int(cmpd_items[attr_num][row], (long)dblX) ;
                else if (use_ints)
                {
                    if (dblX > (double)MAX_G2_INTEGER + 0.1)
                    {
                        longval[row] = MAX_G2_INTEGER ;
                        intOvflErr = TRUE ;
                    }
                    else if (dblX < (double)(MIN_G2_INTEGER - 0.1))
                    {
                        longval[row] = MIN_G2_INTEGER ;
                        intOvflErr = TRUE ;
                    }
                    else
                        longval[row] = (long)dblX ;
                }
                else
                    dblval[row] = dblX ;
            }

            /* Cast the return values to the correct type which depends upon whether or     */
            /* not smart fetch is set, whether or not this column is a DECIMAL(x,0) column, */
            /* and the type of attribute that will receive the values.                      */
            /* ---------------------------------------------------------------------------- */
            if (use_items)
                gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, attr_type) ;
            else if (use_ints)
                if (attr_type == GSI_INTEGER_LIST_TAG)
                    gsi_set_int_list(theAttrs[attr_num], longval, max_rows) ;
                else if (attr_type == GSI_INTEGER_ARRAY_TAG)
                    gsi_set_int_array(theAttrs[attr_num], longval, max_rows) ;
                else
                    gsi_set_int(theAttrs[attr_num], longval[max_rows-1]) ;
            else if (attr_type == GSI_QUANTITY_TAG && genda_ptr->decimal_flags[col] &&
                        dblval[max_rows-1] < (double)MAX_G2_INTEGER + 0.1 && 
                        dblval[max_rows-1] > (double)MIN_G2_INTEGER - 0.1)
                    gsi_set_int(theAttrs[attr_num], (long)dblval[max_rows-1]) ;
            else if (is_list_type(attr_type))
                gsi_set_flt_list(theAttrs[attr_num], dblval, max_rows) ;
            else if (is_array_type(attr_type))
                gsi_set_flt_array(theAttrs[attr_num], dblval, max_rows) ;
            else if (type_of_item(attribs[n], GDB_CATEGORY) == GDB_SIMPLE_TYPE || type_of_item(attribs[n], GDB_CATEGORY) == GDB_PARAM_OR_VAR_TYPE)
                gsi_set_flt(theAttrs[attr_num], dblval[max_rows-1]) ;
            else 
            {
                iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                status = 1 ;
                break ;
            }
            attr_num++ ;
            break ;
            
        default:
            iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s%s", EINVDTY, "na", "na");
            if (debug & DBG6) printf("\n");
            status = 1 ;
            break ;
            
        } /* end switch */
   
    } /* end for col */
  
    if (!status)
        genda_ptr->genda_pos += max_rows ;
    
    if (intOvflErr)
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINTOVF) ;
    if (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed && !status)
    {
        if (!intOvflErr)
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, NULL, FALSE, "%d", IEOFETC) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        cursor_pos = genda_ptr->genStat.rows_processed ;
    }
    else
    {
        if (!status && !intOvflErr)
            iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WNOTEOC) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        cursor_pos = (((genda_ptr->genStat.rows_processed - 1)/ genda_ptr->nrows) * genda_ptr->nrows) + genda_ptr->genda_pos ;
    }

    
    /* update the cursor object status */
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], gsi_handle_of( arg[0] )) ;
    
    theAttrs2 = gdb_status_attr_items ;
    update_object_status(theAttrs2, NULL, UPDATE_ATTRS, 0) ;
    gsi_set_int(theAttrs2[CURSOR_POS], cursor_pos) ;
    gsi_return_attrs(object[0], theAttrs2, NUM_STATUS_ARGS, context_num) ;
    
    /* move attrs + status into the return object */
    if (!status)
        gsi_set_attrs(user_object[0], theAttrs, attr_num) ;
    
    /* return the object & status info to G2 RPC */
    gsi_set_int(user_object[1+NROWS_POS], status ? 0 : max_rows) ;
    gsi_set_int(user_object[1+CURSOR_POS], cursor_pos) ;
    
jumpOut_of_fetch_obj_copy:  
    return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
    
    /* reset the global structures */
    for (n=0;n<attr_num/*nattrs*/;n++)
        gsi_clear_item(theAttrs[n]) ;
    gsi_clear_item(user_object[0]) ;
    /* note: redundant clear follows in case of EINVDTY @ 1st or last attr */ 
    gsi_clear_item(theAttrs[0]) ;
    gsi_clear_item(theAttrs[attr_num+1]) ;
    
    /* release the temp buffers */
    if (qvFlags != NULL)
        XFREE(qvFlags) ;
    if (dblval != NULL)
        XFREE(dblval) ;
    if (longval != NULL)
        XFREE(longval) ;
    if (strval != NULL)
        XFREE(strval) ;
    if (cmpd_items != (gsi_item **)NULL)
    {
        for (n=0;n<ncmpd;n++)
        {
            if (cmpd_items[n] != (gsi_item *)NULL)
                gsi_reclaim_items(cmpd_items[n]) ;
        }
        XFREE ((gsi_item **)cmpd_items) ;
    }
    
    /* release fetched data */
    if ( !status && (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed) || 
        genda_ptr->genda_pos == genda_ptr->nrows)
    {
        genda_ptr->genda_pos = 0;     /* added for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
    }
    
    /* If the attempt to process the first retrieved records failed, remember */
    /* that the genda has already been loaded with the first records.         */
    /* ---------------------------------------------------------------------- */
    if (status && genda_ptr->genda_pos == 0)
        genda_ptr->genda_pos = -1 ;

    return ;
} /* end fetch_object_copy_rp */



/*===========================================================================*
    fetch_object_update_rp                                    (YYY)   GDB-RPC
      - input: [0]=cursor-object (handle only)
               [1]=user-object   (with handle)
               [2]=update-action (OBJECT_REPLACE,OBJECT_APPEND)
               [3]=fetch-batch
               [4]=sequence of attribute names
               [5]=sequence of QUANTITY/VALUE flags
 *===========================================================================*/ 
static void fetch_object_update_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    double                  dblX ;
    double*                 dblval ;
    GENDA*                  genda_ptr ;
    gsi_attr*               attribs ;
    gsi_attr*               theAttrs ;
    gsi_int                 attr_type ;
    gsi_int                 co_handle ;
    gsi_int                 uo_handle ;
    gsi_int                 nattrs ;
    gsi_item*               user_object ;
    gsi_item*               status_args ;
    gsi_item**              cmpd_items = NULL ;
    gsi_registered_item*    object ;
    gsi_symbol              attr_class ;
    gsi_symbol*             symval = NULL ;
    register int            col, row, n ;
    long                    attr_num ;
    long                    cursor_pos = 0 ;
    long                    fetch_batch ;
    long                    float_flag = FALSE ;
    long                    found ;
    long                    lngX ;
    long                    max_rows ;
    long                    rcd = 0 ;   /* local record (row) counter - for batch-fetch */
    long                    selectColumnType ;
    long                    smart_fetch ;
    long                    status ;
    long                    update_action ;
    long*                   longval ;
    short                   int_ovfl, intOvflErr ;
    short                   use_items ;
    short                   use_ints ;
    short                   stopError ;
    short*                  qvFlags ;
    GDB_CHAR**               strval ;
     
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("FETCH_OBJECT_UPDATE_RP: %"), context_num) ;
    
    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    smart_fetch = context[context_num].smart_fetch ;
    
    if (count < 6 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
#ifdef _DEBUG
    printf("\ncount = %d\n", count) ;
    printf("-------------------------------------------------------\n") ;
    printf(" Cursor-Object Information\n") ;
    printf("-------------------------------------------------------\n\n") ;

    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0]));

    printf("    Handle:      %d\n", gsi_handle_of(arg[0]) ) ;
    get_attrib_info(arg[0]) ;
    
    printf("\n-------------------------------------------------------\n") ;
    printf(" User-Object Information\n") ;
    printf("-------------------------------------------------------\n\n") ;

    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[1]), gsi_type_to_string(arg[1]) ) ;
    wprintf(_T("    Class Name:  %s\n"), gsi_symbol_name(gsi_class_name_of(arg[1]))) ;

    if (gsi_name_of(arg[1]) == NULL)
        printf("    Object Name: (null)\n");
    else {

        wprintf(_T("    Object Name: %s\n"), gsi_symbol_name(gsi_name_of(arg[1])));
    }
    printf("    Handle:      %d\n", gsi_handle_of(arg[1]));
    get_attrib_info(arg[1]) ;
    printf("==================\n");
    get_qv_info(arg[4], arg[5]) ;
#endif
    
    /* arg-0 is the cursor-object handle */
    co_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (co_handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-1 is the user object */
    uo_handle = gsi_handle_of(arg[1]) ;
    
    /* Check for ok handle, and object */
    if (uo_handle < MIN_ITEM_HANDLE)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* associate object we're building with existing object in G2 */
    user_object = gsi_item_of_registered_item(gdb_registered_item_array[0]) ;
    gsi_set_handle(gdb_registered_item_array[0], uo_handle) ;
    gsi_set_class_name(user_object, gsi_class_name_of(arg[1])) ;
    gsi_set_type(user_object, GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    
    /* make sure GENDA pointer has been allocated */
    genda_ptr = storage_area(GET, context_num, co_handle, NULL) ;
    if (genda_ptr == (GENDA *)NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVITM, CURSOR_OBJECT_NAME) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(user_object) ;
        return ;
    }
    
    /* arg-2 is the update-action: REPLACE attrib data or APPEND attrib data */
    update_action = gsi_int_of(arg[2]) ;
    if (update_action != OBJECT_REPLACE && update_action != OBJECT_APPEND) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(user_object) ;
        return ;
    }
    
    attribs = gsi_attrs_of(arg[1]) ;
    nattrs = gsi_attr_count_of(arg[1]) ;
    qvFlags = build_qv_list(attribs, nattrs, arg[4], arg[5]) ;
    if (nattrs && qvFlags == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object) ;
        return ;
    }
    
    if (genda_ptr->genStat.rows_processed != 0 && genda_ptr->genda_pos == 0 &&
        genda_ptr->more_rows != genda_ptr->nrows )
    {
    /* If positioned at EOCURSOR simply return EOCURSOR message until user
       either performs SET_QUERY or REFRESH_CURSOR: This check is provided
       because Oracle will automatically refresh the cursor. Performing a
       'ping' here so EOCURSOR message is not returned while disconnected.
       This will also cause the G2 IO db-connection-status to be set to 
       disconnected via KB logic */   
        
        if (!process_ping_db())    
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        else 
        {
        /* this will prevent EOCURSOR message from being returned
           following a reconnect */
            genda_ptr->genStat.rows_processed = 0 ;
        }
        
        genda_ptr->more_rows = 0; /* make sure its 0 */  
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(user_object) ;
        return ;
    }
    
    /* Initially, Allocate then Update (populate) the GENDA with db data */
    if (genda_ptr->genda_pos == 0)
    {    /* add for fetch-batch */
        status = alloc_genda(genda_ptr, ALLOC_ALL) ;
        if (!status)
            status = update_genda(genda_ptr) ;
        if (status) 
        {
            return_rpc_status(NULL, 0, NULL, call_index) ;
            free_genda(DATA_ONLY, genda_ptr) ;
            gsi_clear_item(user_object) ;
            return ;
        }
    }
    if (genda_ptr->genda_pos == -1)     /* First rows have already been loaded */
        genda_ptr->genda_pos = 0 ;
    
    theAttrs = gdb_attr_item_array ;
    
    /* initialize temp buffers to NULL */
    strval  = NULL ;
    longval = NULL ;
    dblval  = NULL ;
    
    /* arg-3 is fetch_batch size */
    fetch_batch = gsi_int_of(arg[3]) ;
    rcd = genda_ptr->genda_pos ;
    
    /******************
    * START FETCHING
    ******************/
    
    max_rows = genda_ptr->more_rows ;
    if (fetch_batch > 0 && genda_ptr->more_rows > 0) 
    { /* && fetch_batch <= genda_ptr->more_rows) -- don't set max_rows > rows fetched */
        if (fetch_batch + rcd < genda_ptr->more_rows)
            max_rows = fetch_batch ;
        else
            max_rows = genda_ptr->more_rows - genda_ptr->genda_pos ;
    }
    if (max_rows > context[context_num].genda_rows)
        max_rows = context[context_num].genda_rows ;
    
    /* If previous fetch returned all rows but the EOCURSOR marker, then this update will
       only get the EOCURSOR status. Therefore, more_rows will be 0. This should only happen
       when update occurs exactly on a genda->rows boundry */
    if (max_rows <= 0) 
    {
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        genda_ptr->genda_pos = 0 ;
        free_genda(DATA_ONLY, genda_ptr) ;
        gsi_clear_item(user_object) ;
        return ;
    }
    
    /* Allocate an array of pointers to gsi_items, one per attribute.  Many   */
    /* of these slots will not be used, but this way will always have a       */
    /* slot available if we discover later that we need it.                   */
    /* ---------------------------------------------------------------------- */      
    if ((cmpd_items = (gsi_item **)XCALLOC(nattrs, sizeof(gsi_item *))) == NULL) 
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    } 

    /* Allocate temp ptrs based on genda_rows for use by 'gsi_set_xxx_list/array. Since 
       the DB data is returned in 1 object, enough space must be allocated for all rows.
       If the number of rows exceeds context[context_num].genda_rows, then return a partially 
       populated object and the message 'end-of-cursor has not been reached' warning. */
    
    for (col=0; col < genda_ptr->ncols; col++)
    {
        switch (genda_ptr->da_col_ptr[col].data_type) 
        {
            case GDB_STRING_TYPE:
                                    if (strval != NULL)
                                        break ;
                                    if ((strval = (GDB_CHAR**)XCALLOC(max_rows+1, sizeof(GDB_CHAR*))) == NULL) 
                                    {
                                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                        return_rpc_status(NULL, 0, NULL, call_index) ;
                                        gsi_clear_item(user_object) ;
                                        goto jumpOut_of_update_obj ;
                
                                    }
                                    break ;

            case GDB_BYTE_TYPE:
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:
                                    if (longval != NULL)
                                        break ;
                                    if ((longval = (long *)XCALLOC(max_rows+1, sizeof(long))) == (long *)NULL) 
                                    {
                                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                        return_rpc_status(NULL, 0, NULL, call_index) ;
                                        gsi_clear_item(user_object) ;
                                        goto jumpOut_of_update_obj ;
                                    }
                                    break ;

            case GDB_FLOAT_TYPE:
            case GDB_DBL_TYPE:
                                    if (dblval != NULL)
                                        break ;
                                    if ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double))) == (double *)NULL) 
                                    {
                                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                        return_rpc_status(NULL, 0, NULL, call_index) ;
                                        gsi_clear_item(user_object) ;
                                        goto jumpOut_of_update_obj ;
                                    } 
                                    break ;

        }
    }
    
    status = 0 ;
    attr_num = 0 ;
    intOvflErr = FALSE ;
    for (col=0; col < genda_ptr->ncols; col++)
    {
        found = FALSE ;
        /* try to match this db column with a user-object attribute */
        for (n=0; n < nattrs; n++) 
        {
            if (!wcscmp(gsi_symbol_name(gsi_attr_name_of(attribs[n])), genda_ptr->da_col_ptr[col].col_name)) 
            {
                gsi_set_attr_name(theAttrs[attr_num], gsi_make_symbol((gsi_char*)genda_ptr->da_col_ptr[col].col_name)) ;
                if (qvFlags && qvFlags[n])
                    attr_type = GSI_QUANTITY_TAG ;
                else
                    attr_type = gsi_type_of(attribs[n]) ;
                attr_class = gsi_class_name_of(attribs[n]) ;
                if (gsi_is_item(attribs[n]) && wcscmp(gsi_symbol_name(attr_class), _T("")))
                {
                    gsi_set_class_name (theAttrs[attr_num], attr_class) ;
                    gsi_set_type(theAttrs[attr_num], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
                    if (!attr_type)
                        attr_type = type_of_item(attribs[n], GDB_TYPE) ;
                }
                found = TRUE ;
                break ;
            }
        }
        if (!found)
            continue ;
        
        /* Activate (1) the append flag on each attrib. This will cause the returned data to
           be "appended" to G2 object attribs that are lists or arrays. If the append flag is
           not set (0) then the returned data will "replace" G2 object attribs. NOTE: This
           has no real meaning for simple types */
        if (update_action == OBJECT_APPEND)
            gsi_set_item_append_flag(gsi_item_of_attr(theAttrs[attr_num]), 1) ;
        
        /* Set the data value based on type */
        selectColumnType = genda_ptr->da_col_ptr[col].data_type ;
        switch(selectColumnType)
        {
            case GDB_STRING_TYPE:
                if (symval == NULL && (attr_type == GSI_SYMBOL_LIST_TAG || attr_type == GSI_SYMBOL_ARRAY_TAG))
                {
                    symval = (gsi_symbol*)XCALLOC(max_rows, sizeof(gsi_symbol*)) ;
                    if (symval == NULL)
                    {
                        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                        return_rpc_status(NULL, 0, NULL, call_index) ;
                        gsi_clear_item(user_object) ;
                        goto jumpOut_of_update_obj ;
                    }
                }
                for (row=0; row<max_rows; row++) 
                {
                    strval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_str ;
                    if (attr_type == GSI_SEQUENCE_TAG) 
                    {
                        if (cmpd_items[attr_num] == NULL)
                            cmpd_items[attr_num] = gsi_make_items(max_rows) ;
                        gsi_set_str(cmpd_items[attr_num][row], (gsi_char*)strval[row]) ;
                    }
                    if (attr_type == GSI_SYMBOL_LIST_TAG || attr_type == GSI_SYMBOL_ARRAY_TAG)
                    {
                        symval[row] = gsi_make_symbol((gsi_char*)strval[row]) ;
                    }
                }
                if (is_list_type(attr_type)) 
                {
                    if (attr_type == GSI_SYMBOL_LIST_TAG)
                        gsi_set_sym_list(theAttrs[attr_num], symval, max_rows) ;
                    else
                        gsi_set_str_list(theAttrs[attr_num], (gsi_char**)strval, max_rows) ;
                }
                else if (is_array_type(attr_type)) 
                {
                    if (attr_type == GSI_SYMBOL_ARRAY_TAG)
                        gsi_set_sym_array(theAttrs[attr_num], symval, max_rows) ;
                    else
                        gsi_set_str_array(theAttrs[attr_num], (gsi_char**)strval, max_rows) ;
                }
                else if (attr_type == GSI_SEQUENCE_TAG)
                    gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, GSI_SEQUENCE_TAG) ;
                else if (type_of_item(attribs[n], GDB_CATEGORY) == GDB_SIMPLE_TYPE || type_of_item(attribs[n], GDB_CATEGORY) == GDB_PARAM_OR_VAR_TYPE) 
                {
                    if (attr_type == GSI_STRING_TAG || attr_type == GSI_NULL_TAG)
                        gsi_set_str(theAttrs[attr_num], (gsi_char*)strval[max_rows-1]) ;
                    else
                        gsi_set_sym(theAttrs[attr_num], gsi_make_symbol((gsi_char*)strval[max_rows-1])) ;
                }
                else 
                {
                    iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                    status = 1 ;
                    break ;
                }
                attr_num++ ;
                break ;
            
            case GDB_BYTE_TYPE:       
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:
                {
                    int_ovfl = FALSE ;
                    for (row=0;row<max_rows;row++)
                    {
                        if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_LONG_TYPE)
                            longval[row] = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                        else if (selectColumnType == GDB_BYTE_TYPE)
                            longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_byte ;
                        else if (selectColumnType == GDB_SHORT_TYPE)
                            longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_short ;
                        else
                            longval[row] = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_int ;
                        if (longval[row] > MAX_G2_INTEGER || longval[row] < MIN_G2_INTEGER)
                            int_ovfl = TRUE ;
                    }
                
                
                    /* If the receiving attribute is a sequence or an array or list of values,    */
                    /* quantities, or item-or-values we must make sure an array of gsi_items      */
                    /* has been allocated.                                                        */
                    /* -------------------------------------------------------------------------- */
                    use_items = attr_type == GSI_SEQUENCE_TAG || 
                        attr_type == GSI_VALUE_LIST_TAG ||    attr_type == GSI_VALUE_ARRAY_TAG || 
                        attr_type == GSI_QUANTITY_LIST_TAG || attr_type == GSI_QUANTITY_ARRAY_TAG ||
                        attr_type == GSI_ITEM_OR_VALUE_LIST_TAG || attr_type == GSI_ITEM_OR_VALUE_ARRAY_TAG ;
                    if (use_items)
                    {
                        if (cmpd_items[attr_num] == (gsi_item *)NULL)
                        {
                            cmpd_items[attr_num] = gsi_make_items(max_rows) ;
                            if (cmpd_items[attr_num] == NULL)
                            {
                                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                return_rpc_status(NULL, 0, NULL, call_index) ;
                                goto jumpOut_of_update_obj ;
                            }
                        }
                    }

                
                    /* We will return all the values as floats if the receiving   */
                    /* attribute is of a float type or if there was integer       */
                    /* overflow and (smart fetch is off or receiving attribute    */
                    /* is a simple quantity/value/item-or-value)                  */
                    /* ---------------------------------------------------------  */
                    if ((int_ovfl && (!smart_fetch || attr_type == GSI_QUANTITY_TAG)) || 
                         attr_type == GSI_FLOAT64_TAG ||
                             attr_type == GSI_FLOAT64_LIST_TAG || attr_type == GSI_FLOAT64_ARRAY_TAG)
                    {
                        if (dblval == (double *)NULL)
                        {
                            if ((dblval = (double *)XCALLOC(max_rows+1, sizeof(double))) == (double *)NULL)
                            {
                                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                                return_rpc_status(NULL, 0, NULL, call_index) ;
                                gsi_clear_item(user_object) ;
                                goto jumpOut_of_update_obj ;
                            }
                        }

                        for (row=0;row<max_rows;row++)
                        {
                            dblval[row] = (GDB_DBL)longval[row] ;
                            GFLOAT_TO_IEEE(dblval[row], &dblval[row], TRUE) ;
                        }
                
                        if (attr_type==GSI_FLOAT64_LIST_TAG)
                            gsi_set_flt_list(theAttrs[attr_num], dblval, max_rows) ;
                        else if (attr_type==GSI_FLOAT64_ARRAY_TAG)
                            gsi_set_flt_array(theAttrs[attr_num], dblval, max_rows) ;
                        else if (use_items)
                        {
                            for (row = 0 ; row < max_rows ; row++)
                                gsi_set_flt(cmpd_items[attr_num][row], dblval[row]) ;
                            gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, attr_type) ;
                        }
                        else if (attr_type == GSI_FLOAT64_TAG || attr_type == GSI_QUANTITY_TAG)
                            gsi_set_flt(theAttrs[attr_num], dblval[max_rows-1]) ;
                        else if (attr_type == GSI_INTEGER_TAG || attr_type == GSI_INTEGER_LIST_TAG ||
                                 attr_type == GSI_INTEGER_ARRAY_TAG )
                        {
                            intOvflErr = TRUE ;
                            status = 1 ;
                        }
                        else
                        {
                            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                            status = 1 ;
                            break ;
                        }                   
                    }

                    /* We will return all the items as integers if the receiving  */
                    /* type is an integer type                                    */
                    /* ---------------------------------------------------------- */
                    else if (attr_type == GSI_INTEGER_TAG || attr_type == GSI_INTEGER_LIST_TAG || 
                            attr_type == GSI_INTEGER_ARRAY_TAG || attr_type == GSI_QUANTITY_TAG )
                    {
                        if (int_ovfl)
                        {
                            /* Smart fetch is known to be enabled */
                            intOvflErr = TRUE ;  /* Request integer overflow error message */
                            for (row = 0 ; row < max_rows ; row++)
                            {
                                lngX = longval[row] ;
                                if (lngX > MAX_G2_INTEGER)
                                    longval[row] = MAX_G2_INTEGER ;
                                else if (lngX < MIN_G2_INTEGER)
                                    longval[row] = MIN_G2_INTEGER ;
                            }
                        }
                        if (attr_type==GSI_INTEGER_LIST_TAG)
                            gsi_set_int_list(theAttrs[attr_num], longval, max_rows) ;
                        else if (attr_type==GSI_INTEGER_ARRAY_TAG)
                            gsi_set_int_array(theAttrs[attr_num], longval, max_rows) ;
                        else
                            gsi_set_int(theAttrs[attr_num], longval[max_rows-1]) ;

                    }


                    /* Since we have already processed the non-smart fetch        */
                    /* case, it is OK to return overflow values as floats to      */
                    /* lists or arrays of values, quantities, or item-or-values.  */
                    /* ---------------------------------------------------------- */
                    else if (use_items)
                    {
                        for (row = 0 ; row < max_rows ; row++)
                        {
                            lngX = longval[row] ;
                            if (lngX > MAX_G2_INTEGER || lngX < MIN_G2_INTEGER)
                                gsi_set_flt(cmpd_items[attr_num][row], (double)lngX) ;
                            else
                                gsi_set_int(cmpd_items[attr_num][row], lngX) ;
                        }
                        gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, attr_type) ;
                    }

                    /*               Incompatible receiving attribute             */
                    /* ---------------------------------------------------------- */
                    else
                    {
                        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                        status = 1 ;
                    }                   
                
                    attr_num++ ;
                    break ;
                }
            
            
            case GDB_FLOAT_TYPE:
            case GDB_DBL_TYPE:
            
                use_items = (attr_type == GSI_SEQUENCE_TAG || (smart_fetch &&
                    (attr_type == GSI_VALUE_LIST_TAG ||    attr_type == GSI_VALUE_ARRAY_TAG || 
                     attr_type == GSI_QUANTITY_LIST_TAG || attr_type == GSI_QUANTITY_ARRAY_TAG ||
                     attr_type == GSI_ITEM_OR_VALUE_LIST_TAG || attr_type == GSI_ITEM_OR_VALUE_ARRAY_TAG))) ;
            
                /* Note that smart fetch is not intended to return true floating point value */
                /* (as opposed to DECIMAL(x, 0) values) to integer-type attributes.           */
                use_ints = genda_ptr->decimal_flags[col] && 
                    (attr_type == GSI_INTEGER_LIST_TAG || attr_type == GSI_INTEGER_ARRAY_TAG ||
                    attr_type == GSI_INTEGER_TAG) ;
            
            
                /* If the receiving attribute is a sequence or an array or list of values     */
                /* or quantities, we must make sure an array of gsi_items has been allocated. */
                /* -------------------------------------------------------------------------- */
                if (use_items)
                {
                    if (cmpd_items[attr_num] == (gsi_item *)NULL)
                    {
                        cmpd_items[attr_num] = gsi_make_items(max_rows) ;
                        if (cmpd_items[attr_num] == NULL)
                        {
                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                            update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                            goto jumpOut_of_update_obj ;
                        }
                    }
                }
            
                /* If the receiving attribute is some type of integer, we must make sure that */
                /* an array of longs (gsi_ints) has been allocated.                           */
                /* -------------------------------------------------------------------------- */
                if (use_ints)
                {
                    if (longval == (long *)NULL)
                        if ((longval = (long *)XCALLOC(max_rows+1, sizeof(long))) == (long *)NULL)
                        {
                            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                            update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
                            goto jumpOut_of_update_obj ;
                        }
                }
            
                for (row=0;row<max_rows;row++)
                {
                    if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_DBL_TYPE)
                        dblX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_dbl ;
                    else 
                        dblX = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_float ;
                    GFLOAT_TO_IEEE(dblX, &dblX, TRUE) ;
                    if (use_items)
                    {
                        if (!smart_fetch || !genda_ptr->decimal_flags[row] || dblX < MIN_G2_INTEGER - 0.1 ||
                                dblX > MAX_G2_INTEGER + 0.1)
                            gsi_set_flt(cmpd_items[attr_num][row], dblX) ;
                        else
                            gsi_set_int(cmpd_items[attr_num][row], (long)dblX) ;
                    }
                    else if (use_ints)
                    {
                        stopError = FALSE ;
                        if (dblX > (double)MAX_G2_INTEGER + 0.1)
                        {
                            longval[row] = MAX_G2_INTEGER ;
                            intOvflErr = TRUE ;
                            stopError = !smart_fetch ;
                        }
                        else if (dblX < (double)(MIN_G2_INTEGER - 0.1))
                        {
                            longval[row] = MIN_G2_INTEGER ;
                            intOvflErr = TRUE ;
                            stopError = !smart_fetch ;
                        }
                        else
                            longval[row] = (long)dblX ;
                        if (stopError)
                        {
                            status = 1 ;
                            break ;
                        }
                    }
                    else
                        dblval[row] = dblX ;
                
                }
                if (status)
                    break ;
            
                /* Cast the return values to the correct type which depends upon whether or     */
                /* not smart fetch is set, whether or not this column is a DECIMAL(x, 0) column, */
                /* and the type of attribute that will receive the values.                      */
                /* ---------------------------------------------------------------------------- */
                if (use_items)
                    gsi_set_elements(theAttrs[attr_num], cmpd_items[attr_num], max_rows, attr_type) ;
                else if (use_ints)
                {
                    if (attr_type == GSI_INTEGER_LIST_TAG)
                        gsi_set_int_list(theAttrs[attr_num], longval, max_rows) ;
                    else if (attr_type == GSI_INTEGER_ARRAY_TAG)
                        gsi_set_int_array(theAttrs[attr_num], longval, max_rows) ;
                    else
                        gsi_set_int(theAttrs[attr_num], longval[max_rows-1]) ;
                }
                else if (attr_type == GSI_QUANTITY_TAG && genda_ptr->decimal_flags[col] &&
                    dblval[max_rows-1] < (double)MAX_G2_INTEGER + 0.1 && 
                    dblval[max_rows-1] > (double)MIN_G2_INTEGER - 0.1)
                    gsi_set_int(theAttrs[attr_num], (long)dblval[max_rows-1]) ;
                else if (is_list_type(attr_type))
                    gsi_set_flt_list(theAttrs[attr_num], dblval, max_rows) ;
                else if (is_array_type(attr_type))
                    gsi_set_flt_array(theAttrs[attr_num], dblval, max_rows) ;
                else if (type_of_item(attribs[n], GDB_CATEGORY) == GDB_SIMPLE_TYPE || type_of_item(attribs[n], GDB_CATEGORY) == GDB_PARAM_OR_VAR_TYPE)
                    gsi_set_flt(theAttrs[attr_num], dblval[max_rows-1]) ;
                else 
                {
                    iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d%s%s", EUNSPDT, gsi_type_to_string(attribs[n]), genda_ptr->da_col_ptr[col].col_name) ;
                    status = 1 ;
                    break ;
                }
                attr_num++ ;
                break ;
                
             default:
                 iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s%s", EINVDTY, "na", "na") ;
                 if (debug & DBG6) printf("\n") ;
                 status = 1 ;
                 break ;
             
        } /* end switch */        
    } /* end for col */
    
    if (!status)
        genda_ptr->genda_pos += max_rows ;
    
    if (intOvflErr)
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINTOVF) ;
    if (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed && !status)
    {
        if (!intOvflErr)
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, NULL, FALSE, "%d", IEOFETC) ;
        cursor_pos = genda_ptr->genStat.rows_processed ;
    }
    else
    {
        if (!status) 
            iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WNOTEOC) ;
        cursor_pos = (((genda_ptr->genStat.rows_processed - 1)/ genda_ptr->nrows) * genda_ptr->nrows) + genda_ptr->genda_pos ;
    }
    
    /* move updated attrs into the return object */
    if (!status)
        gsi_set_attrs(user_object, theAttrs, attr_num) ;
    
    /* return the user-object */
    gsi_return_values(gdb_registered_item_array, 1, context_num) ;
    
    /* update the cursor object status */
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], co_handle) ;
    theAttrs = gdb_attr_item_array ;
    update_object_status(theAttrs, NULL, UPDATE_ATTRS, 0) ;
    gsi_set_int(theAttrs[CURSOR_POS], cursor_pos) ;
    gsi_return_attrs(object[0], theAttrs, NUM_STATUS_ARGS, context_num) ;
    
    /* return the status info to G2 RPC */
    status_args = gdb_status_items ;
    update_object_status(status_args, NULL, UPDATE_ITEMS, 0) ;
    gsi_set_int(status_args[NROWS_POS], status ? 0 : max_rows) ;
    gsi_set_int(status_args[CURSOR_POS], cursor_pos) ;
    return_rpc_status(status_args, NUM_STATUS_ARGS, NULL, call_index) ;
    gsi_clear_item(user_object) ;
    
    /* reset the global structures */
jumpOut_of_update_obj:

    for (n=0;n<attr_num;n++) 
    {
        gsi_clear_item(theAttrs[n]) ;
        /* reset the append flag */
        if (update_action == OBJECT_APPEND)
            gsi_set_item_append_flag(gsi_item_of_attr(theAttrs[n]), 0) ;
    }
    gsi_clear_item(user_object) ;
    /* note: redundant clear follows in case of EINVDTY @ 1st or last attr */ 
    gsi_clear_item(theAttrs[0]) ;
    gsi_clear_item(theAttrs[attr_num+1]) ;
    /* reset the append flag */
    if (update_action == OBJECT_APPEND) 
    {
        gsi_set_item_append_flag(gsi_item_of_attr(theAttrs[0]), 0) ;
        gsi_set_item_append_flag(gsi_item_of_attr(theAttrs[attr_num+1]), 0) ;
    }
      
    /* release the temp buffers */
    if (qvFlags != NULL)
        XFREE(qvFlags) ;
    if (dblval != NULL)
        XFREE(dblval) ;
    if (longval != NULL)
        XFREE(longval) ;
    if (strval != NULL)
        XFREE(strval) ;
    if (symval != NULL)
        XFREE(symval) ;
    if (cmpd_items != (gsi_item **)NULL) 
    {
        for (n=0;n<nattrs;n++) 
        {
            if (cmpd_items[n] != (gsi_item *)NULL)
                gsi_reclaim_items(cmpd_items[n]) ;
        }
        XFREE (cmpd_items) ;
    }
    
    /* release fetched data */
    if ( !status && (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed) || 
        genda_ptr->genda_pos == genda_ptr->nrows)
    {
        genda_ptr->genda_pos = 0;     /* added for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
    }

    /* If the attempt to process the first retrieved records failed, remember */
    /* that the genda has already been loaded with the first records.         */
    /* ---------------------------------------------------------------------- */
    if (status && genda_ptr->genda_pos == 0)
        genda_ptr->genda_pos = -1 ;
    
    return ;
} /* end fetch_object_update_rp */


/*===========================================================================*
    fetch_object_list_rp                                              GDB-RPC
      - input: [0]=cursor-object
               [1]=user-object
               [2]=fetch-batch
               [3]=sequence of attribute names
               [4]=sequence of QUANTITY/VALUE flags
*===========================================================================*/
static void fetch_object_list_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    double                  dblX ;
    double                  float_val ;
    GENDA*                  genda_ptr ;
    gsi_attr*               attribs ;
    gsi_attr*               theAttrs ;
    gsi_int                 attr_type ;
    gsi_int                 nattrs ;
    gsi_int                 obj_handle ;
    gsi_item*               ret_list ;
    gsi_item*               user_object ;
    gsi_registered_item*    object ;
    gsi_symbol              class_name ;
    register int            col, row, n, m ;
    long                    attr_num ;
    long                    cursor_pos ;
    long                    fetch_batch ;
    long                    found ;
    long                    max_rows ;
    long                    lngX ;
    long                    rcd = 0;    /* local record (row) counter - for batch-fetch */
    long                    selectColumnType ;
    long                    smart_fetch ;
    long                    status ;
    short                   incompat_attr = FALSE ;
    short                   intOvfl, intOvflErr = FALSE ;
    short*                  qvFlags ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("FETCH_OBJECT_LIST_RP: %"), context_num) ;
    
    /* Allocate the item-list and status values - Do it here in case error causes
       premature return from this function. Need to send status info back */
    ret_list = gdb_item_array ;
    gsi_set_class_name(ret_list[0], gsi_make_symbol((gsi_char*)_T("ITEM-LIST"))) ;
    gsi_set_type(ret_list[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        return ;
    }

    smart_fetch = context[context_num].smart_fetch ;
    
    if (count < 5 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        return ;
    }
    
#ifdef _DEBUG
    wprintf(_T("\ncount = %d\n"), count) ;
    wprintf(_T("-------------------------------------------------------\n")) ;
    wprintf(_T(" Cursor-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0]) ) ;
    wprintf(_T("    Handle:      %d\n"), gsi_handle_of(arg[0]) ) ;
    get_attrib_info(arg[0]) ;
    
    wprintf(_T("\n-------------------------------------------------------\n")) ;
    wprintf(_T(" User-Object Information\n")) ;
    wprintf(_T("-------------------------------------------------------\n\n")) ;
    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[1]), gsi_type_to_string(arg[1]) ) ;
    wprintf(_T("    Class Name:  %s\n"), gsi_symbol_name(gsi_class_name_of(arg[1]))) ;
    if (gsi_name_of(arg[1]) == NULL)
        wprintf(_T("    Object Name: (null)\n" )) ;
    else
        wprintf(_T("    Object Name: %s\n"), gsi_symbol_name(gsi_name_of(arg[1]))) ;
    get_attrib_info(arg[1]) ;
    wprintf(_T("==================\n")) ;
    get_qv_info(arg[3], arg[4]) ;
#endif
    
    /* arg-0 is the cursor-object handle */
    obj_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (obj_handle < MIN_ITEM_HANDLE) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        return ;
    }
    
    genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
    if (genda_ptr == (GENDA *)NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVITM, CURSOR_OBJECT_NAME) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        return ;
    }
    
    if (genda_ptr->genStat.rows_processed != 0 && genda_ptr->genda_pos == 0 &&
        genda_ptr->more_rows != genda_ptr->nrows )
    {
    /* If positioned at EOCURSOR simply return EOCURSOR message until user
       either performs SET_QUERY or REFRESH_CURSOR: This check is provided
       because Oracle will automatically refresh the cursor. Performing a
       'ping' here so EOCURSOR message is not returned while disconnected.
       This will also cause the G2 IO db-connection-status to be set to 
       disconnected via KB logic */   
        
        if (!process_ping_db())    
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        else 
        {
        /* this will prevent EOCURSOR message from being returned
            following a reconnect */
            genda_ptr->genStat.rows_processed = 0 ;
        }
        genda_ptr->more_rows = 0; /* make sure its 0 */ 
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        return ;
    }
    
    /* arg-2 is fetch_batch size */
    fetch_batch = gsi_int_of(arg[2]) ;
    
    /* Initially, Allocate then Update (populate) the GENDA with db data */
    if (genda_ptr->genda_pos == 0)
    {    /* add for fetch-batch */
        status = alloc_genda(genda_ptr, ALLOC_ALL) ;
        if (!status)
            status = update_genda(genda_ptr) ;
        if (status) 
        {
            update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
            return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
            gsi_clear_item(ret_list[0]) ;
            genda_ptr->genda_pos = 0;     /* add for fetch-batch */
            free_genda(DATA_ONLY, genda_ptr) ;
            return ;
        }
    }
    if (genda_ptr->genda_pos == -1)     /* First rows have already been loaded */
        genda_ptr->genda_pos = 0 ;

    rcd = genda_ptr->genda_pos ;
    
    /******************
    * START FETCHING
    ******************/
    
    max_rows = genda_ptr->more_rows ;
    if (fetch_batch > 0 && genda_ptr->more_rows > 0) 
    { /* && fetch_batch <= genda_ptr->more_rows) -- don't set max_rows > rows fetched */
        if (fetch_batch + rcd < genda_ptr->more_rows)
            max_rows = fetch_batch ;
        else
            max_rows = genda_ptr->more_rows - genda_ptr->genda_pos ;
    }
    if (max_rows > context[context_num].genda_rows)
        max_rows = context[context_num].genda_rows ;
    
    /* arg-1 is the user object: Build n user-object(s) */
    user_object = gdb_object_array ;
    
    attribs = gsi_attrs_of(arg[1]) ;
    nattrs = gsi_attr_count_of(arg[1]) ;
    qvFlags = build_qv_list(attribs, nattrs, arg[3], arg[4]) ;
    if (nattrs && qvFlags == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        return ;
    }
    
    /* If previous fetch returned all rows but the EOCURSOR marker, then this update will
       only get the EOCURSOR status. Therefore, more_rows will be 0. This should only happen
       when update occurs exactly on a genda->rows boundry */
    if (max_rows <= 0) 
    {
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        gsi_set_int(ret_list[1+CURSOR_POS], genda_ptr->genStat.rows_processed) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        genda_ptr->genda_pos = 0;     /* add for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
        return ;
    }
    
    /* if # of query columns exceeds the preallocated -MAXCOLS (max_col_array_size)
       then must reject */
    if (genda_ptr->ncols > max_col_array_size) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d%d", ENCOLEX, genda_ptr->ncols, max_col_array_size) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_list[0]) ;
        process_refresh_cursor(genda_ptr) ;
        genda_ptr->genda_pos = 0;     /* add for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
        return ;
    }
    
    class_name = gsi_class_name_of(arg[1]) ;
    for (n=0;n<max_rows;n++) 
    {
        gsi_set_class_name(user_object[n], class_name) ;
        gsi_set_type(user_object[n], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    }
    
    attr_num = 0 ;
    for (col=0; col < genda_ptr->ncols; col++)
    {
        /* try to match GENDA db columns with user-object attributes */
        found = FALSE ;
        for (n=0;n<nattrs;n++) 
        {
            if (!wcscmp(gsi_symbol_name(gsi_attr_name_of(attribs[n])), genda_ptr->da_col_ptr[col].col_name)) 
            {
                for (m=0;m<max_rows;m++) 
                {
                    gsi_set_attr_name(list_attrs[m][attr_num], gsi_attr_name_of(attribs[n])) ;
                    attr_type = qvFlags[n] ? GSI_QUANTITY_TAG : gsi_type_of(attribs[n]) ;
                    if (type_of_item(attribs[n], GDB_CATEGORY) != GDB_SIMPLE_TYPE) 
                    {
                        /* object's attributes must be simple values */
                        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s%s", EBADDTP, gsi_type_to_string(attribs[n]), gsi_symbol_name(gsi_attr_name_of(attribs[n]))) ;
                        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
                        return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
                        gsi_clear_item(ret_list[0]) ;
                        for (n=0;n<max_rows;n++)
                            gsi_clear_item(user_object[n]) ;
                        process_refresh_cursor(genda_ptr) ;
                        genda_ptr->genda_pos = 0;     /* add for fetch-batch */
                        free_genda(DATA_ONLY, genda_ptr) ;
                        return ;
                    }
                }
                found = TRUE ;
                break ;
            }
        }
        if (!found)
            continue ;
        
        /* Set the data value based on type */
        selectColumnType = genda_ptr->da_col_ptr[col].data_type ;
        switch(selectColumnType)
        {
            case GDB_STRING_TYPE:   for (row=0;row<max_rows;row++) 
                                    {
                                        if (attr_type == GSI_SYMBOL_TAG)
                                            gsi_set_sym(list_attrs[row][attr_num], gsi_make_symbol((gsi_char*)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_str)) ;
                                        else
                                            gsi_set_str(list_attrs[row][attr_num], (gsi_char*)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_str) ;
                                    }
                                    attr_num++ ;
                                    break ;
            
            case GDB_BYTE_TYPE:
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:     
                                    for (row=0;row<max_rows;row++) 
                                    {
                                        if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_LONG_TYPE)
                                            lngX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                                        else if (selectColumnType == GDB_BYTE_TYPE)
                                            lngX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_byte ;
                                        else if (selectColumnType == GDB_SHORT_TYPE)
                                            lngX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_short ;
                                        else
                                            lngX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_int ;
                                        if (lngX > MAX_G2_INTEGER || lngX < MIN_G2_INTEGER )
                                        {
                                            if (smart_fetch && attr_type == GSI_INTEGER_TAG)
                                            {
                                                intOvflErr = TRUE ;
                                                if (lngX < MIN_G2_INTEGER)
                                                    gsi_set_int(list_attrs[row][attr_num], MIN_G2_INTEGER) ;
                                                else
                                                    gsi_set_int(list_attrs[row][attr_num], MAX_G2_INTEGER) ;
                                            }
                                            else
                                            {
                                                /* convert int to float for 29 bit G2 limit */
                                                float_val = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                                                GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;
                                                gsi_set_flt(list_attrs[row][attr_num], float_val) ;
                                            }
                                        }
                                        else
                                            gsi_set_int(list_attrs[row][attr_num], lngX) ;
                                    }
                                    attr_num++ ;
                                    break ;
                      
            case GDB_FLOAT_TYPE:
            case GDB_DBL_TYPE:
                                    for (row=0;row<max_rows;row++) 
                                    {
                                        /* Get the value */
                                        /* ------------- */
                                        if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_DBL_TYPE) 
                                            dblX = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_dbl ;
                                        else 
                                            dblX = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_float ;
                                        GFLOAT_TO_IEEE(float_val, &float_val, TRUE) ;

                                        /* Figure out how to return the value */
                                        /* ---------------------------------- */
                                        intOvfl = (dblX < (double)(MIN_G2_INTEGER - 0.1) || 
                                                   dblX > (double)(MAX_G2_INTEGER + 0.1) ) ;

                                        if ( attr_type == GSI_NULL_TAG || attr_type == GSI_FLOAT64_TAG || 
                                                (attr_type == GSI_QUANTITY_TAG && (!smart_fetch || intOvfl)))
                                        {
                                            gsi_set_flt(list_attrs[row][attr_num], dblX) ;
                                            continue ;  /* don't execute overflow code at end of this for loop */
                                        }

                                        /* At this point, attribute type must be integer or quantity/value */
                                        else if (attr_type != GSI_INTEGER_TAG && attr_type != GSI_QUANTITY_TAG)
                                            incompat_attr = TRUE ;

                                        /* Don't require smart fetch for DECIMAL(x, 0) */
                                        /* as long as there is no overflow */
                                        else if (!smart_fetch)
                                        {
                                            if (attr_type == GSI_INTEGER_TAG && 
                                                        genda_ptr->decimal_flags[col] && !intOvfl)
                                                gsi_set_int(list_attrs[row][attr_num], (long)dblX) ;
                                        }

                                        /* smart fetch for a DECIMAL(x, 0) */
                                        else if (genda_ptr->decimal_flags[col])
                                        {
                                            if (!intOvfl)
                                                gsi_set_int(list_attrs[row][attr_num], (long)dblX) ;
                                        }

                                        /* Storage of true float in integer attribute not allowed */
                                        else
                                            incompat_attr = TRUE ;
                                        if (incompat_attr)
                                        {
                                            /* Attribute type incompatible with retrieved value */
                                            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EBADATY, gsi_symbol_name(gsi_attr_name_of(attribs[n]))) ;
                                            update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
                                            return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
                                            gsi_clear_item(ret_list[0]) ;
                                            for (n=0;n<max_rows;n++)
                                                gsi_clear_item(user_object[n]) ;
                                            process_refresh_cursor(genda_ptr) ;
                                            genda_ptr->genda_pos = 0;     /* add for fetch-batch */
                                            free_genda(DATA_ONLY, genda_ptr) ;
                                            return ;
                                        }
                                        if (intOvfl)
                                        {
                                            intOvflErr = TRUE ;
                                            if (dblX < (double)(MIN_G2_INTEGER - 0.1))
                                                gsi_set_int(list_attrs[row][attr_num], MIN_G2_INTEGER) ;
                                            else
                                                gsi_set_int(list_attrs[row][attr_num], MAX_G2_INTEGER) ;
                                        }
                                    }
                                    attr_num++ ;
                                    break ;
                       
            default:
	      iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s%s", EINVDTY, "na", "na") ;
	      if (debug & DBG6) printf("\n") ;
	      break ;
            
        } /* end switch */
    } /* end for col */
  
    genda_ptr->genda_pos += max_rows ;
    
    /* if (genda_ptr->genStat.status == EOCURSOR && (genda_ptr->genda_pos == genda_ptr->genStat.rows_processed ||
    genda_ptr->genda_pos == 0)) { */
    
    if (intOvflErr)
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, FALSE, "%d", EINTOVF) ;
    if (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed)
    {
        if (!intOvflErr)
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, NULL, FALSE, "%d", IEOFETC) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        cursor_pos = genda_ptr->genStat.rows_processed ;
    }
    else 
    {
        if (!intOvflErr)
            iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WNOTEOC) ;
        update_object_status(ret_list, NULL, UPDATE_ITEMS, 1) ;
        cursor_pos = (((genda_ptr->genStat.rows_processed - 1)/ genda_ptr->nrows) * genda_ptr->nrows) + genda_ptr->genda_pos ;
    }
    
    /* load the attribute values into each object */
    for (n=0;n<max_rows;n++)
        gsi_set_attrs(user_object[n], list_attrs[n], attr_num) ;
    
    /* update the cursor object status */
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], gsi_handle_of( arg[0] )) ;
    
    theAttrs = gdb_attr_item_array ;
    update_object_status(theAttrs, NULL, UPDATE_ATTRS, 0) ;
    gsi_set_int(theAttrs[CURSOR_POS], cursor_pos) ;
    gsi_return_attrs(object[0], theAttrs, NUM_STATUS_ARGS, context_num) ;
    
    /* create the item-list and items for status values */
    gsi_set_elements (ret_list[0], user_object, max_rows, GSI_ITEM_LIST_TAG) ;
    gsi_set_int(ret_list[1+NROWS_POS], max_rows) ;
    gsi_set_int(ret_list[1+CURSOR_POS], cursor_pos) ;
    /* return the item_list and status values to G2 */
    return_rpc_status(ret_list, 1+NUM_STATUS_ARGS, NULL, call_index) ;
    
    for (n=0;n<max_rows;n++)
        gsi_clear_item(user_object[n]) ;
    gsi_clear_item(ret_list[0]) ;
    if (qvFlags != NULL)
        XFREE(qvFlags) ;
    
    /* release fetched data */
    if ( (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed) || 
        genda_ptr->genda_pos == genda_ptr->nrows)
    {
        genda_ptr->genda_pos = 0;     /* add for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
    }
    return ;
} /* end fetch_object_list_rp */


/*===========================================================================*
    fetch_structure_rp                                        (111)   GDB-RPC
      - Execute a query and return results in a G2 structure. Column
        data is contained in name/sequence pairs.
      - input: [0]=cursor-object
               [1]=fetch-batch
 *===========================================================================*/ 
static void fetch_structure_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    double                  dblval ;
    GENDA*                  genda_ptr ;
    gsi_attr*               theAttrs ;
    gsi_attr*               theAttrs2 ;
    gsi_int                 obj_handle ;
    gsi_item**              seq_items ;
    gsi_item*               user_object ;
    gsi_registered_item*    object ;
    register int            col, row ;
    register int            n ;
    long                    attr_num ;
    long                    cursor_pos = 0 ;
    long                    fetch_batch ;
    long                    float_flag = FALSE ;
    long                    longval ;
    long                    max_rows ;
    long                    rcd = 0;              /* local record (row) counter - for batch-fetch */
    long                    selectColumnType ;
    long                    smart_fetch ;
    long                    status ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("FETCH_STRUCTURE_RP: %"), context_num);
    }

    /* Create a structure. Do it here in case error causes premature return from this 
       function - need to send status info back. */
    
    user_object = gdb_object_array ;
    gsi_set_type(user_object[0], GSI_STRUCTURE_TAG) ;
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    smart_fetch = context[context_num].smart_fetch ;
    
    if (count < 2 || gsi_type_of(arg[0]) != GSI_HANDLE_TAG) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
#ifdef _DEBUG
    printf("\ncount = %d\n", count) ;
    printf("-------------------------------------------------------\n") ;
    printf(" Cursor-Object Information\n") ;
    printf("-------------------------------------------------------\n\n") ;

    wprintf(_T("    Object Type: %d (%s)\n"), gsi_type_of(arg[0]), gsi_type_to_string(arg[0]));

    printf("    Handle:      %d\n", gsi_handle_of(arg[0]) ) ;
    get_attrib_info(arg[0]) ;
#endif
    
    /* arg-0 is the cursor-object handle */
    obj_handle = gsi_handle_of(arg[0]) ;
    
    /* Check for ok handle, and object */
    if (obj_handle < MIN_ITEM_HANDLE) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    genda_ptr = storage_area(GET, context_num, obj_handle, NULL) ;
    if (genda_ptr == (GENDA *)NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVITM, CURSOR_OBJECT_NAME) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    if (genda_ptr->genStat.rows_processed != 0 && genda_ptr->genda_pos == 0 &&
        genda_ptr->more_rows != genda_ptr->nrows )
    {

        /* If positioned at EOCURSOR simply return EOCURSOR message until user
           either performs SET_QUERY or REFRESH_CURSOR: This check is provided
           because Oracle will automatically refresh the cursor. Performing a
           'ping' here so EOCURSOR message is not returned while disconnected.
           This will also cause the G2 IO db-connection-status to be set to 
           disconnected via KB logic */    
        if (!process_ping_db())    
            iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        else 
        {
            /* this will prevent EOCURSOR message from being returned
               following a reconnect */
            genda_ptr->genStat.rows_processed = 0 ;
        }
        
        genda_ptr->more_rows = 0; /* make sure its 0 */  
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        return ;
    }
    
    /* Initially, Allocate then Update (populate) the GENDA with db data */
    if (genda_ptr->genda_pos == 0) 
    {   /* add for fetch-batch */
        status = alloc_genda(genda_ptr, ALLOC_ALL) ;
        if (!status)
            status = update_genda(genda_ptr) ;
        if (status) 
        {
            update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
            return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
            gsi_clear_item(user_object[0]) ;
            free_genda(DATA_ONLY, genda_ptr) ;
            return ;
        }
    }
    if (genda_ptr->genda_pos == -1)     /* First rows have already been loaded */
        genda_ptr->genda_pos = 0 ;
    
    theAttrs = gdb_attr_item_array ;
    
    /* arg-2 is fetch_batch size */
    fetch_batch = gsi_int_of(arg[1]) ;
    rcd = genda_ptr->genda_pos ;
    

    /******************
    * START FETCHING
    ******************/
    
    max_rows = genda_ptr->more_rows ;
    if (fetch_batch > 0 && genda_ptr->more_rows > 0) 
    {   /* && fetch_batch <= genda_ptr->more_rows) -- don't set max_rows > rows fetched */
        if (fetch_batch + rcd < genda_ptr->more_rows)
            max_rows = fetch_batch ;
        else
            max_rows = genda_ptr->more_rows - genda_ptr->genda_pos ;
    }
    if (max_rows > context[context_num].genda_rows)
        max_rows = context[context_num].genda_rows ;
    
     /* If previous fetch returned all rows but the EOCURSOR marker, then this update will
        only get the EOCURSOR status. Therefore, more_rows will be 0. This should only happen
        when update occurs exactly on a genda->rows boundary */
    if (max_rows <= 0) 
    {
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", IEOFETC) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        genda_ptr->genda_pos = 0 ;
        free_genda(DATA_ONLY, genda_ptr) ;
        return ;
    }
    
    /* Allocate an array of gsi_item ptrs to hold the DB columns. This array contains
       ptrs to a gsi_items = sequences */
    theAttrs = gdb_attr_item_array ;
    if ((seq_items = (gsi_item **)XCALLOC(genda_ptr->ncols, sizeof(gsi_item *))) == NULL) 
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(user_object[0]) ;
        genda_ptr->genda_pos = 0 ;
        free_genda(DATA_ONLY, genda_ptr) ;
        return ;
    }
    for (col=0; col < genda_ptr->ncols; col++) 
    {
        gsi_set_type(theAttrs[col], GSI_STRUCTURE_TAG) ;
        gsi_set_attr_name(theAttrs[col], gsi_make_symbol((gsi_char*)genda_ptr->da_col_ptr[col].col_name)) ;
        seq_items[col] = gsi_make_items(max_rows) ;   /* allocate sequences */
        if (seq_items[col] == NULL) 
        {
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
            update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
            return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
            gsi_clear_item(user_object[0]) ;
            genda_ptr->genda_pos = 0 ;
            free_genda(DATA_ONLY, genda_ptr) ;
            return ;
        }
    }
    
    /* Fetch & load data into sequences */
    
    status = 0 ;
    attr_num = 0 ;
    for (col=0; col < genda_ptr->ncols; col++)
    {
        /* Set the data value based on type */
        selectColumnType = genda_ptr->da_col_ptr[col].data_type ;
        switch(selectColumnType)
        {
            case GDB_STRING_TYPE:   for (row=0;row<max_rows;row++)
                                        gsi_set_str(seq_items[col][row], (gsi_char*)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_str) ;
                                    attr_num++ ;
                                    break ;
            
            case GDB_BYTE_TYPE:       
            case GDB_SHORT_TYPE:
            case GDB_INT_TYPE:
            case GDB_LONG_TYPE:     for (row=0;row<max_rows;row++) 
                                    {
                                        if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0 || selectColumnType == GDB_LONG_TYPE)
                                            longval = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                                        else if (selectColumnType = GDB_BYTE_TYPE)
                                            longval = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_byte ;
                                        else if (selectColumnType = GDB_SHORT_TYPE)
                                            longval = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_short ;
                                        else
                                            longval = (GDB_LONG)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_int ;
                                        if (longval > MAX_G2_INTEGER || longval < MIN_G2_INTEGER)
                                        {
                                            if (smart_fetch)
                                                gsi_set_flt(seq_items[col][row], (double)longval) ;
                                            else
                                            {
                                                float_flag = TRUE ;
                                                break ;
                                            }
                                        }
                                        else
                                            gsi_set_int(seq_items[col][row], longval) ;
                                    }
            
                                    /* If smart fetch is off, this code should continue to behave as it did in the past. */
                                    /* That means all values will be returned as floats if any overflow.                 */
                                    /*                                                                                   */
                                    /* If smart fetch is on, only those values that would cause integer overflow are     */
                                    /* returned as floats.  The others are returned as integers.                         */
                                    /* --------------------------------------------------------------------------------- */
                                    if (float_flag) 
                                    {
                                        for (row=0;row<max_rows;row++) 
                                        {
                                            dblval = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_long ;
                                            if (!smart_fetch || dblval < (double)(MIN_G2_INTEGER - 0.1) ||
                                                dblval > (double)(MAX_G2_INTEGER + 0.1))
                                            {
                                                GFLOAT_TO_IEEE(dblval, &dblval, TRUE) ;
                                                gsi_set_flt(seq_items[col][row], dblval) ;
                                            }
                                        }
                                        /* note: arg4 must be FALSE to prevent infinite loop */
                                        iomsg(DBG4, LAYER, FALSE, FALSE, NULL, FALSE, "%d%s%s%s", WTYPCHG, genda_ptr->da_col_ptr[col].col_name, _T("INTEGER"), _T("FLOAT")) ;

                                        status = 1 ;
                                    }
                                    attr_num++ ;
                                    break ;          
            
            case GDB_FLOAT_TYPE:
            case GDB_DBL_TYPE:
                                    for (row=0;row<max_rows;row++) 
                                    {
                                        if (genda_ptr->da_col_ptr[col].ind[row+rcd] < 0  || selectColumnType == GDB_DBL_TYPE) 
                                        {
                                            dblval = genda_ptr->da_col_ptr[col].val[row+rcd].gdb_dbl ;
                                            GFLOAT_TO_IEEE(dblval, &dblval, TRUE) ;
                                        }
                                        else 
                                        {
                                            dblval = (GDB_DBL)genda_ptr->da_col_ptr[col].val[row+rcd].gdb_float ;
                                            GFLOAT_TO_IEEE(dblval, &dblval, TRUE) ;
                                        }
                                        if (smart_fetch && genda_ptr->decimal_flags[col] && dblval > (double)(MIN_G2_INTEGER - 0.1) &&
                                            dblval < (double)(MAX_G2_INTEGER + 0.1))
                                            gsi_set_int(seq_items[col][row], (long)dblval) ;
                                        else
                                            gsi_set_flt(seq_items[col][row], dblval) ;
                                    }
                                    attr_num++ ;
                                    break ;
            
            default:
	      iomsg(DBG3, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d%s%s", EINVDTY, "na", "na");
	      if (debug & DBG6) printf("\n");
	      status = 1;
	      break;
            
        } /* end switch */
        
        /* load the sequence into the structure */
        gsi_set_elements(theAttrs[col], seq_items[col], max_rows, GSI_SEQUENCE_TAG) ;
        
    } /* end for col */
    
    genda_ptr->genda_pos += max_rows ;
    
    if (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed && !status)
    {
        iomsg(EOCURSOR_CD, LAYER, TRUE, TRUE, NULL, FALSE, "%d", IEOFETC) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        cursor_pos = genda_ptr->genStat.rows_processed ;
    }
    else 
    {
        if (!status)
            iomsg(DBG4, LAYER, TRUE, TRUE, NULL, FALSE, "%d", WNOTEOC) ;
        update_object_status(user_object, NULL, UPDATE_ITEMS, 1) ;
        cursor_pos = (((genda_ptr->genStat.rows_processed - 1)/ genda_ptr->nrows) * genda_ptr->nrows) + genda_ptr->genda_pos ;
    }
    
    /* update the cursor object status */
    object = gdb_registered_item_array ;
    gsi_set_handle(object[0], gsi_handle_of(arg[0])) ;
    
    theAttrs2 = gdb_status_attr_items ;
    update_object_status(theAttrs2, NULL, UPDATE_ATTRS, 0) ;
    gsi_set_int(theAttrs2[CURSOR_POS], cursor_pos) ;
    gsi_return_attrs(object[0], theAttrs2, NUM_STATUS_ARGS, context_num) ;
    
    /* move attrs + status into the return object = structure */
    gsi_set_attrs(user_object[0], theAttrs, attr_num) ;
    
    /* return the object & status info to G2 RPC */
    gsi_set_int(user_object[1+NROWS_POS], max_rows) ;
    gsi_set_int(user_object[1+CURSOR_POS], cursor_pos) ;
    
    return_rpc_status(user_object, 1+NUM_STATUS_ARGS, NULL, call_index) ;
    
    /* reset the global structures */
    for (n=0;n<attr_num/*nattrs*/;n++)
        gsi_clear_item(theAttrs[n]) ;
    gsi_clear_item(user_object[0]) ;
    /* note: redundant clear follows in case of EINVDTY @ 1st or last attr */ 
    gsi_clear_item(theAttrs[0]) ;
    gsi_clear_item(theAttrs[attr_num+1]) ;
    
    if (seq_items != NULL) 
    {
        for (col=0; col < genda_ptr->ncols; col++) 
        {
            if (seq_items[col] != (gsi_item *)NULL)
                gsi_reclaim_items(seq_items[col]) ;
        }
        XFREE (seq_items) ;
    }
    
    /* release fetched data */
    if ( (genda_ptr->genStat.status == EOCURSOR_CD && genda_ptr->genda_num * genda_ptr->nrows + 
        genda_ptr->genda_pos == genda_ptr->genStat.rows_processed) || 
        genda_ptr->genda_pos == genda_ptr->nrows)
    {
        genda_ptr->genda_pos = 0;     /* added for fetch-batch */
        free_genda(DATA_ONLY, genda_ptr) ;
    }
    
    return ;
} /* end fetch_structure_rp */


/*===========================================================================*
    set_trigger_rp                                                    GDB-RPC
      - activate or deactivate a trigger watch based on the trigger-name 
        provided.
      - trigger may be related to either a db-trigger-object or to the 
        G2 procedure referred to by G2_TRIGGER_MSG_PROC
      - input: [0]=trigger-name or trigger-object
               [1]=trigger-enable (TRUE,FALSE)
      - output: status info (stat,code,msg)
 *===========================================================================*/
static void set_trigger_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    gsi_item    *object ;
    GDB_CHAR     *trig_name ;
    gsi_int     trig_obj = 0 ;
    long        found, n, x ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("SET_TRIGGER_RP: %"), context_num);
    }
    
    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (count < 2) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    
    /* arg-0 is the trigger-name or trigger-object */
    
    /* trigger-name - refer to db-trigger-event procedure in G2 */
    if (gsi_type_of(arg[0]) == GSI_SYMBOL_TAG) 
    {
        trig_name = gsi_symbol_name(gsi_sym_of(arg[0])) ;
        trig_obj = 0 ;
        if (trig_name == NULL) 
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVITM, _T("trigger object name"));

            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
    }

    /* trigger-object - refer to db-trigger-object in G2 */
    else 
    {
        if (wcscmp(gsi_symbol_name(gsi_class_name_of(arg[0])), TRIGGER_OBJECT_NAME) != 0)
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EBADOBJ, TRIGGER_OBJECT_NAME) ;
            return_rpc_status(NULL, 0, NULL, call_index) ;
            return ;
        }
        trig_name = (GDB_CHAR*)gsi_symbol_name(gsi_name_of(arg[0])) ;
        trig_obj = gsi_handle_of( arg[0]) ;
    } 
    
    /* arg-1 is trigger-enable (TRUE,FALSE) */
    found = FALSE ;
    x = 0 ;

    /* ENABLE a trigger */
    if (gsi_log_of(arg[1]) == GSI_TRUE) 
    {
        /* first look for an existing trigger of same name */
        for (n=1;n<MAX_TRIGGERS;n++) 
        {
            if (trigger.names[n] != NULL)
            {
                if (!_wcsicmp(trig_name, trigger.names[n]) && trigger.context[n] == context_num)
                {
                    found = TRUE ;
                    break ;
                }
            }
            else
                if (x == 0)
                    x = n ;
        }
        if (!found) 
        {
            /* since it wasn't found in the trigger list, define a new one */
            if ((trigger.names[x] = (GDB_CHAR*)XCALLOC(wcslen(trig_name)+1, sizeof(GDB_CHAR))) == NULL)
            {
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
                return_rpc_status(NULL, 0, NULL, call_index) ;
                return ;
            }
            wcscpy(trigger.names[x], trig_name) ;
            trigger.obj_handle[x] = trig_obj ;
            trigger.context[x] = context_num ;
            (trigger.count)++ ;
            
            /* if referring to a trigger-object then update status */
            if (trig_obj > 0) 
            {
                object = gdb_registered_item_array ;
                gsi_clear_item(object[0]) ;
                gsi_set_handle(object[0], trig_obj) ;

                gsi_set_str(object[0], (gsi_char*)_T("CONFIGURED")) ;

                gsi_return_values(object, 1, context_num) ;
            }
        }
    }

    /* DISABLE an active trigger */
    else
    {
        for (n=1;n<MAX_TRIGGERS;n++)
        {
            if (trigger.names[n] != NULL)
            {
                if (!_wcsicmp(trig_name, trigger.names[n]))
                {
                    XFREE(trigger.names[n]) ;
                    trigger.names[n] = NULL ;
                    trigger.obj_handle[n] = 0 ;
                    trigger.context[n] = -1 ;
                    (trigger.count)-- ;
                    break ;
                }
            }
        }
    }
    
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;    
}  /* end set_trigger_rp */


/*===========================================================================*
    
    get_triggers_rp                                                   GDB-RPC
      - load all active trigger names into symbol-array and return to G2
      - input: none
      - output: 
          + trigger-name symbol array
          + trigger count
          + status info: stat,code,msg
 *===========================================================================*/
static void get_triggers_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    register int  n, x ;
    gsi_symbol   *trig_array = NULL ;
    gsi_item     *ret_args ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GET_TRIGGERS_RP: %"), context_num) ;
    }

    ret_args = gdb_item_array ;

    gsi_set_class_name(ret_args[0], gsi_make_symbol((gsi_char*)_T("SYMBOL-LIST")));

    gsi_set_type(ret_args[0], GSI_NULL_TAG); /* hack to correct GSI bug with set_class_name */
    gsi_set_int(ret_args[1], 0) ;
    
    trig_array = (gsi_symbol*)XCALLOC(1, sizeof(gsi_symbol)) ;
    
    if (trigger.count == 0) 
    {
        iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
        gsi_set_sym_list(ret_args[0], trig_array, 0) ;
        gsi_set_int(ret_args[1], 0) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 2) ;
        return_rpc_status(ret_args, 2+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item (ret_args[0]) ;
        if (trig_array != NULL)
            XFREE(trig_array) ;
        return ;
    }
    
    if (!context[context_num].available)
    {
        gsi_set_sym_list(ret_args[0], trig_array, 0) ;
        gsi_set_int(ret_args[1], 0) ;
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 2) ;
        return_rpc_status(ret_args, 2+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item (ret_args[0]) ;
        if (trig_array != NULL)
            XFREE(trig_array) ;
        return ;
    }
    
    if (trig_array != NULL)
        XFREE(trig_array) ;
    if ((trig_array = (gsi_symbol*)XCALLOC(trigger.count, sizeof(gsi_symbol))) == NULL)
    {
        gsi_set_sym_list(ret_args[0], trig_array, 0) ;
        gsi_set_int(ret_args[1], 0) ;
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EINSMEM) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 2) ;
        return_rpc_status(ret_args, 2+NUM_STATUS_ARGS, NULL, call_index) ;
        gsi_clear_item(ret_args[0]) ;
        return ;
    }
    
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    
    /* assign trigger name addresses to trig_array for return to G2 */
    x = 0 ;
    for (n=1; n < MAX_TRIGGERS; n++)
    {
        if (trigger.names[n] != NULL)
        {
            trig_array[x] = gsi_make_symbol((gsi_char*)trigger.names[n]) ;
            x++ ;
        }
        if (x >= trigger.count)
            break ;
    }
    
    update_object_status(ret_args, NULL, UPDATE_ITEMS, 2) ;
    
    /* set the return values */
    gsi_set_sym_list(ret_args[0], trig_array, trigger.count) ;
    gsi_set_int(ret_args[1], trigger.count) ;
    
    update_object_status(ret_args, NULL, UPDATE_ITEMS, 2) ;
    return_rpc_status(ret_args, 2+NUM_STATUS_ARGS, NULL, call_index) ;
    
    gsi_clear_item(ret_args[0]) ;
    
    if (trig_array != NULL)
        XFREE(trig_array) ;
    
    return ;
}


/*===========================================================================*
    disable_all_triggers_rp                                           GDB-RPC
 *===========================================================================*/
static void disable_all_triggers_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    gsi_item   *object ;
    long        n ;
    
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ;
    
    /* DISABLE all active triggers */
    
    for (n=1;n<MAX_TRIGGERS;n++) 
    {
        if (trigger.names[n] != NULL)
        {
            context_num = trigger.context[n] ;
            
            /* if referring to a trigger-object then update status */
            if (trigger.obj_handle[n] >= MIN_ITEM_HANDLE) 
            {
                object = gdb_registered_item_array ;
                gsi_clear_item(object[0]) ;
                gsi_set_handle(object[0], trigger.obj_handle[n]) ;

                gsi_set_str(object[0], (gsi_char*)_T("UNDEFINED"));

                gsi_return_values(object, 1, context_num) ;
            }
            
            XFREE(trigger.names[n]) ;
            trigger.names[n] = NULL ;
            trigger.obj_handle[n] = 0 ;
            trigger.context[n] = -1 ;
            
            (trigger.count)-- ;          
        }
    }
    
    return_rpc_status(NULL, 0, NULL, call_index) ;    
    return ;                                
}  /* end disable_all_triggers_rp */


/*===========================================================================*
    information_rp          (PRESENTLY NOT IMPLEMENTED)               GDB-RPC
      - obtain bridge & db information
      - input: 
          [0]=information type (symbol)
      - output: 
          + structure (name/value pairs + status info)
 *===========================================================================*/
static void information_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    gsi_item     *ret_args ;
    gsi_attr     *attrs ;
    long          tmp ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("INFORMATION_RP: %"), context_num) ;
    }
    
    iomsg(DBG0, LAYER, TRUE, TRUE, NULL, TRUE, "%d", NULL_MSG) ; /* null out status */
    
    /* define it here in case we need to abort */
    ret_args = gdb_item_array ;
    attrs = gdb_attr_item_array ;
    gsi_set_type(ret_args[0], GSI_STRUCTURE_TAG) ;
    
    if (count < 1) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_args, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = the info type */
    if (*gsi_symbol_name(gsi_sym_of(arg[0])) == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 1) ;
        return_rpc_status(ret_args, 1+NUM_STATUS_ARGS, NULL, call_index) ;
        return ;
    }
    
    /* check memory */
    if (!_wcsicmp(gsi_symbol_name(gsi_sym_of(arg[0])), _T("MEMORY-TEST")))
    {
        tmp = show_memory() ;
        gsi_set_type(ret_args[0], GSI_STRUCTURE_TAG) ;
        gsi_set_attr_name(attrs[0], gsi_make_symbol((gsi_char*)_T("TOTAL-MEMORY"))) ;
        gsi_set_int (attrs[0], tmp ) ;
        gsi_set_attrs(ret_args[0], attrs, 1) ;
    }
    
    /* for testing redirect-callback feature */
    else if (!_wcsicmp(gsi_sym_of(arg[0]), _T("REDIRECT-CALLBACK-TEST")))
    {
        iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%s", _T("REDIRECT-CALLBACK-TEST = SUCCESS")) ;
        return_event_msg(NULL) ;
    }

    /* get bridge info */
    else if (!_wcsicmp(gsi_symbol_name(gsi_sym_of(arg[0])), SQL_IDENTIFY))
    {
        GDB_CHAR *pwName     = widen(bridge_info.bridge_name) ;
        GDB_CHAR *pwVer      = widen(bridge_info.bridge_version) ;
        GDB_CHAR *pwPlatform = widen(bridge_info.bridge_platform) ;

        gsi_set_type(ret_args[0], GSI_STRUCTURE_TAG) ;
        gsi_set_attr_name(attrs[0], gsi_make_symbol((gsi_char*)SQL_NAME)) ;
        gsi_set_str (attrs[0], (gsi_char*)pwName ) ;
        gsi_set_attr_name(attrs[1], gsi_make_symbol((gsi_char*)SQL_VERSION)) ;
        gsi_set_str (attrs[1], (gsi_char*)pwVer ) ;
        gsi_set_attr_name( attrs[2], gsi_make_symbol((gsi_char*)SQL_PLATFORM)) ;
        gsi_set_str (attrs[2], (gsi_char*)pwPlatform ) ;
        free(pwName) ;
        free(pwVer) ;
        free(pwPlatform) ;
        gsi_set_attrs(ret_args[0], attrs, 3) ;
    }
    
    else
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EOPNSUP) ;
    
    
    /* return the results in a structure */    
    update_object_status(ret_args, NULL, UPDATE_ITEMS, 1) ;
    return_rpc_status(ret_args, 1+NUM_STATUS_ARGS, NULL, call_index) ;    
    gsi_clear_item(ret_args[0]) ;
    return ;                                 
}


/*===========================================================================*
    redirect_callback_rp                                              GDB-RPC
 *===========================================================================*/
static void redirect_callback_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    gsi_char    *cbType = NULL ;
    gsi_char    *cbProc = NULL ;

    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("REDIRECT_CALLBACK_RP: %"), context_num) ;
    }
    
    if (count < 2) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-0 = the callback to modify */
    cbType = gsi_symbol_name(gsi_sym_of(arg[0])) ;
    if (cbType == NULL || *cbType == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        iomsg(DBG3, LAYER, FALSE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    /* arg-1 = the new callback procedure in G2 */
    cbProc = gsi_symbol_name(gsi_sym_of(arg[1])) ;
    if (cbProc == NULL || *cbProc == 0)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        return_rpc_status(NULL, 0, NULL, call_index) ;
        return ;
    }
    
    if (!_wcsicmp(cbType, G2_EVENT_MSG_PROC))
    {
        gsi_rpc_declare_remote(&context_event_msg_hdl[context_num], cbProc, NULL, 5, 0, context_num) ;
        iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s%s", ICALLMD, G2_EVENT_MSG_PROC, cbProc) ;
    }
    else if (!_wcsicmp(cbType, G2_TRIGGER_MSG_PROC))
    {
        gsi_rpc_declare_remote(&context_trigger_msg_hdl[context_num], cbProc, NULL, 3, 0, context_num) ;
        iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s%s", ICALLMD, G2_TRIGGER_MSG_PROC, cbProc) ;
    }
    else
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", EINVCBS, cbProc) ;
    
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;                                
}


/*----------------------------------------------------------
    DEBUG/Bridge Testing Functions
 *----------------------------------------------------------*/

/*===========================================================================*
    reconfigure_rp
      - this functon is used to reconfigure the bridge on the fly via 
        set_init_params. This function should only be used for debugging and 
        should not be provided as a user callable routine.
      - args: [0]=initilization_string
 *===========================================================================*/
static void reconfigure_rp(gsi_item *arg_list, gsi_int count, gsi_int call_index)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("RECONFIGURE_RP: %"), context_num) ;
    }
    
    if (count < 1 || *gsi_str_of(arg_list[0]) == 0) 
    {

        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EININST) ;
        return_event_msg(NULL) ;
        return ;
    }
    
    /* arg-0 = the new initialization string */
    set_init_params((GDB_CHAR*)gsi_str_of(arg_list[0]), FALSE) ;
    if (context[context_num].console_output) printf("\n");
    
    return ;
} /* end reconfigure_rp */


/*===========================================================================*
    break_connect_rp  --  A GDB DEBUG procedure
      - break the current database connection
      - used to test auto-db-reconnect funtionality
 *===========================================================================*/
static void break_connect_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("BREAK_CONNECT_RP: %"), context_num) ;
    }

    process_disconnect(FALSE, context_num) ;
    
    /* return disconnect status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    return ;
}  /* end break_connect_rp */


/*===========================================================================*
    disconnect_one_rp  -- 
      - used to break a particular db-connection after a network loss
        Useful to disconnect from 'dead' connections.
 *===========================================================================*/
static void disconnect_one_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    int        the_context_num ;

    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("DISCONNECT_ONE_RP: %"), context_num) ;
    }

    if (count < 1) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EININST) ;
        return_event_msg(NULL) ;
        return ;
    }
    
    /* arg-0 = the number of the context to disconnect */
    the_context_num = gsi_int_of(arg[0]) ;
    
    process_disconnect(FALSE, the_context_num) ;
    
    /* return disconnect status information from global status struct */   
    return_rpc_status(NULL, 0, NULL, call_index) ;
    
    return ;
    
}  /* end disconnect_one_rp */


/* ========================================================================== */
/*                                                                            */
/*  configure_DSN_rp:                                                         */
/*                                                                            */
/*  - used by the ODBC bridge only                                            */
/*  - add, delete, or modify a DSN                                            */
/*  - args:                                                                   */
/*        [0]=action Code (add, modify, delete)                               */
/*        [1]=ODBC driver name                                                */
/*        [2]=structure of keys/values                                        */
/*                                                                            */
/* ========================================================================== */
static void configure_DSN_rp(gsi_item *pArg, gsi_int count, gsi_int call_index)
{
    gsi_int     ginX, ginY, ginVal ;
    gsi_char*   gstDrvr ;
    gsi_item    *ret_args ;

    int     context_num = gsi_current_context() ;

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("CONFIGURE_DSN_RP: %"), context_num) ;

    ret_args = gdb_item_array ;
    if (!uses_DSN())
    {
        GDB_CHAR *pwName  = widen(bridge_info.bridge_name) ;
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%s", ENODSNS, pwName) ;
        free(pwName) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 0) ;
        return_rpc_status(ret_args, NUM_STATUS_ARGS-2, NULL, call_index) ;
        return ;
    }
  
    if (count < 3)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EARGNUM) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 0) ;
        return_rpc_status(ret_args, NUM_STATUS_ARGS-2, NULL, call_index) ;
        return ;
    }

    /* arg-0 = action code */
    /* ------------------- */
    ginX = gsi_type_of(pArg[0]) ;
    if (ginX == GSI_INTEGER_TAG)
    {
        ginY = ginVal = gsi_int_of(pArg[0]) ;
        if (ginY > 10)
            ginY -= 10 ;
    }
    if (ginX != GSI_INTEGER_TAG || ginY > 3 || ginY < 1)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EDSNOPT) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 0) ;
        return_rpc_status(ret_args, NUM_STATUS_ARGS-2, NULL, call_index) ;
        return ;
    }

    /* arg-1 = DSN driver */
    /* ------------------ */
    ginX = gsi_type_of(pArg[1]) ;
    if (ginX != GSI_STRING_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EDSNDRV) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 0) ;
        return_rpc_status(ret_args, NUM_STATUS_ARGS-2, NULL, call_index) ;
        return ;
    }

    /* arg-2 = DSN key/value structure */
    /* ------------------------------- */
    ginX = gsi_type_of(pArg[2]) ;
    if (ginX != GSI_STRUCTURE_TAG)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EDSNKVS) ;
        update_object_status(ret_args, NULL, UPDATE_ITEMS, 0) ;
        return_rpc_status(ret_args, NUM_STATUS_ARGS-2, NULL, call_index) ;
        return ;
    }

    /* Call the database-specific DSN configurator */
    /* ------------------------------------------- */
    gstDrvr = gsi_str_of(pArg[1]) ;
    configure_DSN(ginVal, gstDrvr, pArg+2) ;


    /* Return results from global status structure */
    /* ------------------------------------------- */
    update_object_status(ret_args, NULL, UPDATE_ITEMS, 0) ;
    return_rpc_status(ret_args, NUM_STATUS_ARGS-2, NULL, call_index) ;
   
    return ;
}


/*===========================================================================*
    dump_bridge_info_rp                                               UTILITY
 *===========================================================================*/
static void dump_bridge_info_rp(gsi_item *arg, gsi_int count, gsi_int call_index)
{
    context_num = gsi_current_context() ;
    
    /* context state info */
    wprintf(_T("name               : %s\n"), context[context_num].name) ;
    wprintf(_T("active             : %s\n"), WSBOOLEAN(context[context_num].active)) ;
    wprintf(_T("available          : %s\n"), WSBOOLEAN(context[context_num].available)) ;
    wprintf(_T("no_rpc_return      : %s\n"), WSBOOLEAN(context[context_num].no_rpc_return)) ;

    /* context configuration */
    printf("genda_rows         : %ld\n", context[context_num].genda_rows) ;
    printf("max_cursors        : %ld\n", context[context_num].max_cursors) ;
    printf("max_bind_vars      : %ld\n", context[context_num].max_bind_vars) ;
    printf("bind_value_length  : %d\n",  context[context_num].max_bind_name_len) ;

    wprintf(_T("null_string        : %s\n"),  context[context_num].null_string) ;

    printf("null_number        : %ld\n", context[context_num].null_number) ;

    wprintf(_T("set_null_string    : %s\n"),  context[context_num].set_null_string) ;

    printf("set_null_number    : %ld\n", context[context_num].set_null_number) ;
    printf("set_null_options   : %d\n",  context[context_num].set_null_options) ;
    printf("max_reg_items      : %ld\n", context[context_num].max_reg_items) ;
    printf("max_text_len       : %ld\n", context[context_num].max_text_len) ;
    printf("need_textsize      : %d\n",  context[context_num].need_textsize) ;

    wprintf(_T("enable_messaging   : %s\n"), WSBOOLEAN(context[context_num].enable_messaging)) ;
    wprintf(_T("console_output     : %s\n"), WSBOOLEAN(context[context_num].console_output)) ;
    wprintf(_T("db_reconnecting    : %s\n"), WSBOOLEAN(context[context_num].db_reconnecting)) ;
    wprintf(_T("iomsg_ts           : %s\n"), WSBOOLEAN(context[context_num].iomsg_ts)) ;
    
    /* logfile info */
    if (context[context_num].logfile_name != NULL)
        wprintf(_T("logfile_name       : %s\n"), context[context_num].logfile_name) ;
    else
        wprintf(_T("logfile_name       : (null)\n")) ;
    wprintf(_T("logfile_filter     : %d\n"), context[context_num].logfile_filter) ;
    wprintf(_T("logfile_active     : %s\n"), WSBOOLEAN(context[context_num].logfile_active)) ;
    wprintf(_T("logfile_ts         : %s\n"), WSBOOLEAN(context[context_num].logfile_ts)) ;

    /* global status info */
    printf("gbl_status.status  : %d\n", context[context_num].gbl_status.status) ;
    printf("gbl_status.code    : %d\n", context[context_num].gbl_status.code) ;
    if (context[context_num].gbl_status.msg != NULL) {

        wprintf(_T("gbl_status.msg     : %s\n"), context[context_num].gbl_status.msg) ;

    } else
        printf("gbl_status.msg     : (null)\n");
    printf("gbl_status.rp      : %d\n", context[context_num].gbl_status.rows_processed) ;
    
    /* connect info */
    wprintf(_T("connected_to_db            : %s\n"), WSBOOLEAN(context[context_num].connected_to_db)) ;
    wprintf(_T("auto_db_reconnect          : %s\n"), WSBOOLEAN(context[context_num].auto_db_reconnect)) ;

    if (context[context_num].db_connect_info.username != NULL) {
        wprintf(_T("db_connect_info.username   : %s\n"), context[context_num].db_connect_info.username);
    } else
        printf("db_connect_info.username   : (null)\n");
    if (context[context_num].db_connect_info.password != NULL) {
        wprintf(_T("db_connect_info.password   : %s\n"), context[context_num].db_connect_info.password) ;
    } else
        printf("db_connect_info.password   : (null)\n") ;
    if (context[context_num].db_connect_info.connection != NULL) {
        wprintf(_T("db_connect_info.connection : %s\n"), context[context_num].db_connect_info.connection) ;
    } else
        printf("db_connect_info.connection : (null)\n") ;
    /*{{{ gsi_connection_string. for project 28544 Gensym-2012 */
    if (context[context_num].db_connect_info.gsi_connection_str != NULL) {
      wprintf(_T("db_connect_info.gsi_connection_str	: %s\n"), context[context_num].db_connect_info.gsi_connection_str);
    } else
      printf("db_connect_info.gsi_connection_str	: (null)\n");
    /*}}}*/
    
    return ;
}


/*---------------------------------------------------------------------------*
                              GSI Toolkit Functions
  ---------------------------------------------------------------------------*/

/*===========================================================================*
    gsi_initialize_context                                        GSI-TOOLKIT
      - called when IO (context) is activated in G2
      - sets context[].active flag to TRUE upon SUCCESS_CD 
 *===========================================================================*/

gsi_int gsi_initialize_context (gsi_char* remote_process_init_string, gsi_int length)
{
    extern  gsi_int periodic() ;
    long    status ;
    
    context_num = gsi_current_context() ;
    
    /* In the event of a premature shutdown during context init */
    if (context_num < 0)
    {
        printf("\nERROR::Connection has terminated during context initialization.\n\n") ;
        fflush(stdout) ;
        return(GSI_REJECT) ;
    }
    
    /* ~~If this context exceeds maximum # of GSI contexts (HACK)*/
    if (context_num > MAX_GDB_CONTEXTS - 1) 
    {
        printf("\nERROR::Context %d exceeds maximum number of GDB contexts (%d).\n\n", context_num, MAX_GDB_CONTEXTS) ;
        fflush(stdout) ;
        return(GSI_REJECT) ;
    }
    
    context[context_num].active    = FALSE;   /* context has not been initialized */
    context[context_num].available = FALSE;   /* context has not been configured */
    
    /*** Check Authorization ***/
    if (periodic() != TRUE) 
    {
        printf("\n===============================================\n") ;
        printf(" G2-Database Bridge Authorization has EXPIRED!\n") ;
        printf(" Please contact Gensym at %s\n", GENSYM_PHONE) ;
        printf("===============================================\n\n") ;
        fflush(stdout) ;
        exit(1) ;
    }
    
    /* initialize bridge context */ 
    status = set_init_params((GDB_CHAR*)remote_process_init_string, ALL) ;
    
    /* initialize value array size based on command line args */ 
    if (max_value_array_size > 0)
        context[context_num].genda_rows = max_value_array_size ;
    
    if (status) 
    {
        iomsg(DBGM, LAYER, FALSE, FALSE, NULL, FALSE, "%d", EINITFA) ;
        return (GSI_REJECT) ;
    }
    
    
    
    /* declare remote: gsi->g2 procedures */
    gsi_rpc_declare_remote(&context_event_msg_hdl[context_num],   (gsi_char*)G2_EVENT_MSG_PROC, NULL, 5, 0, context_num) ;
    gsi_rpc_declare_remote(&context_trigger_msg_hdl[context_num], (gsi_char*)G2_TRIGGER_MSG_PROC, NULL, 3, 0, context_num) ;
    
    /* enable this context */
    context[context_num].active = TRUE ;
    gdb_context_count++ ;
    
    
    return(GSI_ACCEPT) ;
}  /* end gsi_initialize_context */


/*===========================================================================*
    gsi_receive_registration  (gsi_def_obj)                       GSI-TOOLKIT
 *===========================================================================*/
void gsi_receive_registration (gsi_registration item_registration)
{
    gsi_registered_item     *object ;
    gsi_attr                *ret_record ;
    GENDA                   *genda_ptr = NULL ;
    gsi_int                 handle, gdb_handle ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1|DBGC) {
        iomsg(DBG1|DBGC, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GSI_RECEIVE_REGISTRATION: %"), context_num) ;
    }

#ifdef XXX
    /* removed this since data-served objects are sometimes registered before context is
       configured. This will result in GENDA not being defined for some objects if we 
       reject the registration */
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return ;
    }
#endif

    /* Get the object handle */
    handle = gsi_handle_of(item_registration) ;

#ifdef _DEBUG
    printf("\n--------------------------\n") ;
    printf(" Registration\n") ;
    printf("--------------------------\n") ;

    wprintf(_T("  Object Type: %d (%s)\n"), gsi_type_of(item_registration), gsi_type_to_string(item_registration) ) ;
    wprintf(_T("  Handle:      %d\n"), gsi_handle_of(item_registration) ) ;
    wprintf(_T("  Name :       %s\n"), gsi_symbol_name(gsi_name_of(item_registration))) ;
    wprintf(_T("  Class :      %s\n"), gsi_symbol_name(gsi_class_name_of(item_registration))) ;

    printf("\n") ;
#endif

    if (handle < MIN_ITEM_HANDLE) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
        if (debug & DBG6)
            printf("Invalid Object Handle: %d, context-%d\n", handle, context_num) ;
        return ;
    }
    
    /* Note: All data served objects (and non-data served objects passed via RPC)
       will be registered. Unfortunately there is no way to differentiate between
       g2-database 'template' objects and all other objects since we do not have
       the class hierarchy available (only the direct superior class name. */
    
    /* associate a GDB handle with this GSI registered item handle */
    gdb_handle = gdb_index(context_num, handle, FALSE) ;
    if (!gdb_handle) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d", EEXREGI, context[context_num]. max_reg_items) ;
        return ;
    }
    
    /* null out the slot just in case */
    storage_area(SET, context_num, handle, NULL) ;
    
    /* Initialize the Generic Descriptor (info) Area */
    genda_ptr = init_genda(handle) ;
    if (genda_ptr == NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ENOGENP) ;
        return ;
    }
    storage_area(SET, context_num, handle, genda_ptr) ;
    
    /* Return status attribs & object handle to the registered object  */
    object = gdb_registered_item_array ;
    gsi_clear_item(object[0]) ;
    ret_record = gdb_attr_item_array;     /* gdb_attr_item_array */
    gsi_set_handle(object[0], handle) ;
    
    /* Set the object_handle attribute name and value. Note: Must enable object status
    return (if its disabled) in order to get the handle back to the object */
    update_object_status(ret_record, genda_ptr, UPDATE_ATTRS, 0) ;
    gsi_set_attr_name(ret_record[INDX_POS], gsi_make_symbol((gsi_char*)IDX_ATT)) ;
    gsi_set_int(ret_record[INDX_POS], handle) ;
    gsi_return_attrs(object[0], ret_record, NUM_STATUS_ARGS, context_num) ;
    
    if (debug & DBG6) printf("Object Registration - Idx: %d\n", handle) ;
    
    return ;
}   /* end gsi_receive_registration */


/*===========================================================================*
    gsi_get_data                                                  GSI-TOOLKIT
      - called when a G2 object is activated (unless default-update-interval
        is none)
      - called AT the update interval of the G2 object if the 'external-
        system-has-a-scheduler' is 'Y'
      - called when an 'update' action is performed on a G2 object
 *===========================================================================*/
void gsi_get_data (gsi_registered_item registered_items[], gsi_int count)
{
    return ;
}  /* end gsi_get_data */ 


/*===========================================================================*
    gsi_set_data                                                  GSI-TOOLKIT
      - called when a G2 set action is performed on a G2 variable which is
        mapped to a GSI variable.
      - This function will not be used by the bridge. It should return a
        warning or error if called as a result of a user trying to 'set' a
        GSI variable or query object using the interface object to this
        bridge.
 *===========================================================================*/
void gsi_set_data (gsi_registered_item registered_items[], gsi_int count)
{
    GENDA     *genda_ptr ;
    gsi_int    handle ;
    long       i ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1|DBGC)
        iomsg(DBG1|DBGC, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GSI_SET_DATA: %"), context_num) ;
    
    if (!context[context_num].available)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return ;
    }
    
    /* For every G2  object request */
    for(i=0; i<count; i++)
    {
        handle = gsi_handle_of(registered_items[i]) ;
        if (handle < MIN_ITEM_HANDLE) continue ;
        
        genda_ptr = storage_area(GET, context_num, handle, NULL) ;
        if (genda_ptr == NULL) continue ;
        
        /* set the warn msg, illegal set, to global status & genda status */
        iomsg(DBG4, LAYER, TRUE, TRUE, genda_ptr, FALSE, "%d", WILLSET) ;
        
        update_object_status(registered_items[i], genda_ptr, RETURN_TO_OBJECT, 0) ;
    }
}  /* end gsi_set_data */ 


/*===========================================================================*
    gsi_pause_context                                             GSI-TOOLKIT
 *===========================================================================*/
void gsi_pause_context()
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1|DBGC)
        iomsg(DBG1|DBGC, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GSI_PAUSE_CONTEXT: %"), context_num) ;
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return ;
    }
    
    /* close the logfile if designated */
    if (context[context_num].logfile_name != NULL)
    {
        if (!logfileio(F_CLOSE, context[context_num].logfile_name))
            iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, "%d%s", ILOGCLP, context[context_num].logfile_name) ;
        else 
            iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%d%s", ELOGCLO, context[context_num].logfile_name) ;
    }  
}  /* end gsi_pause_context() */ 


/*===========================================================================*
    gsi_resume_context                                            GSI-TOOLKIT
 *===========================================================================*/
void gsi_resume_context()
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1|DBGC)
        iomsg(DBG1|DBGC, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GSI_RESUME_CONTEXT: %"), context_num) ;
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return ;
    }
    
    /* open the logfile if designated */
    if (context[context_num].logfile_name != NULL)
    {
        if (!logfileio(F_OPEN, context[context_num].logfile_name))
            iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, "%d%s", ILOGOPR, context[context_num].logfile_name) ;
        else
            iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, "%d%s", ELOGOPN, context[context_num].logfile_name) ;
    }
}  /* end gsi_resume_context() */ 


/*===========================================================================*
    gsi_shutdown_context                                          GSI-TOOLKIT
 *===========================================================================*/
void gsi_shutdown_context()
{
    int   i = 0 ;
    
    context_num = gsi_current_context() ;
    
    if (context_num < 0)  /* to avoid a GSI bug of context = -1 */
        return ;
    
    if (debug & DBG1|DBGC) {
        iomsg(DBG1|DBGC, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GSI_SHUTDOWN_CONTEXT: %"), context_num) ;
    }
    
    gdb_context_count-- ;
    if (gdb_context_count < 0)
        gdb_context_count = 0 ;
    
    if (debug & DBG2) printf("\n");
    
    /* just return if the context is not available. This prevents a crash if G2 is 
        cycling IO before configuration_rp has a chance to run, i.e. disable/enable in 
        a tight loop, etc. */
    
    if (debug & DBG2) {
        wprintf(_T("Shutting down %s (%d).\n"), context[context_num].name, context_num) ;
    }
    
    /* need to shutdown messaging to avoid crash -- HACK */
    context[context_num].enable_messaging = FALSE ;
    context[context_num].no_rpc_return = TRUE ;
    
    /* release all resources allocated during configuration_rp */
    
    if (context[context_num].available) 
    {
        /* may want an array to monitor db connections to avoid shutdown error */
        disconnect_rp(NULL, 0, 0) ;
        
        /* close the logfile if designated */
        if (context[context_num].logfile_name != NULL)
        {
            if (!logfileio(F_CLOSE, context[context_num].logfile_name))
            {
	      if (debug & DBG2) {
		wprintf(_T("Logfile '%s' has been CLOSED.\n"), context[context_num].logfile_name) ;

	      }
	      return_event_msg(NULL) ;
            }
            else 
            {
	      if (debug & DBG2) {
             wprintf(_T("Logfile '%s' could not be closed.\n"), context[context_num].logfile_name) ;
	      }
	      return_event_msg(NULL) ;
            }
            XFREE(context[context_num].logfile_name) ;
            context[context_num].logfile_name = NULL ;
        }
    }
    
    /* release all resources allocated during set_init_params */
    
    if (context[context_num].active) 
    {
        if (context[context_num].name != NULL)
        {
            XFREE (context[context_num].name) ;
            context[context_num].name = NULL ;
        }
        if (context[context_num].null_string != NULL)
        {
            XFREE (context[context_num].null_string) ;
            context[context_num].null_string = NULL ;
        }
        
        if (context[context_num].set_null_string != NULL)
        {
            XFREE (context[context_num].set_null_string) ;
            context[context_num].set_null_string = NULL ;
        }
        
        /* release status structure */
        if (context[context_num].gbl_status.msg != NULL)
        {
            XFREE (context[context_num].gbl_status.msg) ;
            context[context_num].gbl_status.msg = NULL ;
        }
        
        /* release registered_item arrays */
        if (context[context_num].reg_item.addr != NULL) 
        { 
            XFREE (context[context_num].reg_item.addr) ;
            context[context_num].reg_item.addr = NULL ;
        }
        if (context[context_num].reg_item.gsi_handle != NULL) 
        {
            XFREE (context[context_num].reg_item.gsi_handle) ;
            context[context_num].reg_item.gsi_handle = NULL ;
        }
        
        /* disable the context_num number */
        context[context_num].active = FALSE ;
        context[context_num].available = FALSE ;
        context[context_num].no_rpc_return = FALSE ;
    }
    
    /* If no contexts are connected and shutdown_on_disconnect has been */
    /* requested, shut down this bridge.                                */
    /* ---------------------------------------------------------------- */
    if (gdb_shutdown_on_disconnect)
    {
        /* See if other contexts are still connected */
        /* ----------------------------------------- */
        for (i = 0 ; i < MAX_GDB_CONTEXTS ; i++)
            if (context[i].active)
                return ;
            kill_bridge_rp(NULL, 0, 0) ;
    }
}  /* end gsi_shutdown_context */


/*===========================================================================*
    gsi_g2_poll                                                   GSI-TOOLKIT
      - called by G2 if 'poll-external-system-for-data' is set to 'yes'.
      - call frequency determined by 'scheduler-mode' attrib of
        'timing-parameters' in G2 system table.
 *===========================================================================*/
void gsi_g2_poll()
{
    /* more efficient to use run-loop */
    return ;
} /* end gsi_g2_poll */


/*===========================================================================*
    gsi_receive_deregistrations (gsi_stop_data)                   GSI TOOLKIT
      - called when object or IO is disabled, deactivated, re-defined, etc
        or when identifying attribs are modified.
 *===========================================================================*/
void gsi_receive_deregistrations (gsi_registered_item *registered_items, gsi_int count)
{
    GENDA    *genda_ptr ;
    gsi_int   handle ;
    long      i, n ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1|DBGC) {
        iomsg(DBG1|DBGC, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GSI_RECEIVE_DEREGISTRATIONS: %"), context_num) ;
    }
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", ECONUNA) ;
        return ;
    }
    
    /* For every G2  object request */
    for(i=0; i<count; i++) 
    {
        handle = gsi_handle_of(registered_items[i]) ;
        
#ifdef _DEBUG
        printf("\n--------------------------\n") ;
        printf(" De-Registration\n") ;
        printf("--------------------------\n") ;
        printf("  Object Type: %d (%s)\n", gsi_type_of(gsi_registration_of(handle, context_num)), gsi_type_to_string(gsi_registration_of(handle, context_num))) ;
        printf("  Handle:      %d\n", handle ) ;
        printf("  Name :       %s\n", gsi_symbol_name(gsi_name_of(gsi_registration_of(handle, context_num)))) ;
        printf("  Class :      %s\n", gsi_symbol_name(gsi_class_name_of(gsi_registration_of(handle, context_num)))) ;
        printf("\n") ;
#endif
        
        /* Check for ok handle, and object */
        if (handle < MIN_ITEM_HANDLE) 
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d", EBADIND) ;
            return_event_msg(NULL) ;
        }
        else 
        {
            if (debug & DBG6) printf("Cleanup OBJ : %d\n", handle) ;
            /* identify the genda pointer from the user ptr */
            genda_ptr = storage_area(GET, context_num, handle, NULL) ;
            if (genda_ptr != (GENDA *)NULL) 
            {
                free_genda(ALL, genda_ptr) ;
                /* null-out the slot in case GSI decides to deregister again - hack */
                storage_area(SET, context_num, handle, NULL) ;
            }
            /* unreserve the handle */
            gdb_index(context_num, handle, TRUE) ;
            
            /* see if there is a trigger-object for this context/object-handle
            and reset */
            if (!trigger.count)
                continue ;
            
            for (n=1; n<MAX_TRIGGERS; n++) 
            {
                if (trigger.obj_handle[n] == handle && trigger.context[n] == context_num) 
                {
                    if (trigger.names[n] != NULL)
                        XFREE((char *)trigger.names[n]) ;
                    trigger.names[n] = NULL ;
                    trigger.obj_handle[n] = 0 ;
                    trigger.context[n] = -1 ;
                    (trigger.count)-- ;
                    break ;
                }
            }
            
        }
    }
}   /* end gsi_receive_deregistrations */


/*===========================================================================*
    gsi_receive_message (gsi_send_message)                        GSI TOOLKIT
      - called when an inform action is performed on a GSI message-served
        variable
      - message must be <= 64k
 *===========================================================================*/
void gsi_receive_message (gsi_char* message, gsi_int length)
{
    context_num = gsi_current_context() ;
    
    if (debug & DBG1|DBGC) {
        iomsg(DBG1|DBGC, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("GSI_RECEIVE_MESSAGE: %"), context_num) ;
    }
}


/*===========================================================================*
    gsi_get_tcp_port                                              GSI TOOLKIT
      - called once at bridge startup
      - returns tcpip port number or (GSI_PORT_NUMBER=0) if the default
        (22041) is being used.
      - you can return (any) port number that you wish the bridge to use.
 *===========================================================================*/
gsi_int gsi_get_tcp_port()
{
    return(TCPIP_PORT_NUMBER) ;
} 


/*===========================================================================*
    gsi_set_up  (InitUsrRpcs)                                     GSI TOOLKIT
      - called once at bridge startup
      - used to: install custom error handler; set or reset GSI runtime
        options; declare local RPC functions; initial allocation of GSI
        structures.                                               (SSS)
 *===========================================================================*/
void gsi_set_up ()
{
    register long n ;
    int           nrItems ;
    
    /* 
     *  Turn off GSI memory messages 
     */ 
    g2rtl_Gc_silence = (void *)1 ;
    
    
    /* 
     *  Disable GSI error handler when in debug mode 
     */
    if (debug & DBGX)
        gsi_set_option(GSI_NO_SIGNAL_HANDLERS) ;
    
    /*
     *  Set Character Set Translation Mode
     */
    if (gdb_charset == INVALID_DB_CHARSET)
    {
        gdb_charset = DFLT_DB_CHARSET ;
        printf("\nERROR::INVALID STRING CONVERSION STYLE SPECIFIED\n") ;
        printf("Setting Default String Conversion Style = GENSYM (%s)\n", DB_CHARSET_NAME[gdb_charset]) ;
        gsi_set_string_conversion_style(gdb_charset) ;
    }
    else if (gdb_charset != DFLT_DB_CHARSET) 
    {
        gsi_set_string_conversion_style(gdb_charset) ;
        printf("\nSTRING CONVERSION STYLE = %s\n", DB_CHARSET_NAME[gdb_charset]) ;
    }
    else
        gsi_set_string_conversion_style(DFLT_DB_CHARSET) ;
    
        /*
        *  Allocate data structures that will be needed to support this program's 
        *  features.  Note, that these are never explicitly reclaimed because they
        *  are needed for the entire life of the process and are implicitly 
        *  reclaimed upon exit of the process.
    */
    
    gdb_item_array = gsi_make_items(max_col_array_size+NUM_STATUS_ARGS+1) ;
    gdb_attr_item_array = gsi_make_attrs_with_items(max_col_array_size+NUM_STATUS_ARGS+1) ;
    gdb_registered_item_array = gsi_make_registered_items(2) ;
    nrItems = (max_value_array_size > NUM_STATUS_ARGS) ? (max_value_array_size+2) : (NUM_STATUS_ARGS+2) ;
    gdb_value_array  = gsi_make_items(nrItems) ;
    gdb_column_array = gsi_make_items(max_col_array_size+1) ;
    
    gdb_status_items = gsi_make_items(NUM_STATUS_ARGS) ;
    gdb_status_attr_items = gsi_make_attrs_with_items(NUM_STATUS_ARGS) ;
    
    gdb_trigger_reg  = gsi_make_registered_items(1) ;
    gdb_trigger_item = gsi_make_items(3) ;
    gdb_trigger_attr = gsi_make_attrs_with_items(1) ;
    
    gdb_object_array = gsi_make_items(nrItems) ;
    
    /* allocate attrs for object list return */
    printf("\nAllocating %d x %d data array for object passing...", max_value_array_size, max_col_array_size);
    if ((list_attrs = (gsi_attr **)XCALLOC(max_value_array_size, sizeof(gsi_attr *))) == (gsi_attr **)NULL)
    {
        printf("Failed to allocate attributes for object list return\n");
        exit(1) ;
    }
    for (n=0;n<max_value_array_size;n++)
        list_attrs[n] = gsi_make_attrs_with_items(max_col_array_size) ;
    printf("Done allocating work arrays\n");
    
    /*
     *  Initialize the trigger ptr array
     */
    memset(trigger.names,      0, MAX_TRIGGERS*sizeof(char)) ;
    memset(trigger.obj_handle, 0, MAX_TRIGGERS*sizeof(gsi_int)) ;
    memset(trigger.context,   -1, MAX_TRIGGERS*sizeof(gsi_int)) ;
    trigger.count = 0 ;
    trigger.timeLastChecked = 0 ;
    trigger.checkInterval = 0 ;
    
    
    /*
     *  Declare local functions that may be called 'from' G2
     */
    gsi_rpc_declare_local(connect_rp,                   (gsi_char*)_T("CONNECT_RP")) ;
    gsi_rpc_declare_local(disconnect_rp,                (gsi_char*)_T("DISCONNECT_RP")) ;
    gsi_rpc_declare_local(kill_bridge_rp,               (gsi_char*)_T("KILL_BRIDGE_RP")) ;
    gsi_rpc_declare_local(configuration_rp,             (gsi_char*)_T("CONFIGURATION_RP")) ;
    
    gsi_rpc_declare_local(set_cursor_rp,                (gsi_char*)_T("SET_CURSOR_RP")) ;
    gsi_rpc_declare_local(refresh_cursor_rp,            (gsi_char*)_T("REFRESH_CURSOR_RP")) ;
    
    gsi_rpc_declare_local(sql_function_rp,              (gsi_char*)_T("SQL_FUNCTION_RP")) ;
    gsi_rpc_declare_local(commit_rp,                    (gsi_char*)_T("COMMIT_RP")) ;
    gsi_rpc_declare_local(rollback_rp,                  (gsi_char*)_T("ROLLBACK_RP")) ;
    gsi_rpc_declare_local(log_file_rp,                  (gsi_char*)_T("LOG_FILE_RP")) ;
    gsi_rpc_declare_local(exec_stored_proc_rp,          (gsi_char*)_T("EXEC_STORED_PROC_RP")) ;
    gsi_rpc_declare_local(exec_stored_proc_return_rp,   (gsi_char*)_T("EXEC_STORED_PROC_RETURN_RP")) ;
    gsi_rpc_declare_local(ping_db_rp,                   (gsi_char*)_T("PING_DB_RP")) ;
    
    gsi_rpc_declare_local(reconfigure_rp,               (gsi_char*)_T("RECONFIGURE_RP")) ;
    gsi_rpc_declare_local(break_connect_rp,             (gsi_char*)_T("BREAK_CONNECT_RP")) ;
    gsi_rpc_declare_local(disconnect_one_rp,            (gsi_char*)_T("DISCONNECT_ONE_RP")) ;
    gsi_rpc_declare_local(dump_bridge_info_rp,          (gsi_char*)_T("DUMP_BRIDGE_INFO_RP")) ;
    
    gsi_rpc_declare_local(exec_sql_rp,                  (gsi_char*)_T("EXEC_SQL_RP")) ;
    gsi_rpc_declare_local(exec_sql_obj_rp,              (gsi_char*)_T("EXEC_SQL_OBJ_RP")) ;
    gsi_rpc_declare_local(exec_immediate_rp,            (gsi_char*)_T("EXEC_IMMEDIATE_RP")) ;
    
    gsi_rpc_declare_local(set_trigger_rp,               (gsi_char*)_T("SET_TRIGGER_RP")) ;
    gsi_rpc_declare_local(get_triggers_rp,              (gsi_char*)_T("GET_TRIGGERS_RP")) ;
    gsi_rpc_declare_local(disable_all_triggers_rp,      (gsi_char*)_T("DISABLE_ALL_TRIGGERS_RP")) ;
    gsi_rpc_declare_local(fetch_records_rp,             (gsi_char*)_T("FETCH_RECORDS_RP")) ;
    gsi_rpc_declare_local(fetch_query_item_rp,          (gsi_char*)_T("FETCH_QUERY_ITEM_RP")) ;
    gsi_rpc_declare_local(update_query_item_rp,         (gsi_char*)_T("UPDATE_QUERY_ITEM_RP")) ;
    gsi_rpc_declare_local(fetch_object_update_rp,       (gsi_char*)_T("FETCH_OBJECT_UPDATE_RP")) ;
    gsi_rpc_declare_local(fetch_object_copy_rp,         (gsi_char*)_T("FETCH_OBJECT_COPY_RP")) ;
    gsi_rpc_declare_local(fetch_object_list_rp,         (gsi_char*)_T("FETCH_OBJECT_LIST_RP")) ;
    gsi_rpc_declare_local(fetch_structure_rp,           (gsi_char*)_T("FETCH_STRUCTURE_RP")) ;
    gsi_rpc_declare_local(information_rp,               (gsi_char*)_T("INFORMATION_RP")) ;
    gsi_rpc_declare_local(redirect_callback_rp,         (gsi_char*)_T("REDIRECT_CALLBACK_RP")) ;
    gsi_rpc_declare_local(configure_DSN_rp,             (gsi_char*)_T("CONFIGURE_DSN_RP")) ;
}


/*---------------------------------------------------------------------------*
                              Utility Functions                           UUU
  ---------------------------------------------------------------------------*/

/*===========================================================================*
    storage_area                                                      UTILITY
      - called to access the global storage area
      - replacement for OBJ_DEF_PTRS
      - args: action = GET or SET a user area
              handle = the item handle (object handle from GSI)
              genda_ptr = only required if performing a SET
 *===========================================================================*/
GENDA *storage_area(long action, gsi_int this_context, long handle, GENDA* genda_ptr)
{
    long  gdb_handle = 0 ;

  /* GSI uses object indices > 1. With object passing, the object being passed may
     not have been 'registered', therefore it will have no object handle. In order
     to associate certain GDB structures with this object we will assign the 
     object handle 0 to any UNREGISTERED_OBJ_IDX's. Since structures for unregistered
     objects are allocated, used and immediately released there is no chance for
     conflicts -- NOTE: This may not be true any longer for GSI 4.1+ */
    if (handle == UNREGISTERED_OBJ_IDX)
        handle = 0 ;
    
    switch (action)
    {
    case GET :
                gdb_handle = gdb_index(this_context, handle, FALSE) ;
                if (!gdb_handle)
                    return NULL ;
                genda_ptr = context[this_context].reg_item.addr[gdb_handle] ;
                break ;
        
    case SET :
                gdb_handle = gdb_index(this_context, handle, FALSE) ;
                if (!gdb_handle)
                    return NULL ;
                context[this_context].reg_item.addr[gdb_handle] = genda_ptr ;
                break ;
    } 
    
    /* wprintf(L"Context:%3d \tAction:%d\tGSI-Handle:%3d\tGDB-Handle:%3d\n", this_context, action, handle, gdb_handle) ; */
    return (genda_ptr) ;
}


/*===========================================================================*
    gdb_index                                                         UTILITY
      - associates a GDB index with a GSI item handle (GSI object handle)
      - args: 
          + gsi_handle - GSI item handle (or object handle)
          + release - TRUE  = reserve a GDB handle and associate it with  
                              gsi_handle
                      FALSE = release the handle reservation associated 
                              with gsi_handle
 *===========================================================================*/
long gdb_index(gsi_int this_context, gsi_int gsi_handle, long release)
{
    register int    i ;
    long            avail_index = 0 ;
    long            nhandle = 0 ;
    
    /* search throught the entire gsi_handle array for an available handle (as 
       indicated by value = 0. Also, make sure that there is not a gdb_handle
       already associated with this gsi_handle */
    
    for (i=1; i<context[this_context].max_reg_items+1; i++) 
    { 
        /* get the next available index */
        if (context[this_context].reg_item.gsi_handle[i] == 0 && avail_index == 0) 
            avail_index = i ;
        
        /* gdb_handle already associated with this gsi_handle */
        if (context[this_context].reg_item.gsi_handle[i] == gsi_handle) 
        {
            if (release) 
            {
                context[this_context].reg_item.gsi_handle[i] = 0 ;
                (context[this_context].reg_item.hcount)-- ;
                if (debug & DBG7) printf("+ release : %3d  %3d\n", gsi_handle, i);
                return 0 ;
            }
            /* return the same gdb_handle since it is already assigned to this
            gsi_handle anyway */
            return i ;
        }
        
        /* if a new gdb_handle is assigned and we're sure it doesn't already
           exist in the handle array, then return it rather than scanning the
           entire handle array */
        if (context[this_context].reg_item.gsi_handle[i] > 0)
            nhandle++ ;
        
        if (avail_index > 0 && !release && nhandle >= context[this_context].reg_item.hcount) 
        {
            if (debug & DBG7) printf("- reserve : %3d  %3d\n", gsi_handle, avail_index);
            context[this_context].reg_item.gsi_handle[avail_index] = gsi_handle ;
            (context[this_context].reg_item.hcount)++ ;
            return (avail_index) ;
        }
    }
    
    if (!avail_index || release) 
    {
        if (!avail_index)
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, "%d%d", EEXREGI, context[this_context].max_reg_items) ;
        return 0 ;
    }
    
    /* associate a new gdb_handle with this gsi_handle */
    if (debug & DBG7) printf("- reserve : %3d  %3d\n", gsi_handle, avail_index) ;
    context[this_context].reg_item.gsi_handle[avail_index] = gsi_handle ;
    (context[this_context].reg_item.hcount)++ ;
    
    return (avail_index) ;
}


/*===========================================================================*
    update_object_status   
    Arguments:
    - obj_ptr :
    - genda_ptr :
    - shift : shifts status values 'shift' positions down the status array.
              Use this when 'other' values need to preceed the status values. 
    - action : RETURN_TO_OBJECT
                  sets status attribs and returns directly to the object in G2
                  identified by item_ptr
               UPDATE_OBJECT_ATTRS
                  sets status attribs and associates them with the object 
                  identified by item_ptr
               UPDATE_OBJECT_ITEMS
                  updates the pre-defined status items (by name) associated 
                  with the object identified by item_ptr
               UPDATE_ATTRS
                  updates the status attribs represented by item_ptr
               UPDATE_ITEMS
                  updates the status items represented by item_ptr (does not
                  represent attributes)
 *===========================================================================*/
long update_object_status (void* item_ptr, GENDA *genda_ptr, long action, long shift ) 
{
    gsi_attr  *status_args ;
    gsi_item  *object ;
    gsi_int    obj_handle = 0 ;
    long       status ;
    
    context_num = gsi_current_context() ;
    
    if (debug & DBG1) {
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, "%s%d", _T("UPDATE_OBJ_STATUS: %"), context_num) ;
    }
    
    if (action == RETURN_TO_OBJECT) 
    {
        obj_handle = gsi_handle_of(item_ptr) ;
        object = gdb_registered_item_array ;
        gsi_set_handle(object[0], obj_handle) ;
    }
    
    switch(action) 
    {
    case UPDATE_ATTRS:          status_args = item_ptr ;
                                break ;
    case UPDATE_OBJECT_ITEMS:
    case UPDATE_ITEMS:          status_args = item_ptr ;
                                break ;
    default:
                                status_args = gdb_status_attr_items ;
    }
    
    /* [0] = status
       [1] = code
       [2] = message
       [3] = rows processed 
       [4] = cursor pos */
    
    if (genda_ptr != NULL) 
    {
        gsi_set_int(status_args[CODE_POS+shift],   genda_ptr->genStat.code) ;
        gsi_set_str(status_args[MSG_POS+shift],    (gsi_char*)genda_ptr->genStat.msg) ;
        gsi_set_int(status_args[NROWS_POS+shift],  genda_ptr->more_rows) ;
        gsi_set_int(status_args[CURSOR_POS+shift], genda_ptr->genStat.rows_processed) ;
        status = genda_ptr->genStat.status ;
    }
    else 
    {
        gsi_set_int(status_args[CODE_POS+shift],   context[context_num].gbl_status.code) ;
        gsi_set_str(status_args[MSG_POS+shift],    (gsi_char*)context[context_num].gbl_status.msg) ;
        gsi_set_int(status_args[NROWS_POS+shift],  0) ;
        gsi_set_int(status_args[CURSOR_POS+shift], context[context_num].gbl_status.rows_processed) ;
        status = context[context_num].gbl_status.status ;
    }
    
    switch (status)
    {
        case ERROR_CD:      gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)ERROR_SYM)) ;
                            break ;

        case WARN_CD:       gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)WARN_SYM)) ;
                            break ;

        case INFO_CD:       gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)INFO_SYM)) ;
                            break ;

        case SUCCESS_CD:    gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)SUCC_SYM)) ;
                            break ;

        case EOCURSOR_CD:   gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)EOCURSOR_SYM)) ;
                            break ;

        case NOCONNECT_CD:  gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)NOCONNECT_SYM)) ;
                            break ;

        case FATAL_CD:      gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)FATAL_SYM)) ;
                            break ;

        default:            gsi_set_sym(status_args[STAT_POS+shift], gsi_make_symbol((gsi_char*)INV_SYM)) ;
    }
    
    if (action == UPDATE_OBJECT_ITEMS) 
    {
        gsi_set_attr_by_name (item_ptr, gsi_make_symbol((gsi_char*)STAT_ATT),   status_args[STAT_POS+shift]) ;
        gsi_set_attr_by_name (item_ptr, gsi_make_symbol((gsi_char*)CODE_ATT),   status_args[CODE_POS+shift]) ;
        gsi_set_attr_by_name (item_ptr, gsi_make_symbol((gsi_char*)MSG_ATT),    status_args[MSG_POS+shift]) ;
        gsi_set_attr_by_name (item_ptr, gsi_make_symbol((gsi_char*)NROWS_ATT),  status_args[NROWS_POS+shift]) ;
        gsi_set_attr_by_name (item_ptr, gsi_make_symbol((gsi_char*)CURSOR_ATT), status_args[CURSOR_POS+shift]) ;
    }
    else if (action != UPDATE_ITEMS) 
    {
        gsi_set_attr_name(status_args[STAT_POS+shift],   gsi_make_symbol((gsi_char*)STAT_ATT)) ;
        gsi_set_attr_name(status_args[CODE_POS+shift],   gsi_make_symbol((gsi_char*)CODE_ATT)) ;
        gsi_set_attr_name(status_args[MSG_POS+shift],    gsi_make_symbol((gsi_char*)MSG_ATT)) ;
        gsi_set_attr_name(status_args[NROWS_POS+shift],  gsi_make_symbol((gsi_char*)NROWS_ATT)) ;
        gsi_set_attr_name(status_args[CURSOR_POS+shift], gsi_make_symbol((gsi_char*)CURSOR_ATT)) ;
    }
    
    switch(action) 
    {
        case RETURN_TO_OBJECT:
                    gsi_return_attrs(object[0], status_args, NUM_STATUS_ARGS, context_num) ;
                    break ;
        case UPDATE_OBJECT_ATTRS:
                    gsi_set_attrs(item_ptr, status_args, NUM_STATUS_ARGS) ;
                    break ;
    }
    
    return(GDB_SUCCESS) ;
}


/*===========================================================================*
    get_attrib_info                                                   UTILITY
      - extracts attribute info from an object
      - args: object = any GSI item
 *===========================================================================*/
void get_attrib_info (gsi_item *object)
{
#ifdef XXX
#define is_array_type(type)		    (type & 0x00000010)
#define is_list_type(type)		    (type & 0x00000020)
#define is_simple_value_type(type)	((type>=GSI_INTEGER_TAG)&&(type<=GSI_FLOAT64_TAG))
#endif

    register long    i ;
    gsi_attr*        attribs ;
    gsi_int          nAttribs ;
    gsi_int          vtype ;
    
    nAttribs = gsi_attr_count_of(object);   /* get # of attributes */
    if (nAttribs > 0)
        attribs = gsi_attrs_of(object);      /* assign attributes to local attr array */
    
    printf("    Attr Count : %d\n", gsi_attr_count_of(object)) ;
    
    /* show attribute & type */
    
    for (i=0;i<nAttribs;i++) 
    {
        /* get the type */
        vtype = gsi_type_of(attribs[i]) ;
        
        /* handle */
        if (!wcscmp(gsi_symbol_name(gsi_attr_name_of(attribs[i])), _T("OBJECT-HANDLE")) && vtype != 0)
            wprintf(_T("       [%2d]    : %s  <%d> (%s)-%d\n"), i+1, gsi_symbol_name(gsi_attr_name_of(attribs[i])),
                    gsi_int_of(attribs[i]), gsi_type_to_string(attribs[i]), gsi_element_count_of(attribs[i])) ;
        else
            wprintf(_T("       [%2d]    : %s  (%s)-%d\n"), i+1, gsi_symbol_name(gsi_attr_name_of(attribs[i])), 
                    gsi_type_to_string(attribs[i]), gsi_element_count_of(attribs[i])) ;

        /* if attrib is an item, print the sub-attrib type */
        get_item_values (attribs[i]) ;
    }
    
    return ;
}


/*===========================================================================*
    get_qv_info                                                   UTILITY
      - prints out the names of the attributes & whether or not
        the are of type QUANTITY or VALUE
 *===========================================================================*/
void get_qv_info(gsi_item seq1, gsi_item seq2)
{
    gsi_int     s1t, s2t ;
    gsi_int     n1,  n2 ;
    gsi_int     iX ;
    gsi_item    *pAttrName ;
    gsi_item    *pQVFlag ;
    gsi_char    *attrName ;
    gsi_int     qvFlag ;

    s1t = gsi_type_of(seq1) ;
    if (s1t != GSI_SEQUENCE_TAG)
    {
        printf("First parameter passed to get_qv_info is not a sequence.  (Type %ld)\n", s1t) ;
        return ;
    }
    s2t = gsi_type_of(seq2) ;
    if (s2t != GSI_SEQUENCE_TAG)
    {
        printf("Second parameter passed to get_qv_info is not a sequence.  (Type %ld)\n", s2t) ;
        return ;
    }
    n1 = gsi_element_count_of(seq1) ;
    n2 = gsi_element_count_of(seq1) ;
    if (n1 != n2)
    {
        printf("** get_qv_info: the number of elements (%ld) in the attribute name sequence is not equal\n", n1) ;
        printf("                to the number of elements (%ld) in the qv flag sequence.\n", n2) ;
        return ;
    }

    pAttrName = gsi_elements_of(seq1) ;
    pQVFlag   = gsi_elements_of(seq2) ;
    for (iX = 0 ; iX < n1 ; iX++)
    {
        if ((s1t=gsi_type_of(pAttrName[iX])) != GSI_SYMBOL_TAG)
        {
            printf("** get_qv_info: Attribute name sequence contains something (%ld) other than a string.\n", s1t) ;
            return ;
        }
        else
            attrName = gsi_symbol_name(gsi_sym_of(pAttrName[iX]) ) ;
        if ((s2t=gsi_type_of(pQVFlag[iX])) != GSI_LOGICAL_TAG)
        {
            printf("** get_qv_info: Quantity/Value flag sequence contains something (%ld) other than a truth value.\n", s2t) ;
            return ;
        }
        else
            qvFlag = gsi_log_of(pQVFlag[iX])  ;

        wprintf(_T("       [%2d] %s : %s\n"), iX+1, attrName, (qvFlag > 0) ? _T("Quantity or Value") : _T("--")) ;
    }
}


/*===========================================================================*
    build_qv_list
      - build an array of flags that indicate which of the attributes are
        defined as values or quantities
 *===========================================================================*/
short* build_qv_list(gsi_attr *pAttrs, gsi_int nrAttrs, gsi_item seq1, gsi_item seq2)
{
    short      *pRetVal ;
    gsi_int     s1t, s2t ;
    gsi_int     n1,  n2 ;
    gsi_int     iX, iY ;
    gsi_item    *pAttrName ;
    gsi_item    *pQVFlag ;
    gsi_char    *attrName, *attrName2 ;
    gsi_int     qvFlag ;
    short       inOrder = -1, found ;

    pRetVal = XCALLOC(nrAttrs, sizeof(short)) ;
    if (pRetVal == NULL)
        return pRetVal ;

    s1t = gsi_type_of(seq1) ;
    if (s1t != GSI_SEQUENCE_TAG)
    {
        printf("** build_qv_list : 1 - Not a sequence. (Type %ld)\n", s1t) ;
        return pRetVal ;
    }
    s2t = gsi_type_of(seq2) ;
    if (s2t != GSI_SEQUENCE_TAG)
    {
        printf("** build_qv_list : 2 - Not a sequence. (Type %ld)\n", s2t) ;
        return pRetVal ;
    }
    n1 = gsi_element_count_of(seq1) ;
    n2 = gsi_element_count_of(seq1) ;
    if (n1 != n2 || nrAttrs != n1)
    {
        printf("** build_qv_list: Attribute count mismatch (%ld, %ld %ld).\n", nrAttrs,  n1, n2) ;
        return pRetVal ;
    }

    pAttrName = gsi_elements_of(seq1) ;
    pQVFlag   = gsi_elements_of(seq2) ;
    for (iX = 0 ; iX < nrAttrs ; iX++)
    {
        attrName = gsi_symbol_name(gsi_attr_name_of(pAttrs[iX])) ;

        /* We expect the order of the attributes in seq1/seq2 to the the same */
        /* as those in pAttrs but allow for the possibility that it is not.   */
        /* ------------------------------------------------------------------ */
        if (inOrder)
        {
            if ((s1t=gsi_type_of(pAttrName[iX])) != GSI_SYMBOL_TAG)
            {
                printf("** build_qv_list: Element of sequence 1 is not a symbol\n") ;
                return pRetVal ;
            }
            else
                attrName2 = gsi_symbol_name(gsi_sym_of(pAttrName[iX]) ) ;
            if (_wcsicmp(attrName, attrName2))
                inOrder = 0 ;
            else
            {
                if ((s2t=gsi_type_of(pQVFlag[iX])) != GSI_LOGICAL_TAG)
                {
                    printf("** build_qv_list: Element of sequence 2 is not a logical\n") ;
                    return pRetVal ;
                }
                else
                {
                    qvFlag = gsi_log_of(pQVFlag[iX]) ;
                    pRetVal[iX] = qvFlag > 0 ? -1 : 0 ;
                    continue ;
                }
            }
        }

        found = 0 ;
        for (iY = 0 ; iY < nrAttrs ; iY++)
        {
            if ((s1t=gsi_type_of(pAttrName[iY])) != GSI_SYMBOL_TAG)
            {
                printf("** build_qv_list: Element of sequence 1 is not a symbol\n") ;
                return pRetVal ;
            }
            else
                attrName2 = gsi_symbol_name(gsi_sym_of(pAttrName[iX]) ) ;
            if (_wcsicmp(attrName, attrName2))
                continue ;
            if ((s2t=gsi_type_of(pQVFlag[iY])) != GSI_LOGICAL_TAG)
            {
                printf("** build_qv_list: Element of sequence 2 is not a logical\n") ;
                return pRetVal ;
            }
            else
            {
                qvFlag = gsi_log_of(pQVFlag[iY]) ;
                pRetVal[iX] = qvFlag > 0 ? -1 : 0 ;
                found = -1 ;
                break ;
            }
        }
        if (!found) {
            wprintf(_T("** build_qv_list: Missing QV flag for %s.\n"), attrName) ;
	}
    }
    return pRetVal ;
}


/* ========================================================================== */
/*                                                                            */
/*  build_receptacle_type_list                                                */
/*                                                                            */
/*  Make a list of the types of the record object attributes that will        */
/*  receive the values returned by the select statement attached to a genda.  */
/*                                                                            */  
/* ========================================================================== */

struct lups {   GDB_CHAR*   type_name ;
                gsi_int cast_type ; } lup [] = { {_T("TEXT"), GSI_STRING_TAG},
                                                 {_T("TEXT-LIST"), GSI_STRING_TAG},
                                                 {_T("TEXT-ARRAY"), GSI_STRING_TAG},
                                                 {_T("SYMBOL"), GSI_SYMBOL_TAG},
                                                 {_T("SYMBOL-LIST"), GSI_SYMBOL_TAG},
                                                 {_T("SYMBOL-ARRAY"), GSI_SYMBOL_TAG},
                                                 {_T("INTEGER"), GSI_INTEGER_TAG},
                                                 {_T("INTEGER-LIST"), GSI_INTEGER_TAG},
                                                 {_T("INTEGER-ARRAY"), GSI_INTEGER_TAG},
                                                 {_T("FLOAT"), GSI_FLOAT64_TAG},
                                                 {_T("FLOAT-LIST"), GSI_FLOAT64_TAG},
                                                 {_T("FLOAT-ARRAY"), GSI_FLOAT64_TAG},
                                                 {_T("QUANTITY"), GSI_QUANTITY_TAG},
                                                 {_T("QUANTITY-LIST"), GSI_QUANTITY_TAG},
                                                 {_T("QUANTITY-ARRAY"), GSI_QUANTITY_TAG},
                                                 {_T("VALUE"), GSI_VALUE_TAG},
                                                 {_T("VALUE-LIST"), GSI_VALUE_TAG},
                                                 {_T("VALUE-ARRAY"), GSI_VALUE_TAG},
                                                 {_T("ITEM-OR-VALUE"), GSI_VALUE_TAG},                
                                                 {_T("G2-LIST"), GSI_VALUE_TAG},
                                                 {_T("G2-ARRAY"), GSI_VALUE_TAG} } ;


#define NR_TRANSLATION_ENTRIES sizeof(lup)/sizeof(struct lups)

long* build_receptacle_type_list(GENDA* genda_ptr, gsi_item attr_names,
                                 gsi_item attr_type_names)
{
    gsi_char*   strX ;
    gsi_int     nr_attr_names, nr_attr_type_names ;
    gsi_int     item_type ;
    gsi_item*   attr_name_item ;
    gsi_item*   attr_type_name_item ;
    gsi_symbol  symX ;
    int         iX ;
    long        nr_select_cols, isX, jaX ;
    long*       ret_val ;

    if (gsi_type_of(attr_names) != GSI_SEQUENCE_TAG) return NULL ;
    if (gsi_type_of(attr_type_names) != GSI_SEQUENCE_TAG) return NULL ;

    nr_attr_names = gsi_element_count_of(attr_names) ;
    nr_attr_type_names = gsi_element_count_of(attr_type_names) ;
    if (nr_attr_names != nr_attr_type_names) return NULL ;

    attr_name_item = gsi_elements_of(attr_names) ;
    attr_type_name_item = gsi_elements_of(attr_type_names) ;

    for (jaX=0 ; jaX < nr_attr_names; jaX++)
    {
        item_type = gsi_type_of(attr_name_item[jaX]) ;
        if (item_type != GSI_SYMBOL_TAG) return NULL ;
        item_type = gsi_type_of(attr_type_name_item[jaX]) ;
        if (item_type != GSI_SYMBOL_TAG) return NULL ;
    }

    nr_select_cols = genda_ptr->ncols ;
    if (nr_select_cols)
        ret_val = XCALLOC(nr_select_cols, sizeof(gsi_int)) ;
    else
    {
        ret_val = XCALLOC(1, sizeof(gsi_int)) ;
        return ret_val ;
    }
    if (ret_val == NULL) return NULL ;
        

    /* Determine the type of the attribute that will hold */
    /* the value of the select column iX.                 */
    /* -------------------------------------------------- */

    for (isX = 0 ; isX < nr_select_cols ; isX++)
    {
        for (jaX = 0; jaX < nr_attr_names ; jaX++)
        {
            symX = gsi_sym_of(attr_name_item[jaX]) ;
            strX = gsi_symbol_name(symX) ;
            if (!_wcsicmp(genda_ptr->da_col_ptr[isX].col_name, strX))
                break ;
        }

        /* We will use GSI_NULL_TAG as a code for "there is no attribute of   */
        /* the record object to hold values from this column".                */
        /* ------------------------------------------------------------------ */
        if (jaX == nr_attr_names)  /* not found */
            ret_val[isX] = GSI_NULL_TAG ;

        /* We found the attribute used for this column. Determine the data    */
        /* type we will use to send values to this attribute.  If we don't    */
        /* know, set the type to GSI_ITEM_TAG which we will use as a code     */
        /* for "use the default".                                             */
        /* ------------------------------------------------------------------ */
        else
        {
            symX = gsi_sym_of(attr_type_name_item[jaX]) ;
            strX = gsi_symbol_name(symX) ;
            for (iX = 0 ; iX < NR_TRANSLATION_ENTRIES ; iX++)
            {
                if (!_wcsicmp(strX, lup[iX].type_name))
                {
                    ret_val[isX] = lup[iX].cast_type ;
                    break ;
                }
                if (iX == NR_TRANSLATION_ENTRIES)   /* Not found */
                    ret_val[isX] = GSI_ITEM_TAG ;
            }
        }
    }
    return ret_val ;
}


/* ========================================================================== */
/*                                                                            */
/* column_type_name(<column #>, <GENDA pointer>, <names of attributes of      */
/*                   record sequence>, <types of attributes sequence>         */
/*                                                                            */
/* Return the type (as text) of the attribute of the record object that       */
/* should hold the value returned from the specified column number of the     */
/* cursor's SELECT statement.                                                 */
/*                                                                            */
/* ========================================================================== */
GDB_CHAR* column_type_name(long col_num, GENDA* genda_ptr, gsi_item names_item,
                          gsi_item attr_types_item)
{
    gsi_char*   attr_name ;
    gsi_char*   type_name ;
    gsi_int     nr_elements ;
    gsi_item*   attribute_name_item ;
    gsi_item*   attribute_type_name_item ;
    long        iX ;

#if defined(_DEBUG) && defined(WIN32)
    gsi_int     item_type ;
    gsi_int     nr2_els ;

    item_type = gsi_type_of(names_item) ;
    _ASSERTE(item_type == GSI_SEQUENCE_TAG) ;
    item_type = gsi_type_of(attr_types_item) ;
    _ASSERTE(item_type == GSI_SEQUENCE_TAG) ;
#endif

    nr_elements = gsi_element_count_of(names_item) ;
#if defined(_DEBUG) && defined(WIN32)

    nr2_els = gsi_element_count_of(attr_types_item) ;
    _ASSERTE(nr_elements == nr2_els) ;
#endif

    attribute_name_item = gsi_elements_of(names_item) ;
    attribute_type_name_item = gsi_elements_of(attr_types_item) ;

    for (iX = 0 ; iX < nr_elements ; iX++)
    {
        attr_name = gsi_symbol_name(gsi_sym_of(attribute_name_item[iX])) ;
        if (!_wcsicmp(attr_name, genda_ptr->da_col_ptr[col_num].col_name))
            break ;
    }
#if defined(_DEBUG) && defined(WIN32)
    _ASSERTE(iX != nr_elements) ;
#endif
    if (iX == nr_elements) return _T("");
    type_name = gsi_symbol_name(gsi_sym_of(attribute_type_name_item[iX])) ;
    return (GDB_CHAR*)type_name ;
}


/* ==========================================================================
    get_item_values                                                   UTILITY
      - extracts value of attribute
      - args: attrib = any GSI attribute
 *===========================================================================*/
void get_item_values (gsi_attr *attrib)
{
    gsi_item    *item_array ;
    GDB_CHAR     **strval ;
    gsi_symbol  *symval ;
    long        *intval ;
    double      *fltval ;
    gsi_int     vtype ;
    long        j ;
    
    vtype = gsi_type_of(attrib) ;
    
    /* if attrib is an item, print the sub-attrib type */
    if (gsi_element_count_of(attrib) > 0)
    {
        if (!is_simple_value_type(vtype))
        {
            switch (vtype)
            {
            case GSI_INTEGER_ARRAY_TAG:     intval = gsi_int_array_of(attrib) ;
                                            for (j=0; j<gsi_element_count_of(attrib); j++)
                                                printf("\t\t\t(%d) %d\n", j, intval[j]) ;
                                            break ;

            case GSI_SYMBOL_ARRAY_TAG:      symval = gsi_sym_array_of(attrib) ;
	      for (j=0; j<gsi_element_count_of(attrib); j++) {
		wprintf(_T("\t\t\t(%d) %s\n"), j, gsi_symbol_name(symval[j])) ;
	      }
                                            break ;

            case GSI_STRING_ARRAY_TAG:      strval = (GDB_CHAR**)gsi_str_array_of(attrib) ;
	      for (j=0;j<gsi_element_count_of(attrib);j++) {
		wprintf(_T("\t\t\t(%d) %s\n"), j, strval[j]) ;
	      }
                                            break ;

            case GSI_LOGICAL_ARRAY_TAG:     intval = gsi_log_array_of(attrib) ;
                                            for (j=0;j<gsi_element_count_of(attrib);j++)
                                                printf("\t\t\t(%d) %d\n", j, intval[j]) ;
                                            break ;

            case GSI_FLOAT64_ARRAY_TAG:     fltval = gsi_flt_array_of(attrib) ;
                                            for (j=0;j<gsi_element_count_of(attrib);j++)
                                                printf("\t\t\t(%d) %f\n", j, fltval[j]) ;
                                            break ;
                
            case GSI_INTEGER_LIST_TAG:      intval = gsi_int_list_of(attrib) ;
                                            for (j=0;j<gsi_element_count_of(attrib);j++)
                                                printf("\t\t\t(%d) %d\n", j, intval[j]) ;
                                            break ;

            case GSI_SYMBOL_LIST_TAG:       symval = gsi_sym_list_of(attrib) ;
	      for (j=0; j<gsi_element_count_of(attrib); j++) {
		wprintf(_T("\t\t\t(%d) %s\n"), j, gsi_symbol_name(symval[j])) ;
	      }
                                            break ;

            case GSI_STRING_LIST_TAG:       strval = (GDB_CHAR**)gsi_str_list_of(attrib) ;
	      for (j=0;j<gsi_element_count_of(attrib);j++) {
		wprintf(_T("\t\t\t(%d) %s\n"), j, strval[j]) ;
	      }
                                            break ;

            case GSI_LOGICAL_LIST_TAG:      intval = gsi_log_list_of(attrib) ;
                                            for (j=0;j<gsi_element_count_of(attrib);j++)
                                                printf("\t\t\t(%d) %d\n", j, intval[j]) ;
                                            break ;

            case GSI_FLOAT64_LIST_TAG:      fltval = gsi_flt_list_of(attrib) ;
                                            for (j=0;j<gsi_element_count_of(attrib);j++)
                                                printf("\t\t\t(%d) %f\n", j, fltval[j]) ;
                                            break ;

            case GSI_ITEM_ARRAY_TAG:
            case GSI_VALUE_ARRAY_TAG:
            case GSI_ITEM_LIST_TAG:
            case GSI_VALUE_LIST_TAG:        item_array = gsi_elements_of(attrib) ;
	      for (j=0;j<gsi_element_count_of(attrib);j++) {
		wprintf(_T("\t       [%2d]    : (%s)-%d\n"), j, gsi_type_to_string(item_array[j]),
			gsi_element_count_of(item_array[j]));
	      }
	      break;
            }
        }
    }
    
    return ;
}


/*===========================================================================*
    object_dump                                                       UTILITY
 *===========================================================================*/
void object_dump (void* theItem)
{
    printf("\nObject Dump\n") ;
    printf("-----------\n") ;
  
    wprintf(_T("name:    %s\n"), gsi_symbol_name(gsi_name_of(theItem))) ;
    wprintf(_T("type:    %s\n"), gsi_type_to_string(theItem)) ;
    wprintf(_T("class:   %s\n"), gsi_symbol_name(gsi_class_name_of(theItem))) ;

    printf("e-count: %d\n", gsi_element_count_of(theItem)) ;
    printf("a-count: %d\n", gsi_attr_count_of(theItem)) ;
    
    return ;
}


/*===========================================================================*
    gsi_type_to_string                                                UTILITY
 *===========================================================================*/
GDB_CHAR *gsi_type_to_string (gsi_item *theItem)
{
    gsi_int    theType ;
    
    theType = gsi_type_of(theItem) ;
    
    /* unspecified type or object */
    if (theType == GSI_NULL_TAG) 
    {
        if (gsi_symbol_name(gsi_class_name_of(theItem)) != NULL)
            wcsncpy(gsi_type_as_text, gsi_symbol_name(gsi_class_name_of(theItem)), MAX_GSI_CLASS_LEN-1) ;
        else {
            wcsncpy(gsi_type_as_text, _T("UNSPECIFIED"), MAX_GSI_CLASS_LEN-1) ;
	}
    }
    /* all other types */
    else
        wcsncpy(gsi_type_as_text, GSI_TYPES[theType], MAX_GSI_TYPE_LEN-1) ;
    
    return (gsi_type_as_text) ;
}


/*===========================================================================*
    type_of_item                                                      UTILITY
      - checks the type of a gsi_item and either:
          Categorizes it into one of simple, value, list/array, 
          parameter/variable, user object
          Types it to the actual type of the item
      - input:
          + GDB_CATEGORY = return category of type
          + GDB_TYPE = return type of item
 *===========================================================================*/
long type_of_item (gsi_item *theItem, long action)
{
    gsi_int    lngItemType ;
    long       result ;
    
    lngItemType = gsi_type_of(theItem) ;
    
    if (is_simple_value_type(lngItemType) || 
            (!lngItemType && gsi_symbol_name(gsi_class_name_of(theItem)) == NULL))
        result = GDB_SIMPLE_TYPE ;
    else if (is_compound_value_type(lngItemType))
        result = GDB_COMPOUND_TYPE ;
    else if (is_list_type(lngItemType) || is_array_type(lngItemType))
        result = GDB_LIST_OR_ARRAY_TYPE ;
    
    /* unspecified type or object */
    else if (lngItemType == GSI_NULL_TAG) 
    {
        if (gsi_is_item(theItem) && gsi_history_type_of(theItem) != GSI_NULL_TAG)
        {
            result = GDB_PARAM_OR_VAR_TYPE ;
            lngItemType = gsi_history_type_of(theItem) ;
        }
        else if (gsi_is_item(theItem))
            result = GDB_USER_TYPE ;
    }
    
    /* unknown type */
    else
        result = GDB_UNKNOWN_TYPE ;
    
    if (action == GDB_CATEGORY)
        return result ;
    else
        return lngItemType ;
}


long compare_kb_ver (long nver)
{
	long       def_ver = KB_VER;
    long       result ;

	while(def_ver > 10)
	{
		def_ver = def_ver / 10;
	}

	while(nver > 10)
	{
		nver = nver / 10;
	}
	
	if(def_ver == nver)
		result = 1;
	else
		result = 0;

	return result;
}
