/*================================================================
 *  GDB_GLOBALS.H                                         [header]
 *================================================================
 *   This module contains data that must be accessible to all GDB
 *   layers. If the data is specific to a particular layer, then
 *   it should be placed within the header file for that layer.
 *================================================================*/
#ifndef GDB_GLOBALS_H
#define GDB_GLOBALS_H


#if defined(UNICODE)
 #define __T(x)      L ## x
#else
 #define __T(x)      x
#endif

#define _T(x)       __T(x)

#if defined(WIN32)
 #if defined(UNICODE)
 #define _wscicmp wcscmp
 #else 
 #define _wcsicmp strcmp
 #endif
#else
 #if defined(UNICODE)
 # define _wcsicmp wcscasecmp
 #else
 # define _wcsicmp strcasecmp /* Don't know if strcasecmp exists on Win32 */
 #endif
#endif

#ifndef UNICODE

#define wcscat         strcat
#define wcscpy         strcpy
#define wcscmp         strcmp
#define wcsncpy        strncpy
#define wcsncat	       strncat
#define wcslen         strlen
#define wcsstr         strstr
#define wcstol         strtol
#define wcsftime       strftime
#define wprintf        printf
#define swprintf       sprintf
#define fwprintf       fprintf
#define fputws         fputs
#define fputwc         fputc
#define wstrstrci      strstrci
#define _wtoi          atoi
#define _wtol          atol

#if defined(WIN32)
#  define _snwprintf     _snprintf
#else
#  define _snwprintf     snprintf
#  define _snprintf      snprintf
#endif

#endif /* UNICODE */

/*-----------------------
    defines
  -----------------------*/

/* debug support (bitmask) */
#define  DEBUG                   0x0000L
#define  DBG0                    0x0000L       /* no debug */
#define  DBG1                    0x0001L       /* function names */
#define  DBG2                    0x0002L       /* info */
#define  DBG3                    0x0004L       /* errors */
#define  DBG4                    0x0008L       /* warnings */
#define  DBG5                    0x0010L       /* results */
#define  DBG6                    0x0020L       /* info-detail */
#define  DBG7                    0x0040L       /* debug tools & handles */
#define  DBG8                    0x0080L       /* config & setup */
#define  DBG9                    0x0100L       /* memory */
#define  DBGM                    0x0200L       /* fatal */
#define  DBGC                    0x0400L       /* gsi callback functions */

#define  DBGALL                  0x07FFL       /* DBG1->DBGC */
#define  DBG_DEFAULT             DBG2|DBG3|DBG4|DBGM  /* info + errors + warnings */

/* additional debug */
#define  DBGX                    0x0800L       /* disable GSI error handler */
#define  DBG10                   0x1000L       /* descriptor dump */
#define  DBG11                   0x2000L       /* memory-leak */
#define  DBG12                   0x4000L       /* reserved */
#define  DBG13                   0x8000L       /* reserved */

#define  LAYER1                  DBG1
#define  LAYER2                  DBG2
#define  LAYER3                  DBG3

/* logfile */
#define  DFLT_LOGF_NAME_LEN      35L
#define  MAX_PAGE_WIDTH          79L
#define  F_OPEN                  1L
#define  F_CLOSE                 2L
#define  F_WRITE                 3L
#define  F_FLUSH                 4L
#define  F_EXISTS                5L
#define  F_DELETE                6L
#define  LOGFILE_FILTER_DEF      DBG2|DBG3|DBG4|DBGM  /* info + errors + warnings */
#define  LOGFILE_FILTER_ALL      LOGFILE_FILTER_DEF

/* status */
#ifndef  TRUE
#define  TRUE                    1L
#endif
#ifndef  FALSE
#define  FALSE                   0L
#endif

/* for alloc & free */
#define  DATA_ONLY               1L
#define  ALL                     2L
#define  GDB_INIT                1L
#define  GDB_UPDATE              2L
#define  GDB_EXECUTE             3L
#define  BIND                    4L
#define  SELECT                  5L
#define  STORED_PROC             6L

/* misc */
#define  COMMIT                  1L
#define  ROLLBACK                2L
#define  DEVELOPER_ACCESS        "GensymAccessDeve"
#define  STORED_PROC_DELIM       ':'
#define  PR_MAX_GSI_STRING_LEN   65536  /* 64k */
#define  MAX_GSI_STRING_LEN      1000000

/* internal types */
#define  GDB_SUCCESS             0L
#define  GDB_ERROR               1L
#define  GDB_EXT_ERROR           2L
#define  GDB_BIND_ERROR          3L

#define  GDB_BIND_ERROR_MSG  _T("G2-Database Bridge: Undefined bind parameter.")

#define  GDB_STRING_TYPE       900L
#define  GDB_BYTE_TYPE         901L
#define  GDB_SHORT_TYPE        902L
#define  GDB_INT_TYPE          903L
#define  GDB_LONG_TYPE         904L
#define  GDB_FLOAT_TYPE        905L
#define  GDB_DBL_TYPE          906L
#define  GDB_WSTRING_TYPE      907L
#define  GDB_UNSUPPORTED_TYPE  950L

/* Make wchar_t as Windows only */
#ifdef UNICODE
# define  GDB_CHAR             wchar_t
#else
# define  GDB_CHAR             char
#endif

#define  GDB_BYTE              char
#define  GDB_SHORT             short
#define  GDB_INT               int
#define  GDB_LONG              long
#define  GDB_FLOAT             float
#define  GDB_DBL               double

/*-----------------------
    NLS Language Support
  -----------------------*/

#define  MAX_CHARSET_NAME_LEN  20
#define  DFLT_DB_CHARSET        1  /* latin-1 */
#define  INVALID_DB_CHARSET    -1
#define  MAX_CHARSET_TYPES     20

static char DB_CHARSET_NAME[MAX_CHARSET_TYPES][MAX_CHARSET_NAME_LEN] =
  {
   /* 0*/ "GENSYM",
   /* 1*/ "LATIN-1",
   /* 2*/ "LATIN-2",
   /* 3*/ "LATIN-3",
   /* 4*/ "LATIN-4",
   /* 5*/ "CYRILLIC",
   /* 6*/ "ARABIC",
   /* 7*/ "GREEK",
   /* 8*/ "HEBREW",
   /* 9*/ "LATIN-5",
   /*10*/ "LATIN-6",
   /*11*/ "US-ASCII",
   /*12*/ "JIS-X-0208",
   /*13*/ "JIS-X-0208-EUC",
   /*14*/ "SHIFT-JIS-OR-KANJI",
   /*15*/ "KSC-5601",
   /*16*/ "KSC-5601-EUC",
   /*17*/ "UNICODE-UTF-7",
   /*18*/ "UNICODE-UTF-8",
   /*19*/ "ISO-2022"
  };

/* database type */
#define DB_TYPE_LEN             11L  /* len of db_type + 3 for 'g2-' */
#ifndef DB_TYPE
 #ifdef RDB
 #define DB_TYPE "Rdb"
 # ifdef UNICODE
 #  define wDB_TYPE L"Rdb"
 # else
 #  define wDB_TYPE DB_TYPE
 # endif
 #endif

 #ifdef SQLSVR
 #define DB_TYPE "MSSQL"
 # ifdef UNICODE
 #  define wDB_TYPE L"MSSQL"
 # else
 #  define wDB_TYPE DB_TYPE
 # endif
 #endif

 #ifdef ORACLE
 #define DB_TYPE "Oracle"
 # ifdef UNICODE
 #  define wDB_TYPE L"Oracle"
 # else
 #  define wDB_TYPE DB_TYPE
 # endif
 #endif

 #ifdef ODBC
 #define DB_TYPE "ODBC"
 # ifdef UNICODE
 #  define wDB_TYPE L"ODBC"
 # else
 #  define wDB_TYPE DB_TYPE
 # endif
 #endif

 #ifdef SYBASE
 #define DB_TYPE "Sybase"
 # ifdef UNICODE
 #  define wDB_TYPE L"Sybase"
 # else
 #  define wDB_TYPE DB_TYPE
 # endif
 #endif

 #ifdef INFORMIX
 #define DB_TYPE "Informix"
 # ifdef UNICODE
 #  define wDB_TYPE L"Informix"
 # else
 #  define wDB_TYPE DB_TYPE
 # endif
 #endif
#endif

/*-----------------------
    sizes & limits
  -----------------------*/

#define  MAX_CURSORS              500L        /* max # cursors supported by GDB, increased to 500 for AT&T */
#define  MAX_DCURS_LEN             15L        /* max length of GENDA cursor name CURSORc_xxx */
#define  DFLT_NCOLS               100L        /* default max select-list items MAX_COLS - from 100 */
#define  MAX_BIND_VARS            500L        /* max # bind variables  */
#define  DFLT_BIND_NAME_LEN        31         /* (int) max bind variable value length  */
#define  MAX_COLNAMELEN            40L        /* max length of optional col names */
#define  MAX_STORED_COLS          300L        /* should be equivalent to MAX_NCOLS */
#define  MAX_TRIGGER_MSG_LEN     4000L        /* max length of message read from trigger pipe */
#define  MAX_TRIGGER_NAME_LEN      40L        /* max length of trigger name */
#define  MAX_REGISTERED_ITEMS    5000L        /* for user_ptr storage of structures based on obj index */ 
#define  DFLT_REGISTERED_ITEMS   2000L   
#define  DFLT_BIND_VARS            50L        /* default maximum # bind variables */
#define  MAX_GDB_CONTEXTS          50L
#define  DFLT_VALUE_ARRAY_SZ      200L        /* initial allocation of GSI value array */
#define  DFLT_COLUMN_ARRAY_SZ      30L        /* initial allocation of GSI column array */

#define  EXSPRETRSZ                64L        /* maximum size of routine name passed to sp_handler */
#define  EXSPRET_SZ              4000L        /* size of input to and output from sp_handler */


/*-----------------------
    macros
  -----------------------*/

#define  WSBOOLEAN(n) ((n != 0) ? _T("TRUE") : _T("FALSE"))

/*-----------------------
    structures
  -----------------------*/

typedef struct BIND_STRUCT {
  long       nBind;
  GDB_CHAR **bind_array;
} BIND_STRUCT;

#define  MAX_BRIDGE_NAME_LEN        15L
#define  MAX_BRIDGE_VER_LEN         30L
#define  MAX_BRIDGE_PLATFORM_LEN    25L

typedef struct BRIDGE_INFO {
  char bridge_name[MAX_BRIDGE_NAME_LEN];
  char bridge_version[MAX_BRIDGE_VER_LEN];
  char bridge_platform[MAX_BRIDGE_PLATFORM_LEN];
} BRIDGE_INFO;

#endif
