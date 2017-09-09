#
# This is the makefile for the thunking dlls. These dlls are used
# by G2/TW to "thunk" down to the 16-bit layer on Win32s and Win95
# to check graphics resource usage.
# The source files are maintained in ext/c. When built, the dlls
# should be checked into promote/bin
#
# To build, on an IntelNT system run in the ext/c directory:
#	> nmake -f thunk32.mak
#

NODEBUG=1

!include <ntwin32.mak>

all: gen32.dll gen32ut.dll

gen32.obj: $*.c 
    $(cc) $(cflags) $(cvars) $*.c

gen32.dll: $*.obj $*.def
    $(link) $(dlllflags) $(ldebug) \
    -out:$@ -def:$*.def \
    $*.obj \
    $(guilibs) k32lib.lib thunk32.lib


gen32ut.obj: $*.c 
    $(cc) $(cflags) $(cvars) $(cdebug) $*.c

gen32ut.dll: $*.obj $*.def
    $(link) $(dlllflags) $(ldebug) \
    -out:$@ -def:$*.def \
    $*.obj \
    $(guilibs) w32sut32.lib mpr.lib
