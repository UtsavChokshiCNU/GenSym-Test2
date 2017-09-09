#
# This is the makefile for the thunking dlls. These dlls are used
# by G2/TW to "thunk" down to the 16-bit layer on Win32s and Win95
# to check graphics resource usage.
# The source files are maintained in ext/c. When built, the dlls
# should be checked into promote/bin
#
# To build, on a Win31 system run (with the MS C compiler) in the ext/c dir:
#	> nmake -f thunk16.mak
#

all : gen16ut.dll gen16ut.sym

#update the object files if necessary

gen16ut.obj : $*.c
   cl /c /ASw -G2sw -W3 -Zp -Osge $*.c

# update the import library if necessary

gen16ut.lib : $*.def
   implib $@ $*.def

# update the executable files if necessary

gen16ut.map gen16ut.dll : gen16ut.obj gen16ut.def
   link gen16ut,gen16ut.dll,,/NOE /NOD:slibce /cod /li /map sdllcew libw.lib w32sut16.lib,gen16ut.def
   rc -t gen16ut.dll

gen16ut.sym: $*.map
   mapsym $*
