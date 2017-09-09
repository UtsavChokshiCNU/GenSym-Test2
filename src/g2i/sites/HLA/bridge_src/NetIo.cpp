/***************************************************************************
 *
 *		NetIo.cpp
 *
 *			Contains useful functions used for network communications
 *
 *		This file has been imported and converted from earlier an earlier
 *		version written in ANSI C.
 *
 ***************************************************************************/



#include	<stdlib.h>
#include	<stdio.h>
#include	<string.h>
#include	<stdarg.h>
#include	<errno.h>
#include	<malloc.h>
#include	<math.h>
#include	<time.h>


#include	"G2Hla.h"


/*-------------------------------------------------------------------------*
 *
 *  Byte swapping routines for 2, 4 byte and 8 byte quantities
 *
 *-------------------------------------------------------------------------*/


ushort swap_2byte_quantity(ushort src)
{
	return( swap_2byte_quantityP(&src) );
}




ushort swap_2byte_quantityP(ushort *srcP)
{
	if (is_big_endian == TRUE) {

		ushort	dest;

		memcpy((char *) &dest, (char *) srcP, sizeof(ushort));
		return( dest );

	} else {

		ushort		dest;
		ushort		*destP = &dest;
		long		i;
		uchar		*mptr, *iptr;

		mptr = (uchar *) srcP;
		iptr = (uchar *) (++destP);

		for ( i = 0 ; i < sizeof(ushort) ; i++)
			*--iptr = *mptr++;

		return(dest);
	}
}



ulong swap_4byte_quantity(ulong src)
{
	return( swap_4byte_quantityP(&src) );
}




ulong swap_4byte_quantityP(ulong *srcP)
{
	if (is_big_endian == TRUE) {
	
		ulong	dest;

		memcpy((char *) &dest, (char *) srcP, sizeof(ulong));
		return( dest );

	} else {

		ulong		dest;
		ulong		*destP = &dest;
		long		i;
		uchar		*mptr, *iptr;

		mptr = (uchar *) srcP;
		iptr = (uchar *) (++destP);

		for ( i = 0 ; i < sizeof(ulong) ; i++)
			*--iptr = *mptr++;

		return(dest);
	}
}





double swap_8byte_quantity(double src)
{
	return ( swap_8byte_quantityP( &src ) );
}


double swap_8byte_quantityP(double *srcP)
{
	if (is_big_endian == TRUE) {
	
		double	dest;

		memcpy((char *) &dest, (char *) srcP, sizeof(double));
		return( dest );

	} else {

		double		dest;
		double		*destP = &dest;
		long		i;
		uchar		*mptr, *iptr;

		mptr = (uchar *) srcP;
		iptr = (uchar *) (++destP);

		for ( i = 0 ; i < sizeof(double) ; i++)
			*--iptr = *mptr++;

		return(dest);
	}
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
