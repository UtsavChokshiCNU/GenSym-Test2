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
 * $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fnt/c/useropt.h,v 1.5 2007-01-02 20:51:42 yduj Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.4  2003/11/26 20:02:50  jv
 *
 * Project: C Function Naming
 * Witness: fmw
 * Authorization: mhd
 *
 * Files modified: fnt/c/fontrip.c fnt/c/useropt.h rtl/c/gensym.h
 *    lisp/os-foreign.lisp lisp/fonts.lisp
 *
 * Description of changes:
 *    Add g2fnt_ prefix to all API functions in libfnt.
 *
 *    We had a project several years ago to make all of our "API" functions --
 *    that is, functions which in which one Gensym module calls into a different
 *    Gensym module -- have special prefixes to virtually guarantee uniqueness.
 *    We did this for ext (g2ext_) and rtl (g2rtl_) and then later for xml, but
 *    never for fnt.  This commit finally changes that.
 *
 *    The first thing to do is to *allow* this to happen, because def-gensym-c-
 *    function will append g2ext_ to any C function name unless the function name
 *    fits some profile.  In os-foreign, add g2fnt_ as an acceptable prefix which
 *    does not need to be prepended with g2ext_.
 *
 *    There are some other changes to os-foreign which are not substantive.
 *    Re-ordered the list of names in foreign-functions-without-prefix and add
 *    some comments.  Several of the names in the list are not actually used
 *    by the translated Lisp code, so denote that with a comment.  Also re-order
 *    the prefixes in foreign-function-requires-prefix-p.  Finally, add a
 *    temporary-progn to remind me to remove the font APIs after I've changed
 *    them to g2fnt_ and a little bit of time has passed.
 *
 *    In fontrip.c, change all of the functions which are called from the
 *    translated Lisp code to have a g2fnt_ prefix.  This is the only file in
 *    fnt which defines or calls any API functions.  One comment in useropt.h
 *    refers to one of the functions; update the comment.
 *
 *    In fonts.lisp and gensym.h, update references to the C functions to reflect
 *    the new names.
 *
 * Difficulty of change: easy
 * Number of edit sites:    36
 * Number of lines changed: 61
 * Fanin and fanout of change: after a little bit of time, there should be none
 *    (it should becompletely transparent); the one potential pitfall is if someone
 *    updates and builds fnt right now, they will be unable to build G2 or TW
 *    until they get updated g2/c and tw/c files.  We'll commit those soon.
 *
 * How this has been tested: re-translate and compile G2, TW, and GSI;
 *    recompile G2 in Lisp
 *
 * Revision 1.3  2000/08/22 13:43:40  mhd
 * Project: remove unneeded font rasterizers to save space
 * Files modified and/or added: gen/mfgen/fnt-dependencies.rel   fnt/c/useropt.h
 *   (results in modified make files gen/mfiles/*-fnt-*)
 *
 * Description of changes: removed entries for object files tr_names, tr_mkchr, and
 * tr_mkchr (type1), and hpfnt1, hpfnt2, and load_pcl (pcl).  This is type remove
 * support for the type1 rasterizer ("tr") and PCL ("hp") rasterizer.  The changes
 * here are done in synch with the change in fnt/c/useropt.h, turning off support
 * for these rasterizers.
 *
 * Difficulty of change: easy/medium
 *
 * Number of edit sites: 2
 * Number of lines changed: 7
 * When and how bug was introduced: (not a bug) in original implementation
 *   of the bitstream rasterizer code, and the teasing apart the two
 *   unneeded rasterizers could have been done at any time, but just wasn't.
 * Fanin and fanout of change: touch related code, i.e., using the still-live
 *   rasterizers, whenever you scale fonts up (sometimes down) from normal
 *   size.  Roman and Japanese outline fonts use speedo rasterizer; russian,
 *   chinese, and korean outline fonts use truetype rasterizer.
 *   This results in about ~100K smaller fnt library file.
 * How this has been tested: in my sandbox, both development and production
 *   builds, and by explicitly generating the *-fnt-* makefiles)
 *
 * Revision 1.2  1998/04/08 03:04:13  mhd
 * Witness: JV, RH
 * Bug: HQ-1881196 "seg fault rendering Korean fonts"
 *
 * Fixed illegal return value for failing case for
 * g2fnt_load_outline_font_into_memory -- it should have been -1, not FALSE (0).
 *
 * Also, fixed setup of INTEL flag, which is really the fontrip module's
 * version of the not(BIG_ENDIAN) flag used by the G2 C sources -- made
 * them be in synch, and now correct.
 *
 * (Note: fixed an unreported bug: scaling the Cyrillic truetype font did
 * not work -- scaled bitmaps were always substituted.  We also theorize
 * that this would have been a bug on AlphaOSF.)
 *
 * NOTE: this bug is not completely resolved yet.  We have just fixed
 * the segmentation violation, and the handling of one failure-to-load
 * case.  We still don't have the Korean truetype font rendering properly
 * for little-endian platforms, but at least we expect them, with this
 * fix, to all not be crashing and to all behave the same way.  (The
 * characters all get "rendered" as rectangular outlines, which is wrong
 * and needs to be debugged.)
 *
 * Revision 1.1  1995/11/13 22:33:00  mes
 * Project:  Bitstream Font Transition
 *
 *   Committing all Bitstream fonts files from the ext/c module.  This is the new
 * home for libfnt.a.
 *
 * Revision 1.1  1995/10/03 00:37:58  jra
 * Adding ext files from 4.0 Rev. 1 as initial commit for AB.
 *
 * Revision 1.5  1994/05/02 16:25:52  mhd
 * Plans made (in comments) to exclude processors for certain forms based
 * on current/expected product needs, as an optimization.  However,
 * nothing can be done without work on the build/make files, so this is
 * left as a comment for now.
 *
 * Revision 1.4  1993/08/19  04:52:20  mhd
 * First working version of fontrip for Kanji.  Also, added courier as
 * a built-in font experimentally.  Also, completely converted to new
 * "reentrant_alloc" approach, for faster font-switching.  A few other
 * minor bug fixes.
 *
 * Revision 1.6  1993/07/28  21:53:13  mhd
 * More work on getting 2d writer to work.  Bug with interference with
 * incl_outline discovered.  Documentation of improper hinting
 * of swiss721swa in problems.text.  Some more work on getting Kanji.  No
 * luck yet.
 *
 * Revision 1.5  1993/07/27  22:58:08  mhd
 * Latest series of changes around getting Kanji to work.  Some work maybe
 * on font bounding box issues, also.  See problems.text for latest issues
 * in detail.
 *
 * Revision 1.4  1993/06/11  21:20:02  mhd
 * Shortened many of the names that had grown beyond the 31 character
 * identifier limit of the VAX/Alpha.  Update Alpha makealpha.com file
 * to be simpler, and to compile new files fontrip.c, mhddemo.c, and
 * ripdemo.c.  This update adds also the capability of writing a
 * GF file based on point size and resolution.
 *
 * Revision 1.3  1993/05/20  16:09:22  mhd
 * Added capability to have set-width-adjusted characters -- imposing set
 * widths on Bitstream fonts.  This meant adding an arg to the character
 * making interface function, calling sp_make_char_isw under certain
 * circumstances, and enabling ISW, by turning on INCL_ISW in useropt.h.
 *
 * Revision 1.2  1993/05/08  15:41:42  mhd
 * Various changes in service of getting functionality into fontrip.c
 * to be able to create a bitmap output file, for use on Lispm's in
 * development.
 *
 * Revision 1.1  1993/05/04  20:15:55  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.2  1993/04/27  17:32:18  mhd
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

static char useropt_h_rcsid[] = "$Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fnt/c/useropt.h,v 1.5 2007-01-02 20:51:42 yduj Exp $";


/* GENSYMCID-454: Cyrillic characters cannot be displayed on menus in G2 8.4r3
#if defined(i386) || defined(_X86_) || defined(__alpha)
#define INTEL			1
#else
#define INTEL			0
#endif
 */
/* defined by mhd@gensym, 4/27/93 -- used in tt/fscdefs.h to define SWAPL, etc. */

#define INTEL 1


/* Gensym's flags -- now out of makefile. -mhd, 5/5/93 */
/* for unix or vms */

#define INCL_ISW		1   /* We're enabling this in order to support
				       use of sp_make_char_isw, in order to
				       impose our Adobe Helvetica set widths
				       on Bitstream's Swiss 721.  See comments
				       in FONTS.lisp, and fontrip.c. -mhd, 5/20/93
				       */
#if !(defined(MSDOS))


/* NOTE: All of the processors are currently turned on in development.  To disable */
/* them will require changes to the makefile.  Do this soon! (MHD 5/2/94) */

#define     PROC_PCL          0	/* 0 PCL (HP) format is unlikely ever to be used */
				/*   by Gensym in the forseeable future. */
				/*   Files to link iff this is on:    (MHD 7/2/00)
				        hpfnt1.o hpfnt2.o load_pcl.o
					*/

#define     PROC_TRUETYPE     1 /* 1 Truetype (Microsoft/Apple) format will likely */
				/*   be used for Korean, and maybe for other fonts. */
				/*   It is becoming the most widely used format due */
				/*   its use by Windows and Macintosh.  Keep this */
				/*   enabled. */

#define     PROC_TYPE1        0 /* 0 Type1 (Adobe/Postscript) may some day be used, but it */
				/*   is not likely to be soon.  It */
				/*   is the format with the largest number of very high */
				/*   quality fonts, per the consensus as I understand it. */
				/*   We could conceivably require it in a future release. */
				/*   Files to link iff this is on:    (MHD 7/2/00)
				        tr_ldfnt.o tr_mkchr.o tr_names.o tr_trans.o
					*/

/* PROC_SPEEDO (sp?) is enabled because we Speedo fonts, in fact, only Speedo
   fonts, at present. */



#define SPEEDO_CODE		1
#define INCL_KEYS		0
#define SHORT_LISTS		0 /* Must be 0 if incl_2d is on; always ok to be 0 */
#define INCL_BLACK		1

#define INCL_2D			1

#define INCL_SCREEN		1
#define INCL_WHITE		1

#define PROTOS_AVAIL		0
#define INCL_PFB		1

#define BASELINE_IMPROVE	1
/* #define HAVE_MSL2INDEX */
/* if the above is set, then ksample won't compile, so turn it off.
   Per Bob Eggers@Bitstream. -mhd, 7/27/93
   */




#define INCL_OUTLINE		1
				/* Needed enabled to get around problem with incl_2d */
/* must define outline functions if enabled -- enable for 4demo */
/* enable if making 4demo/disable for mhddemo/ripdemo/G2 */

#define REENTRANT_ALLOC		1 /*  These two are mutually exclusive. */
#define DYNAMIC_ALLOC		0 /* Reentrant is the one we need. This one won't compile
				   anyway -- problems compiling out_blk.c!
				   */

/* bob: all above 1 -- (w/ "define have_msl2index) */

#endif  /* !(defined(MSDOS)) */

/* end of Gensym's Settings */





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
