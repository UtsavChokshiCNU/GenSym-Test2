#include "StdAfx.h"
#include <stdio.h>

#include <fstream>
#include <cassert>


/* ========================================================================== */
/*                                                                            */
/*          Global flags used to track logging level & destinations           */
/*                                                                            */
/* ========================================================================== */

bool        g_archvLastLog   = false ;
short       g_traceLevel     = TL_FATAL_ONLY ;
bool        g_traceWithTime  = true ;
bool        g_traceOn        = true;
bool        g_logToG2        = false;
bool        g_logToStdout    = true ;
bool        g_logToFile      = true ;
long        g_logFileMaxSize = 1048576L ;  // 1 MB
long        g_nrCharsInLog   = 0L ;
bool        g_logIOError     = false ;

/** The file stream used for logging */
static std::wofstream m_logFile;

/** The name of the file to use for logging */
static std::wstring m_logFileName;

/** String of the message to log */
static wchar_t* g_logIOMsg;


/* ========================================================================== */
/*                                                                            */
/* If logging is on and the income message has a level greater than or equal  */
/* to the currently enabled level, send it to the enabled logging devices.    */
/*                                                                            */
/* ========================================================================== */
void    log_message(short msgLevel, wchar_t* msg, gsi_int  ctx)
{

    long        lngDateTimeSz, lngMsgSz ;
    time_t      ltime ;
    struct  tm  *ts ; //time structure
    wchar_t     datetimebuf[128] ;
    wchar_t     *completeMsg ;


    if (g_traceLevel < msgLevel  || !g_traceOn)
        return ;

    time(&ltime) ;
    ts = localtime(&ltime);
    wsprintf(datetimebuf, L"%4d-%02d-%02d %02d:%02d:%02d", ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec) ; 

    lngDateTimeSz = wcslen(datetimebuf) ;
    lngMsgSz      = wcslen(msg) ;
    completeMsg   = new wchar_t[g_traceWithTime ? (lngDateTimeSz+lngMsgSz+4) : (lngMsgSz+1)] ;

    if (g_traceWithTime)
        swprintf(completeMsg,L"%s : %s", datetimebuf, msg) ;
    else
        swprintf(completeMsg,L"%s", msg) ;


    if (g_logToStdout)
        wprintf(L"%s\n", completeMsg) ;

    if (g_logToG2 && ctx >= 0 && ctx < MAX_GDB_CONTEXTS)
        gsi_return_message(completeMsg, ctx) ;

    /* Write the message to the log file */
    /* --------------------------------- */
    if (g_logToFile)
        do // Provide an easy way to jump out on an error //
        {
            if (!m_logFile)
                if (m_logFileName.empty() || !OpenLogFile())
                {
                    g_logToFile = false ;
                    break ;
                }
            lngMsgSz = countCharsInMsg(completeMsg) ;
            if ((lngMsgSz + g_nrCharsInLog) > g_logFileMaxSize)
            {
                m_logFile.close();
                if (!OpenLogFile())
                    break ;
            }
            m_logFile << completeMsg << std::endl;
            if (!m_logFile)
                if (g_logToStdout)
                    wprintf(L"*** Error writing message to log file.\n") ;
                else
                    wprintf(L"*** Error writing \"%s\" to log file\n", completeMsg) ;
            else
                g_nrCharsInLog += (lngMsgSz+2) ;
        } while (0==1) ;
        

    /* If the handling of opening the log file failed, turn off logging to a  */
    /* file and log a message to the screen.                                  */
    /* ---------------------------------------------------------------------- */
    if (g_logIOError)
    {
        wchar_t ioErrMsg[121] ;
        
        g_logToFile = false ;
        g_logIOError = false ;
        if (!g_logToStdout)
        {
            wprintf(L"%s\n", completeMsg) ; // write the message to the screen
                                            // so it is not completely lost
            g_logToStdout = true ;
            _snwprintf(ioErrMsg, 120, L"%s : file logging disabled & screen logging enabled.", g_logIOMsg) ;
        }
        else
            _snwprintf(ioErrMsg,120, L"%s : file logging disabled.", g_logIOMsg) ;
        g_logIOMsg = NULL ;
        log_message(TL_ERRORS, ioErrMsg) ;
    }
    delete [] completeMsg ;
}


void    log_message_s(short msgLevel, wchar_t* msg, wchar_t *s, gsi_int  ctx)
{
    wchar_t *combinedMsg = new wchar_t[wcslen(msg) + wcslen(s)] ;  // msg should ccontain %s

    swprintf(combinedMsg, msg, s) ;
    log_message(msgLevel, combinedMsg, ctx) ;
    delete [] combinedMsg ;
}


void    log_message_sd(short msgLevel, wchar_t* msg, wchar_t *s, long d, gsi_int  ctx)
{
    wchar_t *combinedMsg = new wchar_t[wcslen(msg) + wcslen(s) + 20] ;

    swprintf(combinedMsg, msg, s, d) ;
    log_message(msgLevel, combinedMsg, ctx) ;
    delete [] combinedMsg ;
}

void    log_message_ds(short msgLevel, wchar_t* msg, long d, wchar_t *s, gsi_int  ctx)
{
    wchar_t *combinedMsg = new wchar_t[wcslen(msg) + wcslen(s) + 20] ;

    swprintf(combinedMsg, msg, d, s) ;
    log_message(msgLevel, combinedMsg, ctx) ;
    delete [] combinedMsg ;
}


void    log_message_d(short msgLevel, wchar_t* msg, long d, gsi_int  ctx)
{
    wchar_t *combinedMsg = new wchar_t [wcslen(msg)+ 20] ;

    swprintf(combinedMsg, msg, d) ;
    log_message(msgLevel, combinedMsg, ctx) ;
    delete [] combinedMsg ;
}


void    log_message_dd(short msgLevel, wchar_t* msg, long d1, long d2, gsi_int  ctx)
{
    wchar_t *combinedMsg = new wchar_t [wcslen(msg)+ 40] ;

    swprintf(combinedMsg, msg, d1, d2) ;
    log_message(msgLevel, combinedMsg, ctx) ;
    delete [] combinedMsg ;
}


// ========================================================================== //
//                                                                            //
//                      Open the log file for writing.                        //
//                                                                            //
// ========================================================================== //
bool    OpenLogFile()
{
    struct _stat    statBuf ;

    if (g_archvLastLog)
        if (!_wstat(m_logFileName.c_str(), &statBuf))
            if (!RenameLogFile())
            {
                g_logIOError = true ;
                g_logIOMsg = L"Unable to rename log file";
                return false;
            }
    m_logFile.open(m_logFileName.c_str());
    if (!m_logFile)
    {
        g_logIOError = true ;
        g_logIOMsg = L"Unable to open log file";
        return false;
    } 
    g_nrCharsInLog = 0L ;
    return true ;
}


// ========================================================================== //
//                                                                            //
//      Rather than overwrite a log file, we will rename it, changing its     //
//          extention to the next available number between 000 and 999.       //
//                                                                            //
// ========================================================================== //
bool RenameLogFile()
{
    if (m_logFileName.empty()) {
        return FALSE;
    }
    m_logFile.close();
    std::wstring new_name = m_logFileName.substr(0, m_logFileName.rfind(L'.'));
    new_name.append(L".000");
    int i;
    for (i = 1; i <= 999; ++i) {
        struct _stat sts;
        wchar_t s[16];
        swprintf(s, L".%03d", i);
        new_name.replace(new_name.rfind(L'.'), 4, s);
        if (_wstat(new_name.c_str(), &sts)) {
            return 0 == _wrename(m_logFileName.c_str(), new_name.c_str());
        }
    }
    if (i == 1000) {
        new_name.replace(new_name.rfind(L'.'), 4, L".001");
        _wremove(new_name.c_str());
        return 0 == _wrename(m_logFileName.c_str(), new_name.c_str());
    }
    return FALSE;
}

void CloseLogFile()
{
    m_logFile.close();
}

void SetLogFileName(LPWSTR name)
{
    assert(nullptr != name);
    m_logFileName.assign(name);
}


long    countCharsInMsg(wchar_t* completeMsg)
{
    long        sz = wcslen(completeMsg) ;
    wchar_t*    p = completeMsg ;

    while (*p)
        if (*p++ == '\n')
            sz++ ;
    return sz ;
}
