#include "g2_odbc_src.h"

//----------------------------------------------------------------------------
namespace G2_ODBC
{
//----------------------------------------------------------------------------
#define LAYER LAYER3

long debug = 0;

ODBCERR          g_sqlca;
gsi_int context_num;
CONTEXT_INFO context[MAX_GDB_CONTEXTS];
SQLHDBC hdbc[MAX_GDB_CONTEXTS];
SQLRETURN           rc;
SQLHENV             henv;
wchar_t             proc_spt[MAX_GDB_CONTEXTS][5] ;
float               driver_version[MAX_GDB_CONTEXTS];
SQLHSTMT            hstmt[MAX_GDB_CONTEXTS][MAX_CURSORS+1];
SQLHSTMT            trig_hstmt[MAX_GDB_CONTEXTS];
long             row_count[MAX_GDB_CONTEXTS]; 

BRIDGE_INFO bridge_info ;

long process_reconnect();


/* ========================================================================== */
/*                                                                            */
/*                  Convert an ASCII string to a wide string.                 */
/*         The caller is responsible for freeing the returned string          */
/*                                                                            */
/* ========================================================================== */
wchar_t*    widen(char *narrow)
{
    long        i, strLen = strlen(narrow) ;
    wchar_t*    retStr = (wchar_t*)calloc(strLen+1, sizeof(wchar_t)) ;

    if (retStr)
    {
        for (i = 0 ; i < strLen ; i++)
            retStr[i] = (wchar_t)narrow[i] ;
        retStr[i] = (wchar_t)0 ;
    }
    return retStr ;
}

gsi_int gsi_current_context()
{
	return 0;
}

long iomsg (long flag, long layer, long write_logfile, long setstat, GENDA *sqlGen,
            long row_reset, wchar_t *argtypes, ...)
{
	return GDB_SUCCESS;
}


/*======================================================================
  set_error
    - if an error condition cannot be set due to insufficient memory, 
      this function will set a basic error message in the global and GENDA
      status structures so that the bridge will finish its current task and 
      notify the user. This funct should not be called by anything but 
      get_stat.

    Arguments:
      - sqlGen: GENDA
  ======================================================================*/
long set_error (GENDA* sqlGen)
{
  context_num = gsi_current_context();

  context[context_num].gbl_status.code   = -1;
  context[context_num].gbl_status.status = -1;  

    if (sqlGen != NULL) 
    {
    sqlGen->genStat.code = context[context_num].gbl_status.code;
    sqlGen->genStat.status = context[context_num].gbl_status.status;
  }

  return 0;
}

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
long load_msg(long severity_cd, long idx, long *msg_code, wchar_t *msg_buff, long action)
{
    wchar_t   prefix_buff[PREFIX_SZ], *wDBTYPE ;
    long      status = FALSE ;

    context_num = gsi_current_context() ;

    *msg_buff = 0 ;
    *msg_code = 0 ;
    prefix_buff[0] = 0 ;
  
    wDBTYPE = widen(DB_TYPE) ;
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
                                wsprintf(prefix_buff, L"G2-%s: %s: %s: ", wDBTYPE, context[context_num].name, ERROR_SYM) ;
                            else
                                wsprintf(prefix_buff, L"G2-%s: %d: %s: ", wDBTYPE, context_num, ERROR_SYM) ;
                            if (action)
                                wsprintf(msg_buff, L"%s%s", prefix_buff, MSG_ERROR[idx]) ;
                            break ;

        case FATAL_CD :
                            if (IN_RANGE(idx, MIN_MSG_ERROR, MAX_MSG_ERROR))
                                *msg_code = -(GDB_MSG_BASE + idx) ;
                            else if (action)
                                status = TRUE ;
    
                            if (context_num >=0 && context[context_num].name != NULL)
                                wsprintf(prefix_buff, L"G2-%s: %s: %s: ", wDBTYPE, context[context_num].name, FATAL_SYM) ;
                            else
                                wsprintf(prefix_buff, L"G2-%s: %d: %s: ", wDBTYPE, context_num, FATAL_SYM) ;
                            if (action)
                                wsprintf(msg_buff, L"%s%s", prefix_buff, MSG_ERROR[idx]) ;
                            break ;

        case WARN_CD :
                            if (IN_RANGE(idx, MIN_MSG_WARN, MAX_MSG_WARN))
                                *msg_code = GDB_MSG_BASE + idx ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                wsprintf(prefix_buff, L"G2-%s: %s: %s: ", wDBTYPE, context[context_num].name, WARN_SYM) ;
                            else
                                wsprintf(prefix_buff, L"G2-%s: %d: %s: ", wDBTYPE, context_num, WARN_SYM) ;
                            if (action)
                                wsprintf(msg_buff, L"%s%s", prefix_buff, MSG_WARN[abs(idx-MIN_MSG_WARN)]) ;
                            break ;
  
        case INFO_CD :
                            if (IN_RANGE(idx, MIN_MSG_INFO, MAX_MSG_INFO))
                                *msg_code = GDB_MSG_BASE + idx ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                wsprintf(prefix_buff, L"G2-%s: %s: %s: ", wDBTYPE, context[context_num].name, INFO_SYM) ;
                            else
                                wsprintf(prefix_buff, L"G2-%s: %d: %s: ", wDBTYPE, context_num, INFO_SYM) ;
                            if (action)
                                wsprintf(msg_buff, L"%s%s", prefix_buff, MSG_INFO[idx]) ;
                            break ;

        case EOCURSOR_CD :
                            if (IN_RANGE(IEOFETC, MIN_MSG_INFO, MAX_MSG_INFO))
                                *msg_code = GDB_MSG_BASE + IEOFETC ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                wsprintf(prefix_buff, L"G2-%s: %s: ", wDBTYPE, context[context_num].name) ;
                            else
                                wsprintf(prefix_buff, L"G2-%s: %d: ", wDBTYPE, context_num) ;
                            if (action)
                                wsprintf(msg_buff, L"%s%s", prefix_buff, MSG_INFO[idx]) ;
                            break ;

        case NOCONNECT_CD :
                            if (IN_RANGE(ENODBCT, MIN_MSG_ERROR, MAX_MSG_ERROR))
                                *msg_code = GDB_MSG_BASE + idx ;
                            else if (action)
                                status = TRUE ;

                            if (context_num >=0 && context[context_num].name != NULL)
                                wsprintf(prefix_buff, L"G2-%s: %s: %s: ", wDBTYPE, context[context_num].name, NOCONNECT_SYM) ;
                            else
                                wsprintf(prefix_buff, L"G2-%s: %d: %s: ", wDBTYPE, context_num, NOCONNECT_SYM) ;
                            if (action)
                                wsprintf(msg_buff, L"%s%s", prefix_buff, MSG_ERROR[idx]) ;
                            break ;

        default:
                            wprintf(L"Invalid message type\n") ;
                            if (wDBTYPE) free(wDBTYPE) ;
                            return 0 ;
    }

    if (wDBTYPE) free(wDBTYPE) ;
    if (status)
    {
        wprintf(L"Invalid message index\n") ;
        return (0) ;
    }
  
    if (!action && !status)
        wcscpy(msg_buff, prefix_buff) ;

    return (wcslen(msg_buff)) ;
}
	

  /*======================================================================
  check_sqlstate_disconnect
    - Determines whether or not one of the current SQLstates from
	  a call to an ODBC function indicates a disconnected state.
	  to the ODBC data source
    
    Arguments:
    - none
	Returns:
	- True if in a disconnected state, False otherwise.
  ======================================================================*/
long check_sqlstate_disconnect( )
{
    short i;
    for (i=0; (i<MAX_ODBC_ERRMSGS) && (g_sqlca.state_array[i].native_errlen!=0); i++) 
    {
        if ( (!wcscmp(g_sqlca.state_array[i].sqlstate, L"08001")) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, L"08003")) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, L"08004")) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, L"08007")) ||
             (!wcscmp(g_sqlca.state_array[i].sqlstate, L"08S01")) )
        return  TRUE  ;
    }
    return( FALSE );
}


long get_stat(GENDA *sqlGen)
{
    wchar_t prefix_msg[DB_TYPE_LEN+MAX_CONTEXT_NAME_LEN+STAT_SYM_LEN+4] ;
    wchar_t text_msg[MAX_ODBC_MSG_LEN+1] ;
    wchar_t ss_msg[10] ;
  long   msg_len  = 0;
  long   warn_len = 0;
  long   prefix_len = 0;
  long   odbc_msg_len = 0;                                    
  long   syb_layer=0;
  long   prev_status;
  long   tmp;
  short  i, numerrs=0, notDSN;

  context_num = gsi_current_context();

    if (context[context_num].gbl_status.msg == NULL) 
    {
        if ((context[context_num].gbl_status.msg = (wchar_t*)calloc(MAX_ODBC_MSG_LEN+1, sizeof(wchar_t))) == NULL) 
        {
            iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"Could NOT alloc mem for gbl_status.msg") ;
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, L"%d", EINSMEM) ;
      set_error(sqlGen);
      return (GDB_ERROR);
    }
  }

  /* initialize messages */
  text_msg[0] = 0;
  prefix_msg[0] = 0;
  // context[context_num].gbl_status.code = g_sqlca.code;
  prev_status = context[context_num].gbl_status.status;

    switch (g_sqlca.code) 
    {    
        case (SQL_SUCCESS):             context[context_num].gbl_status.status = SUCCESS_CD ;
      context[context_num].gbl_status.rows_processed = row_count[context_num];
      context[context_num].gbl_status.code = g_sqlca.code;
      break;
       
        case (SQL_SUCCESS_WITH_INFO):   context[context_num].gbl_status.status = WARN_CD ;
      context[context_num].gbl_status.rows_processed = row_count[context_num];
      context[context_num].gbl_status.code = g_sqlca.code;
      break;

        case (SQL_NO_DATA_FOUND):       context[context_num].gbl_status.status = EOCURSOR_CD ;
      context[context_num].gbl_status.rows_processed = row_count[context_num];
      context[context_num].gbl_status.code = g_sqlca.code;
      break;

    case ( SQL_ERROR ):
        case (SQL_INVALID_HANDLE):      context[context_num].gbl_status.status = ERROR_CD ;
      context[context_num].gbl_status.rows_processed = 0;
	  if ( ! context[context_num].gbl_status.code )
        context[context_num].gbl_status.code = ERROR_CD;
      else
        context[context_num].gbl_status.code = abs(context[context_num].gbl_status.code) * -1; 
      break;
	case (GDB_BIND_ERROR):
		context[context_num].gbl_status.status = ERROR_CD;
		context[context_num].gbl_status.rows_processed = 0;
		if ( ! context[context_num].gbl_status.code )
			context[context_num].gbl_status.code = ERROR_CD;
		else
			context[context_num].gbl_status.code = abs(context[context_num].gbl_status.code) * -1;       
        default:                        break ;
  }

  prefix_len = load_msg(context[context_num].gbl_status.status,0,&tmp,prefix_msg,FALSE);
   
  /* set the message length and the text_msg if there's an error */
    if (g_sqlca.code != 0) 
    {
    msg_len = 0;

    /* loop to add each ODBC error message to the text message */
        for (i=0; (i<MAX_ODBC_ERRMSGS) && (g_sqlca.state_array[i].native_errlen>0); i++) 
        {
      
      /* 
	  ** Set the length of the odbc message to the lesser of the length
      ** of the message and the number of chars left in the text message buffer
      ** so we don't write past the end fo the text message buffer.
      */
            notDSN = wcscmp(L"<dsn>", g_sqlca.state_array[i].sqlstate) ? 1 : 0 ;
        odbc_msg_len = ( MAX_ODBC_MSG_LEN -msg_len -notDSN * SS_LEN -prefix_len -1 < g_sqlca.state_array[i].native_errlen) ?
	                        MAX_ODBC_MSG_LEN -msg_len -notDSN * SS_LEN -prefix_len -1 :
                            g_sqlca.state_array[i].native_errlen;

      /* copy odbc message to the text message */
	  if ( odbc_msg_len > 0 )
      {
        numerrs++;
                if (!wcscmp(L"<dsn>", g_sqlca.state_array[i].sqlstate))
                    swprintf(ss_msg, L"%s", !i?L"":L"; ") ;
        else
                    swprintf(ss_msg, L"%sss=%5s ", !i?L"":L"; ", g_sqlca.state_array[i].sqlstate) ;
        if (i==0)
                    wcsncpy(text_msg, ss_msg, SS_LEN+1) ;
        else
                    wcsncat(text_msg, ss_msg, SS_LEN+3) ;

                wcsncat(text_msg, g_sqlca.state_array[i].native_errmsg, odbc_msg_len) ;
        msg_len += notDSN*SS_LEN + odbc_msg_len + (i?2:0);
        text_msg[msg_len] = 0;
      }
            else 
            {
        /* stop when the length of errmsg is 0 */
        break;
      }
	  if ( g_sqlca.state_array[0].native_errcode ) 
        context[context_num].gbl_status.code = abs(g_sqlca.state_array[0].native_errcode) * -1; 
    
	} /* end for loop */
    
    text_msg[msg_len] = 0;

    if (!text_msg[0]) 
      msg_len = 0;
  }
  /*
  ** This next if statement is a Kludge!
  ** Change the gbl_status msg to the text_msg just generated if one
  ** or more of the following are true:	(otherwise leave it alone)
  ** 1) there are ODBC error messages
  ** 2) the current status indicates success
  ** 3) the previous status was success
  */
  if ( (msg_len) ||
       (context[context_num].gbl_status.status >= SUCCESS_CD) ||
        (prev_status >= SUCCESS_CD) ) 
    {
    context[context_num].gbl_status.msg[0] = 0;
    /* concat prefix and message body */
        swprintf(context[context_num].gbl_status.msg, L"%s%s", prefix_msg, text_msg) ;
  }

  /* load the GENDA struct */
    if (sqlGen != NULL) 
    {
        msg_len = wcslen(context[context_num].gbl_status.msg) ;

    if ( sqlGen->more_rows >= sqlGen->nrows )
      sqlGen->more_rows = 0;

        if (sqlGen->genStat.msg == NULL) 
        {
            if ((sqlGen->genStat.msg = (wchar_t*)calloc(msg_len+1, sizeof(wchar_t))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"Could NOT alloc mem for genStat.msg") ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, L"%d", EINSMEM) ;
        set_error(sqlGen);
        return (GDB_ERROR);
      }
    }
        else 
        {
            if ((sqlGen->genStat.msg = (wchar_t*)realloc(sqlGen->genStat.msg, (msg_len+1)*sizeof(wchar_t))) == NULL) 
            {
                iomsg(DBG6|DBG9, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"Could NOT realloc mem for genStat.msg") ;
                iomsg(DBGM, LAYER, TRUE, TRUE, NULL, FALSE, L"%d", EINMEMR) ;
        set_error(sqlGen);
        return (GDB_ERROR);
      }
    }
	if( g_sqlca.code == GDB_BIND_ERROR )
	{
		msg_len = wcslen(GDB_BIND_ERROR_MSG) + 1;
		sqlGen->genStat.msg = (wchar_t *)realloc(sqlGen->genStat.msg,(msg_len+1)*sizeof(wchar_t));
		wcsncpy(sqlGen->genStat.msg,GDB_BIND_ERROR_MSG, msg_len);
		iomsg(DBG3,LAYER,TRUE,FALSE,NULL,FALSE, L"%s", sqlGen->genStat.msg);
	}
	else
		wcsncpy(sqlGen->genStat.msg, context[context_num].gbl_status.msg, msg_len);
    wcsncpy(sqlGen->genStat.msg, context[context_num].gbl_status.msg, msg_len);
    sqlGen->genStat.msg[msg_len] = 0;
    sqlGen->genStat.code = context[context_num].gbl_status.code;
    sqlGen->genStat.rows_processed = context[context_num].gbl_status.rows_processed;
    sqlGen->genStat.status = context[context_num].gbl_status.status;
  }

  /* Check for a disconnected state and reconnect if necessary */
  if ( (check_sqlstate_disconnect() ) ||
        (abs(context[context_num].gbl_status.code) == (GDB_MSG_BASE + ENODBCT)) ) 
    {
    context[context_num].connected_to_db = FALSE;
    context[context_num].gbl_status.status = NOCONNECT_CD;
    process_reconnect();
  }

  /*** reset certain g_sqlca fields to NULL ***/
  g_sqlca.code = SQL_SUCCESS;
    wcscpy(g_sqlca.state_array[0].native_errmsg, L"") ;
  g_sqlca.state_array[0].native_errlen = 0;
  g_sqlca.state_array[0].native_errcode = 0;

    if ((debug & DBG5) && context[context_num].gbl_status.status != SUCCESS_CD) 
    { 
    printf("\nSQL Message Structure\n");
    printf("ver   : %s\n",bridge_info.bridge_version );
    printf("code  : %d\n",context[context_num].gbl_status.code);
    printf("msg   : %s\n",context[context_num].gbl_status.msg);
    printf("nrows : %d\n",context[context_num].gbl_status.rows_processed);
    printf("stat  : %d\n",context[context_num].gbl_status.status);
  }

  if ( context[context_num].gbl_status.status != SUCCESS_CD && 
       context[context_num].gbl_status.status != EOCURSOR_CD ) 
    return (GDB_ERROR);

  return (GDB_SUCCESS);
}
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef SUPPORT_GSI_CONNECTION_STR
#define SUPPORT_GSI_CONNECTION_STR
#endif

  /*======================================================================
    load_odbc_err
      - This function is called whenever an ODBC function is called.
      - It repeatedly calls SQLError until no more error msgs are returned.
      - It loads error information into the g_sqlca structure which is used
        later by the function 'get_stat'
  
      Arguments:
        - l_henv:  environment handle
        - l_hdbc:  database connection handle
        - l_hstmt: database statement handle
        - rc:      return code from the ODBC function
      
    ======================================================================*/
/*   void load_odbc_err( l_henv, l_hdbc, l_hstmt, l_rc )
      HENV        l_henv;
      HDBC        l_hdbc;
      HSTMT       l_hstmt;
      RETCODE     l_rc;*/
void load_odbc_err(HENV l_henv, HDBC l_hdbc, HSTMT l_hstmt, RETCODE l_rc )
  {
      RETCODE     lo_rc;
      register short i;
  
      g_sqlca.state_array[0].native_errlen = 0;
      g_sqlca.state_array[0].native_errmsg[0] = '\0';
      g_sqlca.code = l_rc;
  
      /* Only get error info for non-sucessful ODBC calls */
      if ( g_sqlca.code != SQL_SUCCESS )
      {
        lo_rc = SQL_SUCCESS;
        for (i=0; (i<MAX_ODBC_ERRMSGS) && (lo_rc==SQL_SUCCESS); i++) 
        {
          lo_rc = SQLError( l_henv,
                            l_hdbc,
                            l_hstmt,
                            g_sqlca.state_array[i].sqlstate,
                            (long*)&g_sqlca.state_array[i].native_errcode,
                            g_sqlca.state_array[i].native_errmsg,
                            MAX_NATIVE_ERRLEN,
                            (short*)&g_sqlca.state_array[i].native_errlen );
                   
          if ((lo_rc == SQL_SUCCESS) && (debug & DBG1)) 
          {
            printf("ODBC Error: ");
            printf("sqlstate = '%s'\n", g_sqlca.state_array[i].sqlstate);
            printf("native errcode= %ld\n", g_sqlca.state_array[i].native_errcode);
            printf("native_errmsg = '%s'\n", g_sqlca.state_array[i].native_errmsg);
            printf("native_errlen = '%d'\n", g_sqlca.state_array[i].native_errlen);
          }
          else if (lo_rc != SQL_SUCCESS) 
          {
            g_sqlca.state_array[i].native_errlen = 0;
            g_sqlca.state_array[i].native_errcode = 0;
            break;
          }
          else 
          {
            ; /* just continue */
          }
        }       
      } /* end if ( l_rc != SQL_SUCCESS ) */
  
  }

   
   /*======================================================================
    display_odbc_info
      - queries the ODBC driver manager about the driver and displays results
      
      Arguments:
      - none
    ======================================================================*/
  void display_odbc_info()
  {
      SQLINTEGER    ilen;
      SQLSMALLINT   slen;
      SQLUINTEGER   auto_commit=0;
      SQLUSMALLINT  txn_capable=0;
      UWORD         api_conf, sql_conf ;
      wchar_t       dbms_name[100], dbms_ver[100] ;
      wchar_t       driver_name[100], driver_ver[12], driver_mngr_ver[12] ;
      wchar_t       driver_odbc_ver[6] ;
      wchar_t       ds_name[100] ;
      wchar_t       ds_readonly[2] ;
  
      /* Driver manager */
      SQLGetInfo( hdbc[context_num], SQL_ODBC_VER, driver_mngr_ver, sizeof(driver_mngr_ver), &slen );
  
      /* Driver name and version and which version of ODBC it supports */
      SQLGetInfo( hdbc[context_num], SQL_DRIVER_NAME, driver_name, sizeof(driver_name), &slen );
      SQLGetInfo( hdbc[context_num], SQL_DRIVER_VER, driver_ver, sizeof(driver_ver), &slen );
      SQLGetInfo( hdbc[context_num], SQL_DRIVER_ODBC_VER, driver_odbc_ver, sizeof(driver_odbc_ver), &slen );
  
      /* Database name and version */
      rc = SQLGetInfo( hdbc[context_num], SQL_DBMS_NAME, dbms_name, sizeof(dbms_name), &slen );
      rc = SQLGetInfo( hdbc[context_num], SQL_DBMS_VER, dbms_ver, sizeof(dbms_ver), &slen );
  
      /* Data source name and readonly flag */ 
      rc = SQLGetInfo( hdbc[context_num], SQL_DATA_SOURCE_NAME, ds_name, sizeof(ds_name), &slen );
      rc = SQLGetInfo( hdbc[context_num], SQL_DATA_SOURCE_READ_ONLY, ds_readonly, sizeof(ds_readonly), &slen );
  
      /* Conformance levels */
      SQLGetInfo( hdbc[context_num], SQL_ODBC_API_CONFORMANCE, &api_conf, sizeof(api_conf), &slen );
      SQLGetInfo( hdbc[context_num], SQL_ODBC_SQL_CONFORMANCE, &sql_conf, sizeof(sql_conf), &slen );
  
      wprintf(L"ODBC Info:\n" ) ;
      wprintf(L"    ODBC Driver Manager Version: %s\n", driver_mngr_ver ) ;
      wprintf(L"    ODBC Driver: %s  Version: %s\n", driver_name, driver_ver ) ;
      wprintf(L"    Driver supports ODBC Version: %s\n", driver_odbc_ver ) ;
      wprintf(L"    DBMS: %s  Version: %s\n", dbms_name, dbms_ver ) ;
      wprintf(L"    Data Source Name : %s\n", ds_name ) ;
      wprintf(L"    Data Source Read Only? : %s\n", ds_readonly ) ;
      wprintf(L"    Supports procedures? : %s\n", proc_spt[context_num]) ;
   
      wprintf(L"    ODBC Conformance Level: " ) ;
      if ( api_conf == SQL_OAC_NONE )
        wprintf(L"None\n") ;
      else if ( api_conf == SQL_OAC_LEVEL1 )
        wprintf(L"1\n") ;
      else if ( api_conf == SQL_OAC_LEVEL2 )
        wprintf(L"2\n") ;
      else
        wprintf(L"Unknown: (%d)\n", api_conf) ;
  
      wprintf(L"    SQL grammar support level: ") ;
      if ( sql_conf == SQL_OSC_MINIMUM )
        wprintf(L"Minimum\n") ;
      else if ( sql_conf == SQL_OSC_CORE )
        wprintf(L"Core\n") ;
      else if ( sql_conf == SQL_OSC_EXTENDED )
        wprintf(L"Extended\n") ;
      else
        wprintf(L"Unknown: (%d)\n", sql_conf) ;
  
      /*
      ** Determine if the ODBC driver is capable of transactions and
      ** whether or not auto-commit is on
      */
      rc = SQLGetInfo( hdbc[context_num], SQL_TXN_CAPABLE, &txn_capable, 
                       sizeof(txn_capable), NULL );
      wprintf(L"    Transactions supported? : " ) ;
      if ( txn_capable > SQL_TC_NONE ) 
          wprintf(L"Yes\n" ) ;
      else
          wprintf(L"No\n" ) ;
  
      rc = SQLGetConnectAttr( hdbc[context_num], SQL_ATTR_AUTOCOMMIT, &auto_commit,
                              (SQLINTEGER)NULL, &ilen );
      wprintf(L"    Auto-commit : " ) ;
      if ( auto_commit == SQL_AUTOCOMMIT_OFF ) 
          wprintf(L"OFF\n") ;
      else 
          wprintf(L"ON\n") ;
  }
                 

 /*======================================================================
  sql_set_connection_options
    - applies options to connection before opening one
    Arguments:
    - context_num:   context number
  ======================================================================*/
long sql_set_connection_options( gsi_int context_num )
{
    /* Apply Windows integrated security for authenticating connection flag */

    long isec = context[context_num].integrated_security ;
    BOOL ok = FALSE ;

    rc = SQLSetConnectAttr(hdbc[context_num], SQL_COPT_SS_INTEGRATED_SECURITY, (SQLPOINTER)isec, 0) ;
    ok = SQL_SUCCEEDED(rc) ;
    	
    if (!ok)
    {
        load_odbc_err(henv, hdbc[context_num], SQL_NULL_HSTMT, rc) ;
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", ESCONAT) ;
    } else if (context[context_num].console_output)
    {
	wprintf(L"Config OK   : INTEGRATED_SECURITY set to: %s\n", WSBOOLEAN(isec == SQL_IS_ON)) ;
    }

    return ok ? GDB_SUCCESS : GDB_ERROR ;
}

/*======================================================================
  sql_setup
    - establish mapping and initial setup to esql variables and 
      structures used by all layers.
    - allocate the environment handle used by all ODBC functions
  ======================================================================*/
long sql_setup()
{
    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"SQL_SETUP") ;

    /* 
    ** Allocate the environment handle. 
    ** This is only done once in the program 
    */
    if (henv == NULL) 
    {
      if ( (rc = SQLAllocHandle( SQL_HANDLE_ENV,
                                 SQL_NULL_HANDLE,
                                   &henv )) != SQL_SUCCESS ) 
        {
        /* A memory allocation error */
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
            return GDB_ERROR ;
      }

      /* Set environment for ODBC Version 3.0 */
      if ( (rc = SQLSetEnvAttr( henv, SQL_ATTR_ODBC_VERSION, 
                                 (SQLPOINTER)SQL_OV_ODBC3, 0) ) != SQL_SUCCESS ) 
        {
        /* Warning message */
            iomsg( DBG4, LAYER, TRUE, FALSE, NULL, FALSE, L"%s",
               "Cannot set environment to ODBC Version 3" );
            return GDB_ERROR ;
      }
    }
    return GDB_SUCCESS ;
}

/*======================================================================
  sql_connect  (1)
    - establish connection to database
    Arguments:
    - db_user:   database username
    - db_pass:   database password
    - db_server: DSN data source name in the ODBC driver manager
  ======================================================================*/
long sql_connect(wchar_t* db_user, wchar_t* db_pass, wchar_t* db_dsn )
{
    register short    i;
    wchar_t         *odbc_dsn ;
    wchar_t         *odbc_user ;
    wchar_t         *odbc_pass ;
    wchar_t         driver_odbc_ver[6] ;
    char            narrow_driver_odbc_ver[6] ;
    SWORD           length;
    BOOL            new_con;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"SQL_CONNECT") ;

    /* Make sure user, password, dsn are there */
    if (db_user == NULL) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", ENOUSER) ;
        return GDB_ERROR ;
    }
    if (db_pass == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", ENOPASS) ;
        return GDB_ERROR ;
    }
    if (db_dsn == NULL)
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", ENOCONS) ;
        return GDB_ERROR ;
    }

    /*
    ** Allocate a new connection handle if it has not already been used.
    ** Otherwise, re-use the one already allocated
    */
    new_con = !hdbc[context_num];

    if (new_con)
    {
        rc = SQLAllocHandle( SQL_HANDLE_DBC, henv, &hdbc[context_num] );
        if (!SQL_SUCCEEDED(rc)) 
        {
            load_odbc_err( henv, SQL_NULL_HDBC, SQL_NULL_HSTMT, rc );
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
            return GDB_ERROR  ;
        }
    }

    if (!new_con || context[context_num].integrated_security != SQL_IS_DEFAULT)
    	 sql_set_connection_options(context_num) ;
    
    /* Allocate memory for data source name, user, password */     
    if ((odbc_dsn = (wchar_t*)calloc(wcslen(db_dsn)+1, sizeof(wchar_t))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_dsn, db_dsn) ;

    if ((odbc_user = (wchar_t*)calloc(wcslen(db_user)+1, sizeof(wchar_t))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
        free(odbc_dsn) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_user, db_user) ;

    if ((odbc_pass = (wchar_t*)calloc(wcslen(db_pass)+1, sizeof(wchar_t))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
        free(odbc_dsn) ;
        free(odbc_user) ;
        return GDB_ERROR ;
    }
    wcscpy(odbc_pass, db_pass) ;
    
    /* Connect to the ODBC data source name */
    rc = SQLConnect( hdbc[context_num],
                     odbc_dsn, SQL_NTS,
                     odbc_user, SQL_NTS,
                     odbc_pass, SQL_NTS );

    if (!SQL_SUCCEEDED(rc))
    {
      load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
      /* check for already connected */
        if (!wcscmp(g_sqlca.state_array[0].sqlstate, DB_ALREADY_CONNECTED))
        {
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", IDBCONA) ;
            free(odbc_dsn) ;
            free(odbc_user) ;
            free(odbc_pass) ;
            return GDB_SUCCESS ;
      }
        else
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EBADCON) ;
            free(odbc_dsn) ;
            free(odbc_user) ;
            free(odbc_pass) ;
            return GDB_ERROR  ;
      }
    }

    iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", IDBCONE) ;
  
    /* Determine if stored procedures are supported */  
    SQLGetInfo( hdbc[context_num],
                SQL_PROCEDURES,
                proc_spt[context_num],
                5,
                &length );

    /* Determine the ODBC driver version */
    SQLGetInfo( hdbc[context_num], 
                SQL_DRIVER_ODBC_VER, 
                driver_odbc_ver, 
                sizeof(driver_odbc_ver), 
                &length );
    for (i = 0 ; i < 6 ; i++)
        narrow_driver_odbc_ver[i] = (char)driver_odbc_ver[i] ;
    driver_version[context_num] = (float)atof(narrow_driver_odbc_ver) ;

    /*
    ** Auto-commit is the default for ODBC drivers. But the default
    ** for the bridge is no auto-commit. So if the user wants no
    ** auto-commit, set the connection for that behaviour.
    */
    if (context[context_num].auto_commit == FALSE)
    {
        rc = SQLSetConnectAttr( hdbc[context_num], 
                                SQL_ATTR_AUTOCOMMIT, 
                                SQL_AUTOCOMMIT_OFF, 
                                0 );
        if (!SQL_SUCCEEDED(rc)) 
            load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    }

    /* 
    ** Connection is made.
    ** Set the elements of the HSTMT array for the current context to NULL
    ** and set the triggers statement handle to NULL
    */
    for (i=1; i<MAX_CURSORS+1; i++)
      hstmt[context_num][i] = NULL;
    
    trig_hstmt[context_num] = NULL;

    /* Now display info about ODBC driver and data source */
    if (debug & DBG2)
      display_odbc_info();

    /* free memory and return */
    free(odbc_dsn) ;
    free(odbc_user) ;
    free(odbc_pass) ;

    return GDB_SUCCESS  ;
}


/*{{{ connect database using connection string. added for project 28544 Gensym-2012 */
/*======================================================================
  sql_connect  (2)
    - establish connection to database
    Arguments:
    - gsi_connection_str	: database connection string
  ======================================================================*/
long sql_connect_ex(wchar_t* gsi_connection_str)
{
    register short    i;
    wchar_t         *db_connection_str ;
    wchar_t         driver_odbc_ver[6] ;
    char            narrow_driver_odbc_ver[6] ;
    SWORD           length;
    BOOL            new_con;
	wchar_t			conn_str_out[1024];
	SQLSMALLINT		conn_str_out_len;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"SQL_CONNECT") ;

    /* parameter check. actually, this function will not be invoked if no gsi_connection_str provided */
    if ((gsi_connection_str == NULL) || (*gsi_connection_str == 0))
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", ENOCONS) ;
        return GDB_ERROR ;
    }

    /*
    ** Allocate a new connection handle if it has not already been used.
    ** Otherwise, re-use the one already allocated
    */
    new_con = !hdbc[context_num];

    if (new_con)
    {
        rc = SQLAllocHandle( SQL_HANDLE_DBC, henv, &hdbc[context_num] );
        if (!SQL_SUCCEEDED(rc)) 
        {
            load_odbc_err( henv, SQL_NULL_HDBC, SQL_NULL_HSTMT, rc );
            iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
            return GDB_ERROR  ;
        }
    }

    if (!new_con || context[context_num].integrated_security != SQL_IS_DEFAULT)
    	 sql_set_connection_options(context_num) ;
    
    /* Allocate memory for database connection string */     
    if ((db_connection_str = (wchar_t*)calloc(wcslen(gsi_connection_str)+1, sizeof(wchar_t))) == NULL)
    {
        iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
        return GDB_ERROR ;
    }
    wcscpy(db_connection_str, gsi_connection_str) ;
    
    /* Connect to the database */
	rc = SQLDriverConnect(hdbc[context_num],
						  NULL,
						  db_connection_str,
						  SQL_NTS,
						  conn_str_out,
						  sizeof (conn_str_out) / sizeof (wchar_t),
						  &conn_str_out_len,
						  SQL_DRIVER_NOPROMPT);


    if (!SQL_SUCCEEDED(rc))
    {
      load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
      /* check for already connected */
        if (!wcscmp(g_sqlca.state_array[0].sqlstate, DB_ALREADY_CONNECTED))
        {
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", IDBCONA) ;
			free(db_connection_str);
            return GDB_SUCCESS ;
      }
        else
        {
            iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EBADCON) ;
			free(db_connection_str);
            return GDB_ERROR  ;
      }
    }

    iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", IDBCONE) ;
  
    /* Determine if stored procedures are supported */  
    SQLGetInfo( hdbc[context_num],
                SQL_PROCEDURES,
                proc_spt[context_num],
                5,
                &length );

    /* Determine the ODBC driver version */
    SQLGetInfo( hdbc[context_num], 
                SQL_DRIVER_ODBC_VER, 
                driver_odbc_ver, 
                sizeof(driver_odbc_ver), 
                &length );
    for (i = 0 ; i < 6 ; i++)
        narrow_driver_odbc_ver[i] = (char)driver_odbc_ver[i] ;
    driver_version[context_num] = (float)atof(narrow_driver_odbc_ver) ;

    /*
    ** Auto-commit is the default for ODBC drivers. But the default
    ** for the bridge is no auto-commit. So if the user wants no
    ** auto-commit, set the connection for that behaviour.
    */
    if (context[context_num].auto_commit == FALSE)
    {
        rc = SQLSetConnectAttr( hdbc[context_num], 
                                SQL_ATTR_AUTOCOMMIT, 
                                SQL_AUTOCOMMIT_OFF, 
                                0 );
        if (!SQL_SUCCEEDED(rc)) 
            load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
    }

    /* 
    ** Connection is made.
    ** Set the elements of the HSTMT array for the current context to NULL
    ** and set the triggers statement handle to NULL
    */
    for (i=1; i<MAX_CURSORS+1; i++)
      hstmt[context_num][i] = NULL;
    
    trig_hstmt[context_num] = NULL;

    /* Now display info about ODBC driver and data source */
    if (debug & DBG2)
      display_odbc_info();

    /* free memory and return */
	free(db_connection_str);

    return GDB_SUCCESS  ;
}
/*}}}*/


/*======================================================================
  sql_disconnect
    - disconnect from the database
    - only free the connection handle if there was no connection initially
  ======================================================================*/

long sql_disconnect(gsi_int context_num)
{
    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg (DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"SQL_DISCONNECT") ;

    /* If the connection handle is null, send message that you are not connected */
    if (hdbc[context_num] == NULL) 
    {
        iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, L"%s", L"Database is already disconnected.") ;
        return GDB_SUCCESS ;
    }

    /* rollback any active transaction if auto-commit is OFF */
    if ( ! context[context_num].auto_commit )
      rc = SQLEndTran( SQL_HANDLE_DBC, hdbc[context_num], SQL_ROLLBACK );
    
    /* free the statement handle for triggers if they are being used */
    if (trig_hstmt[context_num]) 
    {
      rc = SQLFreeHandle( SQL_HANDLE_STMT, trig_hstmt[context_num] );
      trig_hstmt[context_num] = NULL;
    }
    /*
    ** NOTE: 
    ** Before disconnecting from the data source all hstmts associated
    ** with the connection should be freed.  However, upon a disconnect
    ** the odbc driver automatically frees those hstmts.
    ** Therefore, we will not call SQLFreeHandle here.
    */

    /* Disconnect from the data source */
    rc = SQLDisconnect( hdbc[context_num] );

    if (rc < SQL_SUCCESS) 
    {
        /* 
        ** If the disconnect fails it means there is something wrong
        ** with the connection or we are not connected.  Set the connection
        ** handle to NULL which will make sure that we get a new one the next time we
        ** try to connect.  This should eliminate "stale" connection handles.
        ** (Stale conections can occur if a database goes down and then back up again
        **  while the interface object is connected)
        */
        hdbc[context_num] = NULL;
    }
    else 
    {
        rc = SQLFreeHandle( SQL_HANDLE_DBC, hdbc[context_num] );
        load_odbc_err( henv, hdbc[context_num], SQL_NULL_HSTMT, rc );
        hdbc[context_num] = NULL;
    }

    return (rc < SQL_SUCCESS ? GDB_EXT_ERROR : GDB_SUCCESS);
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
 long process_connect(wchar_t *db_user, wchar_t *db_pass, wchar_t *c_str, wchar_t *gsi_connection_str )/* add gsi-connection-string. modified for project 28544 Gensym-2012 */
 {
     wchar_t    *tuser, *tpass, *tcstr, *tgsiconnstr ; /* add tgsiconnstr. for project 28544 Gensym-2012 */
     wchar_t*   wDBTYPE = NULL ;    
     
     context_num = gsi_current_context() ;
     
     if (debug & DBG1)
         iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"PROCESS_CONNECT") ;
     
	 /*{{{ if gsi_connection_str supplied, then use it to connect db. for project 28544 Gensym-2012 */
#ifdef SUPPORT_GSI_CONNECTION_STR
	 if ((gsi_connection_str != NULL) && (*gsi_connection_str != 0))
	 {
		 if (sql_connect_ex(gsi_connection_str))
		 {
			 get_stat(NULL) ;
			 iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", context[context_num].gbl_status.msg) ;
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
			 iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", ENOCONS) ;
		 return GDB_ERROR ;
	 }
     
     /*** sub the username USER if no username provided (for display only) ***/
     wDBTYPE = widen(DB_TYPE) ;
     if (!db_user[0])  
         iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, L"%s%s", L"'USER' Attempting % database connection via:", wDBTYPE) ;
     else
         iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, L"%s%s%s", L"'%' Attempting % database connection via:", db_user, wDBTYPE) ;
     if (wDBTYPE) free(wDBTYPE) ;
     
     iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", c_str) ;
     
     if (sql_connect(db_user, db_pass, c_str))
     {
         get_stat(NULL) ;
         iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", context[context_num].gbl_status.msg) ;
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
         
         tuser = (wchar_t *)XCALLOC(wcslen(db_user)+1, sizeof(wchar_t)) ;
         tpass = (wchar_t *)XCALLOC(wcslen(db_pass)+1, sizeof(wchar_t)) ;
         tcstr = (wchar_t *)XCALLOC(wcslen(c_str)+1,  sizeof(wchar_t)) ;
		 tgsiconnstr = (wchar_t *)XCALLOC(wcslen(gsi_connection_str)+1,  sizeof(wchar_t)) ; /* tgsiconnstr. for project 28544 Gensym-2012 */
         if (tuser == NULL || tpass == NULL || tcstr == NULL || tgsiconnstr == NULL) /* tgsiconnstr. for project 28544 Gensym-2012 */
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
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
         if ((context[context_num].db_connect_info.username = (wchar_t *)XCALLOC(wcslen(tuser)+1, sizeof(wchar_t))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
             return GDB_SUCCESS ;
         }
         if (context[context_num].db_connect_info.password != NULL)
         {
             XFREE(context[context_num].db_connect_info.password) ;
             context[context_num].db_connect_info.password = NULL ;
         }
         if ((context[context_num].db_connect_info.password = (wchar_t*)XCALLOC(wcslen(tpass)+1, sizeof(wchar_t))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
             XFREE(context[context_num].db_connect_info.username) ;
             return GDB_SUCCESS ;
         }
         if (context[context_num].db_connect_info.connection != NULL)
         {
             XFREE(context[context_num].db_connect_info.connection) ;
             context[context_num].db_connect_info.connection = NULL ;
         }
         if ((context[context_num].db_connect_info.connection = (wchar_t *)XCALLOC(wcslen(tcstr)+1, sizeof(wchar_t))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
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
         if ((context[context_num].db_connect_info.gsi_connection_str = (wchar_t *)XCALLOC(wcslen(tgsiconnstr)+1, sizeof(wchar_t))) == NULL)
         {
             iomsg(DBGM, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", EINSMEM) ;
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
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"PROCESS_RECONNECT") ;
    
    /* db_reconnecting eliminates the possibility of recursive process_
    reconnect calls (infinite loop) */
    
    iomsg(DBG2, LAYER, TRUE, FALSE, NULL, FALSE, L"%d", IADBREC) ;
    
    sql_disconnect(context_num) ; /* bug HQ-4203852 */
    
    context[context_num].db_reconnecting = TRUE ;
    status = process_connect(context[context_num].db_connect_info.username,
                    context[context_num].db_connect_info.password,
                    context[context_num].db_connect_info.connection,
					context[context_num].db_connect_info.gsi_connection_str) ; /* add gsi-connection-string. for project 28544 Gensym-2012 */
    
    context[context_num].db_reconnecting = FALSE ;
    
    if (!status)
        iomsg(DBG4, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", WDBRECN) ;
    
    /* change status of INFO_CD to SUCCESS_CD for reconnect only */
    if (context[context_num].gbl_status.status == INFO_CD)
        context[context_num].gbl_status.status = SUCCESS_CD ;
    
    return (GDB_SUCCESS) ;
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
        iomsg(DBG1, -LAYER, TRUE, FALSE, NULL, FALSE, L"%s", L"PROCESS_DISCONNECT") ;
    
    if (!context[context_num].available) 
    {
        iomsg(DBG3, LAYER, TRUE, TRUE, NULL, TRUE, L"%d", ECONUNA) ;
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
        iomsg(DBG3, LAYER, TRUE, FALSE, NULL, FALSE, L"%s", context[context_num].gbl_status.msg) ;
        return GDB_ERROR ;
    }
    else 
    {
        if (context[context_num].name != NULL)
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, L"%d%d%s", IDBDISC, context_num, context[context_num].name) ;
        else
            iomsg(DBG2, LAYER, TRUE, TRUE, NULL, TRUE, L"%d%d%s", IDBDISC, context_num, L"") ;
    }
    
    /* change status of INFO_CD to SUCCESS_CD for disconnect only */
    if (context[context_num].gbl_status.status == INFO_CD)
        context[context_num].gbl_status.status = SUCCESS_CD ;
    
    return (GDB_SUCCESS) ;
}
//----------------------------------------------------------------------------
} // G2_ODBC
//----------------------------------------------------------------------------