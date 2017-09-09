/*-----------------------------------------------------------------------------

$Archive: /pi/freeze/intel/piapi/piapi.h $
$Revision: 24 $     $Date: 5/27/08 3:21p $

-------------------------------------------------------------------------------

Copyright (c) 1992-2007 OSIsoft, Inc. All rights reserved.

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

This file contains prototype information for the PI Application Programmers
Interface, a Multi-Platform PI Toolkit.

-----------------------------------------------------------------------------*/

#ifndef __PIAPI_H
#define __PIAPI_H
#include "pidefs.h"
#include "piba.h"
/*  14-jun-93  */                                         
#ifndef PIPTR
#if defined(WIN32)
#define PIPTR
#endif
#endif

#if defined(WIN32)
#include <Winsock2.h>
#include <windows.h>
#define PIINT32 int32 WINAPI
#define PIVOID  void WINAPI
#define PIWIN   WINAPI
#define PIBOOL  pibool WINAPI
#elif defined ( __alpha )
#define PIINT32 int
#define PIVOID void
#define PIWIN 
#define PIBOOL pibool
#else
#define PIINT32 int32
#define PIVOID  void
#define PIWIN
#define PIBOOL pibool
#endif



/*  error structures for queue versions of sendexception and putsnap 28jun93 */
/* static struct qerror *//* 98/06/05 */
#if !defined(VAX) && !defined(__vax) && !defined(vms)
typedef struct qerror
{
   int32 point;
   int32 error;
} QERROR, PIPTR *LPQERROR;

/* static struct qerrors */
typedef struct qerrors
{
   int32 syserror;         /*  current system errors  */
   int32 numbpterrs;       /*  number of individual point errors  */
   struct qerror *qerr;   /*  list of points in error  */
} QERRORS, PIPTR *LPQERRORS;
#endif

/*  exception reporting structure  08-JUN-93 */
typedef struct _pi_except
{
   float  newval;
   int32   newstat;
   int32   newtime;
   float  oldval;
   int32   oldstat;
   int32   oldtime;
   float  prevval;
   int32   prevstat;
   int32   prevtime;
   float  excdeveng;
   int32   excmin;
   int32   excmax;
} PI_EXCEPT;

#ifdef __cplusplus
extern "C" {
#endif

/* PI API Function Prototypes ------------------------------------------------*/
PIINT32 piar_calculation( int32 PIPTR *count, int32 times[], float rvals[],
             int32 istats[], char PIPTR *exp );
PIINT32 piar_compvalues( int32 pt, int32 PIPTR *count, int32 times[],
   float rvals[], int32 istats[], int32 rev );
PIINT32 piar_compvaluesfil( int32 pt, int32 PIPTR *count, int32 times[],
   float rvals[], int32 istats[], char PIPTR *exp, int32 rev, int32 fil );
PIINT32 piar_deletevalue( int32 pt, int32 timedate );
PIINT32 piar_interpvalues( int32 pt, int32 PIPTR *count, int32 times[],
   float rvals[], int32 istats[] );
PIINT32 piar_interpvaluesfil( int32 pt, int32 PIPTR *count, int32 times[],
   float rvals[], int32 istats[], char PIPTR *exp );
PIINT32 piar_panvalues( int32 pt, int32 PIPTR *count, int32 PIPTR *timedate );
PIINT32 piar_plotvalues( int32 pt, int32 intervals, int32 PIPTR *count,
            int32 times[], float rvals[], int32 istats[] );
PIINT32 piar_putvalue( int32 pt, float rval, int32 istat, int32 timedate,
              int32 wait );
PIINT32 piar_replacevalue( int32 pt, int32 timedate, float rval, int32 istat );
PIINT32 piar_summary( int32 pt, int32 PIPTR *time1, int32 PIPTR *time2,
   float PIPTR *rval, float PIPTR *pctgood, int32 code );
PIINT32 piar_timedvalues( int32 pt, int32 PIPTR *count, int32 times[],
   float rvals[], int32 istats[], int32 prev );
PIINT32 piar_timedvaluesfil( int32 pt, int32 PIPTR *count, int32 times[],
   float rvals[], int32 istats[], char *exp );
PIINT32 piar_timefilter( int32 starttime, int32 endtime, char *exp, 
   int32 *tottime, int32 *passtime);
PIINT32 piar_value( int32 pt, int32 PIPTR *timedate, int32 mode,
   float PIPTR *rval, int32 *istat );
PIINT32 piel_addevnt( int32 PIPTR *time, int32 PIPTR *number, int32 group,
             int32 type, char *msg, int32 timeout );
PIINT32 piel_evntactn( int32 PIPTR *time, int32 PIPTR *number,
              int32 PIPTR *group, int32 *type, int32 len, char *msg, int32 action, int32 timeout );
PIINT32 pilg_checklogfile( int action, const char PIPTR *logfile );
PIINT32 pilg_formputlog( const char PIPTR *msg, const char PIPTR *idstring);
PIINT32 pilg_puthomelog( char PIPTR *msg );
PIINT32 pilg_putlog( char PIPTR *msg );
PIINT32 pilg_putoutput( char PIPTR *msg, int32 flags );
PIINT32 pipt_compspecs( int32 pt, int32 PIPTR *compdev, int32 PIPTR *compmin,
               int32 PIPTR *compmax );
PIINT32 pipt_compspecseng( int32 pt, float PIPTR *compdeveng,
              int32 PIPTR *compmin, int32 PIPTR *compmax );
PIINT32 pipt_dates( int32 pt, int32 PIPTR *creationdate, char PIPTR *creator,
           int32 crlen, int32 PIPTR *changedate, char PIPTR *changer, int32 chlen );
PIINT32 pipt_descriptor( int32 pt, char PIPTR *str, int32 len );
PIINT32 pipt_descriptorx( int32 pt, char PIPTR *str, int32 *len );
PIINT32 pipt_digcode( int32 PIPTR *digcode, char PIPTR *digstring  );
PIINT32 pipt_digcodefortag( int32 pt, int32 PIPTR *digcode, char PIPTR *digstring  );
PIINT32 pipt_digpointers( int32 pt, int32 PIPTR *digcode, int32 PIPTR *dignumb );
PIINT32 pipt_digstate( int32 digcode, char PIPTR *digstate, int32 len );
PIINT32 pipt_digstates (int32 startCode, int32 numStates, char PIPTR  * digstates,
                        int32 stateSize);
PIINT32 pipt_displaydigits (int32 point, int32 PIPTR *displaydigits );
PIINT32 pipt_engunitstring( int32 pt, char PIPTR *engunitstring, int32 len );
PIINT32 pipt_engunstring( int32 engunitcode, char PIPTR *engunitstring,
             int32 len );
PIINT32 pipt_excspecseng( int32 pt, float PIPTR *excdeveng, int32 PIPTR *excmin,
             int32 *excmax );
PIINT32 pipt_exdesc( int32 pt, char PIPTR *exdesc, int32 len );
PIINT32 pipt_exdescx( int32 pt, char PIPTR *exdesc, int32 *len );
PIINT32 pipt_findpoint( char PIPTR *tagname, int32 PIPTR *pt );
PIINT32 pipt_inprocbits( int32 pt, int32 PIPTR *larchiving,
            int32 PIPTR *lcompressing, int32 PIPTR *filtercode );
PIINT32 pipt_instrumenttag ( int32 pt, char PIPTR *instrumenttag, int32 len );
PIINT32 pipt_instrumenttagx ( int32 pt, char PIPTR *instrumenttag, int32 *len );
PIINT32 pipt_location( int32 pt, int32 location[5] );
PIINT32 pipt_nextptwsource( char source, int32 PIPTR *pt );
PIINT32 pipt_pointid( int32 pt, int32 PIPTR *ipt );
PIINT32 pipt_pointsource( int32 pt, char PIPTR *source );
PIINT32 pipt_pointsourcelong( int32 pt, char PIPTR *source, int32 len );
PIINT32 pipt_pointtype( int32 pt, char PIPTR *type );
PIINT32 pipt_ptexist( int32 pt );
PIINT32 pipt_recordtype( int32 pt, int32 PIPTR *steps );
PIINT32 pipt_rescode( int32 pt, int32 PIPTR *rescode );
PIINT32 pipt_scale( int32 pt, float PIPTR *zero, float PIPTR *span );
PIINT32 pipt_scan( int32 pt, int32 PIPTR *lscan );
PIINT32 pipt_signupforupdates( void );
PIINT32 pipt_signupforupdatesfil ( char *ptsrc, int32 location1, int32 upclass );
PIINT32 pipt_sourcept ( int32 pt, int32 PIPTR *sourcept );
PIINT32 pipt_squareroot( int32 pt, int32 PIPTR *squareroot );
PIINT32 pipt_tag( int32 pt, char PIPTR *tag, int32 len );
PIINT32 pipt_taglong( int32 pt, char PIPTR *tag, int32 len );
PIINT32 pipt_tagnamex( int32 pt, char PIPTR *tag, int32 *len );
PIINT32 pipt_tagpreferred( int32 pt, char PIPTR *tag, int32 len );
PIINT32 pipt_totalspecs( int32 pt, int32 PIPTR *totalcode, float *convers );
PIINT32 pipt_typicalvalue( int32 pt, float PIPTR *typicalvalue );
PIINT32 pipt_updates( int32 PIPTR *pt, char PIPTR *tagname, int32 len,
             int32 PIPTR *mode );
PIINT32 pipt_userattribs (int32 pt, int32 PIPTR *userint1, int32 PIPTR *userint2,
             float32 PIPTR *userreal1, float32 PIPTR *userreal2);
PIINT32 pipt_wildcardsearch( char PIPTR *tagmask, int32 direction,
                int32 PIPTR *found, char PIPTR *tagname, int32 len, int32 PIPTR *pt,
                int32 PIPTR *numfound );
PIINT32 pisn_evmdisestablish( int32 PIPTR *count, int32 PIPTR *pts );
PIINT32 pisn_evmestablish( int32 PIPTR *count, int32 PIPTR *pts );
PIINT32 pisn_evmexceptions( int32 PIPTR *count, int32 PIPTR *pt,
   float PIPTR *rval, int32 PIPTR *istat, int32 PIPTR *timedate );
PIINT32 pisn_getsnapshot( int32 pt, float PIPTR *rval, int32 PIPTR *istat,
             int32 *timedate );
PIINT32 pisn_getsnapshots ( int32 *pt, float PIPTR *rval, int32 PIPTR *istat,
               int32 PIPTR *timedate, int32 PIPTR *err, int32 count );
PIINT32 pisn_putsnapshot( int32 pt, float rval,  int32 istat, int32 timedate );
PIINT32 pisn_putsnapshots ( int32 PIPTR *pt, float PIPTR *rval,
               int32 PIPTR *istat, int32 PIPTR *timedate, int32 PIPTR *err, int32 count );
PIINT32 pisn_sendexceptions( int32 pt, char type, float PIPTR *oldval,
   short PIPTR *oldstat, int32 PIPTR *oldtime, float PIPTR *prevval,
      short PIPTR *prevstat, int32 PIPTR *prevtime, float newval,
         short newstat, int32 newtime, float excdeveng, short excmin,
            short excmax, int32 PIPTR *count );
PIINT32 pisn_sendexcepstruc ( int32 pt, char type, PI_EXCEPT PIPTR *excpt,
                 int32 PIPTR *count );
/* 25jun93  *//* 98/06/05 */
#if !defined(VAX) && !defined(__vax) && !defined(vms)
PIINT32 pisn_sendexcepstrucq ( int32 pt, char type, PI_EXCEPT PIPTR *excpt,
             int32 PIPTR *count, pibool queueing, int32 PIPTR *numbpterrs,
             QERROR PIPTR *qerrs );
LPQERRORS PIWIN pisn_sendexceptionq (int32 pt, char type,
           float PIPTR *oldval, short PIPTR *oldstat, int32 PIPTR *oldtime,
           float PIPTR *prevval, short PIPTR *prevstat, int32 PIPTR *prevtime,
           float newval, short newstat, int32 newtime,
           float excdeveng, short excmin, short excmax,
           int32 PIPTR *count);
LPQERRORS PIWIN pisn_putsnapshotq ( int32 pt, float rval,
                   int32 istat, int32 timedate );
LPQERRORS PIWIN pisn_flushputsnapq ( void );
#endif

PIINT32 pitm_delay ( uint32 mseconds );
PIINT32 pitm_fastservertime(void);
PIVOID  pitm_formtime( int32 timedate, char PIPTR *timestring, int32 len );
PIVOID  pitm_intsec( int32 PIPTR *timedate, int32 PIPTR timearray[6] );
PIINT32 pitm_parsetime( char PIPTR *str, int32 reltime, int32 PIPTR *timedate);
PIVOID  pitm_secint( int32 timedate, int32 PIPTR timearray[6] );
PIINT32 pitm_servertime( int32 PIPTR *servertime );
PIINT32 pitm_servertimeutc( double PIPTR *servertimeutc);
PIINT32 pitm_fastservertimeutc(double PIPTR *servertimeutc);
PIINT32 pitm_syncwithservertime( void );
PIINT32 pitm_systime( void );
PIINT32 piut_connect( const char PIPTR *procname );
PIINT32 piut_disconnect( void );
PIINT32 piut_disconnectnode( const char PIPTR *nodename );
PIINT32 piut_fastserverversion (int32 PIPTR *minorver, char PIPTR *buildid,
                                int32 buildlen );
PIINT32 piut_getapiversion ( char PIPTR *version, int32 len );
#if defined( WIN32)
#define  piut_getprofile  GetPrivateProfileString
#else
PIINT32 piut_getprofile( const char PIPTR *, const char PIPTR *,
        const char PIPTR *, char PIPTR *, int, const char PIPTR * );
#endif
PIVOID  piut_getprotocolvers ( char PIPTR *vers, int32 len );
char PIPTR * PIPROC piut_getloginuser( void );
PIINT32 piut_getserverversion(int32 PIPTR *nodeid,
   char PIPTR *servername, int32 servernamelen,
   char PIPTR *version, int32 versionlen, char PIPTR *buildid, int32 buildidlen);
PIVOID  piut_inceventcounter( int32 counter, int32 count );
PIINT32 piut_ishome( void );
PIINT32 piut_login( const char PIPTR *, const char PIPTR *, int32 PIPTR * );
PIINT32 piut_netinfo( char PIPTR * namestr, int32 namelen,
   char PIPTR * addressstr, int32 addresslen, char PIPTR * typestr,
   int32 typelen );
PIINT32 piut_netnodeinfo( char PIPTR *namestr, int32 namelen,
   char PIPTR *addressstr, int32 addresslen, int32 PIPTR *connected );
PIINT32 piut_netserverinfo( char PIPTR *namestr, int32 namelen,
   char PIPTR *addressstr, int32 addresslen, int32 PIPTR *connected );
PIINT32 piut_setdefaultservernode( const char PIPTR *servername );
PIINT32 piut_setmaxgridsize ( uint32 size );
PIINT32 piut_setpassword(const char PIPTR *username,
        const char PIPTR *oldpassword, const char PIPTR *newpassword);
PIVOID  piut_setprocname ( const char PIPTR *pname );
PIINT32 piut_setservernode(const char PIPTR *servername);
#if defined( WIN32)
#define  piut_writeprofile  WritePrivateProfileString
#else
PIINT32 piut_writeprofile( const char PIPTR *, const char PIPTR *,
        const char PIPTR *, const char PIPTR * );
#endif
PIVOID  piut_zeroeventcounter( int32 counter );
PIVOID  piut_setbuffering(pibool);
PIBOOL  piut_isbuffered(void);

/* 22-Aug-2006 DPR Function added for point caching */
PIINT32 netdescriptorx (int32 pt, char PIPTR *descriptor, int32 *len);
PIINT32 netdigstate (int32 digcode, char PIPTR *digstate, int32 len);
PIINT32 netexdescx( int32 pt, char PIPTR *exdesc, int32 *len );
PIINT32 netinstrumenttagx ( int32 pt, char PIPTR *instrumenttag, int32 *len );
PIINT32 netnextptwsource( char source, int32 PIPTR *pt );
PIINT32 netpointupdates(int32 *pt, char PIPTR *tagname, int32 len, int32 PIPTR *mode);
PIINT32 netpointsourcelong (int32 pt, char PIPTR *source, int32 len);
PIINT32 nettagnamex( int32 pt, char PIPTR *tag, int32 *len );
PIINT32 netgetserverversion(int32 PIPTR *nodeid, char PIPTR *servername, int32 servernamelen,
                            char PIPTR *version, int32 versionlen, char PIPTR *buildid, int32 buildidlen);
PIINT32 netdigcode (int32 PIPTR *digcode, char PIPTR *digstring);

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif



/* general API defines */

/* piar_summary defines */
#define ARCTOTAL        0
#define ARCMINIMUM      1
#define ARCMAXIMUM      2
#define ARCSTDEV        3
#define ARCRANGE        4
#define ARCAVERAGE      5
#define ARCMEAN         6

/* piar_value defines */
#define ARCVALUEBEFORE  1
#define ARCVALUEAFTER   2
#define ARCVALUEINTERP  3
#define ARCVALUECODE    4

/* pilg_putoutput defines */
#define MSGLOG          0x1
#define STDOUTPUT       0x2

/* pipt_updates defines */
#define NOTAGS          0
#define POINTCREATE     1
#define POINTEDIT       2
#define POINTDELETE     3

/* piel_envtact defines */
#define ELEQSEARCH      1
#define ELGESEARCH      2
#define ELLESEARCH      3
#define ELGTSEARCH      4
#define ELLTSEARCH      5
#define ELEDIT          6       /* NOT SUPPORTED */
#define ELDELETE        7       /* NOT SUPPORTED */

/* piut_login defines  17MAY93 */
#define PILOGINOK      0x0001
#define PIREADACCESS   0x0002
#define PIWRITEACCESS  0x0004
#define PILOGINREAD    0x0008
#define PILOGINWRITE   0x0010
#define PILOGINPIUSER  0x0100
#define PILOGINVMS     0x0200
#define PILOGINUNIX    0x0400
#define PINO           0
#define PIREAD         1
#define PIREADWRITE    2


/* internal iorates */
#if !defined(WIN32)
#define   PLUS   '+'
#define   INIT   '0'
#define   GRAB   '?'
#endif

/* VMS specific defines */
#ifdef vms
#include "pivaxapi.h"
#endif

#endif     /* #ifdef __PIAPI_H  */



