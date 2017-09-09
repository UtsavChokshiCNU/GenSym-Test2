#include "long_support.h"
#include "gsi.h"

DLLEXPORT void gsi_set_long(Object item_attr, gsi_long long_value)
{
    Object integer = INT64_TO_INTEGER(long_value);
    gsi_set_i64 (item_attr, integer);
}

DLLEXPORT gsi_long gsi_long_of(Object item_attr) {
 
	Object integer = gsi_i64_of(item_attr);
        SI_int64 i64 = ILONG64(integer);
	return i64;
}

DLLEXPORT void gsi_set_ulong(Object item_attr, gsi_ulong ulong_value)
{
    SI_int64 i64 = (SI_int64) ulong_value;
    Object integer = INT64_TO_INTEGER(i64);
    gsi_set_i64 (item_attr, integer);
}

DLLEXPORT gsi_ulong gsi_ulong_of(Object item_attr)
{
    Object integer = gsi_i64_of(item_attr);
    SI_int64 i64 = ILONG64(integer);
    return (gsi_ulong) i64;
}
