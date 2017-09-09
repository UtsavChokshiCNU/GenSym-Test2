# -*- Mode: Makefile -*-

# $Id: makefile,v 1.13 2003-09-02 19:50:05 yduj Exp $

# To use this makefile, execute the mybuild command.
# Unless you know what you're doing, DO NOT RUN THIS DIRECTLY USING make.

SHELL		= /bin/sh
CC_FLAGS	= $(QUIRKS) -fno-stack-protector -O
LDFLAGS		=
DEFS 		=
LIBS		=

DEPEND		= makedepend
DEPEND_FLAGS	=
DEPEND_DEFINES	=

INSTALL		= install
INSTALL_FLAGS	= -c
INSTALL_DIR	= 

INCLUDES	=

all: dirs createbundle createkey decode-key geninst obfuscator serialize-family-file unbundle

.c.o:
	cd $(PLATFORM) ; $(CC) -c $(CC_FLAGS) $(INCLUDES) $(DEFS) ../$<

clean:
	sh -c 'if test -d $(PLATFORM) ; then rm -f *.o && cd $(PLATFORM) && rm -f *.o a.out core $(EXE) ; fi'

distclean: clean
	rm -f *~ "#"*

install: $(EXE)
	$(INSTALL) $(INSTALL_FLAGS) $(EXE) $(INSTALL_DIR)

depend:
	$(DEPEND) -s '# DO NOT DELETE: updated by make depend'               \
	$(DEPEND_FLAGS) -- $(INCLUDES) $(DEFS) $(DEPEND_DEFINES) $(CC_FLAGS) \
	-- $(SRCS)

TAGS: tags

tags:
	find . -name '*.[chly]' -print | xargs etags -a

dirs:
	sh -c 'if test ! -d $(PLATFORM) ; then mkdir $(PLATFORM) ; fi'

createbundle: createbundle.o family-file-reader.o gsm-private.o gsm-public.o random.o tag-value-parser.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?

createkey: createkey.o key-public.o key-private.o random.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?

decode-key: decode-key.o key-public.o key-private.o random.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?

geninst: geninst.o family-file-reader.o g2pwaux.o gsm-public.o key-public.o md5_all.o random.o spawn.o tag-value-parser.o obfuscate.o postinstall.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?

obfuscator: obfuscator.o obfuscate.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?

run-as-root: run-as-root.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?

serialize-family-file: serialize-family-file.o family-file-reader.o tag-value-parser.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?

unbundle: unbundle.o family-file-reader.o gsm-private.o gsm-public.o random.o tag-value-parser.o
	cd $(PLATFORM) ; $(CC) $(LDFLAGS) -o $@ $?
