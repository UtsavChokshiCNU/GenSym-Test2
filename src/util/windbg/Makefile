# -*- Mode: makefile -*-

# Default install location for windbg
!ifndef DBGTOOLS
DBGTOOLS = C:\Program Files\Debugging Tools for Windows
!endif

INCLUDE = $(SRCBOX)\rtl\c;$(DBGTOOLS)\sdk\inc;$(INCLUDE)
LIB = $(DBGTOOLS)\sdk\lib\i64;$(LIB)

LINK = link

CFLAGS = /nologo /MD /W3 /Oxs /Zi /D WIN32 /D _WINDOWS /D _MBCS /D _USRDLL /DLL
LFLAGS = /nologo /debug /DLL

TARGET = lisp.dll
INSTALL = $(DBGTOOLS)\winext\$(TARGET)
SRC = lisp.cpp
OBJS = lisp.obj
LIBS = dbgeng.lib user32.lib

all:	$(TARGET) install

$(TARGET): $(OBJS)
	$(LINK) $(LFLAGS) $(OBJS) $(LIBS)

$(INSTALL): $(TARGET)
	copy /Y $(TARGET) "$(INSTALL)"

install: $(INSTALL)

clean :
	-del $(TARGET) $(OBJS) *.exp *.pdb *.ilk *.lib
