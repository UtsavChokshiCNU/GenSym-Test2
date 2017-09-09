/*
 * dummy.h - macros to define prototypes for functions that not yet implemented
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

/* Not yet implemented. */

#define DUMMY_0(name) Object name() { return error(1, "Implementation pending"); }
#define DUMMY_1(name) Object name(x1) Object x1; { return error(1, "Implementation pending"); }
#define DUMMY_2(name) \
    Object name(x1, x2) Object x1, x2; { return error(1, "Implementation pending"); }
#define DUMMY_3(name) \
    Object name(x1, x2, x3) Object x1, x2, x3; { return error(1, "Implementation pending"); }
#define DUMMY_4(name) \
    Object name(x1, x2, x3, x4) Object x1, x2, x3, x4; { return error(1, "Implementation pending"); }

#define DUMMY_V(name) \
    Object name varargs_1(int,n) { return error(1, "Implementation pending"); }




