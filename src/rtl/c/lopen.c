/*
 * lopen.c -  Chestnut Run-Time Library entry for function lopen
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 */

#include "runtime.h"

extern Object Kappend;
extern Object Kcreate;
extern Object Kerror;
extern Object Kinput;
extern Object Kio;
extern Object Knew_version;
extern Object Koutput;
extern Object Koverwrite;
extern Object Kprobe;
extern Object Krename_and_delete;
extern Object Krename;
extern Object Ksupersede;
extern Object Qstring_char;

#if SI_USE_PROTOTYPES

extern Object SI_alloc(SI_Size_type size, long align, enum SI_type type, enum SI_tag tag, enum SI_gcls gcls);
extern Object (*SI_error_fptr) (long n, char *lstr, ...);
extern char *SI_istring(Object o);
extern Object delete_file(Object);
extern Object merge_pathnames(Object,Object,Object);
extern Object probe_file(Object);
extern Object truename(Object);

#else

extern Object SI_alloc();
extern Object (*SI_error_fptr) ();
extern char *SI_istring();
extern Object delete_file();
extern Object merge_pathnames();
extern Object probe_file();
extern Object truename();

#endif


#include "filesys.h"

extern Object Pkeyword;
#ifdef USE_PROTOTYPES
extern Object iintern(char *name, Object pkg);
#else
extern Object iintern();
#endif

static int lopen_syms_initialized = 0;

static void init_lopen_syms()
{
  Kappend = iintern("APPEND",Pkeyword);
  Kcreate = iintern("CREATE",Pkeyword);
  Kerror = iintern("ERROR",Pkeyword);
  Kinput = iintern("INPUT",Pkeyword);
  Kio = iintern("IO",Pkeyword);
  Knew_version = iintern("NEW-VERSION",Pkeyword);
  Koutput = iintern("OUTPUT",Pkeyword);
  Koverwrite = iintern("OVERWRITE",Pkeyword);
  Kprobe = iintern("PROBE",Pkeyword);
  Krename_and_delete = iintern("RENAME-AND-DELETE",Pkeyword);
  Krename = iintern("RENAME",Pkeyword);
  Ksupersede = iintern("SUPERSEDE",Pkeyword);
  lopen_syms_initialized = 1;
}


Object lopen (filename, direction, element_type, if_exists, if_does_not_exist)
    Object filename, direction, element_type, if_exists, if_does_not_exist;
{
    Declare_local_temp;
    Object exists_p, newnode, stream;
    short etype, dir;
    char *fname;
    FILE *fp;
    char mode[4], readflag, writeflag, binflag, ioflag;
    extern int element_type_to_etype();
    Declare_stack_pointer;

    SAVE_STACK();
    PROTECT_1(filename);
    PROTECTI_2(newnode,stream);
    ioflag = readflag = writeflag = binflag = FALSE;
    mode[0] = '\0';

    if(!lopen_syms_initialized)init_lopen_syms();

    filename = truename(merge_pathnames(filename,KOPT,KOPT));
    if (!STRINGP(filename))
	error(2, "open: filename not a string - ~s", filename);
    fname = ISTRING(filename);

    if (UNSUPPLIED_P(direction)) direction = Kinput;
    exists_p = probe_file(filename);
    if (direction == Kprobe) {
	RESTORE_STACK();
	return VALUES_1(exists_p);
    }

    if (UNSUPPLIED_P(element_type)) element_type = Qstring_char;
    etype = element_type_to_etype(element_type);
    switch(etype) {
    case S_UNSIGNED_BYTE_8:
    case S_UNSIGNED_BYTE_16:
    case S_UNSIGNED_BYTE_32:
    case S_UNSIGNED_BYTE:
    case S_BIT:
    case S_INTEGER:
	binflag = TRUE;
	break;
    case S_STRING_CHAR:
    case S_CHARACTER:
    case S_SIGNED_BYTE_8:
    case S_SIGNED_BYTE_16:
    case S_SIGNED_BYTE_32:
    case S_SIGNED_BYTE:
    default:
	binflag = FALSE;
	break;
    }

    if (direction == Kio) {
	ioflag = TRUE;
	dir = S_IO;
	strcpy(mode, "r+");
    }
    else if (direction == Kinput) {
	dir = S_INPUT;
        readflag = TRUE;
	strcpy(mode, "r");
    }
    else if (direction == Koutput) {
	dir = S_OUTPUT;
	writeflag = TRUE;
	strcpy(mode, "w");
    }

    if (binflag)
	strcat(mode, "b");
    else
	strcat(mode, "t");

    if ((dir == S_OUTPUT) || (dir == S_IO)) {
	if (!UNSUPPLIED_P(exists_p)) {
	    if (EQ(if_exists, Kerror))
		error(2, "open: file exists - ~s", filename);
	    else if (EQ(if_exists, Knew_version))
		error(1, "open: :new-version not available");
	    else if (EQ(if_exists, Krename))
		error(1, "open: :rename not available");
	    else if (EQ(if_exists, Krename_and_delete))
		error(1, "open: :rename-and-delete not available");
	    else if (EQ(if_exists, Ksupersede))
		delete_file(filename);
	    else if (EQ(if_exists, NIL)) {
		RESTORE_STACK();
		return VALUES_1(NIL);
	    }
	    else if (EQ(if_exists, Kappend))
		mode[0] = 'a';
	    /* :overwrite do its stuff later */
	}
    }
    if ((dir == S_INPUT) || (dir == S_IO)) {
	if (UNSUPPLIED_P(exists_p)) {
	    if (EQ(if_does_not_exist, Kerror))
		error(2, "open: file does not exists - ~s", filename);
	    else if (EQ(if_does_not_exist, Kcreate)) {
		if (!(fp = fopen(fname, "wt")))
		    error(2, "open: unable to create file - ~s", filename);
		fclose(fp);
	    }
	    else if (EQ(if_does_not_exist,NIL)) {
		RESTORE_STACK();
		return VALUES_1(NIL);
	    }
	}

    }

#if lint /* flags are needed for true error-checking */
    ioflag = ioflag && readflag && writeflag;
#endif

    fp = fopen(fname, mode);
    if (!fp)
	error(2, "open: unable to open file - ~S", filename);
    if (EQ(if_exists, Koverwrite))
	fseek(fp, 0L, SEEK_SET);
    if (EQ(if_exists, Kappend))
	fseek(fp, 0L, SEEK_END);
    newnode = SI_ALLOC(SI_Cobject, COBJECT_TYPE, SI_INSTANCE_TAG, SI_UGLY);
    SI_SET_WRAPPER(newnode, SI_WRAPPER_cobject);
    COBJECT_OBJ(newnode) = (char *) fp;
    COBJECT_NAME(newnode) = filename;
    stream = SI_ALLOC(SI_Stream, STREAM_TYPE, SI_INSTANCE_TAG, SI_UGLY);
    SI_SET_WRAPPER(stream, SI_WRAPPER_file_stream);
    STREAM_INFO(stream) = (FILE_STREAM | dir | etype);
    STREAM_CURRPOS(stream) = 0;
    STREAM_OBJ(stream) = newnode;
    RESTORE_STACK();
    return VALUES_1(stream);
}
