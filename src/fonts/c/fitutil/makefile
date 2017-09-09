#################################################################
#		Unix Makefile for building FIT utility and test programs
#
# $Log: not supported by cvs2svn $
# Revision 1.2  1993/04/19 15:32:53  mpc
# Changed //ninja/archive dirs to local references.
#
# Revision 1.1.1.1  1993/04/15  20:14:25  mhd
# Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
#
#  Revision 1.13  93/03/15  12:41:34  roberte
#  Release
#  
#  Revision 1.2  93/03/03  09:28:47  roberte
#  Changed tt_dir from "true_typ" to "tt"
#  Removed general rule for making objects.
#  
#  Revision 1.1  93/02/02  15:01:08  roberte
#  Initial revision
#  
#  Revision 1.4  93/02/02  14:58:40  roberte
#  Added comment header and RCS control string.  Made macro
#  "tt_dir" and use this in include macro.
#  
#

CFLAGS = -g -c
LINKS = finfotbl.o 

# we use these directories for development:
#utils_dir = //ninja/archive/src/utils
#tt_dir = //ninja/archive/src/true_type
# you should use these directories to match deleivery diskettes:
utils_dir = ../type1
tt_dir = ../tt

userinc = /user/include
#
incl = -I$(userinc) -I$(utils_dir) -I$(tt_dir)

all: fitutil finfotes

fitutil : $(LINKS)
	cc -o fitutil $(LINKS)


finfotbl.o: pclhdrs.h \
			finfotbl.h
	cc $(CFLAGS) $(incl) $*.c
 
#test program target:
finfotest : finfotes.o
	cc -o finfotest finfotes.o

finfotes.o: pclhdrs.h finfotbl.h
	cc $(CFLAGS) $(incl) $*.c
 

