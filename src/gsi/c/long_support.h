#ifndef LONG_SUPPORT_H
#define LONG_SUPPORT_H

#include "user.h"

typedef SI_uint64 gsi_ulong;
typedef SI_int64 gsi_long;

DLLEXPORT void gsi_set_long(Object item_attr, gsi_long long_value);
DLLEXPORT gsi_long gsi_long_of(Object item_attr);
DLLEXPORT void gsi_set_ulong(Object item_attr, gsi_ulong ulong_value);
DLLEXPORT gsi_ulong gsi_ulong_of(Object item_attr);

#endif
