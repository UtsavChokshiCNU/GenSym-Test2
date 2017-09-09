# $Revision: 10980 $ $Date: 2010-03-19 13:59:17 -0700 (Fri, 19 Mar 2010) $
# Copyright (c) Bullseye Testing Technology
# This source file contains confidential proprietary information.

CC=cl -c -GS- -nologo -O1 -WX -Zl $(CCFLAGS)
SIGN=echo

Depend = Makefile atomic.h cmn-autoSave.h covrt.c libcov.h
CrossDepend = $(Depend) cmn-getenvBuf.h
NativeDepend = $(Depend) libcov-win32.h win32-dynamic.h
StaticDepend = $(NativeDepend) libcov-win32-static.h
DynamicDepend = $(NativeDepend) libcov-win32-dynamic.h libcov-win32-entryUser.c

#-----------------------------------------------------------------------
# Windows NT with dynamic run-time
DynamicDependNT = $(DynamicDepend) libcov-win32-NT.c

../lib/libcov-windows-x86.lib: $(DynamicDependNT) win32-dynamic-bin-x86.h
	$(CC) -Gr -Gy- -W4 libcov-win32-NT.c libcov-win32-entryUser.c
	lib -nologo -out:$@ libcov-win32-NT.obj libcov-win32-entryUser.obj

../lib/libcov-windows-x64.lib: $(DynamicDependNT) win32-dynamic-bin-x64.h
	$(CC) -Gr -Gy- -W4 libcov-win32-NT.c libcov-win32-entryUser.c
	lib -nologo -out:$@ libcov-win32-NT.obj libcov-win32-entryUser.obj

../lib/libcov-windows-ia64.lib: $(DynamicDependNT) win32-dynamic-bin-ia64.h
	$(CC) -Gr -Gy- -W4 libcov-win32-NT.c libcov-win32-entryUser.c
	link -lib -nologo -out:$@ libcov-win32-NT.obj libcov-win32-entryUser.obj

#-----------------------------------------------------------------------
# Windows CE
DynamicDependCE = $(DynamicDepend) libcov-win32-CE.c cmn-getenvBuf.h

../lib/libcov-windowsCE-x86.lib: $(DynamicDependCE) win32-dynamic-bin-x86ce.h
	$(CC) -Gy- -W3 libcov-win32-CE.c libcov-win32-entryUser.c
	lib -nologo -out:$@ libcov-win32-CE.obj libcov-win32-entryUser.obj

../lib/libcov-windowsCE-arm.lib: $(DynamicDependCE) win32-dynamic-bin-arm.h
	$(CC) -W3 libcov-win32-CE.c libcov-win32-entryUser.c
	lib -nologo -out:$@ libcov-win32-CE.obj libcov-win32-entryUser.obj

../lib/libcov-windowsCE-armv4i.lib: $(DynamicDependCE) win32-dynamic-bin-armv4i.h
	$(CC) -QRarch4T -QRinterwork-return -W3 libcov-win32-CE.c libcov-win32-entryUser.c
	lib -nologo -out:$@ libcov-win32-CE.obj libcov-win32-entryUser.obj

../lib/libcov-windowsCE-mips.lib: $(DynamicDependCE) win32-dynamic-bin-mips.h
	$(CC) -W3 libcov-win32-CE.c libcov-win32-entryUser.c
	lib -nologo -out:$@ libcov-win32-CE.obj libcov-win32-entryUser.obj

../lib/libcov-windowsCE-sh4.lib: $(DynamicDependCE) win32-dynamic-bin-sh4.h
	$(CC) -Qsh4 -W3 libcov-win32-CE.c libcov-win32-entryUser.c
	lib -nologo -out:$@ libcov-win32-CE.obj libcov-win32-entryUser.obj

#-----------------------------------------------------------------------
# Dynamic run-time DLL
DllDepend = Makefile atomic.h bin2c.exe libcov.h win32-dynamic.cpp win32-dynamic.h
DllLink = link -dll -entry:dllMain -ignore:4078 -merge:.rdata=.text -nodefaultlib -nologo -stub:dosstub.exe win32-dynamic.obj
DllLinkNT = $(DllLink) kernel32.lib
DllLinkCE = $(DllLink) -subsystem:windowsce coredll.lib

win32-dynamic-bin-x86.h: $(DllDepend)
	$(CC) -W4 win32-dynamic.cpp
	$(DllLinkNT) -out:BullseyeCoverage-x86.dll
	$(SIGN) BullseyeCoverage-x86.dll
	bin2c dll BullseyeCoverage-x86.dll >$@
	rm BullseyeCoverage-x86.*

win32-dynamic-bin-x64.h: $(DllDepend)
	$(CC) -W4 win32-dynamic.cpp
	$(DllLinkNT) -out:BullseyeCoverage-x64.dll
	$(SIGN) BullseyeCoverage-x64.dll
	bin2c dll BullseyeCoverage-x64.dll >$@
	rm BullseyeCoverage-x64.*

win32-dynamic-bin-ia64.h: $(DllDepend)
	$(CC) -W4 win32-dynamic.cpp
	$(DllLinkNT) -out:BullseyeCoverage-ia64.dll
	bin2c dll BullseyeCoverage-ia64.dll >$@
	rm BullseyeCoverage-ia64.*

win32-dynamic-bin-arm.h: $(DllDepend)
	$(CC) -W3 win32-dynamic.cpp
	$(DllLinkCE) -out:BullseyeCoverage-arm.dll -machine:arm
	bin2c dll BullseyeCoverage-arm.dll >$@
	rm BullseyeCoverage-arm.*

win32-dynamic-bin-armv4i.h: $(DllDepend)
	$(CC) -QRarch4T -QRinterwork-return -W3 win32-dynamic.cpp
	$(DllLinkCE) -out:BullseyeCoverage-armv4i.dll -machine:thumb
	bin2c dll BullseyeCoverage-armv4i.dll >$@
	rm BullseyeCoverage-armv4i.*

win32-dynamic-bin-mips.h: $(DllDepend)
	$(CC) -W3 win32-dynamic.cpp
	$(DllLinkCE) -out:BullseyeCoverage-mips.dll -machine:mips
	bin2c dll BullseyeCoverage-mips.dll >$@
	rm BullseyeCoverage-mips.*

win32-dynamic-bin-sh4.h: $(DllDepend)
	$(CC) -Qsh4 -W3 win32-dynamic.cpp
	$(DllLinkCE) -out:BullseyeCoverage-sh4.dll -machine:sh4
	bin2c dll BullseyeCoverage-sh4.dll >$@
	rm BullseyeCoverage-sh4.*

win32-dynamic-bin-x86ce.h: $(DllDepend)
	$(CC) -DUNDER_CE -W3 win32-dynamic.cpp
	$(DllLinkCE) -out:BullseyeCoverage-x86ce.dll -machine:x86
	bin2c dll BullseyeCoverage-x86ce.dll >$@
	rm BullseyeCoverage-x86ce.*

bin2c.exe: bin2c.cpp
	cl -nologo $(CCFLAGS) bin2c.cpp
	rm bin2c.obj

#-----------------------------------------------------------------------
# Windows Embarcadero C++
../lib/libcov-windows-x86-embarcadero.lib: $(StaticDepend)
	bcc32 -c -O1 -j5 -olibcovwin32NT.obj -w- $(CCFLAGS) libcov-win32-NT.c
	tlib tmp.lib -+libcovwin32NT.obj
	mv tmp.lib $@

#-----------------------------------------------------------------------
# Windows GNU C++
../lib/libcov.a: $(StaticDepend)
	gcc $(CCFLAGS) -c -Os -Wall -Wextra libcov-win32-NT.c
	ar -cr $@ libcov-win32-NT.o

#-----------------------------------------------------------------------
# Windows Graphic
GraphicDepend = $(Depend) libcov-windowsGraphic-entry.c libcov-windowsGraphic.c

../lib/libcov-windowsGraphic-x86.lib: $(GraphicDepend)
	$(CC) -Gy- -W3 libcov-windowsGraphic.c
	$(CC) -W4 libcov-windowsGraphic-entry.c -Dvalue=1
	$(CC) -W4 libcov-windowsGraphic-entry.c -Dvalue=0 -Fo../lib/libcov-windowsGraphic-entry0-x86.obj
	lib -nologo -out:$@ libcov-windowsGraphic.obj libcov-windowsGraphic-entry.obj

../lib/libcov-windowsGraphic-x64.lib: $(GraphicDepend)
	$(CC) -Gy- -W3 libcov-windowsGraphic.c
	$(CC) -W4 libcov-windowsGraphic-entry.c -Dvalue=1
	$(CC) -W4 libcov-windowsGraphic-entry.c -Dvalue=0 -Fo../lib/libcov-windowsGraphic-entry0-x64.obj
	lib -nologo -out:$@ libcov-windowsGraphic.obj libcov-windowsGraphic-entry.obj

../lib/libcov-windowsGraphic-ia64.lib: $(GraphicDepend)
	$(CC) -Gy- -W3 libcov-windowsGraphic.c
	$(CC) -W4 libcov-windowsGraphic-entry.c -Dvalue=1
	$(CC) -W4 libcov-windowsGraphic-entry.c -Dvalue=0 -Fo../lib/libcov-windowsGraphic-entry0-ia64.obj
	link -lib -nologo -out:$@ libcov-windowsGraphic.obj libcov-windowsGraphic-entry.obj

#-----------------------------------------------------------------------
# Windows Kernel
KernelDepend = $(Depend) libcov-windowsKernel.c

../lib/libcov-windowsKernel-x86.lib: $(KernelDepend)
	$(CC) -Gy- -Gz -W4 libcov-windowsKernel.c
	lib -nologo -out:$@ libcov-windowsKernel.obj

../lib/libcov-windowsKernel-x64.lib: $(KernelDepend)
	$(CC) -Gy- -Gz -W4 libcov-windowsKernel.c
	lib -nologo -out:$@ libcov-windowsKernel.obj

../lib/libcov-windowsKernel-ia64.lib: $(KernelDepend)
	$(CC) -Gy- -Gz -W4 libcov-windowsKernel.c
	link -lib -nologo -out:$@ libcov-windowsKernel.obj

#-----------------------------------------------------------------------
# lcc-win32
../lib/libcov-windows-lcc.lib: $(StaticDepend)
	c:/opt/lcc/bin/lcc -O -p6 $(CCFLAGS) libcov-win32-NT.c
	ar -r $@ libcov-win32-NT.obj

#-----------------------------------------------------------------------
# Symbian OS ARM GCC
#	Adjust the settings of $(i) and __PRODUCT_INCLUDE__ for your SDK version
i=/S60/devices/S60_3rd_FP2_SDK_v1.1/epoc32/include
../lib/libcov-symbian-gcc.lib: $(CrossDepend) libcov-symbian.cpp
	arm-none-symbianelf-g++ -D__PRODUCT_INCLUDE__=\"Symbian_OS_v9.3.hrh\" -I$(i) -I$(i)/libc -I$(i)/variant -c -mapcs -march=armv5t -msoft-float -mthumb-interwork -nostdinc -O -Wall -Wextra $(CCFLAGS) -include $(i)/gcce/gcce.h libcov-symbian.cpp
	arm-none-symbianelf-ar -cr $@ libcov-symbian.o

#-----------------------------------------------------------------------
# Symbian OS ARM RVCT
#	Adjust the setting of $(i) for your SDK version
i=/S60/devices/S60_3rd_FP2_SDK_v1.1/epoc32/include
../lib/libcov-symbian-rvct.lib: $(CrossDepend) libcov-symbian.cpp
	armcc -I$(i) -I$(i)/libc -I$(i)/variant --preinclude rvct2_2/rvct2_2.h --apcs /inter --cpu 5T --diag_suppress 66,161,550,611,654,997,1152,1300,1464,1488,1566,6318,6331 --dllimport_runtime --enum_is_int --exceptions --exceptions_unwind --export_all_vtbl --fpmode ieee_no_fenv --fpu softvfp --no_vfe --thumb -D__ARMCC__ -D__EABI__ -D__EPOC32__ -D__SYMBIAN32__ -O2 -Ono_known_library -c $(CCFLAGS) libcov-symbian.cpp
	armar --create $@ libcov-symbian.o

#-----------------------------------------------------------------------
# POSIX
../lib/libcov-posix.a: $(CrossDepend) libcov-posix.c
	cc -c $(CCFLAGS) libcov-posix.c
	# Put the object produced above into the library
	ar -r $@ libcov-posix.obj

#-----------------------------------------------------------------------
# User Defined
../lib/libcov-user.lib: $(CrossDepend) libcov-user.c
	cc -c $(CCFLAGS) libcov-user.c
	# Put the object produced above into the library
	ar -r $@ libcov-user.obj
