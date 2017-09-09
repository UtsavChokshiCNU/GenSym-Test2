/*
 * room.c -  Chestnut Run-Time Library entry for function room
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern SI_Area Dynamic_area;
extern SI_Area Local_area;
extern SI_Area Static_area;

#if SI_USE_PROTOTYPES

extern Object format(long n, Object destination, char *control_string, ...);
extern Object unsigned_long_to_bignum(SI_Ulong x);

#else

extern Object format();
extern Object unsigned_long_to_bignum();

#endif



extern SI_Size_type area_bytes_in_use();
extern SI_Size_type area_total_size();

#define ULFIX(x) UNSIGNED_LONG_TO_INTEGER(x)

Object room (x)
    Object x;
{
    extern SI_Area Static_area, Dynamic_area, Local_area;

    SI_Ulong
	snu = area_bytes_in_use(&Static_area),
	snl = area_total_size(&Static_area),
	snt = Static_area.target_size,
	dnu = area_bytes_in_use(&Dynamic_area),
	dnl = area_total_size(&Dynamic_area),
	dnt = Dynamic_area.target_size,
	lnu = area_bytes_in_use(&Local_area),
	lnl = area_total_size(&Local_area),
	lnt = Local_area.target_size;

    static char *fstring =
	" used ~8D bytes, current size ~8D, target size ~8D~%";

    format(2, T, "~&Static area:  ");
    format(5, T, fstring, ULFIX(snu), ULFIX(snl), ULFIX(snt));
    format(2, T, "Dynamic area: ");
    format(5, T, fstring, ULFIX(dnu), ULFIX(dnl), ULFIX(dnt));
    format(2, T, "Local area:   ");
    format(5, T, fstring, ULFIX(lnu), ULFIX(lnl), ULFIX(lnt));
    format(2, T, "Total:        ");
    format(5, T, fstring,
	   ULFIX(snu + dnu + lnu),
	   ULFIX(snl + dnl + lnl),
	   ULFIX(snt + dnt + lnt));
    return VALUES_0();
}
