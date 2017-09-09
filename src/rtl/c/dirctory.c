/*
 * dirctory.c -  Chestnut Run-Time Library entry for function directory
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"


#if SI_USE_PROTOTYPES

extern Object (*SI_error_fptr) (int n, char *lstr, ...);

#else

extern Object (*SI_error_fptr) ();

#endif


#include "filesys.h"

 /* 10/5/93, mpc:  The compiler flag (_MSC_VER) is defined by all of
  *     the NT compilers in the blessed name of compatibility. Here
  *     however that causes a problem, because the directory() 
  *     procedures use dos/windows specific functions which are not
  *     available on NT.
  */
#if !defined(_MSC_VER)  || defined(WIN32)
Object directory varargs_1(int, n)
{
    error(1, "directory: implementation pending");
	return VALUES_1(NIL);
}
#else  /* Microsoft */

static int find1st(), findnext();
static void setdta();

Object directory varargs_1(int, n)
{
    Declare_local_temp;
    Object pathnm;
    char *fname;
    Object result = NIL, newnode;
    UCHAR attrib = FA_ORDINARY;
    int err;
    char itembuff[ITEM_SIZE];
    Declare_stack_pointer;
    va_list ap;

    SI_va_start(ap,n);
    pathnm = va_arg(ap, Object);

    SAVE_STACK();
    PROTECT_2(pathnm,result);
    PROTECTI_1(newnode);
    fname = ISTRING(truename(merge_pathnames(pathnm,KOPT,KOPT)));
    if ((err = find1st(itembuff, fname, attrib)) == FILE_FOUND) {
	do {
	    newnode = make_string(FIX(strlen(&itembuff[FNAME])), NIL);
	    strcpy(ISTRING(newnode), &itembuff[FNAME]);
	    result = cons(newnode, result);
	    err = findnext(fname, attrib);
	} while (err == FILE_FOUND);
    }
    va_end(ap);
    RESTORE_STACK();
    return VALUES_1(result);
}

#define SETDTA_DOS	0x1a
#define FIND1ST_DOS	0x4e
#define FINDNEXT_DOS	0x4f

static int find1st(dta, filename, attribute)
    char	*dta, *filename;
    UCHAR	attribute;
{
    union REGS regs;
    struct SREGS segregs;

    setdta(dta);
    regs.x.cx = attribute;
    regs.x.dx = FP_OFF(filename);
    segregs.ds = FP_SEG(filename);
    regs.h.ah = FIND1ST_DOS;
    intdosx(&regs, &regs, &segregs);
    return(regs.x.cflag);	/* set=error, clear=FOUND */
}

static int findnext(filename, attribute)
    char	*filename;
    UCHAR	attribute;
{
    union REGS regs;
    struct SREGS segregs;

    regs.x.cx = attribute;
    regs.x.dx = FP_OFF(filename);
    segregs.ds = FP_SEG(filename);
    regs.h.ah = FINDNEXT_DOS;
    intdosx(&regs, &regs, &segregs);
    return(regs.x.cflag);
}

static void setdta(dta)
    char	*dta;
{
    union REGS regs;
    struct SREGS segregs;

    regs.x.dx = FP_OFF(dta);
    segregs.ds = FP_SEG(dta);
    regs.h.ah = SETDTA_DOS;
    intdosx(&regs, &regs, &segregs);
}
#endif
#ifdef GCLISP
Object file_info(pathnm)
    Object pathnm;
{
    Declare_local_temp;
    char *fname;
    int result;
    struct stat buf;
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(pathnm);
    fname = ISTRING(truename(merge_pathnames(pathnm,KOPT,KOPT)));
    result = stat(fname, &buf);
    RESTORE_STACK();
    if (!result) {
	return(VALUES_5(FIX(buf.st_mode),
			FIX((buf.st_size >> 16) & 0xffff),
			FIX(buf.st_size & 0xffff),
			FIX(buf.st_ctime),
			FIX(buf.st_ctime)));
    }
    return VALUES_1(NIL);
}
#endif

