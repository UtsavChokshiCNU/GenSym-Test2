
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


# Runtime init source files

INITSOURCES1  = \
$(INITDIR)/arrays.c\
$(INITDIR)/biginit.c\
$(INITDIR)/biginit2.c\
$(INITDIR)/bit_arrs.c\
$(INITDIR)/bqinit.c\
$(INITDIR)/chars.c\
$(INITDIR)/ctrlvars.c\
$(INITDIR)/err_aux.c\
$(INITDIR)/evalinit.c\
$(INITDIR)/filesys.c\
$(INITDIR)/fptrs.c\
$(INITDIR)/funcln.c\
$(INITDIR)/gc.c\
$(INITDIR)/initgc.c\
$(INITDIR)/io.c\
$(INITDIR)/lambinit.c\
$(INITDIR)/numinit.c\
$(INITDIR)/pkginit.c\
$(INITDIR)/prntinit.c\
$(INITDIR)/readinit.c\
$(INITDIR)/seqsimp.c\
$(INITDIR)/statics.c\
$(INITDIR)/stderror.c\
$(INITDIR)/stdpkgs.c\
$(INITDIR)/strings.c\
$(INITDIR)/strinint.c\
$(INITDIR)/strminit.c\
$(INITDIR)/structi.c

# Runtime init object files

INITOBJECTS1  = \
$(bin)/arrays.o\
$(bin)/biginit.o\
$(bin)/biginit2.o\
$(bin)/bit_arrs.o\
$(bin)/bqinit.o\
$(bin)/chars.o\
$(bin)/ctrlvars.o\
$(bin)/err_aux.o\
$(bin)/evalinit.o\
$(bin)/filesys.o\
$(bin)/fptrs.o\
$(bin)/funcln.o\
$(bin)/gc.o\
$(bin)/initgc.o\
$(bin)/io.o\
$(bin)/lambinit.o\
$(bin)/numinit.o\
$(bin)/pkginit.o\
$(bin)/prntinit.o\
$(bin)/readinit.o\
$(bin)/seqsimp.o\
$(bin)/statics.o\
$(bin)/stderror.o\
$(bin)/stdpkgs.o\
$(bin)/strings.o\
$(bin)/strinint.o\
$(bin)/strminit.o\
$(bin)/structi.o

INITSOURCES = $(INITSOURCES1)
INITOBJECTS = $(INITOBJECTS1)

# init compilation targets


$(bin)/arrays.o : $(INITDIR)/arrays.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/arrays.o $(INITDIR)/arrays.c 


$(bin)/biginit.o : $(INITDIR)/biginit.c $(INITHEADERS) \
                $(RUNTIME.H) $(BIGNMINT.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/biginit.o $(INITDIR)/biginit.c 


$(bin)/biginit2.o : $(INITDIR)/biginit2.c $(INITHEADERS) \
                $(RUNTIME.H) $(BIGNMINT.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/biginit2.o $(INITDIR)/biginit2.c 


$(bin)/bit_arrs.o : $(INITDIR)/bit_arrs.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/bit_arrs.o $(INITDIR)/bit_arrs.c 


$(bin)/bqinit.o : $(INITDIR)/bqinit.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/bqinit.o $(INITDIR)/bqinit.c 


$(bin)/chars.o : $(INITDIR)/chars.c $(INITHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/chars.o $(INITDIR)/chars.c 


$(bin)/ctrlvars.o : $(INITDIR)/ctrlvars.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/ctrlvars.o $(INITDIR)/ctrlvars.c 


$(bin)/err_aux.o : $(INITDIR)/err_aux.c $(INITHEADERS) \
                $(RUNTIME.H) $(ERRORS.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/err_aux.o $(INITDIR)/err_aux.c 


$(bin)/evalinit.o : $(INITDIR)/evalinit.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/evalinit.o $(INITDIR)/evalinit.c 


$(bin)/filesys.o : $(INITDIR)/filesys.c $(INITHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/filesys.o $(INITDIR)/filesys.c 


$(bin)/fptrs.o : $(INITDIR)/fptrs.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/fptrs.o $(INITDIR)/fptrs.c 


$(bin)/funcln.o : $(INITDIR)/funcln.c $(INITHEADERS) \
                $(RUNTIME.H) $(FUNCALL.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/funcln.o $(INITDIR)/funcln.c 


$(bin)/gc.o : $(INITDIR)/gc.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/gc.o $(INITDIR)/gc.c 


$(bin)/initgc.o : $(INITDIR)/initgc.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/initgc.o $(INITDIR)/initgc.c 


$(bin)/io.o : $(INITDIR)/io.c $(INITHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/io.o $(INITDIR)/io.c 


$(bin)/lambinit.o : $(INITDIR)/lambinit.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/lambinit.o $(INITDIR)/lambinit.c 


$(bin)/numinit.o : $(INITDIR)/numinit.c $(INITHEADERS) \
                $(RUNTIME.H) $(TIME.H) $(LTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/numinit.o $(INITDIR)/numinit.c 


$(bin)/pkginit.o : $(INITDIR)/pkginit.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/pkginit.o $(INITDIR)/pkginit.c 


$(bin)/prntinit.o : $(INITDIR)/prntinit.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/prntinit.o $(INITDIR)/prntinit.c 


$(bin)/readinit.o : $(INITDIR)/readinit.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/readinit.o $(INITDIR)/readinit.c 


$(bin)/seqsimp.o : $(INITDIR)/seqsimp.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/seqsimp.o $(INITDIR)/seqsimp.c 


$(bin)/statics.o : $(INITDIR)/statics.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/statics.o $(INITDIR)/statics.c 


$(bin)/stderror.o : $(INITDIR)/stderror.c $(INITHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/stderror.o $(INITDIR)/stderror.c 


$(bin)/stdpkgs.o : $(INITDIR)/stdpkgs.c $(INITHEADERS) \
                $(KERNEL.H) $(SDEFS.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/stdpkgs.o $(INITDIR)/stdpkgs.c 


$(bin)/strings.o : $(INITDIR)/strings.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/strings.o $(INITDIR)/strings.c 


$(bin)/strinint.o : $(INITDIR)/strinint.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/strinint.o $(INITDIR)/strinint.c 


$(bin)/strminit.o : $(INITDIR)/strminit.c $(INITHEADERS) \
                $(RUNTIME.H) $(STRMINIT.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/strminit.o $(INITDIR)/strminit.c 


$(bin)/structi.o : $(INITDIR)/structi.c $(INITHEADERS) \
                $(RUNTIME.H) 
	$(CCOMPILE) $(OUTCFLAG)$(bin)/structi.o $(INITDIR)/structi.c 


# end 

