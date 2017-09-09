
###############################################################################
#                       Make file for PROCOB demos
###############################################################################
#  Usage :
# For compiling procob demos
#    make -f demo_procob_ic.mk
#
# For precompiling, compiling & linking the procobdemo.pco file
#    make -f demo_procob_ic.mk build EXE=procobdemo COBS=procobdemo.cob
#
# In general, for any procob program
#    make -f demo_procob_ic.mk build EXE=<exename> COBS="<list of dependent cobs>"
#    To make use of any PROCOB options during precompilation, 
#        make -f demo_procob_ic.mk build PROCOBFLAGS="<list of procob options>" 
#            EXE=<exename> COBS="<list of dependent cobs>"
#
# NOTES: 
#    1. Please change "COB" and the "InstantClient directories" to point to 
#       appropiate locations on your machine before using this makefile.
#    2. In case of RPM installation, please change the following variables
#       as mentioned below:
#         PROCOB=/usr/lib/oracle/VV.v/client/bin/procob
#         ICLIBHOME=/usr/lib/oracle/VV.v/client/lib/
#       Legend:
#         VV - Major Oracle version number
#          v - Minor Oracle version number
#         (Ex:  For the release 12.1, VV = 12 and v = 1)
#
###############################################################################

COB=cob

# InstantClient Directories.
ICSDKHOME=../
ICLIBHOME=../../

MKLINK=ln
REMOVE=rm -rf
CLNCACHE=cleancache
CACHEDIR=SunWS_cachea
MAKE=make
MAKEFILE=demo_procob_ic.mk
PROCOBDEMO=procobdemo

PROCOB=$(ICSDKHOME)/procob
ICLIBPATH=$(LDPATHFLAG)$(ICLIBHOME)
SO_EXT=.so
COBFLAGS=-C IBMCOMP -C NESTCALL -t -x
LDPATHFLAG=-L
COBSQLINTF=$(ICLIBHOME)cobsqlintf.o
LDLIBS=$(EXSYSLIBS) $(MATHLIB) $(USRLIBS)
EXSYSLIBS=-ldl
MATHLIB=-lm
COBOL_PROLDLIBS=$(SHARED_CLIENTLIBS) $(LDLIBS)
SHARED_CLIENTLIBS=$(LLIBCLNTSH) $(LDFLAGS)
LLIBCLNTSH=$(LDLIBFLAG)$(LIBCLNTSHNAME)
LDLIBFLAG=-l
LIBCLNTCORENAME=clntshcore
LIBCLNTSHNAME=clntsh
LDFLAGS=-g

DEMO_PROCOB_BUILD=$(COB) $(COBFLAGS) -o $(EXE) $(COBS) $(ICLIBPATH) $(COBSQLINTF) $(COBOL_PROLDLIBS)

#-----------------------------------------------------------------------------
# Targets for building the procob sample programs.
#
# The target 'build' puts together an executable $(EXE) from the cobol
# sources in $(COBS) and the libraries in $(COBOL_PROLDLIBS).
# The rules to make .cob files from .pco files are later in this file.
#
all: clean $(PROCOBDEMO)

$(PROCOBDEMO):
	$(MAKE) -f $(MAKEFILE) build COBS=$@.cob EXE=$@
	
build: $(CLNCACHE) $(COBS)
	$(MKLINK) $(ICLIBHOME)libclntshcore$(SO_EXT).12.1 $(ICLIBHOME)libclntshcore$(SO_EXT)
	$(MKLINK) $(ICLIBHOME)libclntsh$(SO_EXT).12.1 $(ICLIBHOME)libclntsh$(SO_EXT)
	$(DEMO_PROCOB_BUILD)
	$(REMOVE) $(ICLIBHOME)libclntshcore$(SO_EXT)
	$(REMOVE) $(ICLIBHOME)libclntsh$(SO_EXT)

#-----------------------------------------------------------------------------
# Here are some rules for converting .pco -> .cob -> .o and for .cob -> .gnt.
#
.SUFFIXES: .cob .cbl .o .pco $(GNT)

.pco.cob:
	$(PROCOB) $(PROCOBFLAGS) iname=$*.pco

.cob$(GNT):
	$(COB2GNT)

#-----------------------------------------------------------------------------
# Clean up all executables, *.o and generated *.cob files
clean: $(CLNCACHE)
	$(REMOVE) $(PROCOBDEMO) $(PROCOBDEMO).o $(PROCOBDEMO).cob $(PROCDEMO).lis $(PROCOBDEMO).int $(PROCOBDEMO).idy 

cleancache:
	$(REMOVE) $(CACHEDIR)
	$(REMOVE) $(ICLIBHOME)libclntshcore$(SO_EXT)
	$(REMOVE) $(ICLIBHOME)libclntsh$(SO_EXT)
