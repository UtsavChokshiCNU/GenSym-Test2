



/*****************************************************************************
*                                                                            *
*  Copyright 1989, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                         U.S. Patent No 4,785,391                           *
*                           Other Patent Pending                             *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
*****************************************************************************/
/********************* Revision Control Information **********************************
*                                                                                    *
*     $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/speedo/out_wht.c,v 1.1 1995-10-03 01:03:35 jra Exp $                                                                       *
*                                                                                    *
*     $Log: not supported by cvs2svn $
*     Revision 1.5  1993/04/23 22:53:01  mhd
*     fixed comment
*
 * Revision 1.4  1993/04/23  22:43:38  mhd
 * Fixed problem in the changelog comment itself.
 *
 * Revision 1.3  1993/04/23  22:34:55  mhd
 * I moved these here from the inner block of the function below; static
 * function declarations are illegal in ANSI C.
 *   static void  intersect_2vect();
 *   static void  ww_line();
 *
 * Revision 1.2  1993/04/19  15:32:01  mpc
 * Changed def of intersect_2vect() from void to static void, per bitstream.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:20  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
*       Revision 28.37  93/03/15  12:47:41  roberte
*       Release
*       
*       Revision 28.13  93/03/09  10:17:56  roberte
*       Made this module truly REENTRANT by moving its' static variables
*       from here to SPEEDO_GLOBALS structure.  Found some int data types,
*       investigated them and changed them as appropriate.  Moved #define
*       of NORTS to speedo.h as well.  Added some function prototypes
*       of some neglected static functions.
*       
*       Revision 28.12  93/01/29  09:09:25  roberte
*       Added reentrant code macros PARAMS1 and PARAMS2 I overlooked earlier for whichway() and ww_line().
*       
*       Revision 28.11  93/01/07  12:06:53  roberte
*       Corrected a comment.
*       
*       Revision 28.10  93/01/04  16:41:36  roberte
*       Changed all references to new union fields of SPEEDO_GLOBALS to sp_globals.processor.speedo prefix.
*       
*       Revision 28.9  92/12/30  17:47:30  roberte
*       Functions no longer renamed in spdo_prv.h now declared with "sp_"
*       Use PARAMS1&2 macros throughout.
*       
*       Revision 28.8  92/12/14  15:28:31  weili
*       Modified sp_proc_intercepts_white(PARAMS1) to fix the -x
*       bits problems aused by characters below 6 lines.
*       Modified sp_init_white(PARAMS1) to hardcode the displacement
*       vector to be 128.
*       
*       Revision 28.7  92/11/24  18:48:48  laurar
*       correct typo.
*       
*       Revision 28.6  92/11/24  12:05:16  laurar
*       include fino.h
*       
*       Revision 28.5  92/11/19  15:17:44  roberte
*       Release
*       
*       Revision 28.1  92/06/25  13:41:28  leeann
*       Release
*       
*       Revision 27.1  92/03/23  14:01:12  leeann
*       Release
*       
*       Revision 26.1  92/01/30  17:00:33  leeann
*       Release
*       
*       Revision 25.1  91/07/10  11:06:16  leeann
*       Release
*       
*       Revision 24.1  91/07/10  10:39:51  leeann
*       Release
*       
*       Revision 23.1  91/07/09  18:00:51  leeann
*       Release
*       
*       Revision 22.2  91/04/08  17:09:37  joyce
*       
*       Replacement for old white writer module. This thickens
*       the stroke by one pixel (change made by Mike Yudis)
*       
*       Revision 22.1  91/01/23  17:20:05  leeann
*       Release
*       
*       Revision 21.1  90/11/20  14:39:17  leeann
*       Release
*       
*       Revision 20.1  90/11/12  09:32:05  leeann
*       Release
*       
*       Revision 19.1  90/11/08  10:24:40  leeann
*       Release
*       
*       Revision 18.1  90/09/24  10:15:45  mark
*       Release
*       
*       Revision 17.1  90/09/13  16:00:13  mark
*       Release name rel0913
*       
*       Revision 16.1  90/09/11  13:20:57  mark
*       Release
*       
*       Revision 15.1  90/08/29  10:04:33  mark
*       Release name rel0829
*       
*       Revision 14.1  90/07/13  10:40:56  mark
*       Release name rel071390
*       
*       Revision 13.1  90/07/02  10:40:00  mark
*       Release name REL2070290
*       
*       Revision 12.1  90/04/23  12:13:07  mark
*       Release name REL20
*       
*       Revision 11.1  90/04/23  10:13:21  mark
*       Release name REV2
*       
*       Revision 10.1  89/07/28  18:11:00  mark
*       Release name PRODUCT
*       
*       Revision 9.1  89/07/27  10:24:22  mark
*       Release name PRODUCT
*       
*       Revision 8.1  89/07/13  18:20:32  mark
*       Release name Product
*       
*       Revision 7.1  89/07/11  09:02:37  mark
*       Release name PRODUCT
*       
*       Revision 6.3  89/07/09  14:47:07  mark
*       make specsarg argument to init_white GLOBALFAR
*       
*       Revision 6.2  89/07/09  13:19:22  mark
*       changed arguments to sp_open_bitmap to contain
*       new high resolution positioning information
*           
*       
*       Revision 6.1  89/06/19  08:36:00  mark
*       Release name prod
*       
*       Revision 5.4  89/06/06  17:23:43  mark
*       add curve depth to output module curve functions
*       
*       Revision 5.3  89/06/05  17:21:23  mark
*       reference intercept lists via new symbol sp_intercepts so
*       that they may conditionally be allocated off the stack for
*       reentrant mode
*       
*       Revision 5.2  89/06/01  16:54:16  mark
*       changed declaration of begin_char_white to boolean,
*       return TRUE
*       
*       Revision 5.1  89/05/01  17:55:01  mark
*       Release name Beta
*       
*       Revision 4.2  89/05/01  17:14:16  mark
*       remove unreferenced local variables
*       
*       Revision 4.1  89/04/27  12:16:58  mark
*       Release name Beta
*       
*       Revision 3.2  89/04/27  10:16:05  csdf
*       Fixed the "+" problem where the left half and right half of the 
*       cross-bar (on things like "t" too) would be different thicknesses.
*       
*       Revision 3.1  89/04/25  08:30:03  mark
*       Release name beta
*       
*       Revision 2.2  89/04/12  12:12:29  mark
*       added stuff for far stack and font
*       
*       Revision 2.1  89/04/04  13:36:17  mark
*       Release name EVAL
*       
*       Revision 1.6  89/04/04  13:22:12  mark
*       Update copyright text
*       
*       Revision 1.5  89/03/31  14:49:09  mark
*       change arguments to open_bitmap
*       change speedo.h to spdo_prv.h
*       eliminate thresh
*       change fontware to comments to speedo
*       
*       Revision 1.4  89/03/30  17:51:03  john
*       Calculation of normal moved to set_spcs.c
*       Bitmap extents and initial band simplified to take
*       advantage of reliable bounding box data.
*       
*       Revision 1.3  89/03/29  16:10:04  mark
*       changes for slot independence and dynamic/reentrant
*       data allocation
*       
*       Revision 1.2  89/03/21  13:28:26  mark
*       change name from oemfw.h to speedo.h
*       
*       Revision 1.1  89/03/15  12:34:13  mark
*       Initial revision
*                                                                                 *
*                                                                                    *
*************************************************************************************/

#ifdef RCSSTATUS
static char rcsid[] = "$Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/speedo/out_wht.c,v 1.1 1995-10-03 01:03:35 jra Exp $";
#endif

/*************************** O U T _ 1 _ 1 . C *******************************
 *                                                                           *
 * This is an output module for write-writer mode.                           *
 *                                                                           *
 ********************** R E V I S I O N   H I S T O R Y **********************
 *                                                                           *
 *  1) 16 Dec 88  jsc  Created                                               *
 *                                                                           *
 *  2) 23 Jan 89  jsc  normal computed from tcb.xtype, tcb.ytype now it is   *
 *                     no longer a member of tcb                             *
 *                                                                           *
 *  3) 27 Jan 89  cdf  merged white-write code into black_writer to make     *
 *                     this                                                  *
 *                                                                           *
 *  4)  2 Feb 89  cdf  froze changes for white writer. added comments        *
 *                                                                           *
 *  5)  7 Feb 89  jsc  Additional commenting.                                *
 *                                                                           *
 *  6) 16 Feb 89  jsc  init_out1() function added.                           *
 *                                                                           *
 ****************************************************************************/
#include "spdo_prv.h"               /* General definitions for Speedo   */
#include "fino.h"


#define DEBUG_INT  0
#define DEBUGWW    0
#define DEBUG      0
#define LOCAL      static
#define ABS(a)     (((a) >  0) ? (a) : -(a))
#define MAX(a, b)  ((a) > (b) ? (a) : (b))
#define MIN(a, b)  ((a) < (b) ? (a) : (b))

#if DEBUG_INT
#include <math.h>
#endif

#if DEBUG
#include <stdio.h>
#define SHOW(X) printf("X = %d\n", X)
#else
#define SHOW(X)
#endif


/***** GLOBAL VARIABLES *****/

/***** GLOBAL FUNCTIONS *****/

/***** EXTERNAL VARIABLES *****/

/***** EXTERNAL FUNCTIONS *****/

/***** STATIC VARIABLES *****/
#ifdef OLDWAY
static  fix7    fill_pipe;
static  point_t   PP[6];            /* 6 points (3 vectors) */
static  point_t  *PA, *PB, *PC;
static  point_t   P_contour_start;
static  point_t   Psave_0, Psave_1;
static  boolean   ww_contour_init;  /* set TRUE by begin_contour */
static  ww_info_t *ww_infoPtr;         /* comes from <specs>.out_info */
static  point_t   ww_displ;         /* displacement vector */
static  fix7      ww_nrt_size;      /* # entries in normal table */
static  fix15     ww_x0_spxl, ww_y0_spxl;       /* coordinates of current (shifted) vector in subpixels */
static  fix15     ww_y_pxl;         /* Y coord of current (shifted) point (whole pixels) */
static  fix15     ww_normal[NORTS][2]; /* a table of normals for the white
                                        writer algorithm */
#endif /* OLDWAY */

#if INCL_WHITE
static  fix15  tangnt[NORTS][2] =   /* table of tangents, 0 to 45 */
{ {16384, 0},    {16382, 256},  {16376, 512},  {16366, 767},
  {16352, 1022}, {16334, 1276}, {16312, 1529}, {16287, 1781},
  {16257, 2032}, {16224, 2282}, {16188, 2529}, {16147, 2775},
  {16103, 3019}, {16056, 3261}, {16006, 3501}, {15952, 3739},
  {15895, 3974}, {15835, 4206}, {15772, 4436}, {15706, 4663},
  {15638, 4887}, {15567, 5108}, {15494, 5326}, {15419, 5541},
  {15341, 5753}, {15261, 5961}, {15179, 6167}, {15096, 6368},
  {15010, 6567}, {14923, 6762}, {14835, 6954}, {14745, 7142},
  {14654, 7327}, {14562, 7509}, {14469, 7687}, {14375, 7861},
  {14280, 8032}, {14184, 8200}, {14088, 8365}, {13991, 8526},
  {13894, 8684}, {13796, 8838}, {13698, 8989}, {13600, 9137},
  {13501, 9282}, {13403, 9424}, {13304, 9562}, {13206, 9698},
  {13107, 9830}, {13009, 9960}, {12911, 10087}, {12813, 10211},
  {12716, 10332}, {12619, 10450}, {12522, 10566}, {12426, 10679},
  {12330, 10789}, {12235, 10897}, {12140, 11002}, {12046, 11105},
  {11953, 11206}, {11860, 11304}, {11768, 11400}, {11676, 11494},
  {11585, 11585} };
#endif

/***** STATIC FUNCTIONS *****/
#if INCL_WHITE
static fix15 whichway PROTO((PROTO_DECL2 point_t V00,point_t V01,point_t V10,point_t V11));
static void ww_line PROTO((PROTO_DECL2 point_t P1));
static void  intersect_2vect PROTO((point_t V00, point_t V01, point_t V10, point_t V11, point_t *Pout));
static fix15  bit_count PROTO((fix31 arg));
#endif


#if INCL_WHITE
FUNCTION boolean sp_init_white(PARAMS2 specsarg)
GDECL
specs_t GLOBALFAR *specsarg;
/*
 * init_out0() is called by sp_set_specs(PARAMS1) to initialize the output module.
 * Returns TRUE if output module can accept requested specifications.
 * Returns FALSE otherwise.
 */
{
int  ii, shift, round;

#if DEBUG
printf("INIT_WHITE()\n");
#endif
if (specsarg->flags & CURVES_OUT)
    return FALSE;           /* Curves out not supported */
sp_globals.ww_nrt_size = NORTS - 1;
/* displacement vector */
sp_globals.ww_infoPtr = (ww_info_t *)specsarg->out_info;
/* hardcoded the displacement vector to be 128, that's half pixel */
sp_globals.ww_displ.x = ((fix31)(128) * sp_globals.onepix) >> 8;
sp_globals.ww_displ.y = ((fix31)(128) * sp_globals.onepix) >> 8;
shift = 15 - sp_globals.pixshift;       /* 0.5 pixel expansion */
round = 1 << (shift - 1);
for (ii=0; ii<NORTS; ii++)
    {
    sp_globals.ww_normal[ii][0] = (tangnt[ii][1] + round) >> shift;
    sp_globals.ww_normal[ii][1] = -((tangnt[ii][0] + round) >> shift);
    }
return (TRUE);
}
#endif


#if INCL_WHITE
FUNCTION boolean sp_begin_char_white(PARAMS2 Psw, Pmin, Pmax)
GDECL
point_t Psw;
point_t Pmin;
point_t Pmax;
/* Called once at the start of the character generation process
 */
{
#if DEBUG
printf("BEGIN_CHAR_WHITE(%3.1f, %3.1f, %3.1f, %3.1f, %3.1f, %3.1f\n",
                    (real)Psw.x / (real)sp_globals.onepix, (real)Psw.y / (real)sp_globals.onepix,
                    (real)Pmin.x / (real)sp_globals.onepix, (real)Pmin.y / (real)sp_globals.onepix,
                    (real)Pmax.x / (real)sp_globals.onepix, (real)Pmax.y / (real)sp_globals.onepix);
#endif
Pmin.x -= sp_globals.onepix;            /* expand bbox outward by 1 pixel */
Pmin.y -= sp_globals.onepix;            /* for white-writer */
Pmax.x += sp_globals.onepix;
Pmax.y += sp_globals.onepix;
sp_init_char_out(PARAMS2 Psw,Pmin,Pmax);
return TRUE;
}
#endif


#if INCL_WHITE
FUNCTION void sp_begin_contour_white(PARAMS2 P1, outside)
GDECL
point_t P1;                   
boolean outside;
/* Called at the start of each contour
 */
{

#if DEBUG
printf("BEGIN_CONTOUR_WHITE(%3.4f, %3.4f, %s)\n", 
    (real)P1.x / (real)sp_globals.onepix, (real)P1.y / (real)sp_globals.onepix, outside? "outside": "inside");
#endif
sp_globals.PA = sp_globals.PP;                                /* endpoints of 1st vector in pipeline */
sp_globals.PB = sp_globals.PA + 2;                            /* endpoints of 2nd vector in pipeline */
sp_globals.PC = sp_globals.PB + 2;                            /* endpoints of current vector */
sp_globals.fill_pipe = 2;                          /* read in 2 vectors before pipeline is filled */
sp_globals.x0_spxl = P1.x;
sp_globals.y0_spxl = P1.y;
sp_globals.y_pxl = (sp_globals.y0_spxl + sp_globals.pixrnd) >> sp_globals.pixshift;
sp_globals.ww_contour_init = TRUE;
}
#endif


#if INCL_WHITE
/* I moved these here from the inner block of the function below; static 
   function declarations are illegal in ANSI C.
   --mhd@gensym, 4/22/93
   */
static void  intersect_2vect();
static void  ww_line();
FUNCTION void sp_line_white(PARAMS2 Pcur)
GDECL
point_t Pcur;                   
/* Called for each vector in the transformed character
 */
{
         fix15    d1;
register fix31  dx, dy;
register fix15  dxa, dya;
register fix15  ii;
register fix15  nx, ny;
         point_t  P0, *P1;
register fix15  vn, vd;
register fix15  wx0, wy0, wx1, wy1;
         fix15  x0,y0,x1,y1;        /* PIX.FRAC start and endpoints */

	/* a static function declaration in an inner block is illegal in ansi c,
	   at least as far the SGI (strict ansi) compiler is concerned.  I've commented
	   and moved the following to top-level, above this function.  -mhd@gensym, 4/22/93
	   */
/*
static void  intersect_2vect();
static void  ww_line();
*/

if (sp_globals.intercept_oflo  &&  !sp_globals.extents_running)
    return;
x0 = sp_globals.x0_spxl;                /* get start of line (== current point) */
y0 = sp_globals.y0_spxl;
sp_globals.x0_spxl = x1 = Pcur.x;      /* end of line */
sp_globals.y0_spxl = y1 = Pcur.y;      /*  (also update current point to end of line) */
if (x0 == x1  &&  y0 == y1)
    return;
dx = x1 - x0;
dy = y1 - y0;
if (dx >= 0)
    dxa = dx;
else
    dxa = -dx;
if (dy >= 0)
    dya = dy;
else
    dya = -dy;
if (dxa <= dya)
    {
    vn = dxa;
    vd = dya;
    }
else
    {
    vn = dya;
    vd = dxa;
    }
ii = ((fix31)vn * (fix31)sp_globals.ww_nrt_size + (vd >> 1)) / vd;
nx = sp_globals.ww_normal[ii][0];                     /* normal tables set up for */
ny = sp_globals.ww_normal[ii][1];                     /*   1st octant (0 to 45 dg) and */
if (dya > dxa)                          /*   Speedo rules for curve direction. */
    {                                   /* octants 2,3,6,7 */
    ii = -nx;
    nx = -ny;
    ny = ii;
    }
if (dx < 0)                             /* 2nd + 3rd quadrants */
    ny = -ny;
if (dy < 0)                             /* 3rd + 4th quadrants */
    nx = -nx;
if (sp_globals.tcb0.mirror == -1)
    {
    nx = -nx;
    ny = -ny;
    }
wx0 = x0 + nx + sp_globals.ww_displ.x;             /* the new vector, displaced _outwards_  */
wy0 = y0 + ny + sp_globals.ww_displ.y;             /* by ___ pixels from the original.  */
wx1 = x1 + nx + sp_globals.ww_displ.x;
wy1 = y1 + ny + sp_globals.ww_displ.y;

if (sp_globals.fill_pipe > 0)
    {
    if (sp_globals.fill_pipe == 2)
        {
        sp_globals.PA[0].x = wx0;
        sp_globals.PA[0].y = wy0;
        sp_globals.PA[1].x = wx1;
        sp_globals.PA[1].y = wy1;
        sp_globals.Psave_0.x = x1;                 /* save first original vector for */
        sp_globals.Psave_0.y = y1;                 /* end of contour processing */
        }
    else
        {
        sp_globals.PB[0].x = wx0;
        sp_globals.PB[0].y = wy0;
        sp_globals.PB[1].x = wx1;
        sp_globals.PB[1].y = wy1;
        sp_globals.Psave_1.x = x1;                 /* save second original vector for */
        sp_globals.Psave_1.y = y1;                 /* end of contour processing */
        }
    }

#if DEBUG
printf("LINE_WHITE(%3.4f, %3.4f)\n", 
       (real)Pcur.x/(real)sp_globals.onepix, 
       (real)Pcur.y/(real)sp_globals.onepix);
#endif

if (sp_globals.extents_running)
    {
    if (wx0 > sp_globals.bmap_xmax)         
        sp_globals.bmap_xmax = wx0;
    if (wx1 > sp_globals.bmap_xmax)         
        sp_globals.bmap_xmax = wx1;
    if (wx0 < sp_globals.bmap_xmin)
        sp_globals.bmap_xmin = wx0;
    if (wx1 < sp_globals.bmap_xmin)
        sp_globals.bmap_xmin = wx1;
    if (wy0 > sp_globals.bmap_ymax)
        sp_globals.bmap_ymax = wy0;
    if (wy1 > sp_globals.bmap_ymax)
        sp_globals.bmap_ymax = wy1;
    if (wy0 < sp_globals.bmap_ymin)
        sp_globals.bmap_ymin = wy0;
    if (wy1 < sp_globals.bmap_ymin)
        sp_globals.bmap_ymin = wy1;
    if (sp_globals.intercept_oflo)  return;
    }

if (sp_globals.fill_pipe > 0)
    {
    sp_globals.fill_pipe--;
    return;
    }

sp_globals.PC[0].x = wx0;
sp_globals.PC[0].y = wy0;
sp_globals.PC[1].x = wx1;
sp_globals.PC[1].y = wy1;

/*  sp_globals.PA is most previous
    sp_globals.PB is previous
    sp_globals.PC is current             */
d1 = whichway (PARAMS2 sp_globals.PA[0], sp_globals.PA[1],
				sp_globals.PB[0], sp_globals.PB[1]);     /* 1 CW; -1 CCW */
if (sp_globals.ww_contour_init)
    {
    if (d1 == 1)
        {
        intersect_2vect (sp_globals.PA[0], sp_globals.PA[1], sp_globals.PB[0], 
							sp_globals.PB[1], &sp_globals.P_contour_start);
        }
    else
        {
        sp_globals.P_contour_start.x = sp_globals.PA[1].x;
        sp_globals.P_contour_start.y = sp_globals.PA[1].y;
        }
    sp_globals.ww_x0_spxl = sp_globals.P_contour_start.x;
    sp_globals.ww_y0_spxl = sp_globals.P_contour_start.y;
#if DEBUGWW
printf("WW_sp_globals.P_contour_start(%3.4f, %3.4f)\n", 
       (real)sp_globals.P_contour_start.x/(real)sp_globals.onepix, 
       (real)sp_globals.P_contour_start.y/(real)sp_globals.onepix);
#endif
    sp_globals.ww_y_pxl = (sp_globals.ww_y0_spxl + sp_globals.pixrnd) >> sp_globals.pixshift;
    sp_globals.ww_contour_init = FALSE;
    }
if (d1 == -1)                           /* Bevel-connect 2nd point of A vector */
    {                                   /*   with 1st point of B vector. */
    ww_line (PARAMS2 sp_globals.PB[0]);
    }
d1 = whichway (PARAMS2 sp_globals.PB[0], sp_globals.PB[1],
					sp_globals.PC[0], sp_globals.PC[1]);
if (d1 == -1)
    {
    ww_line (PARAMS2 sp_globals.PB[1]);                    /* a bevel connection here (next time through) */
    }
else
    {
    intersect_2vect (sp_globals.PB[0], sp_globals.PB[1], sp_globals.PC[0],
						sp_globals.PC[1], &P0);
    ww_line (PARAMS2 P0);
    }
P1 = sp_globals.PA;                                /* rotate points through pipeline */
sp_globals.PA = sp_globals.PB;
sp_globals.PB = sp_globals.PC;
sp_globals.PC = P1;
}
#endif


#if INCL_WHITE
FUNCTION static void ww_line(PARAMS2 P1)
GDECL
point_t P1;                   
{
register fix15  how_many_y;       /* # of intercepts at y = n + 1/2  */
register fix15  yc, i;            /* Current scan-line */
         fix15  temp1;            /* various uses */
         fix15  temp2;            /* various uses */
register fix31     dx_dy;            /* slope of line in 16.16 form */
register fix31     xc;               /* high-precision (16.16) x coordinate */
         fix15     x0,y0,x1,y1;      /* PIX.FRAC start and endpoints */


#if DEBUGWW
printf("WW_LINE(%3.4f, %3.4f)\n", 
       (real)P1.x/(real)sp_globals.onepix, 
       (real)P1.y/(real)sp_globals.onepix);
#endif
x0 = sp_globals.ww_x0_spxl;                        /* get start of line (== current point) */
y0 = sp_globals.ww_y0_spxl;
sp_globals.ww_x0_spxl = x1 = P1.x;                 /* end of line */
sp_globals.ww_y0_spxl = y1 = P1.y;                 /*  (also update current point to end of line) */
yc = sp_globals.ww_y_pxl;                          /* current scan line = end of last line */
sp_globals.ww_y_pxl = (y1 + sp_globals.pixrnd) >> sp_globals.pixshift;
                                        /* calculate new end-scan sp_globals.line */
if ((how_many_y = sp_globals.ww_y_pxl - yc) == 0) return;   /* Don't draw a null line */

if (how_many_y < 0) yc--; /* Predecrment downward lines */

if (yc > sp_globals.y_band.band_max) /* Is start point above band? */
    {
    if (sp_globals.ww_y_pxl > sp_globals.y_band.band_max)  return;   /* line has to go down! */
    how_many_y = sp_globals.ww_y_pxl - (yc = sp_globals.y_band.band_max) - 1;   /* Yes, limit it */
    }

if (yc < sp_globals.y_band.band_min)   /* Is start point below band? */
    {
    if (sp_globals.ww_y_pxl < sp_globals.y_band.band_min) return;   /* line has to go up! */
    how_many_y = sp_globals.ww_y_pxl - (yc = sp_globals.y_band.band_min);   /* Yes, limit it */
    }

xc = (fix31)(x0 + sp_globals.pixrnd) << (16 - sp_globals.pixshift);
                    /* Original x coordinate with built in rounding. 16.16 form */


if ( (temp1 = (x1 - x0)) == 0)  /* check for vertical line */
    {
    yc -= sp_globals.y_band.band_min; /* yc is now an offset relative to the band */
    temp1 = (fix15)(xc >> 16); 
    if (how_many_y < 0)
        {   /* Vector down */
        if ((how_many_y += yc + 1) < 0) how_many_y = 0; /* can't go below 0 */
        for (i = yc; i >= how_many_y; i--)
            sp_add_intercept_white(PARAMS2 i,temp1); 
        }
    else
        {   /* Vector up */
     /* check to see that line doesn't extend beyond top of band */
        if ((how_many_y += yc) > sp_globals.no_y_lists) how_many_y = sp_globals.no_y_lists;
        for (i = yc; i != how_many_y; i++)
            sp_add_intercept_white(PARAMS2 i,temp1); 
        }
    return;
    }
          
/* calculate dx_dy at 16.16 fixed point */

dx_dy = ( (fix31)temp1 << 16 )/(fix31)(y1 - y0);

/* We have to check for a @#$%@# possible multiply overflow  */
/* by doing another @#$*& multiply.  In assembly language,   */
/* the program could just check the OVerflow flag or whatever*/
/* works on the particular processor.  This C code is meant  */
/* to be processor independant.                              */

temp1 = (yc << sp_globals.pixshift) - y0 + sp_globals.pixrnd;
/* This sees if the sign bits start at bit 15 */
/* if they do, no overflow has occurred       */

temp2 = (fix15)(MULT16(temp1,(fix15)(dx_dy >> 16)) >> 15);

if (  (temp2 != (fix15)0xFFFF) &&
      (temp2 != 0x0000) &&
      /* Overflow. Pick point closest to yc + .5 */
    (ABS(temp1) < ABS((yc << sp_globals.pixshift) - y1 + sp_globals.pixrnd)) )
    { /* use x1 instead of x0 */
    xc = (fix31)(x1 + sp_globals.pixrnd) << (16 - sp_globals.pixshift);
    }
else
    {
/* calculate new xc at the center of the *current* scan line */
/* due to banding, yc may be several lines away from y0      */
/*  xc += (yc + .5 - y0) * dx_dy */
/* This multiply generates a subpixel delta. */
/* So we shift it to be a 16.16 delta */

    xc += ((fix31)temp1 * dx_dy) >> sp_globals.pixshift;
    }

yc -= sp_globals.y_band.band_min; /* yc is now an offset relative to the band */

if (how_many_y < 0)
    {   /* Vector down */
    if (how_many_y == -1)
        sp_add_intercept_white(PARAMS2 yc, (fix15) (xc >> 16));
    else
        {
        if ((how_many_y += yc + 1) < 0) how_many_y = 0; /* can't go below 0 */
        for (i = yc; i >= how_many_y; i--)
            {
            temp1 = (fix15)(xc >> 16); 
            sp_add_intercept_white(PARAMS2 i,temp1); 
            xc -= dx_dy;
            }
        }
    }
    else
    {   /* Vector up */
     /* check to see that line doesn't extend beyond top of band */
    if (how_many_y == 1)
        sp_add_intercept_white(PARAMS2 yc, (fix15) (xc >> 16));
    else
        {
        if ((how_many_y += yc) > sp_globals.no_y_lists) how_many_y = sp_globals.no_y_lists;
        for (i = yc; i != how_many_y; i++)
            {
            temp1 = (fix15)(xc >> 16);
            sp_add_intercept_white(PARAMS2 i,temp1); 
            xc += dx_dy;
            }
        }
    }
}
#endif


#if INCL_WHITE
FUNCTION void sp_end_contour_white(PARAMS1)
GDECL
/* Called after the last vector in each contour
 */
{
#if DEBUG
printf("END_CONTOUR_WHITE()\n");
#endif
fn_line(sp_globals.Psave_0);
fn_line(sp_globals.Psave_1);
}
#endif


#if INCL_WHITE
FUNCTION boolean sp_end_char_white(PARAMS1)
GDECL
/* Called when all character data has been output
 * Return TRUE if output process is complete
 * Return FALSE to repeat output of the transformed data beginning
 * with the first contour
 */
{

fix31 xorg;
fix31 yorg;
void  sp_proc_intercepts_white();
#if INCL_CLIPPING
fix31 em_max, em_min, bmap_max, bmap_min;
#endif

#if DEBUG
printf("END_CHAR_WHITE()\n");
#endif

if (sp_globals.first_pass)
    {
    if (sp_globals.bmap_xmax >= sp_globals.bmap_xmin)
        {
        sp_globals.xmin = (sp_globals.bmap_xmin + sp_globals.pixrnd + 1) >> sp_globals.pixshift;
        sp_globals.xmax = (sp_globals.bmap_xmax + sp_globals.pixrnd) >> sp_globals.pixshift;
        }
    else
        {
        sp_globals.xmin = sp_globals.xmax = 0;
        }
    if (sp_globals.bmap_ymax >= sp_globals.bmap_ymin)
        {

#if INCL_CLIPPING
        if (sp_globals.specs.flags & CLIP_TOP)
            {
            em_max = (fix31)((fix31)EM_TOP * sp_globals.tcb0.yppo + sp_globals.mprnd);
            em_max = em_max >> sp_globals.multshift;
            bmap_max = (sp_globals.bmap_ymax + sp_globals.pixrnd) >> sp_globals.pixshift;
            if (bmap_max < em_max)
                sp_globals.ymax=bmap_max;
            else
                sp_globals.ymax=em_max;
            }
        else
#endif

            sp_globals.ymax = (sp_globals.bmap_ymax + sp_globals.pixrnd) >> sp_globals.pixshift;

#if INCL_CLIPPING
        if (sp_globals.specs.flags & CLIP_BOTTOM)
            {
            em_min = (fix31)((fix31)EM_BOT * sp_globals.tcb0.yppo + sp_globals.mprnd);
            em_min = em_min >> sp_globals.multshift;
            bmap_min = (sp_globals.bmap_ymin + sp_globals.pixrnd + 1) >> sp_globals.pixshift;
            if (bmap_min < em_min)
                sp_globals.ymin = em_min;
            else
                sp_globals.ymin = bmap_min;
            }
    else
#endif

        sp_globals.ymin = (sp_globals.bmap_ymin + sp_globals.pixrnd + 1) >> sp_globals.pixshift;
        }
    else
        {
        sp_globals.ymin = sp_globals.ymax = 0;
        }

    /* add in the rounded out part (from xform.) of the left edge */
    if (sp_globals.tcb.xmode == 0)    /* for X pix is function of X orus only add the round */
        xorg = (((fix31)sp_globals.xmin << 16) + (sp_globals.rnd_xmin << sp_globals.poshift));
    else
        if (sp_globals.tcb.xmode == 1) /* for X pix is function of -X orus only, subtr. round */
            xorg = (((fix31)sp_globals.xmin << 16) - (sp_globals.rnd_xmin << sp_globals.poshift)) ;
        else
            xorg = (fix31)sp_globals.xmin << 16;   /* for other cases don't use round on x */
           
    if (sp_globals.tcb.ymode == 2)   /* for Y pix is function of X orus only, add round error */ 
        yorg = (((fix31)sp_globals.ymin << 16) + (sp_globals.rnd_xmin << sp_globals.poshift));
    else
        if (sp_globals.tcb.ymode == 3) /* for Y pix is function of -X orus only, sub round */
            yorg = (((fix31)sp_globals.ymin << 16) - (sp_globals.rnd_xmin << sp_globals.poshift));
        else                          /* all other cases have no round error on yorg */
            yorg = (fix31)sp_globals.ymin << 16;

    open_bitmap(sp_globals.set_width.x, sp_globals.set_width.y, xorg, yorg,
                sp_globals.xmax - sp_globals.xmin, sp_globals.ymax -  sp_globals.ymin);
    if (sp_globals.intercept_oflo)
        {
        sp_globals.y_band.band_min = sp_globals.ymin;
        sp_globals.y_band.band_max = sp_globals.ymax;
        sp_init_intercepts_out(PARAMS1);
        sp_globals.first_pass = FALSE;
        sp_globals.extents_running = FALSE;
        return FALSE;
        }
    else
        {
        sp_proc_intercepts_white(PARAMS1);
        close_bitmap();
        return TRUE;
        }
    }
else
    {
    if (sp_globals.intercept_oflo)
        {
        sp_reduce_band_size_out(PARAMS1);
        sp_init_intercepts_out(PARAMS1);
        return FALSE;
        }
    else
        {
        sp_proc_intercepts_white(PARAMS1);
        if (sp_next_band_out(PARAMS1))
            {
            sp_init_intercepts_out(PARAMS1);
            return FALSE;
            }
        close_bitmap();
        return TRUE;
        }
    }
}
#endif


#if INCL_WHITE
FUNCTION  static void  intersect_2vect (V00, V01, V10, V11, Pout)
  point_t  V00, V01, V10, V11;      /* coordinates in shifted pixels */
  point_t *Pout;                    /* intersection point */
{
#if DEBUG_INT
real  x0, x1, x2, x3, x4;
real  y0, y1, y2, y3, y4;
real  q;
real   save_x4, save_y4;
fix15  save_x, save_y;
#endif

fix31  lmu, lq, lx, ly;
fix15  sign;
fix15  b1, b2, b3, sh1, sh2;

#if DEBUG_INT
x0 = V00.x;
y0 = V00.y;
x1 = V01.x;
y1 = V01.y;
x2 = V10.x;
y2 = V10.y;
x3 = V11.x;
y3 = V11.y;
q = (x1 - x0)*(y3 - y2) - (y1 - y0)*(x3 - x2);
if (q == 0.0)
    {
    x4 = y4 = save_x4 = save_y4 = 0;
    Pout->x = x2;
    Pout->y = y2;
    save_x = Pout->x; save_y = Pout->y;
    }
else
    {
    x4 = ((x3 - x2) * (x1*y0 - x0*y1) - (x1 - x0) * (x3*y2 - x2*y3)) / q;
    y4 = ((y3 - y2) * (x1*y0 - x0*y1) - (y1 - y0) * (x3*y2 - x2*y3)) / q;
    save_x4 = (x3 - x2) * (x1*y0 - x0*y1) - (x1 - x0) * (x3*y2 - x2*y3);
    save_y4 = (y3 - y2) * (x1*y0 - x0*y1) - (y1 - y0) * (x3*y2 - x2*y3);
    Pout->x = (fix15)(floor(x4 + 0.5));
    Pout->y = (fix15)(floor(y4 + 0.5));
    save_x = Pout->x; save_y = Pout->y;
    }
#endif

lq = ((fix31)V01.x - V00.x) * ((fix31)V11.y - V10.y) -
             ((fix31)V01.y - V00.y) * ((fix31)V11.x - V10.x);
if (lq == 0)                            /* divide by 0? */
    {
    Pout->x = V10.x;
    Pout->y = V10.y;
    return;
    }
lmu = ((fix31)V11.x - V00.x) * ((fix31)V10.y - V00.y) -
              ((fix31)V10.x - V00.x) * ((fix31)V11.y - V00.y);
if (ABS(lmu) <= 65535)
    {
    lx = (((fix31)V01.x - V00.x) * lmu + (lq >> 1)) / lq;
    ly = (((fix31)V01.y - V00.y) * lmu + (lq >> 1)) / lq;
    }
else
    {
    sign = 1;
    if (lmu < 0)
        {
        sign = -1;
        lmu = -lmu;
        }
    if (lq < 0)
        {
        lq = -lq;
        sign = -sign;
        }
    b1 = bit_count(lmu);
    b2 = bit_count( ABS( ((fix31)V01.x - V00.x) ) );
    b3 = bit_count( ABS( ((fix31)V01.y - V00.y) ) );
    b2 = MAX(b2, b3);
    sh1 = MAX(0, (b1 + b2 - 31));
    b3 = bit_count(lq);
    sh2 = MAX(0, (b3-16));
    sh2 = MIN(sh2, sh1);
    lmu = (lmu + (1 << (sh1 - 1))) >> sh1;
    lq = (lq + (1 << (sh2 - 1))) >> sh2;
    lx = sign * (((fix31)V01.x - V00.x) * lmu + (lq >> 1)) / lq;
    ly = sign * (((fix31)V01.y - V00.y) * lmu + (lq >> 1)) / lq;
    lx <<= (sh1 - sh2);
    ly <<= (sh1 - sh2);
    }
Pout->x = V00.x - (fix15)lx;
Pout->y = V00.y - (fix15)ly;
#if DEBUG_INT
if ( ABS(Pout->x - save_x) > (sp_globals.onepix >> 7)  ||
             ABS(Pout->y - save_y) > (sp_globals.onepix >> 7))
    {
    printf("#1: %d, %d    %d, %d\n", V00.x, V00.y, V01.x, V01.y);
    printf("#2: %d, %d    %d, %d\n", V10.x, V10.y, V11.x, V11.y);
    printf("Float: q, numx, numy = %.1f %.1f %.1f   Pout = %.3f, %.3f\n", q, save_x4, save_y4, x4, y4);
    printf("Int: Pout = %d, %d\n", Pout->x, Pout->y);
    printf("\n");
    }
#endif
}
#endif


#if INCL_WHITE
FUNCTION  static fix15  whichway (PARAMS2 V00, V01, V10, V11)
  GDECL
  point_t  V00, V01, V10, V11;
/*
    Returns 1 for clockwise; -1 for counterclockwise
    If transformation is mirror-imaged, the return
    value is switched */
{
fix15  x0, y0, x1, y1;
x0 = V01.x - V00.x;
y0 = V01.y - V00.y;
x1 = V11.x - V10.x;
y1 = V11.y - V10.y;
if ((x0*y1 - x1*y0) >= 0)
    return(-sp_globals.tcb0.mirror);    /* 1 for normal; -1 for mirror-imaged */
else
    return(sp_globals.tcb0.mirror);
}
#endif



#if INCL_WHITE
FUNCTION  static fix15  bit_count (arg)
  fix31  arg;
{
fix31  ii;
fix15    jj;

for (jj=32, ii=0x80000000; jj > 0; ii >>= 1, jj--)
    {
    if (arg & ii)
        break;
    }
return(jj);
}
#endif


#if INCL_WHITE
FUNCTION LOCAL  void sp_add_intercept_white(PARAMS2 y, x)
GDECL
fix15 y;                 /* Y coordinate in relative pixel units */
                         /* (0 is lowest sample in band) */
fix15 x;                 /* X coordinate of intercept in subpixel units */

/*  Called by line() to add an intercept to the intercept list structure
 */

{
register fix15 from;   /* Insertion pointers for the linked list sort */
register fix15 to;

#if DEBUG
printf("    Add intercept(%2d, %d)\n", y + sp_globals.y_band.band_min,x);

/* Bounds checking IS done in debug mode */
if (y < 0)       /* Y value below bottom of current band? */
    {
    printf(" Intecerpt less than 0!!!\007\n");
    return;
    }

if (y > (sp_globals.no_y_lists - 1))              /* Y value above top of current band? */
    {
    printf(" Intercept too big for band!!!!!\007\n");
    return;
    }
#endif

/* Store new values */

sp_intercepts.car[sp_globals.next_offset] = x;

/* Find slot to insert new element (between from and to) */

from = y; /* Start at list head */

while( (to = sp_intercepts.cdr[from]) >= sp_globals.first_offset) /* Until to == end of list */
    {
    if (x <= sp_intercepts.car[to]) /* If next item is larger than or same as this one... */
        goto insert_element; /* ... drop out and insert here */
    from = to; /* move forward in list */
    }

insert_element: /* insert element "sp_globals.next_offset" between elements "from" */
                /* and "to" */

sp_intercepts.cdr[from] = sp_globals.next_offset;
sp_intercepts.cdr[sp_globals.next_offset] = to;

if (++sp_globals.next_offset >= MAX_INTERCEPTS) /* Intercept buffer full? */
    {
    sp_globals.intercept_oflo = TRUE;
/* There may be a few more calls to "add_intercept" from the current line */
/* To avoid problems, we set next_offset to a safe value. We don't care   */
/* if the intercept table gets trashed at this point                      */
    sp_globals.next_offset = sp_globals.first_offset;
    }
}

#endif


#if INCL_WHITE
FUNCTION LOCAL  void sp_proc_intercepts_white(PARAMS1)
GDECL

/*  Called by sp_make_char to output accumulated intercept lists
 *  Clips output to sp_globals.xmin, sp_globals.xmax, sp_globals.ymin, sp_globals.ymax boundaries
 */
{
register fix15 i;
register fix15 from, to;          /* Start and end of run in pixel units   
                            relative to left extent of character  */
register fix15 y;
register fix15 scan_line;
         fix15 first_y, last_y;
         fix15 xmin, xmax;
         boolean clipleft, clipright;

/* fixed the -x bits problems cause by characters below 6 lines */
if ( sp_globals.xmax <= sp_globals.xmin )
    return;

#if DEBUG
printf("\nIntercept lists:\n");
#endif

#if INCL_CLIPPING
clipleft = (sp_globals.specs.flags & CLIP_LEFT) && (sp_globals.xmin < 0);
    xmax = ((sp_globals.set_width.x+32768L) >> 16);
clipright = (sp_globals.specs.flags & CLIP_RIGHT) && (sp_globals.xmax > xmax);
if (clipleft || clipright)
    {
    xmax = xmax - sp_globals.xmin;
    xmin = - sp_globals.xmin;
    }
#endif

if ((first_y = sp_globals.y_band.band_max) >= sp_globals.ymax)    
    first_y = sp_globals.ymax - 1;               /* Clip to sp_globals.ymax boundary */

if ((last_y = sp_globals.y_band.band_min) < sp_globals.ymin)      
    last_y = sp_globals.ymin;                    /* Clip to sp_globals.ymin boundary */

last_y  -= sp_globals.y_band.band_min;
#if DEBUG
/* Print out all of the intercept info */
scan_line = sp_globals.ymax - first_y - 1;

for (y = first_y - sp_globals.y_band.band_min; y >= last_y; y--, scan_line++)
    {
    i = y;                            /* Index head of intercept list */
    while ((i = sp_intercepts.cdr[i]) != 0)         /* Link to next intercept if present */
        {
        if ((from = sp_intercepts.car[i] - sp_globals.xmin) < 0)
            from = 0;                 /* Clip to sp_globals.xmin boundary */
        i = sp_intercepts.cdr[i];                   /* Link to next intercept */
        if (i == 0)                   /* End of list? */
            {
            printf("****** proc_intercepts: odd number of intercepts\n");
            break;
            }
        if ((to = sp_intercepts.car[i]) > sp_globals.xmax)
            to = sp_globals.xmax - sp_globals.xmin;         /* Clip to sp_globals.xmax boundary */
        else
            to -= sp_globals.xmin;
        printf("    Y = %2d (scanline %2d): %d %d:\n", 
            y + sp_globals.y_band.band_min, scan_line, from, to);
        }
    }
#endif

/* Draw the image */
scan_line = sp_globals.ymax - first_y - 1;

for (y = first_y - sp_globals.y_band.band_min; y >= last_y; y--, scan_line++)
    {
    i = y;                            /* Index head of intercept list */
    while ((i = sp_intercepts.cdr[i]) != 0)         /* Link to next intercept if present */
        {
        if ((from = sp_intercepts.car[i] - sp_globals.xmin) < 0)
            from = 0;                 /* Clip to sp_globals.xmin boundary */
        i = sp_intercepts.cdr[i];                   /* Link to next intercept */

        if ((to = sp_intercepts.car[i]) > sp_globals.xmax)
            to = sp_globals.xmax - sp_globals.xmin;         /* Clip to sp_globals.xmax boundary */
        else
            to -= sp_globals.xmin;
        if (from >= to)
            {
            if (from >= sp_globals.xmax - sp_globals.xmin)
                {
                --from ;
                }
            to = from+1;
            }
#if INCL_CLIPPING
        if (clipleft)
            {
            if (to <= xmin)
                continue;
            if (from < xmin)
                from = xmin;
            }
    if (clipright)
            {
            if (from >= xmax)
                continue;
            if (to > xmax)
                to = xmax;
            }
#endif
        set_bitmap_bits(scan_line, from, to);
        }
    }
}

#endif


