!include <win32.mak>

deplibs = $(DSTBOX)\ext\o\libcprim.lib $(DSTBOX)\fnt\o\libfnt.lib $(DSTBOX)\jpeg\o\libjpeg.lib $(DSTBOX)\xml\o\liblsxml.lib
libs = comctl32.lib crypt32.lib shell32.lib version.lib rpcrt4.lib Activeds.lib ADSIid.lib ole32.lib $(deplibs)
libxml2_a = $(SRCBOX)\specific\intelnt\libxml2_a.lib
all: g2libs.dll twlibs.dll gsilibs.dll

g2libs.dll: $(deplibs) g2xprts.def g2callbacks.obj
    $(link) $(linkdebug)  /nodefaultlib:libc.lib /nodefaultlib:libcmtd.lib -entry:DllMain $(dlllflags) $(guilibsdll) $(libs) $(libxml2_a) g2callbacks.obj -def:g2xprts.def -out:g2libs.dll

twlibs.dll: $(deplibs) twxprts.def twcallbacks.obj
    $(link) $(linkdebug)  /nodefaultlib:libc.lib /nodefaultlib:libcmtd.lib -entry:DllMain $(dlllflags) $(guilibsdll) $(libs) $(libxml2_a) twcallbacks.obj -def:twxprts.def -out:twlibs.dll

gsilibs.dll: $(deplibs) gsixprts.def gsicallbacks.obj
    $(link) $(linkdebug)  /nodefaultlib:libc.lib /nodefaultlib:libcmtd.lib -entry:DllMain $(dlllflags) $(guilibsdll) $(libs) $(libxml2_a) gsicallbacks.obj -def:gsixprts.def -out:gsilibs.dll

.c.obj: 
    $(cc) $(cdebug) $(cflags) $(cvarsmt) $<

clean :
    -del *.dll *.lib *.pdb *.exp *.obj

