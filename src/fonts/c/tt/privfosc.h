/********************* Revision Control Information **********************************
*                                                                                    *
*     $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/tt/privfosc.h,v 1.1 1995-10-03 01:04:04 jra Exp $                                                                       *
*                                                                                    *
*     $Log: not supported by cvs2svn $
*     Revision 1.1.1.1  1993/04/15 20:14:39  mhd
*     Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
*
 * Revision 6.44  93/03/15  13:21:38  roberte
 * Release
 * 
 * Revision 6.3  92/11/19  16:06:25  roberte
 * Release
 * 
 * Revision 6.2  92/04/30  11:26:45  leeann
 * stripped 2 non-ASCII characters
 * 
 * Revision 6.1  91/08/14  16:47:25  mark
 * Release
 * 
 * Revision 5.1  91/08/07  12:28:34  mark
 * Release
 * 
 * Revision 4.2  91/08/07  11:47:59  mark
 * lock fnt.h
 * added RCS control strings
 * 
*************************************************************************************/

/*
	File:		privateFontScaler.h

	Contains:	Nothing Important

	Written by:	Charlton E. Lui

	Copyright:	) 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <3>	 7/18/90	MR		change parameters of SetupKey to be input*, unsigned and int
		 <2>	  5/3/90	RB		nothing new
		 <1>	 4/16/90	HJR		first checked in
		 <1>	 4/10/90	CL		first checked in

	To Do:
*/

/* ****************************************************
**
** CKL	02/20/1990	Added ANSI-C prototypes
**
** ****************************************************
*/
 
/*
 *
 *  ) Apple Computer Inc. 1988, 1989, 1990.
 *
 *	The file defines private sfnt stuff
 *
 * History:
 * 
 */




/* extern pascal int32 fs_SetMem(register fs_GlyphInputType *inputPtr, fs_GlyphInfoType *outputPtr); */
/* extern fsg_SplineKey* fs_SetUpKey(fs_GlyphInputType* inptr, unsigned stateBits, int* error); */
extern int32 fs_SetMem();
extern fsg_SplineKey* fs_SetUpKey();

