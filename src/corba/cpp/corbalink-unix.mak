#
# makefile to build CorbaLink for HPUX, AIX/rs6000, or SunOS/Sparc Solaris.
#            "MACHINE" should be defined either as a command-line macro or 
#            an enviroment variable when this file is invoked
#

include $(SRCBOX)/corba/cpp/corba.def

# define compile and link options for this platform
# -------------------------------------------------
alphaosf_INCLUDES   = -I/usr/local/lib/gcc-lib/alpha-dec-osf3.2/2.7.2/include
sparcsol_INCLUDES   = -I/usr/local/lib/g++-include
hp9000s700_INCLUDES = -I/opt/gcc/include/g++
hp9000s800_INCLUDES = $(hp9000s700_INCLUDES)
linux_INCLUDES      = -I/usr/local/lib/g++-include
rs6000_INCLUDES     = -I/usr/local/include/g++
PLATFORM_INCLUDES   = $($(MACHINE)_INCLUDES)

alphaosf_LIBS       = -lm
sparcsol_LIBS       = -lsocket -lnsl -lm -ldl
hp9000s700_LIBS     = -lm
hp9000s800_LIBS     = $(hp9000s700_LIBS)
linux_LIBS          = -lnsl -lm -ltcp -ldl
rs6000_LIBS         =
PLATFORM_LIBS       = $($(MACHINE)_LIBS)

SRCDIR              = ${SRCBOX}/corba/cpp

LIBS                = $(GSIDIR)/gsi_misc.o $(GSIDIR)/libgsi.a \
                      $(GSIDIR)/libtcp.a $(GSIDIR)/libnogsec.a \
                      $(GSIDIR)/librtl.a ${PLATFORM_LIBS}

alphaosf_CFLAGS     = -c -D${MACHINE} -DCORBALINK_VER=\"${CORBALINK_VER}\" \
                      -I$(SRCDIR) -I$(GSIDIR) $(PLATFORM_INCLUDES) -o ${@F}
alphaosf_CCFLAGS    =
alphaosf_EXTRA      = echo 
sparcsol_CFLAGS     = -c -D${MACHINE} -DCORBALINK_VER=\"${CORBALINK_VER}\" \
                      -I$(SRCDIR) -I$(GSIDIR) $(PLATFORM_INCLUDES) -o ${@F}
sparcsol_CCFLAGS    =
sparcsol_EXTRA      = echo 
hp9000s700_CFLAGS   = -c -g -D$(MACHINE) -DCORBALINK_VER=\"${CORBALINK_VER}\" \
                      -I$(SRCDIR) -I$(GSIDIR) $(PLATFORM_INCLUDES) -o ${@F}
hp9000s700_CCFLAGS  = -Wno-deprecated
hp9000s700_EXTRA    = chatr +s enable $@
hp9000s800_CFLAGS   = ${hp9000s700_CFLAGS}
hp9000s800_CCFLAGS  = ${hp9000s700_CCFLAGS}
hp9000s800_EXTRA    = $(hp9000s700_EXTRA)
linux_CFLAGS        = -c -D${MACHINE} -DCORBALINK_VER=\"${CORBALINK_VER}\" \
                      -I$(SRCDIR) -I$(GSIDIR) $(PLATFORM_INCLUDES) -o ${@F}
linux_CCFLAGS       =
linux_EXTRA         = echo 
rs6000_CFLAGS       = -c -D$(MACHINE) -fsigned-char \
                      -DCORBALINK_VER=\"${CORBALINK_VER}\" -Wno-deprecated \
                      -I$(SRCDIR) -I$(GSIDIR) $(PLATFORM_INCLUDES) -o ${@F}
rs6000_CCFLAGS      =
rs6000_EXTRA        = echo 

PLATFORM_CFLAGS     = $($(MACHINE)_CFLAGS)
PLATFORM_CCFLAGS    = $($(MACHINE)_CCFLAGS)
PLATFORM_EXTRA      = $($(MACHINE)_EXTRA)
LINKFLAGS           = -g -L/usr/local/lib

# These are the object files generated from C++ source files
# ----------------------------------------------------------
EXE_1_CPP_OBJS =    builder.o \
                    code_tokens.o \
                    connections.o \
                    download_ir.o \
                    encoding.o \
                    error_handler.o \
                    G2Container.o \
                    G2CorbaContainer.o \
                    g2item.o \
                    g2string.o \
                    gsi_compile_idl.o \
                    gsi_fcns.o \
                    iiop.o \
                    init_context.o \
                    ior.o \
                    lex_1.o \
                    locator.o \
                    orbtype.o \
                    parse.o \
                    parse_tree_node.o \
                    pause.o \
                    recv_req.o \
                    reg_obj.o \
                    reg_proxy.o \
                    send_req.o \
                    shutdown_context.o \
                    sockbase.o \
                    token.o \
                    utils.o

TYPICAL        =    connections.o       gsi_fcns.o          iiop.o             \
                    init_context.o      ior.o               pause.o            \
                    reg_obj.o           reg_proxy.o         shutdown_context.o \
                    sockbase.o

# This object file is generated for a C source file
# -------------------------------------------------
EXE_1_C_OBJS   =  ytab.o

# Common combinations of dependencies
# -----------------------------------
GSI_MAIN       =  ${SRCDIR}/gsi_main_cpp.h     ${GSIDIR}/gsi_main.h
GSI_MISC       =  ${SRCDIR}/gsi_misc_cpp.h     ${GSIDIR}/gsi_misc.h
COMMON_DEPS    =  $(SRCDIR)/connections.h      $(SRCDIR)/corba_main.h  $(SRCDIR)/G2ContainerClass.h    \
                  $(SRCDIR)/G2CorbaContainer.h $(SRCDIR)/g2string.h    $(SRCDIR)/iiop.h                \
                  $(SRCDIR)/references.h       ${GSI_MAIN}
COM_W_GSIMAIN  =  ${COMMON_DEPS} 
MAKEFILE       =  ${SRCDIR}/corbalink-unix.mak


# The rules
# ---------
all      : g2-corba 

g2-corba : prelim startup.o $(EXE_1_CPP_OBJS) $(EXE_1_C_OBJS)
	@g++ $(LINKFLAGS) -o $@ startup.o ${EXE_1_CPP_OBJS} ${EXE_1_C_OBJS} ${LIBS}
	@$(PLATFORM_EXTRA)
	@chmod +x $@
	@ls -l $@

startup.o:          ${SRCDIR}/startup.cpp           ${MAKEFILE}                             \
                    ${COMMON_DEPS}                  $(SRCDIR)/yacc_supp.h
	@g++  -DBUILD_CODE=\"${BLDCOD}\" -DG2KB_VER=\"$(CLORBV)\" -DG2KB_IDL_VER=\"$(CLIDLV)\" $(PLATFORM_CFLAGS) $(PLATFORM_CCFLAGS)  $(SRCDIR)/$(@:.o=.cpp)
	@echo ${@}

${EXE_1_CPP_OBJS} : ${SRCDIR}/$${@:.o=.cpp} ${MAKEFILE}
	@g++ $(PLATFORM_CFLAGS) $(PLATFORM_CCFLAGS) $(SRCDIR)/$(@:.o=.cpp)
	@echo ${@}

${EXE_1_C_OBJS}   : ${SRCDIR}/$${@:.o=.c} ${MAKEFILE}
	@gcc $(PLATFORM_CFLAGS) $(SRCDIR)/$(@:.o=.c)
	@echo ${@}

${TYPICAL}        : ${COMMON_DEPS}

builder.o         : ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/code_tokens.h         $(SRCDIR)/lex_1_dcl.h           \
                    $(SRCDIR)/parse_dcl.h           $(SRCDIR)/parse_tree_node_dcl.h \
                    $(SRCDIR)/token_dcl.h           $(SRCDIR)/yacc_supp.h           \
                    $(SRCDIR)/ytab.h

code_tokens.o:      ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/code_tokens.h

download_ir.o:      ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/orbtype.h             

encoding.o:         ${COMMON_DEPS}                  $(SRCDIR)/encoding.h            
                    

G2Container.o:      $(GSI_MAIN)                     $(SRCDIR)/G2ContainerClass.h    \
                    $(SRCDIR)/references.h

G2CorbaContainer.o: ${COMMON_DEPS}                  $(SRCDIR)/encoding.h            \
                    $(SRCDIR)/orbtype.h             

g2item.o:           ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/encoding.h            $(SRCDIR)/typecodes.h 

g2string.o:         $(SRCDIR)/g2string.h  

gsi_compile_idl.o:  ${COMMON_DEPS}                  $(SRCDIR)/code_tokens.h         \
                    $(SRCDIR)/gsi_compile_idl.h     $(SRCDIR)/utils.h               \
                    $(SRCDIR)/yacc_supp.h

lex_1.o:            ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/builder_dcl.h         $(SRCDIR)/code_tokens.h         \
                    $(SRCDIR)/lex_1_dcl.h           $(SRCDIR)/parse_dcl.h           \
                    $(SRCDIR)/parse_tree_node_dcl.h $(SRCDIR)/token_dcl.h           \
                    $(SRCDIR)/yacc_supp.h           $(SRCDIR)/ytab.h 

locator.o:          ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/encoding.h           

orbtype.o:          ${COMMON_DEPS}                  $(SRCDIR)/encoding.h            \
                    $(SRCDIR)/orbtype.h            

parse.o:            ${COMMON_DEPS}                  $(SRCDIR)/code_tokens.h         \
                    $(SRCDIR)/parse_dcl.h           $(SRCDIR)/yacc_supp.h           \
                    $(SRCDIR)/ytab.h 

parse_tree_node.o:  ${COMMON_DEPS}                  $(SRCDIR)/code_tokens.h         \
                    $(SRCDIR)/parse_dcl.h           $(SRCDIR)/parse_tree_node_dcl.h \
                    $(SRCDIR)/yacc_supp.h           $(SRCDIR)/ytab.h 
                    
recv_req.o:         ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/encoding.h

send_req.o:         ${COMMON_DEPS}                  ${GSI_MISC}                     \
                    $(SRCDIR)/encoding.h            $(SRCDIR)/orbtype.h                    

token.o:            ${COMMON_DEPS}                  $(SRCDIR)/code_tokens.h         \
                    $(SRCDIR)/parse_dcl.h           $(SRCDIR)/token_dcl.h           \
                    $(SRCDIR)/yacc_supp.h           $(SRCDIR)/ytab.h

utils.o:            $(SRCDIR)/utils.h               $(SRCDIR)/yacc_supp.h

# Remove intermediate files
# -------------------------
clean:
	@- rm *.o 2> /dev/null

prelim:
	@echo ======================================
	@echo '  CorbaLink Ver.' ${CORBALINK_VER}
	@echo
	@echo '  Machine       = ' ${MACHINE}
	@echo '  Build Code    = ' ${BLDCOD}
	@echo '  Source Dir    = ' ${SRCBOX}/corba/cpp
	@echo '  GSI Dir       = ' ${GSIDIR}
	@echo '  Destination   = ' `pwd`
	@echo
	@echo ======================================
	@if test ! "${CORBALINK_VER}" ; \
	   then echo Missing Version \(CORBALINK_VER\) ; false ; fi
	@if test ! "${MACHINE}" ; \
	   then echo Missing Version \(MACHINE\) ; false ; fi
	@if test  "${MACHINE}" != hp9000s700 -a "${MACHINE}" != hp9000s800 -a \
           "${MACHINE}" != sparcsol -a "${MACHINE}" != rs6000 -a \
           "${MACHINE}" != linux -a "${MACHINE}" != alphaosf ; \
	   then echo Invalid MACHINE \(${MACHINE}\) ; false ; fi
	@if test ! "${GSIDIR}" ; \
	   then echo Missing GSI Directory \(GSIDIR\) ; false ; fi
	@if test ! "${BLDCOD}" ; \
	   then echo Missing Version \(BLDCOD\) ; false ; fi
	@if test ! "${CLORBV}" ; \
	   then echo Missing specification of version of g2orb.kb \(CLORBV\) ; false ; fi
	@if test ! "${CLIDLV}" ; \
	   then echo Missing specification of version of g2idl.kb \(CLIDLV\) ; false ; fi

