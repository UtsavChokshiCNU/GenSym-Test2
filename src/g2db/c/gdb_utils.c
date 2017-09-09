/*======================================================================
 *  GDB_UTILS.C - Generic Utility Functions
 *======================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#if (defined(WindowsNT) && defined(_DEBUG))
#include <crtdbg.h>
#endif
#include "gdb_globals.h"
#include "gdb_utils.h"

extern long   debug ;

typedef struct CHUNK
 {
    unsigned int csize ;
    char *cbuff;        } CHUNK ;

#define MAXBUF  256
    static CHUNK hbuff[MAXBUF] ;
    static unsigned int tmem ;


/*======================================================================
    upper_case
      - convert widestring to uppercase
 *======================================================================*/
GDB_CHAR *upper_case (GDB_CHAR *theStr )
{
    register GDB_CHAR *c;
    
    if (theStr == NULL)
        return NULL ;
    
    c = theStr ;
    while (*c != 0)
    {
        if (*c >= 'a' && *c <= 'z')
            *c -= 32 ;
        c++ ;
    }
    return theStr ;
}


/* ========================================================================== */
/*                                                                            */
/*                     Convert ANSI string to upper case                      */
/*                                                                            */
/* ========================================================================== */
char *as_upper_case (char *theStr)
{
    register char   *c ;
    
    if (theStr == NULL)
        return NULL ;
    
    c = theStr ;
    while (*c != 0) 
    {
        if (*c >= 'a' && *c <= 'z')
            *c -= 32 ;
        c++ ;
    }
    return theStr ;
}


/*======================================================================
    strcmpci: case-insensitive ANSI string compare
      - return: 0=equal,1=str1>str2,-1=str1<str2
 *======================================================================*/
long strcmpci(char *str1, char *str2)
{
    register char *ptr1, *ptr2;
    long     n1, n2 ;
    short    ok ;
    
    if (str1 == NULL) return -1 ;
    if (str2 == NULL) return  1 ;
    
    ptr1 = str1 ;
    ptr2 = str2 ;
    
    ok = 1 ;
    while (*ptr1 != 0 && *ptr2 != 0)
    {
        n1 = 0 ;
        n2 = 0 ;
        if (*ptr1 >= 'A' && *ptr1 <= 'Z')
            n1 = 32 ;
        if (*ptr2 >= 'A' && *ptr2 <= 'Z')
            n2 = 32 ;
        if (*ptr1+n1 != *ptr2+n2)
            ok = 0 ;
        ptr1++ ;
        ptr2++ ;
    }
    if (*ptr1 == 0 && *ptr2 == 0 && ok) return 0 ;
    if (*ptr1 == 0) return -1 ;
    return 1 ;
}


/*======================================================================
    strstrci   (case-insensitive)
      - locate substring in string
      - return ptr to beginning of found string or
        NULL if not found
 *======================================================================*/
char *strstrci (char *str, char *sub_str)
{
    register char    *ptr1, *ptr2, *ptr3 ;
    long     n1, n2 ;
    
    if (str == NULL || sub_str == NULL)
        return NULL ;
    
    ptr1 = str ;
    ptr2 = sub_str ;
    
    while (*ptr1 != 0 && *ptr2 != 0) 
    {
        n1 = 0 ;
        n2 = 0 ;
        if (*ptr1 >= 'A' && *ptr1 <= 'Z')
            n1 = 32 ;
        if (*ptr2 >= 'A' && *ptr2 <= 'Z')
            n2 = 32 ;
        
        if (*ptr1+n1 != *ptr2+n2)
        {
            ptr1++ ;
            continue ;
        }
        
        ptr3 = ptr1;  /* save the start loc of potential sub-string found */
        ptr1++ ;
        ptr2++ ;
        while (*ptr2 != 0) 
        {
            n1 = 0 ;
            n2 = 0 ;
            if (*ptr1 >= 'A' && *ptr1 <= 'Z')
                n1 = 32 ;
            if (*ptr2 >= 'A' && *ptr2 <= 'Z')
                n2 = 32 ;
            if (*ptr1+n1 == *ptr2+n2) 
            {
                ptr1++ ;
                ptr2++ ;
                if (*ptr2 == 0)
                    return ptr3 ;   /* found */
            }
            else 
            {
                ptr2 = sub_str ;
                break ;
            }
        }
        if (*ptr2 == 0)  /* single char match */
            return ptr3 ;
    }
    return NULL ;  /* not found */
}


/*======================================================================
    wstrstrci   (case-insensitive)
      - locate substring in wide string
      - return ptr to beginning of found string or
        NULL if not found
 *======================================================================*/
#if defined(UNICODE)
wchar_t* wstrstrci (wchar_t *str, wchar_t *sub_str )
{
    register wchar_t    *ptr1, *ptr2, *ptr3 ;
    long                n1, n2 ;
    
    if (str == NULL || sub_str == NULL)
        return NULL ;
    
    ptr1 = str ;
    ptr2 = sub_str ;
    
    while (*ptr1 != 0 && *ptr2 != 0)
    {
        n1 = 0 ;
        n2 = 0 ;
        if (*ptr1 >= 'A' && *ptr1 <= 'Z')
            n1 = 32 ;
        if (*ptr2 >= 'A' && *ptr2 <= 'Z')
            n2 = 32 ;
        
        if (*ptr1+n1 != *ptr2+n2) 
        {
            ptr1++ ;
            continue ;
        }
        
        ptr3 = ptr1;  /* save the start loc of potential sub-string found */
        ptr1++ ;
        ptr2++ ;
        while (*ptr2 != 0)
        {
            n1 = 0 ;
            n2 = 0 ;
            if (*ptr1 >= 'A' && *ptr1 <= 'Z')
                n1 = 32 ;
            if (*ptr2 >= 'A' && *ptr2 <= 'Z')
                n2 = 32 ;
            if (*ptr1+n1 == *ptr2+n2)
            {
                ptr1++ ;
                ptr2++ ;
                if (*ptr2 == 0)
                    return ptr3 ;   /* found */
            }
            else 
            {
                ptr2 = sub_str ;
                break ;
            }
        }
        if (*ptr2 == 0)  /* single char match */
            return ptr3 ;
    }
    return NULL ;  /* not found */
}
#endif

/*======================================================================
    strgettoken
      - locate & return element (index) in a delimited string
      - ret_str must be big enought to hold the element
 *======================================================================*/
GDB_CHAR *strgettoken (GDB_CHAR *str, GDB_CHAR *ret_str, GDB_CHAR token, long index)
{
    register GDB_CHAR    *ptr1, *ptr2;   /* need error check for ret_str length */
    long                n ;
    
    if (str == NULL)
        return NULL ;
    
    n = 0 ;
    ptr1 = str ;
    ptr2 = ret_str ;
    while (*ptr1 != 0) 
    {
        if (*ptr1 == token)
        {
            if (index == n) 
            {
                *ptr2 = 0 ;
                return ret_str ;
            }
            else
            {
                ptr2 = ret_str ;
                ptr1++ ;
                n++ ;
                continue ;
            }
        }
        *ptr2++ = *ptr1++ ;
    }
    if (index == n) 
    {
        *ptr2 = 0 ;
        return ret_str ;
    }
    
    return NULL ;  /* not found */
}


/*======================================================================
    time_stamp
      - format=string containing format specifiers
        listed below; length=length of result buffer
      - returns time in format specified
      - logfile & io = "%d%b%y_%H%M%S" default format
 *======================================================================*/
GDB_CHAR *time_stamp (GDB_CHAR *format, GDB_CHAR *result, long length)
{
    time_t t;
    
    /* Time-Stamp formats:
       ------------------
       %a  abbr weekday
        A  weekday
        b  abbr month
        B  month
        c  locales date & time representation
        d  day of month (1-31)
        H  hour of day (0-23)
        I  hour of day (1-12)
        j  day of year (1-366)
        m  month of year (1-12)
        M  minute (0-59)
        p  locales version of am or pm
        S  seconds (0-59)
        w  weekday (Sun=0,Sat=6)
        x  locales date rep (mm/dd/yy or dd/mm/yy)
        X  locales time rep
        y  two-digit year (00-99)
        Y  four-digit year
        Z  time zone name
    */

    if (result == NULL || format == NULL)
      return (GDB_CHAR*) NULL ;

    time(&t) ;
    if (length > 0)
        result[0] = _T('\0');
    wcsftime(result, length, format, localtime(&t)) ;

    return result ;
}


/*======================================================================
    time_code
      - returns the current time as a double
 *======================================================================*/
long time_code (TIMESTAMP_TYPE *datetime )
{
    time_t   t;
    char     result[5] ;
    
    time(&t) ;
    
    strftime(result, 5, "%Y", gmtime(&t)) ;
    datetime->yr = atol(result) ;
    
    strftime(result, 5, "%m", gmtime(&t)) ;
    datetime->mon = atol(result) ;
    
    strftime(result, 5, "%d", gmtime(&t)) ;
    datetime->day = atol(result) ;
    
    strftime(result, 5, "%I", gmtime(&t)) ;
    datetime->hr = atol(result) ;
    
    strftime(result, 5, "%M", gmtime(&t)) ;
    datetime->min = atol(result) ;
    
    strftime(result, 5, "%S", gmtime(&t)) ;
    datetime->sec = atol(result) ;
    
    return 0 ;
}


/*======================================================================
    get_time
      - returns # of seconds elapsed since midnight (00:00:00), 
        January 1, 1970, coordinated universal time, according to the
        system clock
 *======================================================================*/
long get_time ()
{
    time_t   t;

    time(&t) ;
    return (long)t;
}


/*======================================================================
    date_code
      - returns the current date as a coded string
      - e.g. J207 = October 20, 1997
 *======================================================================*/
GDB_CHAR *date_code (GDB_CHAR *result)
{
    GDB_CHAR   t_stamp1[3], *stop_string;
    GDB_CHAR   t_stamp2[3] ;
    GDB_CHAR   t_stamp3[3] ;

    time_stamp(_T("%m"), t_stamp1, 3) ;
    time_stamp(_T("%d"), t_stamp2, 3) ;
    time_stamp(_T("%y"), t_stamp3, 3) ;
    _snwprintf(result, 4, _T("%c%s%c"), 64 + wcstol(t_stamp1, &stop_string, 10),
	     t_stamp2, t_stamp3[1]);

    return result ;
}


/*======================================================================
    search_replace
      - user must provide a buffer (source_str) of sufficient 
        size not to exceed maxbufsize
      - replaces every occurence of ssearch with sreplace
      - case sensitive
 *======================================================================*/
char *search_replace (char *ssearch, char *sreplace, char *source_str, long maxbufsize )
{
    char  *source_ptr ;
    char  *target_ptr ;
    char  *target_str ;
    char  *search_ptr ;
    char  *replace_ptr ;
    long   n, slen ;
    long   status ;
    
    if (source_str == NULL || ssearch == NULL || sreplace == NULL)
        return NULL ;
    
    if ((target_str = (char *)calloc(maxbufsize+1, sizeof(char))) == NULL)
        return NULL ;
    
    slen        = strlen(ssearch) ;
    source_ptr  = source_str ;
    target_ptr  = target_str ;
    search_ptr  = ssearch ;
    replace_ptr = sreplace ;
    
    while (*source_ptr != 0) 
    { 
        if (*source_ptr == *search_ptr)
        {              
            status = 1 ;
            n = 0 ;
            while (*(source_ptr+n) != 0 && n < slen && status) 
            {
                if (*(source_ptr+n) == *(search_ptr+n)) 
                {
                    n++ ;
                    status = 1 ;
                }
                else
                    status = 0 ;
            }
            
            if (n == slen) {       /* match found */
                while (*replace_ptr != 0)
                    *target_ptr++ = *replace_ptr++ ;
                replace_ptr = sreplace ;
                source_ptr += n ;
            }   
            else
                *target_ptr++ = *source_ptr++ ;
        }
        else
            *target_ptr++ = *source_ptr++ ;
    }
    
    *target_ptr = 0 ;
    
    strncpy(source_str,target_str, maxbufsize) ;
    free((char *)target_str) ;
    
    return source_str ;
}


/*======================================================================
    xmalloc
 *======================================================================*/
void *xmalloc(char *file, int lineno, unsigned int size )
{
    register int n ;
    void  *buff ;
    
    if ((buff = malloc(size)) == NULL)
    {
        if (debug & DBG11)
            printf("??? Could NOT m_Allocate %u bytes (%d)\n    File: %s, Line: %d\n", size, tmem, file, lineno) ;
        return NULL ;
    }
    
    /* store addr in array */
    for (n=0;n<MAXBUF;n++) 
    {
        if (hbuff[n].cbuff == NULL) 
        {
            hbuff[n].cbuff = buff ;
            hbuff[n].csize = size ;
            tmem += size ;
            if (debug & DBG11)
                printf("+++ m_Allocated %u bytes (%d)\n    File: %s, Line: %d\n", size, tmem, file, lineno) ;
            return buff ;
        }
    }
    
    if (debug & DBG11) 
    {
        printf("NO ROOM LEFT IN DEBUG BUFFER\n") ;
        printf("+++ m_Allocated %u bytes (%d)\n    File: %s, Line: %d\n", size, tmem, file, lineno) ;
    }
    
    return buff ;
}


/*======================================================================
    xcalloc
 *======================================================================*/
void *xcalloc(char *file, int lineno, unsigned int nelem, unsigned int size)
{
    int n ;
    void  *buff ;
    
    if ((buff = calloc(nelem, size)) == NULL) 
    {
        if (debug & DBG11)
            printf("??? Could NOT c_Allocate %u bytes (%d)\n    File: %s, Line: %d\n", nelem*size, tmem, file, lineno) ;
        return NULL ;
    }
    
    /* store addr in array */
    for (n=0;n<MAXBUF;n++) 
    {
        if (hbuff[n].cbuff == NULL) 
        {
            hbuff[n].cbuff = buff ;
            hbuff[n].csize = nelem*size ;
            tmem += nelem*size ;
            if (debug & DBG11)
                printf("+++ c_Allocated %u bytes (%d)\n    File: %s, Line: %d\n", nelem*size, tmem, file, lineno) ;
            return buff ;
        }
    }
    
    if (debug & DBG11) 
    {
        printf("NO ROOM LEFT IN DEBUG BUFFER\n") ;
        printf("+++ c_Allocated %u bytes (%d)\n    File: %s, Line: %d\n", nelem*size, tmem, file, lineno) ;
    }
    
    return buff ;
}


/*======================================================================
    xfree
 *======================================================================*/
void xfree(char *file, int lineno, void *buff)
{
    int n ;
    
    free(buff) ;
    
    /* remove addr from array */
    for (n=0;n<MAXBUF;n++) 
    {
        if (hbuff[n].cbuff == (char *)buff) 
        {
            if (debug & DBG11)
                printf("--- Released %u bytes (%d)\n    File: %s, Line: %d\n", hbuff[n]. csize, tmem, file, lineno) ;
            tmem -= hbuff[n].csize ;
            hbuff[n].cbuff = NULL ;
            hbuff[n].csize = 0 ;
            return ;
        }
    }
    
    if (debug & DBG11) 
    {
        printf("ALLOCATED MEMORY NOT FOUND IN DEBUG BUFFER\n") ;
        printf("--- Released %u bytes (%d)\n    File: %s, Line: %d\n", hbuff[n]. csize, tmem, file, lineno) ;
    }
}


/*======================================================================
    show_memory
      - returns the total # of bytes allocated by this process 
 *======================================================================*/
long show_memory()
{
#if (defined(WindowsNT) && defined(_DEBUG))
    _CrtMemState   chkpt;
    register int n ;
    long  tmp ;
    long  mTot = 0 ;
    
    // Note: Add libcd.lib to end of object/library modules under link tab
    
    tmp = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) ;
    tmp |= _CRTDBG_CHECK_ALWAYS_DF ;
    _CrtSetDbgFlag(tmp) ;
    
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW) ;
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT) ;
    
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW) ;
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT) ;
    
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_WNDW) ;
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT) ;
    
    _CrtMemCheckpoint(&chkpt) ;
    
    for (n=0;n<_MAX_BLOCKS;n++)
        mTot += chkpt.lSizes[n] ;
    
    return  mTot ;
#endif
    
    return 0 ;
}


/*======================================================================
    gfloat_to_ieee
      - converts GFLOAT floating point numbers to IEEE format for 
        return to G2
      - this is a HACK until GFLOATS are once again handled in GSI
        (promised in 5.0)
 *======================================================================*/
void gfloat_to_ieee (double gfval, double *ieeeval, long byteSwap )
{
#ifdef GDB_USE_GFLOATS

  /* If on an alpha VMS, then convert GFLOATS to IEEE format for G2 */

    globalvalue CVT$K_VAX_G ;
    globalvalue CVT$K_IEEE_T;           
    globalvalue CVT$M_ROUND_TO_NEAREST;
    globalvalue CVT$_NORMAL ;
    
    union 
    {
        double ival ;
        short ibyte[4] ;
    } iswap ;
    
    short    tmpbyte ;
    unsigned long cvt_stat;
    
    cvt_stat = CVT$CONVERT_FLOAT(&gfval, CVT$K_VAX_G, ieeeval, CVT$K_IEEE_T, CVT$M_ROUND_TO_NEAREST) ;
    
    /* must perform a byte swap if using GSI API functions that deal with 'simple' 
       values (e.g. gsi_set_flt). Must not swap if using functions that deal
       with complex types i.e. values passed by address (e.g. gsi_set_flt_array).
       See HQ-695712 */
    
    if (byteSwap)
    {
        iswap.ival = *ieeeval ;
        tmpbyte = iswap.ibyte[0] ;
        iswap.ibyte[0] = iswap.ibyte[3] ;
        iswap.ibyte[3] = tmpbyte ;
        tmpbyte = iswap.ibyte[2] ;
        iswap.ibyte[2] = iswap.ibyte[1] ;
        iswap.ibyte[1] = tmpbyte ;
        *ieeeval = iswap.ival ;
    }
    
    return ;
    
#endif
    
    /* Since not on an Alpha VMS, simply set the IEEE value equal to
    the GFLOAT value (no conversion necessary) */
    
    *ieeeval = gfval ;
    
    return ;
}


/* ========================================================================== */
/*                                                                            */
/*                  Convert an ASCII string to a wide string.                 */
/*         The caller is responsible for freeing the returned string          */
/*                                                                            */
/* ========================================================================== */
GDB_CHAR* widen(char *narrow)
{
    long        i, strLen = strlen(narrow) ;
    GDB_CHAR*   retStr = (GDB_CHAR*) calloc(strLen+1, sizeof(GDB_CHAR)) ;

    if (retStr)
    {
        for (i = 0 ; i < strLen ; i++)
            retStr[i] = (GDB_CHAR) narrow[i];
        retStr[i] = (GDB_CHAR) 0;
    }
    return retStr;
}

/* ========================================================================== */
/*                                                                            */
/*    Replaces in-place every occurence of old_char with new_char             */
/*    in given string str.               				      */
/*                                                                            */
/*    Returns the number of replacements have occured.                        */
/*                                                                            */
/*    Arguments:                                                              */
/*    str: UCS-2 string with zero terminator.                                 */
/*    old_char - char to replace with new_char                                */
/*    new char - the replacement of old_char                                  */
/*                                                                            */
/* ========================================================================== */
size_t wstrrepl( GDB_CHAR *str, GDB_CHAR old_char, GDB_CHAR new_char )
{   
    size_t cnt = 0 ;

    if (str)
    {
	for ( ; *str ; ++str)
	{
	    if (*str == old_char)
	    {
		*str = new_char ;
		++cnt ;
	    }	
	}
    }

    return cnt ;
}

