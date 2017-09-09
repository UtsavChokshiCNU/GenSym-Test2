/*************************** truetype.h  *********************************
 *                                                                           *
 *   TrueType processor interface definitions
 *                                                                           */
/********************* Revision Control Information **********************************
*                                                                                    *
*     $Header: /media/gensym/home/versata1/cvs_repo_copyDec06/ab-repos/fnt/c/truetype.h,v 1.1 1995-11-13 22:32:54 mes Exp $                                                                       *
*                                                                                    *
*     $Log: not supported by cvs2svn $
*     Revision 1.1  1995/10/03 00:37:50  jra
*     Adding ext files from 4.0 Rev. 1 as initial commit for AB.
*
*     Revision 1.1  1993/05/19 22:04:41  mhd
*     Added Bitstream fontrip (Font Raster Image Processor) c & h files.  Not
*     all are compiles -- some are demos, or test modules.
*
 * Revision 1.1  1993/05/04  20:15:38  mhd
 * The flat-directory version of the Bitstream 4-in-1 software.
 *
 * Revision 1.1.1.1  1993/04/15  20:14:41  mhd
 * Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
 *
 * Revision 6.44  93/03/15  13:23:47  roberte
 * Release
 * 
 * Revision 6.10  93/03/04  11:56:18  roberte
 * Added prototype of tt_load_font_params() function.
 * 
 * Revision 6.9  93/02/24  17:37:03  weili
 * Uncommented tt_get_font_fragment(), found problem in fscdefs.h.
 * 
 * Revision 6.8  93/02/24  17:22:31  roberte
 * commented out prototype of tt_get_font_fragment.  This is a problem.
 * 
 * Revision 6.7  93/02/24  16:57:23  roberte
 * Added #ifndef truetype_h flag so file can be re-included.
 * 
 * Revision 6.6  93/01/26  13:37:15  roberte
 * Added PROTO_DECL1 and PROTO_DECL2 macros in support of all reentrant function prototypes.
 * 
 * Revision 6.5  93/01/22  15:22:38  roberte
 * Changed all prototypes to use new PROTO macro.
 * 
 * Revision 6.4  93/01/08  12:17:09  roberte
 * Redefined return value of tt_release_font to ReleaseSFNTFunc rather than void.
 * They are equivalent..
 * 
 * Revision 6.3  92/11/19  16:10:29  roberte
 * Release
 * 
 * Revision 6.1  91/08/14  16:49:16  mark
 * Release
 * 
 * Revision 5.1  91/08/07  12:30:21  mark
 * Release
 * 
 * Revision 4.2  91/08/07  12:02:53  mark
 * add rcs control strings
 * 
*************************************************************************************/


#ifndef truetype_h
#define truetype_h
GetSFNTFunc  tt_get_font_fragment PROTO(( int32  clientID, int32 offset, int32 length));
void tt_release_font_fragment PROTO(( void *ptr));

boolean tt_reset PROTO((PROTO_DECL1));
boolean tt_load_font PROTO((PROTO_DECL2 int32 fontHandle));
boolean tt_load_font_params PROTO((PROTO_DECL2 int32 fontHandle, uint16 platID, uint16 specID));
boolean tt_set_specs PROTO((PROTO_DECL2 specs_t*pspecs));
boolean tt_make_char PROTO((PROTO_DECL2 ufix16 char_code));
boolean tt_make_char_idx PROTO((PROTO_DECL2 ufix16 char_idx));
fix31 tt_get_char_width_idx PROTO((PROTO_DECL2 ufix16 char_index));
fix31 tt_get_char_width PROTO((PROTO_DECL2 ufix16 char_code));
boolean tt_release_font PROTO((PROTO_DECL1));
int16 tt_rendercurve PROTO((PROTO_DECL2 F26Dot6 Ax,F26Dot6 Ay,F26Dot6 Bx,F26Dot6 By,F26Dot6 Cx,F26Dot6 Cy));
int16 split_Qbez PROTO((PROTO_DECL2 long Ax,long Ay,long Bx,long By,long Cx,long Cy,int index,fix15 depth));
void dump_bitmap PROTO((PROTO_DECL2 BitMap *bitmap,point_t *Psw));

#if INCL_APPLESCAN
#define MODE_APPLE MODE_2D+1
#endif

#endif /* truetype_h */
