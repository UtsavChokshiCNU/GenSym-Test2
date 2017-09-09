
#############################################################################
#
#   Include file for Chestnut Run-Time Library Makefile
#   Produced automatically by running 
#     % write-make <this-file-name>
#
#   Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
#   Use of this file is subject to the terms of a license from
#   Chestnut Software, Inc.  Please refer to the License for details.
#
############################################################################
# Notes:
#
# ALL dependencies on .h files are specified for every .c
# The files composed in several separate lists for portability reasons
#
#############################################################################

#
# list of core Runtime source files
CORESOURCES = \
$(COREDIR)/backquot.c\
$(COREDIR)/bignum.c\
$(COREDIR)/bindsyms.c\
$(COREDIR)/copygc.c\
$(COREDIR)/diag.c\
$(COREDIR)/errors.c\
$(COREDIR)/evalrun.c\
$(COREDIR)/evals.c\
$(COREDIR)/format.c\
$(COREDIR)/hash.c\
$(COREDIR)/heap.c\
$(COREDIR)/lreader.c\
$(COREDIR)/macros.c\
$(COREDIR)/mapcar.c\
$(COREDIR)/map-objs.c\
$(COREDIR)/markgc.c\
$(COREDIR)/numbers.c\
$(COREDIR)/oldsyms.c\
$(COREDIR)/packages.c\
$(COREDIR)/streams.c\
$(COREDIR)/struct.c\
$(COREDIR)/symbols.c\
$(COREDIR)/usersyms.c

#
# list of core Runtime symbol definition source files
BASESYMSOURCES = \
$(COREDIR)/ifuns.c $(COREDIR)/isyms.c $(COREDIR)/sdefs.c

#
# list of core Runtime  object files
COREOBJECTS = \
$(bin)/backquot.o\
$(bin)/bignum.o\
$(bin)/bindsyms.o\
$(bin)/copygc.o\
$(bin)/diag.o\
$(bin)/errors.o\
$(bin)/evalrun.o\
$(bin)/evals.o\
$(bin)/format.o\
$(bin)/hash.o\
$(bin)/heap.o\
$(bin)/lreader.o\
$(bin)/macros.o\
$(bin)/mapcar.o\
$(bin)/map-objs.o\
$(bin)/markgc.o\
$(bin)/numbers.o\
$(bin)/oldsyms.o\
$(bin)/packages.o\
$(bin)/streams.o\
$(bin)/struct.o\
$(bin)/symbols.o\
$(bin)/usersyms.o

#
# list of core Runtime  symbol definition object files
BASESYMOBJECTS = \
$(bin)/ifuns.o $(bin)/isyms.o $(bin)/sdefs.o


## CORE compilation targets


$(bin)/backquot.o : $(COREDIR)/backquot.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/backquot.o $(COREDIR)/backquot.c 


$(bin)/bignum.o : $(COREDIR)/bignum.c $(COREHEADERS) \
                $(SCHEME.H) $(RUNTIME.H) $(BIGNUM.H) $(BIGNMINT.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/bignum.o $(COREDIR)/bignum.c 


$(bin)/bindsyms.o : $(COREDIR)/bindsyms.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/bindsyms.o $(COREDIR)/bindsyms.c 


$(bin)/copygc.o : $(COREDIR)/copygc.c $(COREHEADERS) \
                $(RUNTIME.H) $(GC.H) $(GCOBJMAP.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/copygc.o $(COREDIR)/copygc.c 


$(bin)/diag.o : $(COREDIR)/diag.c $(COREHEADERS) \
                $(KERNEL.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/diag.o $(COREDIR)/diag.c 


$(bin)/errors.o : $(COREDIR)/errors.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/errors.o $(COREDIR)/errors.c 


$(bin)/evalrun.o : $(COREDIR)/evalrun.c $(COREHEADERS) \
                $(RUNTIME.H) $(EVALRUN.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/evalrun.o $(COREDIR)/evalrun.c 


$(bin)/evals.o : $(COREDIR)/evals.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/evals.o $(COREDIR)/evals.c 


$(bin)/format.o : $(COREDIR)/format.c $(COREHEADERS) \
                $(RUNTIME.H) $(FORMAT.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/format.o $(COREDIR)/format.c 


$(bin)/hash.o : $(COREDIR)/hash.c $(COREHEADERS) \
                $(HASH.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/hash.o $(COREDIR)/hash.c 


$(bin)/heap.o : $(COREDIR)/heap.c $(COREHEADERS) \
                $(RUNTIME.H) $(GC.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/heap.o $(COREDIR)/heap.c 


$(bin)/ifuns.o : $(COREDIR)/ifuns.c $(COREHEADERS) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/ifuns.o $(COREDIR)/ifuns.c 


$(bin)/isyms.o : $(COREDIR)/isyms.c $(COREHEADERS) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/isyms.o $(COREDIR)/isyms.c 


$(bin)/lreader.o : $(COREDIR)/lreader.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/lreader.o $(COREDIR)/lreader.c 


$(bin)/macros.o : $(COREDIR)/macros.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/macros.o $(COREDIR)/macros.c 


$(bin)/mapcar.o : $(COREDIR)/mapcar.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/mapcar.o $(COREDIR)/mapcar.c 


$(bin)/map-objs.o : $(COREDIR)/map-objs.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/map-objs.o $(COREDIR)/map-objs.c 


$(bin)/markgc.o : $(COREDIR)/markgc.c $(COREHEADERS) \
                $(RUNTIME.H) $(GC.H) $(GCOBJMAP.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/markgc.o $(COREDIR)/markgc.c 


$(bin)/numbers.o : $(COREDIR)/numbers.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/numbers.o $(COREDIR)/numbers.c 


$(bin)/oldsyms.o : $(COREDIR)/oldsyms.c $(COREHEADERS) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/oldsyms.o $(COREDIR)/oldsyms.c 


$(bin)/packages.o : $(COREDIR)/packages.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/packages.o $(COREDIR)/packages.c 


$(bin)/streams.o : $(COREDIR)/streams.c $(COREHEADERS) \
                $(RUNTIME.H) $(STRMINIT.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/streams.o $(COREDIR)/streams.c 


$(bin)/struct.o : $(COREDIR)/struct.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/struct.o $(COREDIR)/struct.c 


$(bin)/symbols.o : $(COREDIR)/symbols.c $(COREHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/symbols.o $(COREDIR)/symbols.c 


$(bin)/sdefs.o : $(COREDIR)/sdefs.c $(COREHEADERS) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/sdefs.o $(COREDIR)/sdefs.c 


$(bin)/usersyms.o : $(COREDIR)/usersyms.c $(COREHEADERS) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/usersyms.o $(COREDIR)/usersyms.c 


# end 

