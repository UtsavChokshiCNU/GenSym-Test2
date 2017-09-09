/****************************************************************************
*                                                                            *
*  Copyright 1989, as an unpublished work by Bitstream Inc., Cambridge, MA   *
*                         U.S. Patent No 4,785,391                           *
*                           Other Patent Pending                             *
*                                                                            *
*         These programs are the sole property of Bitstream Inc. and         *
*           contain its proprietary and confidential information.            *
*                                                                            *
*****************************************************************************/

#include <stdio.h>
#include "speedo.h"                 /* General definition for speedo */

/* JIS ward odd :					*/
/* 0x21 - 0x5f -> 0x40 - 0x7e */
/* 0x60 - 0x7e -> 0x80 - 0x9e */
/* JIS ward even : 				*/
/* 0x21 - 0x7e -> 0x9F - 0xfc */

FUNCTION ufix16 JIS2SJ(code)
     ufix16 code;
/*
 * Convert JIS to shift-JIS
 */
{
	ufix16 sj ;
	ufix16 j1, j2, sj1 ;
	int plus, flag = 0 ;

	j1 = (code & 0xff00) >> 8 ;
	j2 = (code & 0x00ff) ;
	if ( j1 > 0x5e )
		plus = 0xc100 ;
	else
		plus = 0x8100 ;
	sj1 = j1 - 0x21 ;
	if ( sj1 % 2 )
	{
		sj1 -- ;
		flag = 1 ;
	}
	sj = (( sj1/2 ) << 8) + plus ;
	if ( flag )
		sj += j2 + 0x7e ;
	else if ( j2 <= 0x5f )
		sj += j2 + 0x1f ;
	else if ( j2 >= 0x60 )
		sj += j2 + 0x20 ;
	return(sj);
}

FUNCTION ufix16 EUC2JIS(code)
/*
 * Convert EUC (Extended Unix Code) to JIS 
 */
ufix16 code;
{
	return (code-0x8080);
}

FUNCTION ufix16 EUC2SJ(code)
ufix16 code;
/*
 * Convert EUC (Extended Unix Code) to shift-JIS 
 */
{
	ufix16 jis, sj ;
	jis = EUC2JIS(code);
	sj = JIS2SJ(jis);
	return(sj);
}

