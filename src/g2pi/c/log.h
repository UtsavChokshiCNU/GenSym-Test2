#ifndef _LOG_C_
#define _LOG_C_

#define LLEVHIGH  1
#define LLEVNORM  2
#define LLEVMORE  3
#define LLEVDEBUG 9
#define LLEVMOST 50
#define LLEVALL 100

#define MAXFNLEN 64

#define OVERWRITE   1
#define APPEND     -1
#define RENAME      0

#ifdef WIN32
    #define SEPLEN 2
#else
    #define SEPLEN 1
#endif 

#define LOGMSG(msgLev, msg)     logMsg(msgLev, (msgLev>=LLEVDEBUG) ? "=> " : \
                                    (msgLev==LLEVNORM) ? "   ": "** ", FALSE, -1, 0, msg, 0)

extern int      defLogLev ;
extern int      defScreenLog ;
extern int      defFileLog ;
extern int      defMsgBdLog ;
extern int      defG2ProcLog ;
extern int      defPILog ;
extern char     *LogFileName ;
extern int      fNewLog ;
extern short    ofb ;
extern long     maxLogSize ;
extern short    fwf ;
extern FILE     *pLog ;

extern long maxLogSize ;

int     cfgFileLooksGood(char *fileName, char *readBuffer, int *nrCharInBuff ) ;
void    gsiErrHndlr(gsi_item *args, gsi_int count, gsi_call_identifier_type cid, gsi_int iCtx) ;
int     moreGoodCfgLines(char **ppLineStart, int *pLineLen, char *pBeyondBuff) ;
void    registerLogRPCs() ;
int     renameLogFile(char *logFileName) ;
void    logMsg(int msgLev, char *intro, int tsf, int srvNr, long piptnr, char *msg, long code) ;
void    logMsgs(int msgLev, char *intro, char *msg, char *str ) ;
void    logMsgss(int msgLev, char *intro, char *fmt, char *s1, char *s2) ;
void    logMsgld(int msgLev, char *intro, char *msg, long L ) ;
void    logMsgll(int msgLev, char *intro, char *fmt, long lval1, long lval2) ;
void    logMsgsld(int msgLev, char *intro, char *msg, char *str, long lval ) ;
void    log_to_g2(long piPtNr, char *msg, long code) ;
void    log_settings_common(int type, gsi_item *args, gsi_int count, gsi_int call_index) ;
void    set_or_clear_logging_flag(gsi_item *args, gsi_int count, gsi_int call_index, 
                               short *pFlag, char *g2Name, char *bridgeName) ;
void    WriteToLogFile(char *msg) ;

#endif
