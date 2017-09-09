# $Id: Makefile,v 1.2 2002-10-02 16:32:25 fmw Exp $

!include <win32.mak>

proj = starter
objs = starter.obj
libs = user32.lib
cflags = /nologo
lflags = /nologo

all: $(proj).exe

.cpp.obj:
	$(cc) $(cflags) /c $<

$(proj).exe: $(objs) Makefile
	$(link) $(lflags) $(objs) $(libs) -out:$(proj).exe

clean :
	-del *.obj $(proj).exe *~ *.ilk *.pdb
