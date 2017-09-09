#include "StdAfx.h"

#if !defined(_OPC_LOG_H_)
#define _OPC_LOG_H_

// Trace levels
// ------------
#define TL_FATAL_ONLY   0
#define TL_CRITICAL     1
#define TL_ERRORS       2
#define TL_WARNINGS     3
#define TL_INFO         4


// Global logging flags
// --------------------
extern bool     g_archvLastLog ;
extern short    g_traceLevel ;
extern bool     g_traceWithTime ;
extern bool     g_traceOn ;
extern bool     g_logToG2 ;
extern bool     g_logToStdout ;
extern bool     g_logToFile ;
extern long     g_logFileMaxSize ;
extern long     g_nrCharsInLog ;


// Prototypes
// ----------
void log_message    (short msgLevel, wchar_t* msg, gsi_int ctx=gsi_current_context()) ;
void log_message_d  (short msgLevel, wchar_t* msg, long d, gsi_int ctx=gsi_current_context()) ;
void log_message_dd (short msgLevel, wchar_t* msg, long d1, long d2, gsi_int ctx=gsi_current_context()) ;
void log_message_ds (short msgLevel, wchar_t* msg, long d, wchar_t* s, gsi_int ctx=gsi_current_context()) ;
void log_message_s  (short msgLevel, wchar_t* msg, wchar_t* s, gsi_int ctx=gsi_current_context()) ;
void log_message_sd (short msgLevel, wchar_t* msg, wchar_t* s, long d, gsi_int ctx=gsi_current_context()) ;
bool OpenLogFile    () ;
bool RenameLogFile  () ;
void CloseLogFile();
void SetLogFileName(LPWSTR name);

long countCharsInMsg(wchar_t* completeMsg) ;

#endif