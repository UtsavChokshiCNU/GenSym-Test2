/*===========================================================================*
 *  GDB_UTILS.H                                                      [header]
 *===========================================================================*/

#ifndef GDB_UTILS_H
#define GDB_UTILS_H

/*-----------------------
    macros
  -----------------------*/

#define  TIME_STAMP(fmt,t) time_stamp(fmt,t,MAX_TIMESTAMP_LEN)

#if defined (_DEBUG) && defined (_DBGMEM)
#define  XCALLOC(n,s) xcalloc(__FILE__,__LINE__,n,s)
#define  XMALLOC(s) xcalloc(__FILE__,__LINE__,s)
#define  XFREE(b) xfree(__FILE__,__LINE__,b)
#else
#define  XCALLOC(n,s) calloc(n,s)
#define  XMALLOC(s) malloc(s)
#define  XFREE(b) free(b)
#endif


#define CTASTR2(pre,post) pre ## post
#define CTASTR(pre,post) CTASTR2(pre,post)

/** Compile-time ("static") assert.
    The "msg" parameter must be a valid identifier, _not_ a string.
    Must be at most one per line.
 */
#define STATIC_ASSERT(cond,msg) \
    typedef struct { int CTASTR(static_assertion_failed_,msg) : !!(cond); } \
        CTASTR(static_assertion_failed_,__LINE__)


/*-----------------------
    defines
  -----------------------*/

#define  GDB_ENCODE            1
#define  GDB_DECODE            2

#define  MAX_TIMESTAMP_LEN     21L   /* max timestamp string length = dd-mmm-yy hh:mm:ss */

#define  DFLT_TS_FMT           _T("%d-%b-%y %H:%M:%S")

#if defined (__alpha) && defined (vms)
#define GFLOAT_TO_IEEE(g,i,s) gfloat_to_ieee(g,i,s)
#else
#define GFLOAT_TO_IEEE(g,i,s) *i=g
#endif

/*-----------------------
    typedefs
  -----------------------*/

  typedef struct {
    long        yr;
    long        mon;
    long        day;
    long        hr;
    long        min;
    long        sec;
  } TIMESTAMP_TYPE;

/*-----------------------
    prototypes
  -----------------------*/

/* string functions */


#ifdef  __cplusplus
extern "C" {
#endif

size_t wstrrepl( GDB_CHAR *str, GDB_CHAR old_char, GDB_CHAR new_char ) ;

#ifdef  __cplusplus
}
#endif


GDB_CHAR *upper_case (GDB_CHAR *theStr);
char    *as_upper_case(char *theStr) ;

/*  strcmp
    stricmp
    wcscmp
    _wcsicmp
    ========
    strstr
    wcsstr
    ** strstrci
    ** wstrstci
*/

extern long    strcmpci(char *str1, char *str2);
#if defined(UNICODE)
extern wchar_t *wstrstrci(wchar_t *str1, wchar_t *str2);
#else
extern char    *strstrci(char *str, char *sub_str);
#endif
extern char    *search_replace(char *ssearch, char *sreplace, char *source_str, long maxbufsize);
extern GDB_CHAR *strgettoken(GDB_CHAR *str, GDB_CHAR *ret_str, GDB_CHAR token, long index);

GDB_CHAR *widen(char *ascii_str);

/* time functions */

extern GDB_CHAR *time_stamp (GDB_CHAR *format, GDB_CHAR *result, long length);
extern long    time_code (TIMESTAMP_TYPE *datetime);
extern long    get_time ();
extern GDB_CHAR *date_code (GDB_CHAR *result);

/* math functions */
extern void    gfloat_to_ieee ( double gfval, double *ieeeval, long swapFlag );

/* memory functions */
extern long    show_memory ();
extern void   *xcalloc (char *file, int lineno, unsigned int nelem,unsigned int size);
extern void   *xmalloc (char *file, int lineno, unsigned int size);
extern void    xfree (char *file, int lineno, void *buff);


#endif
