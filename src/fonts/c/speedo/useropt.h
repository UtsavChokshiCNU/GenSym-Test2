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

/***************************  U S E R O P T . H  *****************************
 *                                                                           *
 * This overrides the Speedo default settings.                               *
 *                                                                           *
 ********************** R E V I S I O N   H I S T O R Y **********************
 * $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/speedo/useropt.h,v 1.1 1995-10-03 01:03:45 jra Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.2  1993/04/27 17:32:18  mhd
 * Added other cases under which to define INTEL=1.  (VMS, Ultrix, i386, etc.)
 * This will replace passing in the INTEL flag in the make[alpha].com files.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:23  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 2.19  93/03/15  14:00:19  roberte
 * Release
 * 
 * Revision 2.7  93/03/11  20:39:44  roberte
 * #define HAVE_MSL2INDEX for all demo packages.
 * Turn on PROTOS_AVAIL. This is essential for IBM PC at this time.
 * 
 * Revision 2.6  93/03/11  11:40:18  roberte
 * Added define of INTEL as 1 if MSDOS defined. For shortening command lines on PC makefiles.
 * 
 * Revision 2.5  93/03/11  11:20:53  roberte
 * Restored STACKFAR, FONTFAR and GLOBALFAR as "far" ifdef MSDOS in the _4DEMO_ compile.
 * 
 * Revision 2.4  93/03/10  17:20:23  weili
 * Removed spurious defines of INCL_WHITE, REENTRANT_ALLOC and
 * etc that were causing problems if this file was included twice.
 * 
 * Revision 2.3  93/02/23  17:29:44  roberte
 * Shut off INCL_APPLESCAN flags.  These should normally be set to 0,
 * unless implementor wants to use the AppleScan rasterizer for
 * some reason.
 * 
 * Revision 2.2  93/02/08  15:23:21  roberte
 * Turned setting for INCL_APPLESCAN to 0
 * 
 * Revision 2.1  93/01/29  08:58:25  roberte
 * Changed value of PROTOS_AVAIL for non-INTEL builds to 0.  Doesn't work
 * properly on the APOLLO with standard K&R function declartions.
 * 
 * Revision 2.0  92/11/19  15:42:25  roberte
 * Release
 * 
 * Revision 1.13  92/11/18  12:49:06  roberte
 * Got rid of extraneous #defines of WDECL, FONTFAR, STACKFAR and GLOBALFAR
 * 
 * Revision 1.12  92/11/17  15:53:55  laurar
 * changes that only affect compilation for DLL. (WINDOWS_4IN1)
 * 
 * Revision 1.6  92/10/01  15:22:17  roberte
 * Added define INCL_MS_SETS to leave Microsoft encoding arrays defined in
 * msstglob.c
 * 
 * Revision 1.5  92/10/01  13:57:53  roberte
 * Put in ifdefs to shut off MSL's, Unicode, PSNames, and User in the 4DEMO
 * block (for the IBM PC port).
 * 
 * Revision 1.4  92/10/01  13:30:10  laurar
 * define INTEL explicitly as 1.
 * 
 * Revision 1.3  92/09/30  11:19:29  roberte
 * Removed CTRL-Z at end of file!
 * 
 * Revision 1.2  92/09/29  16:32:42  laurar
 * add defines for 4demo (PC test program)
 * 
 * Revision 26.1  92/06/26  10:27:07  leeann
 * Release
 * 
 * Revision 25.1  92/04/06  11:43:31  leeann
 * Release
 * 
 * Revision 24.1  92/03/23  14:11:50  leeann
 * Release
 * 
 * Revision 23.1  92/01/29  17:03:08  leeann
 * Release
 * 
 * Revision 22.1  92/01/20  13:34:29  leeann
 * Release
 * 
 * Revision 21.1  91/10/28  16:46:50  leeann
 * Release
 * 
 * Revision 20.1  91/10/28  15:30:33  leeann
 * Release
 * 
 * Revision 18.1  91/10/17  11:42:04  leeann
 * Release
 * 
 * Revision 17.1  91/06/13  10:46:49  leeann
 * Release
 * 
 * Revision 16.1  91/06/04  15:37:19  leeann
 * Release
 * 
 * Revision 15.1  91/05/08  18:09:26  leeann
 * Release
 * 
 * Revision 14.1  91/05/07  16:31:24  leeann
 * Release
 * 
 * Revision 13.1  91/04/30  17:06:02  leeann
 * Release
 * 
 * Revision 12.1  91/04/29  14:56:23  leeann
 * Release
 * 
 * Revision 11.1  91/04/04  11:00:19  leeann
 * Release
 * 
 * Revision 10.1  91/03/14  14:33:02  leeann
 * Release
 * 
 * Revision 9.1  91/03/14  10:07:40  leeann
 * Release
 * 
 * Revision 8.1  91/01/30  19:04:31  leeann
 * Release
 * 
 * Revision 7.1  91/01/22  14:29:04  leeann
 * Release
 * 
 * Revision 6.1  91/01/16  10:54:41  leeann
 * Release
 * 
 * Revision 5.1  90/12/12  17:21:16  leeann
 * Release
 * 
 * Revision 4.1  90/12/12  14:47:08  leeann
 * Release
 * 
 * Revision 3.1  90/12/06  10:29:29  leeann
 * Release
 * 
 * Revision 2.1  90/12/03  12:58:15  mark
 * Release
 * 
 * Revision 1.5  90/11/29  17:06:22  leeann
 * use speedo defaults
 * 
 * Revision 1.4  90/11/19  17:30:19  joyce
 * set screen, outline, 2d output modes to 0 for testing
 * 
 * Revision 1.3  90/11/19  15:58:07  joyce
 * set speedo output mode includes (black, outline, 2d)
 * 
 * Revision 1.2  90/09/17  17:09:01  roger
 * changed to comply with RCS
 * 
 * Revision 1.1  90/08/13  15:31:00  arg
 * Initial revision
 * 
 *                                                                           *
 *  1) 23 Apr 90  jsc  Created                                               *
 *                                                                           *
 ****************************************************************************/

#ifndef useropt_h
#define useropt_h

static char useropt_h_rcsid[] = "$Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/speedo/useropt.h,v 1.1 1995-10-03 01:03:45 jra Exp $";


#if defined(vms) || defined(ultrix) || defined(i386) || defined(MSDOS)
#define		INTEL			1
#else
#define		INTEL			0
#endif  /* defined by mhd@gensym, 4/27/93 -- used in tt/fscdefs.h to define SWAPL, etc. */


#ifdef		_4DEMO_

#define HAVE_MSL2INDEX
#define		SPEEDO_CODE				1
#define		INCL_KEYS				1
#define		SHORT_LISTS				1
#define		INCL_BLACK				1
#define		INCL_2D					1
#define		INCL_OUTLINE			1
#define		INCL_SCREEN				1
#define		INCL_WHITE				1
#define		PROTOS_AVAIL			1
#define		INCL_APPLESCAN			0
#define		INCL_PFB					1
#define		BASELINE_IMPROVE		1

/* shut of all columns in the gMasterGlyphCodes[] */
#define CMT_MSL	1
#define CMT_UNI	1
#define CMT_PS	1
#define CMT_USR	0
#ifdef MSDOS
#define     FONTFAR     far
#define     STACKFAR    far
#define     GLOBALFAR   far
#endif /* MSDOS */
#else
#define INCL_MS_SETS
#endif



#if WINDOWS_4IN1
#define     PROC_PCL          0
#define     PROC_TRUETYPE     0
#define     PROC_TYPE1        1

#if         PROC_TYPE1
#define		INCL_PFB					1
#define     RESTRICTED_ENVIRON   1
#else
#define		INCL_PFB					0
#define     RESTRICTED_ENVIRON   0
#endif

#define		SPEEDO_CODE				1
#define		INCL_KEYS				1
#define		SHORT_LISTS				0
#define     PROTOS_AVAIL         1
#define		INCL_BLACK				1
#define		INCL_WHITE				0
#define		INCL_APPLESCAN			0
#define		BASELINE_IMPROVE		1
#define     INCL_LCD       1  /* Windows always uses load_char dynamically method */

#define     RC_INVOKED        1 
#define     NOCOLOR           1
#define     NOWINSTYLES       1
#define     NOWINOFFSETS      1
#define     NOMDI             1
#define     NOHELP            1
                         /* cut out alot of windows.h to save */
                        /* near heap space */

#define     FONTFAR     _far
#define     STACKFAR    _far
#define     GLOBALFAR    _far
#define     WDECL    _far _pascal _export
#endif

#define		NOT_ON_THE_MAC	1
#endif
