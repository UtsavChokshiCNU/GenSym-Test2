/*-----------------------------------------------------------------------------

$Archive: /pi/freeze/intel/piapi/piapix.h $
$Revision: 32 $     $Date: 5/27/08 3:21p $

-------------------------------------------------------------------------------

Copyright (c) 1995-2007 OSIsoft, Inc. All rights reserved.

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

This is the header file for the extended PI-API, which supports the new data
types of the PI 3 system and subsecond timestamps.

-----------------------------------------------------------------------------*/ 
#ifndef _PIAPIX_H
#define _PIAPIX_H

#include "piapi.h"

#ifndef GETFIRST    /* caller may include 'pilogex.h' */
#define GETFIRST (0)
#define GETNEXT  (1)
#endif
#define GETSAME  (2)
#define PI_NOMOREVALUES (100)

#define PI_M_AFLAG ((int16)0x0001)
#define PI_M_QFLAG ((int16)0x0002)
#define PI_M_SFLAG ((int16)0x0004)

/* piar_putarcvaluesx defines */
#define ARCNOREPLACE 3     /* add unless event(s) exist at same time (PI 2.x) */
#define ARCAPPEND    4     /* add event regardless of existing events; this will create 
                            * a duplicate if there is an event at the same time already 
                            * in the archive. If ARCAPPEND is called with a value newer 
                            * than the snapshot, however, this value will be subject to 
                            * compression.
                            */
#define ARCREPLACE   5     /* add event, replace if event at same time */
#define ARCREPLACEX  6     /* replace existing event (fail if no event at time) */
#define ARCDELETE    7     /* remove existing event */
#define ARCAPPENDX   8     /* add event regardless of existing events, no compression; 
                            * this means that a value newer than the snapshot is not 
                            * subject to compression. In this case, the snapshot will be 
                            * forced to the archive and the new value will become the 
                            * snapshot.
                            */
#ifdef __cplusplus
extern "C" {
#endif

/*=== PI-API-X Definitions ============================================================*/
typedef struct _PITIMESTAMP {
   int32 month;    /* 1-12 */
   int32 year;     /* four digit */
   int32 day;      /* 1-31 */
   int32 hour;     /* 0-23 */
   int32 minute;   /* 0-59 */
   int32 tzinfo;   /* timezone information */
   double second; /* 0-59.99999999.... */
} PITIMESTAMP;

/*=======================================================================================
NOTE: this PIvaluetype typedef must be kept current with the definition in PIVALUE.HXX
=======================================================================================*/
typedef enum _PIvaluetype {
   PI_Type_null = 0,
   PI_Type_bool,
   PI_Type_uint8,
   PI_Type_int8,
   PI_Type_char,
   PI_Type_uint16,
   PI_Type_int16,
   PI_Type_uint32,
   PI_Type_int32,
   PI_Type_uint64,
   PI_Type_int64,
   PI_Type_float16,
   PI_Type_float32,
   PI_Type_float64,
   PI_Type_PI2,
   PI_Type_digital = 101,
   PI_Type_blob,
   PI_Type_PItimestamp = 104,
   PI_Type_PIstring,
   PI_Type_bad = 255
} PIvaluetype;

typedef struct _pi_event
{
   PIvaluetype typex;
   float64  drval;
   int32    ival;
   void     *bval;  /* Set to NULL if not used. */
   uint32   bsize;
   int32    istat;
   int16    flags;
   PITIMESTAMP timestamp;
} PI_EVENT;

typedef struct _pi_exceptstru
{
   PI_EVENT *newvalue;  /* Must be allocated */
   PI_EVENT *prevvalue; /* Must be set to NULL if not allocated */
   PI_EVENT *oldvalue;  /* Must be set to NULL if not allocated */
   float64   excdeveng;
   float64   excmin;
   float64   excmax;
} PI_EXCEPTSTRU;

/*=== PI-API-X Function Prototypes ====================================================*/
int32 PIPROC piar_getarcvaluesx( int32 ptnum, int32 arcmode, int32 PIPTR *count,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp0,
   PITIMESTAMP PIPTR *timestamp, int32 funccode);
int32 PIPROC piar_getarcvaluesfilterx(int32 ptnum, int32 arcmode, int32 PIPTR *count,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp0,
   PITIMESTAMP PIPTR *timestamp, char PIPTR *expression, int32 funccode);
int32 PIPROC piar_getarcvaluex( int32 ptnum, int32 mode, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp);
int32 PIPROC piar_putarcvaluesx(int32 count, int32 mode, int32 PIPTR *ptnum,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR **bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp,
   int32 PIPTR *errors);
int32 PIPROC piar_putarcvaluex(int32 ptnum, int32 mode, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp);

int32 PIPROC pipt_pointtypex( int32 ptnum, PIvaluetype PIPTR *typex);

int32 PIPROC pisn_evmexceptionsx( int32 PIPTR *count, int32 PIPTR *ptnum,
   PI_EVENT PIPTR *values, int32 funccode);
int32 PIPROC pisn_flushputsnapqx( int32 PIPTR *numbpterrs, QERROR PIPTR *qerrs);
int32 PIPROC pisn_getsnapshotsx( int32 PIPTR *ptnum, int32 PIPTR *count_ptnum,
   float64 PIPTR *rval, int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize,
   int32 PIPTR *istat, int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp,
   int32 PIPTR *error, int32 funccode);
int32 PIPROC pisn_getsnapshotx( int32 ptnum, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp);
int32 PIPROC pisn_putsnapshotqx( int32 ptnum, float64 PIPTR *rval, int32 PIPTR *ival,
   void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat,  int16 PIPTR *flags,
   PITIMESTAMP PIPTR *timestamp, pibool queueing, int32 PIPTR *numbpterrs,
   QERROR PIPTR *qerrs );
int32 PIPROC pisn_putsnapshotsx( int32 count, int32 PIPTR *ptnum, float64 PIPTR *rval,
   int32 PIPTR *ival, void PIPTR **bval, uint32 PIPTR *bsize, int32 PIPTR *istat,
   int16 PIPTR *flags, PITIMESTAMP PIPTR *timestamp, int32 PIPTR *errors);
int32 PIPROC pisn_putsnapshotx(int32 ptnum, float64 PIPTR *rval, int32 PIPTR *ival,
   void PIPTR *bval, uint32 PIPTR *bsize, int32 PIPTR *istat, int16 PIPTR *flags,
   PITIMESTAMP PIPTR *timestamp);
int32 PIPROC pisn_sendexceptionqx( int32 pt,
      PI_EVENT PIPTR *oldvalue, PI_EVENT PIPTR *prevvalue, PI_EVENT newvalue,
      float64 excdeveng, float64 excmin, float64 excmax, int32 PIPTR *count,
      pibool queueing, int32 PIPTR *numbpterrs, QERROR PIPTR *qerrs );
int32 PIPROC pisn_sendexceptionsx( int32 num_pts, int32 PIPTR *pt,
   PI_EXCEPTSTRU PIPTR **excepts, int32 PIPTR *errors, int32 PIPTR *count);
PIINT32 pipt_nextptwsourcelong (char* pointsource, int32 PIPTR *pt);
PIINT32 piut_setappidentity(char *guid);
PIINT32 piut_isconnected();

int32 PIPROC pitm_isdst(PITIMESTAMP PIPTR *timestamp);
int32 PIPROC pitm_getpitime(PITIMESTAMP PIPTR *timestamp, float64 PIPTR *frac);
double PIPROC pitm_getutctime(PITIMESTAMP PIPTR *timestamp);
void PIPROC pitm_setcurtime(PITIMESTAMP PIPTR *timestamp, pibool incl_subsec);
int32 PIPROC pitm_setpitime(PITIMESTAMP PIPTR *timestamp, int32 pitime, float64 frac);
int32 PIPROC pitm_settime(PITIMESTAMP PIPTR *timestamp, int32 year, int32 month,
   int32 day, int32 hour, int32 minute, float64 second);
void PIPROC pitm_setdst(PITIMESTAMP PIPTR *timestamp, int32 tm_isdst);

int32 PIPROC piut_errormsg(int32 stat, TCHAR PIPTR *msg, size_t PIPTR *msglen);
int32 PIPROC piut_strerror(int32 stat, TCHAR PIPTR *msg, size_t PIPTR *msglen,
                           const TCHAR PIPTR *filter);
PIINT32 piut_syscommand(char PIPTR *command, char PIPTR *outfilename,
                        int32 PIPTR *sysstatus);
PIINT32 piut_putfile(char PIPTR *localfilename, char PIPTR *remotefilename,
                     int32 len);

/* 22-Aug-2006 DPR Function added for point caching */
int32 PIPROC getpointtypex(int32 pt, PIvaluetype PIPTR *typex);
PIINT32 netnextptwsourcelong (char* pointsource, int32 PIPTR *pt);

#ifdef __cplusplus
}
#endif

#endif /* ifdef _PIAPIX_H */
