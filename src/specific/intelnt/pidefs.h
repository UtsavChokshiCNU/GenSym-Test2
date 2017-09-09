/*-----------------------------------------------------------------------------

$Archive: /pi/freeze/intel/piapi/pidefs.h $
$Revision: 28 $     $Date: 5/27/08 3:21p $
  
-------------------------------------------------------------------------------
    
Copyright (c) 1994-2002 OSIsoft, Inc. All rights reserved.

THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF
OSIsoft, INC.  USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF OSIsoft, INC.

RESTRICTED RIGHTS LEGEND
Use, duplication, or disclosure by the Government is subject to re-
strictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227.7013

OSIsoft, Inc.
777 Davis St., San Leandro CA 94577

-------------------------------------------------------------------------------

Description:
    General PI System data type definitions.

-----------------------------------------------------------------------------*/ 
#ifndef PI__DEFINITIONS
#define PI__DEFINITIONS

#ifdef PI_SHARED_BUILD
#include "piutshr.h"
#else
#define PIUTSHR_API 
#endif

/*----------------------------------------------- includes ------------------*/
#include <stddef.h>          /* for size_t */
#include <limits.h>          /* for int(word), long sizes */
/*----------------------------------------------- typedefs ------------------*/

#ifdef UNICODE
typedef wchar_t TCHAR;                        /* text characters */
#else
typedef char TCHAR;
#ifdef unix
#define _TEXT(s) s
#endif
#endif

#if defined( hppa ) || defined( sparc ) || defined( rs6000 ) || defined(aix) || defined (__HHW_BIG_ENDIAN__)
#define PI_BIGENDIAN
#ifndef _BIG_ENDIAN
#define _BIG_ENDIAN
#endif
#else
#define PI_LITTLEENDIAN 
#ifndef _LITTLE_ENDIAN
#define _LITTLE_ENDIAN
#endif
#endif

#if defined(WIN32) && !defined(WIN64)
#define WIN32_EXCLUSIVE
#endif

#if defined(WIN32) || defined(WIN64)
#define WIN32_OR_WIN64
#include <winsock2.h>
#include <windows.h>
#endif

/*backup subsystem*/
#ifdef WIN32_OR_WIN64
#define PIRESTOREDIR_ENV_VAR "PIRESTOREDIR"
#endif

#ifdef WIN32_EXCLUSIVE

   typedef char             int8;                  /* integers */
   typedef short            int16;
   typedef long             int32;
   typedef __int64          int64;
   
   typedef unsigned char    uint8;                  /* unsigned */
   typedef unsigned short   uint16;
   typedef unsigned long    uint32;
   typedef unsigned __int64 uint64;

   typedef unsigned long    PIFuncPtr;
   typedef unsigned long    PIDataPtr;

#elif defined (WIN64)   

   typedef char             int8;                  /* integers */
   typedef short            int16;
   typedef long             int32;
   typedef __int64          int64;
   
   typedef unsigned char    uint8;                  /* unsigned */
   typedef unsigned short   uint16;
   typedef unsigned long    uint32;
   typedef unsigned __int64 uint64;

   typedef unsigned __int64    PIFuncPtr;
   typedef unsigned __int64    PIDataPtr;

#elif defined (aix)  /* aix defines int8, etc. */

#include <sys/inttypes.h>
   typedef u_int8 uint8;                  /* unsigned */
   typedef u_int16 uint16;
   typedef u_int32 uint32;
   typedef u_int64 uint64;
   typedef unsigned char    BYTE;
   typedef int              BOOL;
   typedef int              LONG;
   typedef int *            LPLONG;
   typedef unsigned int     DWORD;
   typedef u_int32          PIFuncPtr;
   typedef u_int32          PIDataPtr;
   typedef const char *     LPCSTR;
   typedef const char *     LPCTSTR;
   typedef int              SOCKET;

#else  /* Unix */

   typedef char               int8;
   typedef unsigned char      uint8;
   typedef short              int16;
   typedef unsigned short     uint16;
#if (WORD_BIT==32)
   typedef int                int32;
   typedef unsigned int       uint32;
#elif (LONG_BIT==32)
   typedef long               int32;
   typedef unsigned long      uint32;
#endif
#if (LONG_BIT==64)
   typedef long               int64;
   typedef unsigned long      uint64;
#else
   typedef long               int64;
   typedef unsigned long      uint64;
#endif

   typedef unsigned char      BYTE;
   typedef int                BOOL;
#if (WORD_BIT==32)
   typedef int                LONG;
   typedef int *              LPLONG;
   typedef unsigned int       DWORD;
#elif (LONG_BIT==32)
   typedef long               LONG;
   typedef long *             LPLONG;
   typedef unsigned long      DWORD;
#endif
   typedef unsigned long      PIFuncPtr;
   typedef unsigned long      PIDataPtr;
   typedef const char *       LPCSTR;
   typedef const char *       LPCTSTR;
   typedef int                SOCKET;

#endif

#ifdef unix
	typedef size_t            SIZE_T;
#endif

typedef float          float32;               /* floats */
typedef double         float64;


/* typedef long double    float80; */

/*  18 mar 96 jhp following definition obsoletes bool typedef  */
typedef char pibool;
/* Following is to support MFC Version 4.2 Delivered with Visual C++ 4.2 */
#ifndef linux
#if !defined(_MFC_VER) || (_MFC_VER < 0x420)
#define true           ((pibool)1)
#define false          ((pibool)0)
#endif
#endif

#ifdef unix
#ifndef osf1
#define FALSE 0
#ifdef aix
#define TRUE 1
#else
#define TRUE  (!FALSE)
#endif
#endif

#define WAIT_OBJECT_0  0
#define WAIT_ABANDONED 0x10000000
#define WAIT_FAILED    0x20000000
#define WAIT_TIMEOUT   0x40000000

#ifndef MAX_PATH
#define MAX_PATH ((int)(255))
#endif

#define EVENT_ALL_ACCESS 1

#endif

/* 29-jan-98 lfm    add typedef bool for vms */
#if defined(vms)
typedef char bool;
#endif

/* these definitions are consistent with the adopted ANSI/ISO C++ 
   definition of the new type bool
   */
/* #ifndef __GNUG__ bool is defined in gnu c++ */
/* typedef char bool;   jhp  6dec94  */
/*#define true           ((bool)1)
#define false          ((bool)0)*/
/* following typedef has been replaced by defines above. */
/* typedef int            bool; */                 /* boolean */
/*#endif */ 


/* Changed to _WINDOWS from _DOS below to avoid MFC problem 30aug95 hks */
#if defined (_WINDOWS) && (!defined (WIN32) && !defined(_WIN32))
#include <windows.h>     /*  WINAPI definition  */
#define PIPTR _far
#define PIPROC WINAPI   /* WINAPI = far pascal */
#elif (defined(WIN32) || defined(_WIN32)) 
#include <windows.h>     /*  WINAPI definition  */
#define PIPTR 
#define PIPROC WINAPI   /* WINAPI = _stdcall */ 
#else
#define PIPTR 
#define PIPROC
#ifdef unix
#define WINAPI
#endif
#endif

/*
Pointer size on Windows is defined as INT_PTR (__int64 or int for 32 bit).
Pointer size on UNIX is the same as size of long.
*/
#ifdef unix
   typedef long INT_PTR;
#endif

/* general file descriptor definition */
#ifdef WIN32_OR_WIN64
#define PIFILEHANDLE HANDLE
#define _PISTATSTRUCT _stat
#define _PISTATFUNC ::_stat
#else
#define PIFILEHANDLE int
#define _PICLOSE ::close
#define _PIFSTAT ::fstat
#define _PISTATSTRUCT stat
#define _PILSEEK ::lseek
#define _PIWRITE ::write
#define _PIREAD ::read
#define _PISTATFUNC ::stat
#define _PIUNLINK ::unlink
#endif

#define MININT8 -128
#define MAXINT8 127
#define MININT16 -32768
#define MAXINT16 32767
#define MININT32 (-2147483647L - 1)
#ifndef MAXINT32  /* 98/08/07 */
#define MAXINT32 2147483647L
#endif
#define MAXUINT8 255
#ifndef MAXUINT16  /* 98/08/07 */
#define MAXUINT16 65535
#endif
#ifndef linux
#define MININT64 (-9223372036854775807L - 1)
#define MAXINT64 9223372036854775807L
#define MAXUINT64 18446744073709551615UL
#else
#define MININT64 (-9223372036854775807LL-1)
#define MAXINT64 9223372036854775807LL
#define MAXUINT64 18446744073709551615ULL
#endif /* linux */
#ifdef osf1
#define MAXUINT32 4294967295U
#else
#define MAXUINT32 4294967295UL
#endif

#define MAX_LONG_NAME_LEN (80)

#ifdef WIN32
#define PATHSEPARATOR (TCHAR) '\\'
#define PIPARAMSPATH "\\system\\"
#define PIPARAMSFILE "\\system\\piparams.default"
#define DEFDATAPATH "c:\\PI\\dat\\"
#else
#define PATHSEPARATOR (TCHAR) '/'
#define PIPARAMSPATH "/etc/"
#define PIPARAMSFILE "/etc/piparams.default"
#define DEFDATAPATH "/usr/PI/dat/"
#endif

#define VP_ROOT 0
#define VP_PIADMIN 1

/*----- PIarcmode -------------------------------------------------------------
   Archive Data Access Modes
-----------------------------------------------------------------------------*/
enum PIarcmode 
{
   eventprevious = -3,     /* previous value, not including query date */
   eventinterpbefore = -2, /* equivalent to PI 2.x - Mode 4 */
   eventbefore = -1,       /* equivalent to PI 2.x - Mode 1 */
   eventinterp = 0,        /* equivalent to PI 2.x - Mode 3 */
   eventafter = 1,         /* equivalent to PI 2.x - Mode 2 */
   eventnext = 3           /* next value, not including query date */
};

/*----- PIsummarycode ---------------------------------------------------------
   Archive summary method modes.
-----------------------------------------------------------------------------*/
enum PIsummarycode
{
   PIarctotal,
   PIarcminimum,
   PIarcmaximum,
   PIarcstdev,
   PIarcrange,
   PIarcaverage,
   PIarcmean,
   PIarcPctTimeGood,
   PIarcPctValGood
};
enum PIarcflag
{
   ARCflag_all=0x001,
   ARCflag_numb=0x002,
   ARCflag_time=0x004,
   ARCflag_even=0x008,
   ARCflag_filter=0x010,
   ARCflag_mark=0x020,
   ARCflag_comp=0x040,
   ARCflag_expand=0x080
};

/* archive and general purpose enums */
enum PIcompoper {EQ, NE, GT, GE, LT, LE};
enum PIarcoper {ARC_read, ARC_write, ARC_delete, ARC_create, ARC_shift};
/*
 BoundaryTypeConstants for SDK
*/
enum PIarcBoundaryTypeConstants{
   piarcbtInside     = 0,          /* values inside the start and end times */
   piarcbtOutside    = 1,          /* values outside the start and end times (error if none) */
   piarcbtInterp     = 2,          /* values interpolated at the start and times */
   piarcbtAuto       = 3           /* values inside of step tag, else interpolated */
};


/*  Database enum  */
enum PIDBNAMES {
   PIdb_Null=0, 
   PIdb_Point=1, 
   PIdb_Digital=2, 
   PIdb_Attribset=4, 
   PIdb_Context=8, 
   PIdb_PointClass=0x10,
   PIdb_User=0x20, 
   PIdb_Group=0x40, 
   PIdb_Trust=0x80, 
   PIdb_Module=0x100, 
   PIdb_Heading=0x200, 
   PIdb_TransferRecord=0x400, 
   PIdb_Campaign=0x800, 
   PIdb_Batch=0x1000, 
   PIdb_Unit=0x2000, 
   PIdb_Snapshot=0x10000000,
   PIdb_Archive=0x20000000,
   PIdb_DBsecurity=0x40000000 
};
enum AuditAction {
   AUDITADD, 
   AUDITEDIT, 
   AUDITREMOVE,
   AUDITEDITATTEMPT,
   AUDITREMOVEATTEMPT
};

enum TableAction {
   TABLEDUMMY=0,
   TABLELIST=1, 
   TABLEADD, 
   TABLEEDIT, 
   TABLEREMOVE,
   TABLERENAME,
   TABLEADDOREDIT,
   TABLENOACTION
};
/*----------------------------------------------- macros and inlines ---------*/
#ifdef vms
#define PIsleep(x) {float wait_time = 0.10 * x; lib$wait ( &wait_time );}
#elif defined( WIN32 )
#define PIsleep(x) {Sleep ( x*1000 );}
#elif defined( _WINDOWS )
#define PIsleep(x) 
#else
#include <unistd.h>
#define PIsleep(x) {sleep ( x );}
#endif
/*
 get time_t current utc time. Uses CRT on Unix
 WIN32 calls on NT to avoid inconsistencies with NT
 and the CRT. For exaple, when tz is set, WIN32 CRT calls
 have different behavior. This function also avoids dependency
 on pitime.hxx
*/
#ifdef __cplusplus
#ifdef WIN32
#include <time.h>
inline time_t PIGetCurrentTime( time_t *pretVal )
{ 
   double dTime;
   time_t val;
   SYSTEMTIME st;   
   GetSystemTime( &st ); 
   if ( st.wMonth <= 2 ) 
      dTime = ( (1461L * (st.wYear - 1L)/4L) + (153L * (st.wMonth + 13L) / 5L) + st.wDay ) - 719606L; 
   else 
      dTime = ( (1461L * (int32) st.wYear / 4L) +          (153L * ((int32) st.wMonth +1L) / 5L) + (int32) st.wDay ) - 719606L; 
   dTime = ((dTime * 24 + st.wHour) * 60 + st.wMinute) * 60 + st.wSecond;
   val = (time_t)(dTime);
   if ( pretVal )
      *pretVal = val;
   return val;
} 
#else
#include <time.h>
inline time_t PIGetCurrentTime( time_t *pretVal )
{ 
   time_t val = time(0);
   if ( pretVal ) *pretVal=val; 
   return val;
} 
#endif
#endif      
#ifdef __cplusplus
#if(!defined(_MFC_VER) || (_MFC_VER < 0x400)) 
#ifndef __PLACEMENT_NEW_INLINE
/*----- placement operator new ----------------------------------------
 * This operator new places the object allocated at the passed address.
 * 10 Sep 93 BV  See C++ ARM page 279.
 *---------------------------------------------------------------------*/
#define __PLACEMENT_NEW_INLINE
#ifdef WIN32
#pragma warning(disable:4291)  /* get rid of the Microsoft heave */
#endif

#if !defined(aix) && !defined(linux)   /* otherwise, new compiler complains about declaration conflict */
inline void* operator new (size_t, void *p) {
   return p;
}
#endif 

#endif /* __PLACEMENT_NEW_INLINE */
#endif /* _MFC_VER */
#endif /* __cplusplus */



#ifdef WIN32

// #define ENABLESTACKPROTECTION

#ifdef ENABLESTACKPROTECTION

#define PAGEMASK 0xFFFFF000
#define PAGESIZE 0x00001000

#define PROTECTSTACK() __asm  \
{ \
_asm mov ebx,esp                 /* keep track of the current esp*/ \
_asm and esp,PAGEMASK            /* round down to nearest pageboundary     */ \
_asm sub esp,PAGESIZE            /* move down one more page*/ \
_asm mov [esp],ebx               /* store the old esp (it is in ebx)here   */ \
_asm mov ebx,esp                 /* store this address to protectlater     */ \
_asm sub esp,4                   /* move esp to now point to thenext page  */ \
\
\
_asm push esp                    /* Dummy location for the 4th "out" param  */ \
_asm push PAGE_NOACCESS          /* allow NOACCESS*/ \
_asm push 1                      /* 1 byte (which gets the wholepage)      */ \
_asm push ebx                    /* the stored page to change access*/ \
_asm call dword ptr [VirtualProtect]  /* make the call to change the access */ \
} 


#define UNPROTECTSTACK() _asm \
{ \
/* if all is ok, esp should now be just below the protected page*/ \
_asm mov ebx,esp                 /* start here*/ \
_asm add ebx,4                   /* protected page is 4 bytes up*/ \
\
/* make the function call to VirtualProtect.*/ \
_asm push esp                    /* Dummy location for the 4th "out"param  */ \
_asm push PAGE_READWRITE         /* allow NOACCESS*/ \
_asm push 1                      /* 1 byte (which gets the whole page)      */ \
_asm push ebx                    /* the previous page to change access      */ \
_asm call dword ptr [VirtualProtect]  /* make the call to change theaccess */ \
\
_asm mov esp,[ebx]               /* restore the old esp (storedearlier)    */ \
} 
#else
#define PROTECTSTACK() {}
#define UNPROTECTSTACK() {}
#endif
#else
#define PROTECTSTACK() {}
#define UNPROTECTSTACK() {}
#endif


/* Replacements for Microsoft _ASSERT() and _ASSERTE() on UNIX
*/
#ifdef unix

#ifdef _DEBUG
#define _ASSERT(e) \
   {if (!(e)) \
      cout << "Error: " << __FILE__ << ", " << __LINE__ << endl << flush;}
#else
#define _ASSERT(e)
#endif

#ifdef _DEBUG
#define _ASSERTE(e) \
   {if (!(e)) \
      cout << "Error: " << __FILE__ << ", " << __LINE__ << endl << flush;}
#else
#define _ASSERTE(e)
#endif

#endif  /* unix */


#ifdef unix

/* Subtitute for Microsoft's definition of INVALID_HANDLE_VALUE
*/
#define INVALID_HANDLE_VALUE 0

#endif  /* unix */

/* Defined invalid thread ID
 * for both Windows and UNIX
 */
#define INVALID_THREAD_ID 0xffffffff


#ifdef WIN32_OR_WIN64

#include <windows.h>
typedef HANDLE			    PIthread_handle;
typedef uint32			    PIthread_id;
typedef LPTHREAD_START_ROUTINE	    PIthread_func;
typedef LPVOID			    PIthread_args;

#else

#if ( (defined(aix) && defined(_THREAD_SAFE)) ||\
      (defined(hpux) && defined(_REENTRANT)) ||\
      (defined(solaris) && defined(_REENTRANT)) ||\
      (defined(osf1) && defined(_REENTRANT)) )
#define  PI_THREADSAFE
#include <sys/times.h>
#include <pthread.h>
typedef pthread_t                   PIthread_handle;
typedef uint32			    PIthread_id;
typedef void*(*PIthread_func)(void* args);
typedef void*                       PIthread_args;
#endif  /* _REENTRANT */

#endif  /* WIN32_OR_WIN64 */

#ifdef linux
#include <sys/times.h>
#include <pthread.h>
typedef uint32 PIthread_id;
typedef pthread_t PIthread_handle;
#ifndef __cplusplus
#ifndef true
#define true           ((pibool)1)
#define false          ((pibool)0)
#endif
#endif
#endif

/* Added compilation check for Windows, error if we're building with the wrong compiler.
*/

#if defined(X64) && !defined(_AMD64_) 
#ifdef _IA64_
#error ERROR: Building X64 in the IA64 environment
#else
#error ERROR: Building X64 in the X86 environment
#endif
#endif
#if defined(IA64) && !defined(_IA64_)
#ifdef _AMD64_
#error ERROR: Building IA64 in the X64 environment
#else
#error ERROR: Building IA64 in the X86 environment
#endif
#endif
#if ((defined(X64) || defined(IA64)) && !defined(_AMD64_) && !defined(_IA64_)) || \
    (!defined(X64) && !defined(IA64) && (defined(_AMD64_) || defined(_IA64_)))
#ifdef _IA64_
#error ERROR: Building X86 in the IA64 environment
#else
#error ERROR: Building X86 in the X64 environment
#endif
#endif


#endif /* PI__DEFINITIONS */
/*===== end of include file PIDEFS.H =========================================*/

