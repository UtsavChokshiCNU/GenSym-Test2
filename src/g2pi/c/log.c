#include <winsock2.h>
#include <stdio.h>
#include <sys/stat.h>
#include "gsi_main.h"
#include "gsi_pi_utils.h"
#include "log.h"
#include "osipi.h"
#include "osipi_bridge.h"

FILE    *pLog = NULL ;
char    *LogFileName = "g2pi.log" ;
int     fNewLog = FALSE ;
short   fwf = FALSE ;
short   ofb = APPEND ; /* "open file" behavior */
long    maxLogSize = 0 ;
long    curLFLen = 0 ;

int     defLogLev = 2, 
        defScreenLog = TRUE, 
        defFileLog = FALSE,
        defMsgBdLog = FALSE , 
        defG2ProcLog = TRUE, 
        defPILog = FALSE ;



/* ========================================================================== */
/*                                                                            */
/* The central logging function.  Every request for logging passes through    */
/* this function.  If the number associated with the message is lower than    */
/* the logging level for the current context, the message will be logged to   */
/* the screen, a file, the PI log, the G2 message board, and/or a G2          */
/* procedure, depending upon the settings of logging flags for this context.  */
/*                                                                            */
/* ========================================================================== */
void logMsg(int msgLev, char *intro, int tsf, int srvNr, long piptnr, char *msg, long code)
{
    char            *msg2log, scratch[20] ;
    size_t          len ;
    gsi_int         iContext = gsi_current_context() ;
    CtxCfg          *pCtrl ;


    if (iContext < 0 || iContext > MAXCONTEXTS)
        iContext = MAXCONTEXTS ;
    pCtrl = &CtxCfgs[iContext] ;

    /* Every message to be logged has an associated level number.  The */
    /* message will only be logged if the current process level is     */
    /* greater than or equal to the attached level number              */
    /* --------------------------------------------------------------- */
    if (msgLev > pCtrl->log_level)
        return ;

    /* Construct the message to log */
    /* ---------------------------- */
    if (intro == NULL && tsf == FALSE && srvNr < 0 && piptnr <= 0 && code == 0)
        msg2log = msg ;
    else
    {
        if (intro == NULL)
            len = 0;
        else
            len = strlen(intro) ;
        len += MAXNOWLEN + strlen(msg) + 50 ;
        if (srvNr >= 0 && srvNr < gNrServers)
            len += strlen(gServer[srvNr].srvrName) + 1 ;
        msg2log = malloc(len) ;
        if (msg2log == NULL)
            msg2log = msg ;
        else
        {
            msg2log[0] = '\0' ;
            if (intro != NULL) strcpy(msg2log, intro) ;
            if (tsf)
            {
                strcat(msg2log, NOW) ;
                strcat(msg2log, " : ") ;
            }
            if (srvNr >= 0 && srvNr < gNrServers)
            {
                strcat(msg2log, gServer[srvNr].srvrName) ;
                strcat(msg2log, " ") ;
            }
            if (piptnr > 0)
            {
                sprintf(scratch,"# %ld : ", piptnr) ;
                strcat(msg2log, scratch) ;
            }
            strcat(msg2log, msg) ;
            if (code != 0)
            {
                sprintf(scratch, " (%ld)", code) ;
                strcat(msg2log, scratch) ;
            }
        }
    }


    /* A message can be directed to any combination of the screen, */
    /* a log file, PI's log file, the G2 message board, and the G2 */
    /* procedure OSI-ERROR.                                        */
    /* ----------------------------------------------------------- */
    if (pCtrl->log_to_screen)
        fprintf(stderr, "%s\n", msg2log) ;
    if (pCtrl->log_to_pi)
        pilg_putoutput(msg2log, MSGLOG) ;
    if (pCtrl->log_to_file)
        WriteToLogFile(msg2log) ;
    if (iContext >= 0 && iContext < MAXCONTEXTS && CtxCfgs[iContext].alive)
    {
        if (deReging)
            gsi_set_option(GSI_SUPPRESS_OUTPUT) ;
        if (pCtrl->log_to_mb)
            gsi_return_message(msg2log, iContext) ;
        if (pCtrl->log_to_g2)
            log_to_g2(piptnr, msg2log, code) ;
        if (deReging)
            gsi_reset_option(GSI_SUPPRESS_OUTPUT) ;
    }

    /* Give back the memory that we used */
    /* --------------------------------- */
    if (msg2log != msg)
        free(msg2log) ;
}


/* ============================================= */
/*                                               */
/* Log a Message with a long value that can vary */
/*                                               */
/* ============================================= */
void logMsgld(int msgLev, char *intro, char *fmt, long L)
{
    size_t  len = strlen(fmt) + 12 ;
    char    *msg = malloc(len+1) ;

    if (msg == NULL)
        logMsg(msgLev, intro, FALSE, -1, 0, fmt, 0) ;
    else
    {
        sprintf(msg, fmt, L) ;
        logMsg(msgLev, intro, FALSE, -1, 0, msg, 0) ;
        free(msg) ;
    }
}

/* ============================================= */
/*                                               */
/* Log a Message with a text value that can vary */
/*                                               */
/* ============================================= */
void logMsgs(int msgLev, char *intro, char *fmt, char *det)
{
    size_t  len = strlen(fmt) + strlen(det) ;
    char    *msg = malloc(len) ;

    if (msg == NULL)
        logMsg(msgLev, intro, FALSE, -1, 0, fmt, 0) ;
    else
    {
        sprintf(msg, fmt, det) ;
        logMsg(msgLev, intro, FALSE, -1, 0, msg, 0) ;
        free(msg) ;
    }
}

/* =============================================================== */
/*                                                                 */
/* Add a text string and a long value to a message and then log it */
/*                                                                 */
/* =============================================================== */
void logMsgsld(int msgLev, char *intro, char *fmt, char *det, long lval)
{
    size_t  len = strlen(fmt) + strlen(det)+12 ;
    char    *msg = malloc(len) ;

    if (msg == NULL)
        logMsg(msgLev, intro, FALSE, -1, 0, fmt, 0) ;
    else
    {
        sprintf(msg, fmt, det, lval) ;
        logMsg(msgLev, intro, FALSE, -1, 0, msg, 0) ;
        free(msg) ;
    }
}

/* =============================================================== */
/*                                                                 */
/*        Add two long values to a message and then log it         */
/*                                                                 */
/* =============================================================== */
void logMsgll(int msgLev, char *intro, char *fmt, long lval1, long lval2)
{
    size_t  len = strlen(fmt) + 24 ;
    char    *msg = malloc(len) ;

    if (msg == NULL)
        logMsg(msgLev, intro, FALSE, -1, 0, fmt, 0) ;
    else
    {
        sprintf(msg, fmt, lval1, lval2) ;
        logMsg(msgLev, intro, FALSE, -1, 0, msg, 0) ;
        free(msg) ;
    }
}

/* =============================================================== */
/*                                                                 */
/*        Add two text strings to a message and then log it        */
/*                                                                 */
/* =============================================================== */
void logMsgss(int msgLev, char *intro, char *fmt, char *s1, char *s2)
{
    size_t  len = strlen(fmt) + strlen(s1) + strlen(s2) ;
    char    *msg = malloc(len) ;

    if (msg == NULL)
        logMsg(msgLev, intro, FALSE, -1, 0, fmt, 0) ;
    else
    {
        sprintf(msg, fmt, s1, s2) ;
        logMsg(msgLev, intro, FALSE, -1, 0, msg, 0) ;
        free(msg) ;
    }
}


/* ================================================================== */
/*                                                                    */
/* Write a message to the log file.  If the log file size is limited, */
/* manage it here.                                                    */
/*                                                                    */
/* ================================================================== */
void WriteToLogFile(char *msg)
{
    int         retVal, cnr ;
    long        msgLen = strlen(msg) + SEPLEN ;
    struct stat sts ;

    gsi_int     iContext = gsi_current_context() ;

    /* If the log file has not yet been opened, do so here */
    /* --------------------------------------------------- */
    if (pLog == NULL)
    {
        retVal = stat(LogFileName, &sts) ;

        /* If the file does not exist, we can open it and go */
        /* ------------------------------------------------- */
        if (retVal)
            pLog = fopen(LogFileName, "w") ;

        /* The file exists.  We have 3 possibilities: */
        /*  -overwrite it                             */
        /*  -append to it                             */
        /*  -rename it before opening a new log       */
        /* ------------------------------------------ */
        else if (ofb == APPEND)
            pLog = fopen(LogFileName, "a+") ;
        else
        {
            if (ofb == FALSE)
                renameLogFile(LogFileName) ;
            pLog = fopen(LogFileName, "w") ;
        }
        if (pLog == NULL)
        {
            cnr = (iContext < 0 || iContext >= MAXCONTEXTS) ? MAXCONTEXTS : iContext ;
            CtxCfgs[cnr].log_to_file = FALSE ;
            logMsgs(LLEVHIGH, "** ", "Unable to open log file \"%s\".  Discontinuing log to file.",
                LogFileName) ;
            return ;
        }
    }


    /* Check if this file is getting too big.    */
    /* If so, rename it and open a new log file. */
    /* ----------------------------------------- */
    if (maxLogSize > 0)
        if (curLFLen + msgLen > maxLogSize)
        {
            fclose(pLog) ;
            curLFLen = 0 ;
            renameLogFile(LogFileName) ;
            pLog = fopen(LogFileName, "rw") ;
        }

    /* Here is where we write the message in the log file */
    /* -------------------------------------------------- */
    fprintf(pLog, "%s\n", msg) ;
    if (fwf)
        fflush(pLog) ;

    if (maxLogSize > 0)
        curLFLen += msgLen ;
}


/* ========================================================================= */
/*                                                                           */
/* Pass a log code and message to the G2 procedure OSI-ERROR.  Although this */
/* function replaces osipi_error, we add the PI point number to the message  */
/* instead of sending it as a separate value to avoid incompatibility with   */
/* existing knowledge bases.                                                 */
/*                                                                           */
/* ========================================================================= */
void log_to_g2 (piptnr, message, code)
long    piptnr;
char    *message;
long    code ;
{
	char        msg[STRSZ+1], scratch[20] ;
	gsi_item    *error_args = gsi_make_items(NUMERRARGS)  ;
	gsi_int     iContext = gsi_current_context();

    /* Forget it if the context is not live */
    /* ------------------------------------ */
    if (iContext < 0 || iContext >= MAXCONTEXTS)
        return ;
    if (!CtxCfgs[iContext].alive)
        return ;

    /* Construct the message */
    /* --------------------- */
    msg[0] = '\0' ;
    if (piptnr)
        sprintf(msg, "PI # %ld : ", piptnr) ;
    strncat(msg, message, STRSZ-strlen(msg)) ;
    if (code)
    {
        sprintf(scratch, " (%ld)", code) ;
        strncat(msg, scratch, STRSZ-strlen(msg)) ;
    }

    /* Send the code & message to G2 */
    /* ----------------------------- */
    gsi_set_int(error_args[ERRCD_POS],   code);
	gsi_set_str(error_args[ERRMSG_POS],  msg);
	gsi_rpc_start(ErrorHandle[iContext],error_args,iContext);

	gsi_reclaim_items(error_args);
}




int renameLogFile(char *logFileName)
{
    int         i, len = strlen(logFileName), bLen, eLen, retVal ;
    char        *pD, *pNewName = malloc(len+4) ;
    struct stat sts ;

    if (!len)
        return FALSE ;
    if (pNewName == NULL)
        return FALSE ;

    if (pLog)
        fclose(pLog) ;

    /* Find where the extension begins */
    /* ------------------------------- */
    for (i = len-1 ; i >= 0 ; i--)
    {
        if (logFileName[i] == '.')
            break ;
    }

    /* Prepare to find the next available number */
    /* ----------------------------------------- */
    if (i < 0 )
    {
        bLen = len ;
        eLen = 0 ;
        strcpy(pNewName,logFileName) ;
        pD = pNewName+bLen ;
    }
    else
    {
        bLen = i ;
        eLen = len - i - 1 ;
        strncpy(pNewName, logFileName, bLen) ;
        pD = pNewName+bLen ;
    }

    /* Find the next available number */
    /* ------------------------------ */
    for (i = 1 ; i <= 999 ; i++)
    {
        sprintf(pD,"%03d",i) ;
        if (eLen) strcpy(pD+3, logFileName + bLen) ;
        pNewName[len+3] = '\0' ;
        retVal = stat(pNewName, &sts) ;
        if (retVal)
            break ;
    }

    if (i < 1000)
        retVal = rename(logFileName, pNewName) ;

    return !retVal ;
}


/* =================================================================== */
/*                                                                     */
/*                  Set the log level for this context                 */
/*                                                                     */
/*   The higher the number, the more information that will be logged   */
/*                                                                     */
/* =================================================================== */
static void rpc_log_level(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *Ret_array = gsi_make_items(1);
    gsi_int     iContext = gsi_current_context() ;
    gsi_int     retStat = 0 ;
    gsi_int     iX ;

    char        *errMsg ;

    if (count != 1)
    {
        retStat = -1 ;
        errMsg = "log_level requires exactly one argument" ;
    }
    else
    {
        if (gsi_type_of(args[0]) != GSI_INTEGER_TAG)
            retStat = -1 ;
        else
        {
            iX = gsi_int_of(args[0]) ;
            if (iX < 0 || (iX > 9 && iX != LLEVMOST && iX != LLEVALL))
                retStat = -1 ;
        }
        if (retStat)
            errMsg = "log_level requires an integer argument from 0 to 9";
    }
    if (!retStat)
    {
        CtxCfgs[iContext].log_level = (short)iX ;
        logMsgld(LLEVDEBUG, "=> ", "rpc_log_level set debug level to %ld", iX) ;
    }
    else
        logMsgs(LLEVHIGH, "=> ", "rpc_log_level; **Error: %s", errMsg) ;

    gsi_set_int(Ret_array[0], retStat) ;
    gsi_rpc_return_values(Ret_array, 1, call_index, iContext);
    gsi_reclaim_items(Ret_array);

}


/* =================================================================== */
/*                                                                     */
/*               Enable or disable logging to the log file             */
/*                                                                     */
/* =================================================================== */
static void rpc_log_to_file(gsi_item *args, gsi_int count, gsi_int call_index)
{
    set_or_clear_logging_flag(args, count, call_index,
        &CtxCfgs[gsi_current_context()].log_to_file,"log-to-file","rpc_log_to_file");
}

    
/* =================================================================== */
/*                                                                     */
/*                Set or clear the flush-on-write flag                 */
/*                                                                     */
/* =================================================================== */
static void rpc_log_force_writes(gsi_item *args, gsi_int count, gsi_int call_index)
{
    set_or_clear_logging_flag(args, count, call_index, &fwf, 
                              "log-force-writes","rpc_log_force_writes");
}

    
/* =================================================================== */
/*                                                                     */
/*              Enable or disable logging to the console               */
/*                                                                     */
/* =================================================================== */
static void rpc_log_to_screen(gsi_item *args, gsi_int count, gsi_int call_index)
{
    set_or_clear_logging_flag(args, count, call_index,
        &CtxCfgs[gsi_current_context()].log_to_screen,"log-to-screen","rpc_log_to_screen");
}


/* =================================================================== */
/*                                                                     */
/*          Enable or disable logging to the G2 message board          */
/*                                                                     */
/* =================================================================== */
static void rpc_log_to_message_board(gsi_item *args, gsi_int count, gsi_int call_index)
{
    set_or_clear_logging_flag(args, count, call_index,
        &CtxCfgs[gsi_current_context()].log_to_mb,"log-to-message-board","rpc_log_to_message_board");
}


/* =================================================================== */
/*                                                                     */
/*     Enable or disable logging to the G2 procedure OSIPI-ERROR       */
/*                                                                     */
/* =================================================================== */
static void rpc_log_to_g2(gsi_item *args, gsi_int count, gsi_int call_index)
{
    set_or_clear_logging_flag(args, count, call_index,
        &CtxCfgs[gsi_current_context()].log_to_g2,"log-to-g2","rpc_log_to_g2");
}


/* =================================================================== */
/*                                                                     */
/*               Enable or disable logging to the PI log               */
/*                                                                     */
/* =================================================================== */
static void rpc_log_to_pi(gsi_item *args, gsi_int count, gsi_int call_index)
{
    set_or_clear_logging_flag(args, count, call_index,
        &CtxCfgs[gsi_current_context()].log_to_pi,"log-to-pi","rpc_log_to_pi");
}


/* ========================================================================== */
/*                                                                            */
/* Return the log settings for this context to G2                             */
/*                                                                            */
/* rpc_log_settings2 returns the following settings:                          */
/* returned values:  1. log file name ("" if none)                            */
/*                   2. current log level                                     */
/*                   3. maximum file size (0 if unlimited or not logging)     */
/*                   4. forced-writes flag                                    */
/*                   5. log-to-screen flag                                    */
/*                   6. log-to-message-board flag                             */
/*                   7. log-to-g2 flag                                        */
/*                   8. log-to-pi flag                                        */
/*                                                                            */
/* rpc_log_settings is provided for compatibility with prior versions of the  */
/* bridge and does not return the last 2 values.                              */
/*                                                                            */
/* ========================================================================== */
static void rpc_log_settings(gsi_item *args, gsi_int count, gsi_int call_index)
{
    log_settings_common(1, args, count, call_index) ;
}

static void rpc_log_settings2(gsi_item *args, gsi_int count, gsi_int call_index)
{
    log_settings_common(2, args, count, call_index) ;
}

void log_settings_common(int typec, gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *Ret_array ;
    gsi_int     iContext = gsi_current_context() ;
    CtxCfg      *pCtxCfg = &CtxCfgs[iContext] ;

    char        *fnForG2=NULL, *p, *p2, *pe ;
    int         len, nrSpChs=0 ;

    LOGMSG(LLEVDEBUG, "rpc_log_settings") ;

    Ret_array = gsi_make_items((typec == 1)? 6 : 8);

    /* It is necessary to tag \, ~, and @ as literals before sending them to G2 */
    /* ------------------------------------------------------------------------ */
    if (pCtxCfg->log_to_file)
    {
        len = strlen(LogFileName) ;
        pe = LogFileName + len ;
        for (p = LogFileName ; p < pe ; p++ )
            if (*p == '\\'  || *p == '~' || *p == '@') nrSpChs++ ;
        fnForG2 = malloc(len + nrSpChs + 1) ;
        if (fnForG2 == NULL)
        {
            LOGMSG(LLEVHIGH, "Unable to allocate memory for log file name") ;
            gsi_set_str(Ret_array[0], "???????") ;
        }
        else
        {
            for (p = LogFileName, p2 = fnForG2 ; p < pe ; p++, p2++)
            {
                if (*p == '\\' || *p == '~' || *p == '@')
                {
                    *(p2++) = '~';
                }
                *p2 = *p ;
            }
            *p2 = '\0' ;
            gsi_set_str(Ret_array[0], fnForG2) ;
        }
    }
    else
        gsi_set_str(Ret_array[0], "") ;

    /* Return the remaining settings */
    /* ----------------------------- */
    gsi_set_int(Ret_array[1], pCtxCfg->log_level);
    gsi_set_int(Ret_array[2], (pCtxCfg->log_to_file) ? maxLogSize : 0) ;
    gsi_set_log(Ret_array[3], fwf ? GSI_TRUE : GSI_FALSE) ;
    gsi_set_log(Ret_array[4], (pCtxCfg->log_to_screen) ? GSI_TRUE : GSI_FALSE) ;
    gsi_set_log(Ret_array[5], (pCtxCfg->log_to_mb) ? GSI_TRUE : GSI_FALSE) ;

    if (typec == 2)
    {
        gsi_set_log(Ret_array[6], (pCtxCfg->log_to_g2) ? GSI_TRUE : GSI_FALSE) ;
        gsi_set_log(Ret_array[7], (pCtxCfg->log_to_pi) ? GSI_TRUE : GSI_FALSE) ;
    }

    /* Send the results to G2 */
    /* ---------------------- */
    gsi_rpc_return_values(Ret_array, (typec == 1) ? 6 : 8, call_index, iContext);

    /* Give back the memory we used */
    /* ---------------------------- */
    if (fnForG2 != NULL) free (fnForG2) ;
    gsi_reclaim_items(Ret_array);

    logMsg(LLEVMOST, "<= ", FALSE, -1, 0, "rpc_log_settings", 0) ;

}


/* =================================================================== */
/*                                                                     */
/*            Add a message sent by the user to the log                */
/*                                                                     */
/* =================================================================== */
static void rpc_log_message(gsi_item *args, gsi_int count, gsi_int call_index)
{
    gsi_item    *Ret_array = gsi_make_items(2);
    gsi_int     iContext = gsi_current_context() ;
    gsi_int     retStat = 0, argType ;

    char        *errMsg, *msg ;
    short       tsf ;

    /* Validate input */
    /* -------------- */
    if (count != 2)
    {
        retStat = -1 ;
        errMsg = "log-message requires two argument." ;
    }
    else
    {
        if ((argType=gsi_type_of(args[0])) != GSI_STRING_TAG && argType != GSI_SYMBOL_TAG)
        {
            retStat = -1 ;
            errMsg = "The first argument to log-message must be text or a symbol.";
        }
        if (!retStat)
            if (gsi_type_of(args[1]) != GSI_LOGICAL_TAG)
            {
                retStat = -1 ;
                errMsg = "The second argument to log-message must be a truth value";
            }
            else
                tsf = (gsi_log_of(args[1]) == GSI_TRUE) ? TRUE : FALSE ;
        
    }

    /* Log the message or report the error */
    /* ----------------------------------- */
    if (!retStat)
    {
        msg = (argType == GSI_STRING_TAG) ? gsi_str_of(args[0]) : gsi_sym_of(args[0]) ;
        logMsg(0, "", tsf, -1, 0, msg, 0) ;
    }
    else
        logMsgs(LLEVNORM, "=> ", "log-message.  **Error: %s", errMsg) ;


    /* Let G2 know how it went */
    /* ----------------------- */
    gsi_set_int(Ret_array[0], retStat) ;
    gsi_set_str(Ret_array[1], retStat ? errMsg : "SUCCESS") ;
    gsi_rpc_return_values(Ret_array, 2, call_index, iContext);
    gsi_reclaim_items(Ret_array);

}


/* ================================================================= */
/*                                                                   */
/* There are numerous RPC functions that set or clear a logging flag */
/* They all call this function to validate the parameters, process   */
/* the request, to log the results, and to return the results to G2. */
/*                                                                   */
/* ================================================================= */
void set_or_clear_logging_flag(gsi_item *args, gsi_int count, gsi_int call_index, 
                               short *pFlag, char *g2Name, char *bridgeName)
{
    gsi_item    *Ret_array = gsi_make_items(1);
    gsi_int     iContext = gsi_current_context() ;
    gsi_int     retStat = 0 ;
    gsi_int     iX ;

    char        errMsg[STRSZ] ;

    /* Validate input */
    /* -------------- */
    if (count != 1)
    {
        retStat = -1 ;
        sprintf(errMsg, "%s requires a single argument.", g2Name) ;
    }
    else
    {
        if (gsi_type_of(args[0]) != GSI_LOGICAL_TAG)
        {
            retStat = -1 ;
            sprintf(errMsg, "The argument to %s must be a truth value.", g2Name);
        }
    }
    iX = gsi_log_of(args[0]) ;

    /* The change requested by this function is performed here.  Then a */
    /* debug entry is added to the log to report the success or failure */
    /* of this call.                                                    */
    /* ---------------------------------------------------------------- */
    if (!retStat)
    {
        *pFlag = (iX < 0 ? FALSE : TRUE) ;
        logMsgss(LLEVDEBUG, "=> ", "%s. Set %s", bridgeName, (iX < 0) ? "Off" : "On") ;
    }
    else
        logMsgss(LLEVHIGH, "=> ", "%s; **Error: %s", bridgeName, errMsg) ;

    /* Report success or failure to calling procedure in G2 */
    /* ---------------------------------------------------- */
    gsi_set_int(Ret_array[0], retStat) ;
    gsi_rpc_return_values(Ret_array, 1, call_index, iContext);
    gsi_reclaim_items(Ret_array);
}


/* =================================================== */
/*                                                     */
/* Tell GSI that these functions can be called from G2 */
/*                                                     */
/* =================================================== */
void registerLogRPCs()
{
    gsi_rpc_declare_local(rpc_log_level,            "LOG-LEVEL" );
    gsi_rpc_declare_local(rpc_log_to_screen,        "LOG-TO-SCREEN");
    gsi_rpc_declare_local(rpc_log_to_pi,            "PILOG");
    gsi_rpc_declare_local(rpc_log_to_message_board, "LOG-TO-MESSAGE-BOARD" );
    gsi_rpc_declare_local(rpc_log_to_g2,            "G2LOG" );
    gsi_rpc_declare_local(rpc_log_to_file,          "FILELOG" );
    gsi_rpc_declare_local(rpc_log_force_writes,     "LOG-FORCE-WRITES" );
    gsi_rpc_declare_local(rpc_log_settings,         "LOG-SETTINGS" );
    gsi_rpc_declare_local(rpc_log_settings2,        "LOG-SETTINGS2" );
    gsi_rpc_declare_local(rpc_log_message,          "MSG2LOG" );
}
