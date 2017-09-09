/********************* Revision Control Information **********************************
*                                                                                    *
*     $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fonts/c/tt/mapstrng.h,v 1.1 1995-10-03 01:04:02 jra Exp $                                                                       *
*                                                                                    *
*     $Log: not supported by cvs2svn $
*     Revision 1.1.1.1  1993/04/15 20:14:39  mhd
*     Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
*
 * Revision 6.44  93/03/15  13:13:48  roberte
 * Release
 * 
 * Revision 6.4  93/01/22  15:25:12  roberte
 * Changed all prototypes to use new PROTO macro.
 * 
 * Revision 6.3  92/10/15  11:52:10  roberte
 * Changed all ifdef PROTOS_AVAIL statements to if PROTOS_AVAIL.
 * 
 * Revision 6.2  92/04/30  11:17:33  leeann
 * take out binary byte
 * 
 * Revision 6.1  91/08/14  16:46:27  mark
 * Release
 * 
 * Revision 5.1  91/08/07  12:27:39  mark
 * Release
 * 
 * Revision 4.3  91/08/07  11:52:38  mark
 * remove rcsstatus string
 * 
 * Revision 4.2  91/08/07  11:46:16  mark
 * added RCS control strings
 * 
*************************************************************************************/

/*
	File:		MapString.h

	Contains:	Char2glyph calls

	Written by:	Mike Reed

	Copyright:	) 1990 by Apple Computer, Inc., all rights reserved.

	Change History (most recent first):

		 <2>	 8/10/90	MR		Add textLength to MapString2
		 <1>	 7/23/90	MR		first checked in
				 7/23/90	MR		xxx put comment here xxx

	To Do:
*/

long MapString0 PROTO((uint8* map, uint8* charCodes, int16* glyphs, long glyphCount));
long MapString2 PROTO((uint16 *map,uint8 *charCodes,int16 *glyphs,long glyphCount,long *textLength));
long MapString4_8 PROTO((uint16* map, uint8* charCodes, int16* glyphs, long glyphCount));
long MapString4_16 PROTO((uint16 *map,uint16 *charCodes,int16 *glyphs,long glyphCount));
long MapString6_8 PROTO((uint16* map, uint8* charCodes, int16* glyphs, long glyphCount));
long MapString6_16 PROTO((uint16 *map,uint16 *charCodes,int16 *glyphs,long glyphCount));
