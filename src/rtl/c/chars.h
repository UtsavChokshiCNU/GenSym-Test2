/*
 * chars-aux.h - character-handling externals
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

struct char_name {
    long code;
    char *iname;
    Object name;
};


#ifdef USE_PROTOTYPES

extern Object SI_char_relop(Object (*f) (Object, Object), Object a, Object b);
extern Object SI_char_relopn(Object (*f) (Object, Object), long n, va_list ap);

#else

extern Object SI_char_relop();
extern Object SI_char_relopn();

#endif

extern struct char_name SI_Char_names[];
