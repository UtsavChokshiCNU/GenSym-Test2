/*   This is a makefile template for the GSI, GSPAN, and foreign image
 * distribution makefiles.  It is in the spirit of imake; i.e., it contains
 * macro definitions that are processed by the gcc C preprocessor to tailor it
 * to platform or product specifics.  It is currently invoked from
 * generate-dst-makefiles, which is run only on a sun machine.
 *   The file is divided into sections that mirror the sections of the
 * generated makefiles.  The initial sections define machine flags and
 * C macros.  The remaining sections provide lines to be conditionally
 * included in the makefile.  To understand the organization, first examine
 * generated makefiles for the different operating systems.
 *
 * Notes:
 *   Propagating blank lines:  The C preprocessor leaves an empty line
 * wherever an #ifdef or comment appears.  The empty lines are stripped by
 * a grep filter in generate-dst-makefiles.  To allow blank lines in the
 * customer makefiles, non-empty lines that contain a single space should
 * be inserted.  To make their presence known, they should always be preceded
 * by a line containing ========= in comments; i.e.,
 *    \* ========= *\     -- with \s replaced by /s of course
 *    <space>
 * A quick way to verify the presence of spaces in empty lines is to
 * pipe the file through "more" and highlight sections of it with the mouse.
 *   The gcc C preprocessor that is currently used has a few idiosynchrasies.
 * It emits lines of the form #<space><digit>* to keep track of line numbers.
 * We remove these lines explicitly.  If you really want a comment that begins
 * with a digit, you'll have to put two or more spaces before the digit.
 * Also, gcc abhors <backslash><newline> pairs; see the comment for the
 * "clean" target at the end of the file.
 *   GSI40_DEF really means the Lisp-based GSI.  So it applies to later
 * versions of GSI as well.
 */

/* -------------------------------------------------------------------------- */
/* Determine the type of operating system. */

#if defined(vax) || defined(alphavms)
#  define vms
#  undef unix
#endif

#if defined(alphant) || defined(intelnt)
#  define win32
#  undef unix
#endif

/* -------------------------------------------------------------------------- */
/* Cpp macros used internally. They provide default directories, command lines,
 * and file extensions. */

/* The Pound Sign (_PS) macro allows a # to be emitted, which begins comment
 * lines in makefiles. */
#define _PS #

#if defined(win32)

#  define EXE(x) $(EXE_DIR)x.exe
#  define OBJ(x) $(OBJ_DIR)x.obj
#  define C(x) $(C_DIR)x.c
#  define COMPILE(x) $(cc) -c $(CCFLAGS) C(x)
#  define LINK(x) $(link) -out:x.exe $(LINKFLAGS)

/* these #defines used for win32 foreign images only */
#  define TPL(x) $(TEMPLATE_DIR)x.tpl
#  define LIB(x) $(LIB_DIR)x.lib
#  define FGN(x) $(EXE_DIR)x.fgn
#  define RUN_OVERLAY(in, out) $(OVERLAY_DIR)overlay in out
#  define COMPILE_FGN(x) $(cc) -c $(CCFLAGS) -o OBJ(x) C(x)
#  define LINK_FGN(x) $(link) -out:$(EXE_DIR)x.fgn $(LINKFLAGS)

#elif defined(unix)

#  define EXE(x) $(EXE_DIR)x
#  define OBJ(x) $(OBJ_DIR)x.o
#  define C(x) $(C_DIR)x.c
#  define COMPILE(x) cc -c $(CCFLAGS) -I$(INCLUDE_DIR) C(x)
#  define LINK(x) cc -o x

/* these #defines used for unix foreign images only */
#  define TPL(x) $(TEMPLATE_DIR)x.tpl
#  define LIB(x) $(LIB_DIR)x.a
#  define FGN(x) $(EXE_DIR)x.fgn
#  define RUN_OVERLAY(in, out) $(OVERLAY_DIR)overlay in out
#  define COMPILE_FGN(x) cc -c $(CCFLAGS) -I$(INCLUDE_DIR) -o OBJ(x) C(x)
#  define LINK_FGN(x) cc -o $(EXE_DIR)x.fgn

#elif defined(vms)

#  define EXE(x) $(EXE_DIR)x.exe
#  define OBJ(x) $(OBJ_DIR)x.obj
#  define C(x) $(C_DIR)x.c
#  define COMPILE(x) CC $(CCFLAGS) C(x)
#  define LINK(x) link/executable=$(EXE_DIR)x.exe

/* these #defines used for vms foreign images only */
#  define TPL(x) $(TEMPLATE_DIR)x.tpl
#  define LIB(x) $(LIB_DIR)x.olb
#  define FGN(x) $(EXE_DIR)x.fgn
#  define RUN_OVERLAY(in, out) overlay in out
#  define COMPILE_FGN(x) CC /OBJECT=OBJ(x) $(CCFLAGS) C(x)
#  define LINK_FGN(x) link/executable=$(EXE_DIR)x.fgn

#endif

/* -------------------------------------------------------------------------- */
/* Not all unix machines need to specify the Bourne shell, but some do. */

#ifdef unix
SHELL=/bin/sh
/* ========= */
 
#endif

/* -------------------------------------------------------------------------- */
/* User comment to identify product */

#ifdef GSI_DEF
_PS Sample makefile for GSI programs.
#ifdef GSI40_DEF
_PS   GSI Version 8.3.
#else
_PS   GSI Version 3.2.
#endif
#elif GSPAN_DEF
_PS Sample makefile for GSPAN programs.
_PS   GSPAN Version 3.1.
#elif FGN_DEF
_PS Sample makefile for foreign images to connect to G2.
#endif

/* -------------------------------------------------------------------------- */
/* User comment to identify the machine type */

#if intelnt
_PS Machine type: Intel NT 486/586
#elif sparcsol
_PS Machine type: Sun4/Sparcstation Solaris
#elif linux
_PS Machine type: Linux
#elif defined(hp9000s700)
_PS Machine type: PA-RISC HP-UX
#elif defined(hpia64)
_PS Machine type: Itanium HP-UX
#elif rs6000
_PS Machine type: IBM RS6000
#elif alphaosf
_PS Machine type: DEC OSF/1 AXP
#elif sun4
_PS Machine type: Sun4/Sparcstation
#elif sgi
_PS Machine type: Silicon Graphics
#elif alphavms
_PS Machine type: DEC Alpha AXP/OpenVMS
#elif vax
_PS Machine type: Vax VMS
#elif alphant
_PS Machine type: DEC NT AXP
#elif defined(hp9000s800)
_PS Machine type: HP9000 Series 800
#elif defined(hp9000s300)
_PS Machine type: HP9000 Series 300/400
#elif defined(mips)
_PS Machine type: Decstation
#elif aviion
_PS Machine type: DGUX Aviion
#elif motorola
_PS Machine type: Motorola 88000
#elif nec
_PS Machine type: NEC EWS4800 Series
#elif ncr
_PS Machine type: NCR 386/486
#elif sun3
_PS Machine type: Sun3
#else
_PS Machine type: Unknown machine type
#endif
/* ========= */
 

/* -------------------------------------------------------------------------- */
/*
 * The NT must include a special file <ntwin32.mak> to define the system
 * properly. */

#ifdef intelnt
 
TARGETOS = WINNT
#endif intelnt

#ifdef win32
!include <ntwin32.mak>
/* ========= */
 
#endif

/* -------------------------------------------------------------------------- */
/* Flags and macros */

C_DIR = 
OBJ_DIR = 
EXE_DIR = 

#ifdef FGN_DEF
TEMPLATE_DIR = $(C_DIR)
#  ifndef vms
OVERLAY_DIR = 
#  endif /* !vms */
#endif

#if defined(unix)

H_DIR = ./
INCLUDE_DIR = $(H_DIR)

#  if defined(mips)
CCFLAGS = -O -G 0
#  else
CCFLAGS = -O
#  endif

LIB_DIR = ./

#elif defined(vms)

PURGE = purge
H_DIR = 
#  ifdef vax
CCFLAGS = /NOWARNING/DEFINE=("CC$mixed_float")
#  else /* alphavms */
CCFLAGS = /NOWARNING/FLOAT=IEEE_FLOAT/STANDARD=VAXC/EXTERN=COMMON/SHARE
#  endif
LIB_DIR = 

#elif defined(win32)
H_DIR = 
CCFLAGS = $(common) $(cflags) $(cvarsmt) -MT
#  if defined(win32) && defined(GSI40_DEF)
LINKFLAGS = $(guilflags)
#  else
#    if defined(intelnt) && (defined(GSI_DEF) || defined(FGN_DEF))
_PS When creating images to execute under Win32s, you should use
_PS $(guilflags) for LINKFLAGS as well as the appropriate DEFAULT_LIBS below.
_PS LINKFLAGS = $(guilflags)
/* ========= */
 
_PS LIBPATH: This is set up to work in a bundle installation which has GSI installed.
_PS If you move your GSI installation, you may need to update this value.
/* ========= */
 
#    endif
LINKFLAGS = $(conflags) /LIBPATH:..\..\gsi
#  endif
LIB_DIR = 
#endif
/* ========= */
 
/* -------------------------------------------------------------------------- */
/* Library definitions.  These are complex because they are dependent on
   both platform and product. */

/* ---------------------------------- */
#ifdef unix

#  if defined(alphaosf)
_PS If your system defines vsnprintf in libc, you can remove -ldb
_PS from PLATFORM_SPECIFIC_LIBS below.
#  endif

#  ifdef GSI_DEF
#    ifdef GSI40_DEF
DEFAULT_LIBS = -lgsi -ltcp -lrtl
NOSSL_LIBS = -lnogsec
#      if defined(linux) || defined(rs6000) || defined(sparcsol)
SSL_LIBS = -lgsec libssl.a libcrypto.a
#      elif defined(hp9000s700)
SSL_LIBS = -lgsec libssl.a libcrypto.a libgcc.a
#      endif
#    else
DEFAULT_LIBS = -lgsi -ltcp
#    endif
#  elif GSPAN_DEF
DEFAULT_LIBS = -lgspan -ltcp
#  elif FGN_DEF
DEFAULT_LIBS = -lforgn
#  endif

#  if defined(mips) && !defined(sgi)
PLATFORM_SPECIFIC_LIBS = -lm
#  elif defined(rs6000)
PLATFORM_SPECIFIC_LIBS = -lm -lbsd -lc
#  elif defined(sun4) || defined(linux)
PLATFORM_SPECIFIC_LIBS = -lm -ldl
#  elif defined(sparcsol)
PLATFORM_SPECIFIC_LIBS = -lsocket -lintl -lm -lnsl -ldl
#  elif defined(alphaosf)
PLATFORM_SPECIFIC_LIBS = -lm -ldb
#  elif defined(motorola) || defined(nec) || defined(ncr)
PLATFORM_SPECIFIC_LIBS = -lsocket -lm -lnsl
#  else
PLATFORM_SPECIFIC_LIBS = -lm
#  endif

LIBS = -L$(LIB_DIR) $(DEFAULT_LIBS) $(PLATFORM_SPECIFIC_LIBS) 

/* ---------------------------------- */
#elif defined(vms)
#  ifdef GSI_DEF
#    ifdef GSI40_DEF
LIBS =  ,gsioptions/opt, librtl.olb/lib
#    else
LIBS =  ,gsioptions/opt
#    endif
#  elif GSPAN_DEF
LIBS =  ,libgspan.olb/lib, gsioptions/opt
#  elif FGN_DEF
LIBS =  ,LIB(libforgn)/lib
#  endif

/* ---------------------------------- */
#elif defined(win32)

#  ifdef GSI_DEF
#    if defined(intelnt)
_PS When creating images to execute under Win32s, you should
_PS use the DEFAULT_LIBS below that has winio.lib.
#    endif
#    ifdef GSI40_DEF
#      if defined(intelnt)
_PS DEFAULT_LIBS = libgsi.lib libtcp.lib librtl.lib libnogsec.lib winio.lib
#      endif
DEFAULT_LIBS = libgsi.lib libtcp.lib librtl.lib
NOSSL_LIBS = libnogsec.lib
SSL_LIBS = libgsec.lib crypt32.lib
#    else
#      if defined(intelnt)
_PS DEFAULT_LIBS = libgsi.lib libtcp.lib winio.lib
#      endif
DEFAULT_LIBS = libgsi.lib libtcp.lib
#    endif
#  elif GSPAN_DEF
DEFAULT_LIBS = libgspan.lib libtcp.lib
#  elif FGN_DEF
#    if defined(intelnt)
_PS When creating images to execute under Win32s, you should
_PS use the DEFAULT_LIBS below that has winio.lib.
#    endif
_PS DEFAULT_LIBS = libforgn.lib winio.lib
DEFAULT_LIBS = libforgn.lib
#  endif

LIBS = $(DEFAULT_LIBS) $(guilibsmt) advapi32.lib wsock32.lib netapi32.lib libircmt.lib libmmt.lib

#endif  /* Library definitions */
/* ========= */
 
/* -------------------------------------------------------------------------- */
/* Product-specific header file dependencies. */

#ifdef GSI_DEF
#  ifdef GSI40_DEF
H_FILES = $(H_DIR)gsi_main.h
#  else  /* GSI3x */
H_FILES = $(H_DIR)gsi.h $(H_DIR)icp.h
#  endif
#elif GSPAN_DEF
H_FILES = $(H_DIR)gspan.h $(H_DIR)icp.h $(H_DIR)xs_sys.h
#elif FGN_DEF
H_FILES = $(H_DIR)foreign.h
#endif

/* -------------------------------------------------------------------------- */
/* Product- and operating-system-specific file lists.  Note the need for
 * commas to delimit command line lists in VMS; however, commas are not needed
 * in dependency lists. */

#ifdef GSI_DEF
#  ifdef GSI40_DEF
#    if defined(win32) || defined(hp9000s700) || defined(sparcsol) || defined(linux)
EXECUTABLES = EXE(filetest) EXE(typetest) EXE(skeleton) EXE(alarmer) EXE(itemtest) EXE(matrix) EXE(pub_subscribe) EXE(reposit) EXE(mapchar) EXE(skeleton_ssl)
#    else
EXECUTABLES = EXE(filetest) EXE(typetest) EXE(skeleton) EXE(alarmer) EXE(itemtest) EXE(matrix) EXE(pub_subscribe) EXE(reposit) EXE(mapchar)
#    endif
#  else  /* GSI3x */
EXECUTABLES = EXE(filetest) EXE(typetest) EXE(skeleton)
#  endif

#  ifdef vms
FILETEST_FILES = OBJ(filetest), OBJ(rpcfuncs)
TYPETEST_FILES = OBJ(typetest), OBJ(gsi_main)
SKELETON_FILES = OBJ(skeleton), OBJ(gsi_main)
#    ifdef GSI40_DEF
ALARMER_FILES = OBJ(alarmer), OBJ(gsi_main)
MAPCHAR_FILES = OBJ(mapchar), OBJ(gsi_main)
ITEMTEST_FILES = OBJ(itemtest), OBJ(gsi_misc)
MATRIX_FILES = OBJ(matrix), OBJ(gsi_main)
PUB_SUBSCRIBE_FILES = OBJ(pub_subscribe), OBJ(gsi_main), OBJ(gsi_misc)
REPOSIT_FILES = OBJ(reposit), OBJ(gsi_main), OBJ(gsi_misc)
#    endif

#  else /* unix, nt, etc. */
#    if defined(win32) && defined(GSI40_DEF)
FILETEST_FILES = OBJ(filetest) OBJ(rpcfuncs) OBJ(gsimmain)
TYPETEST_FILES = OBJ(typetest) OBJ(gsi_main) OBJ(gsimmain)
SKELETON_FILES = OBJ(skeleton) OBJ(gsi_main) OBJ(gsimmain)
#      ifdef GSI40_DEF
ALARMER_FILES = OBJ(alarmer) OBJ(gsi_main) OBJ(gsimmain)
MAPCHAR_FILES = OBJ(mapchar) OBJ(gsi_main) OBJ(gsimmain)
ITEMTEST_FILES = OBJ(itemtest) OBJ(gsi_misc) OBJ(gsimmain)
MATRIX_FILES = OBJ(matrix) OBJ(gsi_main) OBJ(gsimmain)
PUB_SUBSCRIBE_FILES = OBJ(pub_subscribe) OBJ(gsi_main) OBJ(gsi_misc) OBJ(gsimmain)
REPOSIT_FILES = OBJ(reposit) OBJ(gsi_main) OBJ(gsi_misc) OBJ(gsimmain)
#      endif

#    else
FILETEST_FILES = OBJ(filetest) OBJ(rpcfuncs)
TYPETEST_FILES = OBJ(typetest) OBJ(gsi_main)
SKELETON_FILES = OBJ(skeleton) OBJ(gsi_main)
#      ifdef GSI40_DEF
ALARMER_FILES = OBJ(alarmer) OBJ(gsi_main)
MAPCHAR_FILES = OBJ(mapchar) OBJ(gsi_main)
ITEMTEST_FILES = OBJ(itemtest) OBJ(gsi_misc)
MATRIX_FILES = OBJ(matrix) OBJ(gsi_main)
PUB_SUBSCRIBE_FILES = OBJ(pub_subscribe) OBJ(gsi_main) OBJ(gsi_misc)
REPOSIT_FILES = OBJ(reposit) OBJ(gsi_main) OBJ(gsi_misc)
#      endif

#    endif
#  endif /* vms */

#elif defined(GSPAN_DEF)

EXECUTABLES= EXE(gsp_exm1) EXE(gsp_exm2)

# ifdef vms
GSP_EXM1_FILES = OBJ(gsp_exm1), OBJ(gsp_mai1), OBJ(gspan_main)
GSP_EXM2_FILES = OBJ(gsp_exm2), OBJ(gsp_mai2), OBJ(gspan_main)
# else /* unix, nt, etc. */
GSP_EXM1_FILES = OBJ(gsp_exm1) OBJ(gsp_mai1) OBJ(gspan_main)
GSP_EXM2_FILES = OBJ(gsp_exm2) OBJ(gsp_mai2) OBJ(gspan_main)
# endif /* vms */

#elif defined(FGN_DEF)

EXECUTABLES = FGN(fgntest)

# ifdef vms
FGNTEST_FILES = OBJ(fgntest), OBJ(fgnover)
# else /* unix, nt, etc. */
FGNTEST_FILES = OBJ(fgntest) OBJ(fgnover)
# endif /* vms */

#endif
/* ========= */
 
/* -------------------------------------------------------------------------- */
/* The remainder of this file is largely system independent.  It provides the
 * entries of the makefile. */
ALL : $(EXECUTABLES)
#ifdef vms
     $(PURGE) $(OBJ_DIR)
     $(PURGE) $(EXE_DIR)
#endif
/* ========= */
 
/* ---------------------------------- */
/* Entries for GSI makefiles */
#ifdef GSI_DEF

EXE(filetest) : $(FILETEST_FILES)
	LINK(filetest) $(FILETEST_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
EXE(skeleton) : $(SKELETON_FILES)
	LINK(skeleton) $(SKELETON_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
#  if defined(linux) || defined(rs6000) || defined(sparcsol) || defined(hp9000s700) || defined(win32)
EXE(skeleton_ssl) : $(SKELETON_FILES)
	LINK(skeleton_ssl) $(SKELETON_FILES) $(LIBS) $(SSL_LIBS)
/* ========= */
#  endif

EXE(typetest) : $(TYPETEST_FILES)
	LINK(typetest) $(TYPETEST_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
#  ifdef GSI40_DEF
EXE(alarmer) : $(ALARMER_FILES)
	LINK(alarmer) $(ALARMER_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
EXE(mapchar) : $(MAPCHAR_FILES)
	LINK(mapchar) $(MAPCHAR_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
EXE(itemtest) : $(ITEMTEST_FILES)
	LINK(itemtest) $(ITEMTEST_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
EXE(matrix) : $(MATRIX_FILES)
	LINK(matrix) $(MATRIX_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
EXE(pub_subscribe) : $(PUB_SUBSCRIBE_FILES)
	LINK(pub_subscribe) $(PUB_SUBSCRIBE_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
EXE(reposit) : $(REPOSIT_FILES)
	LINK(reposit) $(REPOSIT_FILES) $(LIBS) $(NOSSL_LIBS)
/* ========= */
 
#  endif

OBJ(filetest) : C(filetest) $(H_FILES)
	COMPILE(filetest)
/* ========= */
 
OBJ(typetest) : C(typetest) $(H_FILES)
	COMPILE(typetest)
/* ========= */
 
OBJ(rpcfuncs) : C(rpcfuncs) $(H_FILES)
	COMPILE(rpcfuncs)
/* ========= */
 
OBJ(skeleton) : C(skeleton) $(H_FILES)
	COMPILE(skeleton)
/* ========= */
 
#  ifdef GSI40_DEF
OBJ(alarmer) : C(alarmer) $(H_FILES)
	COMPILE(alarmer)
/* ========= */
 
OBJ(gsi_misc) : C(gsi_misc) $(H_FILES) $(H_DIR)gsi_misc.h
	COMPILE(gsi_misc)
/* ========= */
 
OBJ(mapchar) : C(mapchar) $(H_FILES)
	COMPILE(mapchar)
/* ========= */
 
OBJ(itemtest) : C(itemtest) $(H_FILES) $(H_DIR)gsi_misc.h
	COMPILE(itemtest)
/* ========= */
 
OBJ(matrix) : C(matrix) $(H_FILES)
	COMPILE(matrix)
/* ========= */
 
OBJ(pub_subscribe) : C(pub_subscribe) $(H_FILES)
	COMPILE(pub_subscribe)
/* ========= */
 
OBJ(reposit) : C(reposit) $(H_FILES)
	COMPILE(reposit)
/* ========= */
 
#  endif

OBJ(gsi_main) : C(gsi_main) $(H_FILES)
	COMPILE(gsi_main)
/* ========= */

#if defined(win32) && defined(GSI40_DEF)
 
OBJ(gsimmain) : C(gsimmain) $(H_FILES)
	COMPILE(gsimmain)

#endif

#elif defined(GSPAN_DEF)
/* ---------------------------------- */
/* Entries for GSPAN makefiles */

EXE(gsp_exm1) : $(GSP_EXM1_FILES)
	LINK(gsp_exm1) $(GSP_EXM1_FILES) $(LIBS)
/* ========= */
 
EXE(gsp_exm2) : $(GSP_EXM2_FILES)
	LINK(gsp_exm2) $(GSP_EXM2_FILES) $(LIBS)
/* ========= */
 
OBJ(gsp_exm1) : C(gsp_exm1) $(H_FILES)
	COMPILE(gsp_exm1)
/* ========= */
 
OBJ(gsp_exm2) : C(gsp_exm2) $(H_FILES)
	COMPILE(gsp_exm2)
/* ========= */
 
OBJ(gsp_mai1) : C(gsp_mai1) $(H_FILES)
	COMPILE(gsp_mai1)
/* ========= */
 
OBJ(gsp_mai2) : C(gsp_mai2) $(H_FILES)
	COMPILE(gsp_mai2)
/* ========= */
 
OBJ(gspan_main) : C(gspan_main) $(H_FILES)
	COMPILE(gspan_main)

#elif defined(FGN_DEF)
/* ---------------------------------- */
/* Entries for foreign image makefiles */

FGN(fgntest) : $(FGNTEST_FILES)
	LINK_FGN(fgntest) $(FGNTEST_FILES) $(LIBS)
/* ========= */
 
OBJ(fgntest) : C(fgntest) $(H_FILES)
	COMPILE_FGN(fgntest)
/* ========= */
 
OBJ(fgnover) : C(fgnover) $(H_FILES)
	COMPILE_FGN(fgnover)
/* ========= */
 
C(fgnover) : TPL(fgntest)
	RUN_OVERLAY(TPL(fgntest), C(fgnover))
#endif

/* ---------------------------------- */
/* Product-independent clean entry for Unix only.
 * The double backslash is needed because gcc removes all backslash-newline
 * pairs.  The double backslash is passed through unchanged and
 * replaced by a single backslash by sed.
 */
#ifdef unix
/* ========= */
 
clean :
	@for file in $(EXECUTABLES); do \\
		if [ -f $$file ] ; then \\
			rm $$file; \\
		fi ;\\
	done
	@rm *.o
#endif /* unix */
