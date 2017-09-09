divert(11) Start M4 Comment

This is passed to to M4 on a command line like so:

  /usr/5bin/m4 -Dflavor=opt  makefile.m4 > $SPIN_ID/gw/opt/makefile
  /usr/5bin/m4 -Dflavor=o    makefile.m4 > $SPIN_ID/gw/o/makefile
  /usr/5bin/m4 -Dflavor=o-pg makefile.m4 > $SPIN_ID/gw/o-pg/makefile

To generate one of the three variation on makefiles.

This does not currently utilize helpers, to enable helpers
do add -Dhelpers=yes to the command line.

Next we have the definitions.

End M4 Comment divert(0)

define(compile_c_and_h_file,`
$1.o : $($2)/$1.c $(RTHFILES) $($2)/$1.h
	@- if [ -f $1.o ] ; then rm -f $1.o ; fi
	ifelse(helpers(),yes,@ $(UTILDIR)/help-please $(MFDIR)) gcc -c $(CC_FLAGS) -I$(EXCDIR) -I$(RTHDIR) $($2)/$1.c')

define(compile_c_file,`
$1.o : $($2)/$1.c $(RTHFILES)
	@- if [ -f $1.o ] ; then rm -f $1.o ; fi
	ifelse(helpers(),yes,@ $(UTILDIR)/help-please $(MFDIR)) gcc -c $(CC_FLAGS) -I$(EXCDIR) -I$(RTHDIR) $($2)/$1.c')

define(insert_into_libgw,`
libgw.a :: $1.o
	ar rv libgw.a $1.o
	@-rm -f touch-libgw.a')

#### Boilerplate Defines.
SHELL = /bin/sh
PRODUCT = gw
ODIR = flavor()
AUTODIR = /bt/$(SPIN_ID)/auto
CDIR = /bt/$(SPIN_ID)/$(PRODUCT)/c
EXCDIR = /bt/$(SPIN_ID)/ext/c
EXTDIR = /bt/$(SPIN_ID)/ext/$(ODIR)
# MFDIR = /bt/$(SPIN_ID)/$(PRODUCT)/$(ODIR)
RTHDIR = /bt/$(SPIN_ID)/rtl/c
RTLDIR = /bt/$(SPIN_ID)/rtl/$(ODIR)
UTILDIR = /bt/$(SPIN_ID)/util
KBDIR = /bt/$(SPIN_ID)/kbs
MFPROMDIR = /bt/$(SPIN_ID)/util/promote/lspgsi
PROMDIR = /bt/$(SPIN_ID)/util/promote
TAPEDST = /bt/$(SPIN_ID)/$(PRODUCT)/tape
TESTDST = /bt/$(SPIN_ID)/$(PRODUCT)/test
PLIST = /bt/$(SPIN_ID)/$(PRODUCT)/tape/parts.list

RTHFILES = $(RTHDIR)/c-ifuns.h $(RTHDIR)/c-sdefs.h \
  $(RTHDIR)/config.h $(RTHDIR)/core.h $(RTHDIR)/ffi.h $(RTHDIR)/gensym.h \
  $(RTHDIR)/initvars.h $(RTHDIR)/inline.h $(RTHDIR)/instance.h \
  $(RTHDIR)/kernel.h $(RTHDIR)/lisplib.h $(RTHDIR)/longname.h \
  $(RTHDIR)/object.h $(RTHDIR)/smcompat.h $(RTHDIR)/specific.h \
  $(RTHDIR)/svarargs.h $(RTHDIR)/uconfig.h $(RTHDIR)/values.h


#### Custom Defines

CC_FLAGS = ifelse(flavor(),opt,-O) ifelse(flavor(),o,-g) -DGSI_TRANS -w
LINK_FLAGS = ifelse(flavor(),opt,-s) 
LIBS = /gensym/ut/gsi-40r1/librtl.a /gensym/ut/gsi-40r1/libtcp.a

## Stand on the runtime library shipped in 40r1, but we patch this.
SRC_LIBGSI = /gensym/ut/gsi-40r1/libgsi.a

# LIBRTL = /gensym/ut/gsi-40r1/librtl.a 

GWOBJS = \
	gsiannex.o \
	symtab.o \
	userfuns.o \
	userinit.o \
	usersyms.o \
	load.o \
	btstrp.o \
	systm.o \
	delta.o \
	gspts.o \
	loop.o \
	lspfxs.o \
	glbscs.o \
	osfrgn.o \
	basics.o \
	ostme.o \
	os-set.o \
	os-mem.o \
	prmtvs.o \
	chars.o \
	utlts0.o \
	utlts1.o \
	utlts2.o \
	utlts3.o \
	osrrr.o \
	launch.o \
	ntwrks.o \
	int1.o \
	int2.o \
	int3.o \
	int4.o \
	gscmn.o \
	rpcmn1.o \
	rpcmn2.o \
	gsi.o \
	gsrpc1.o \
	gsrpc2.o \
	tran.o \
	gw_main.o \
	pthnms.o flprse.o strms.o \
	bridge.o buffer.o htmlgn.o server.o thread.o wbgsi.o web.o

#### End of DEFINES

all : _mfenter gsiweb _mfexit

_mfenter : 
	@- $(UTILDIR)/errsweep -init

_mfexit : 
	@- $(UTILDIR)/errsweep -finish


##### End of standard Header ######

##### Linking Executables


gsiweb : $(LIBS) $(GWOBJS) libgw.a touch-libgw.a
	ifelse(helpers(),yes,@ $(UTILDIR)/wait-for-helpers,@-echo -n)
	@- if [ -f gsiweb ] ; then rm -f gsiweb ; fi
	gcc -o gsiweb $(LINK_FLAGS) $(GWOBJS)\
          libgw.a $(LIBS) -lm -lc



#### Build a library from all the object modules.
#### This is sort of libgsi+webgsi

touch-libgw.a : libgw.a
	ranlib libgw.a
	touch touch-libgw.a

insert_into_libgw(gsiannex)
insert_into_libgw(symtab)
insert_into_libgw(userfuns)
insert_into_libgw(userinit)
insert_into_libgw(usersyms)
insert_into_libgw(load)
insert_into_libgw(btstrp)
insert_into_libgw(systm)
insert_into_libgw(delta)
insert_into_libgw(gspts)
insert_into_libgw(loop)
insert_into_libgw(lspfxs)
insert_into_libgw(glbscs)
insert_into_libgw(osfrgn)
insert_into_libgw(basics)
insert_into_libgw(ostme)
insert_into_libgw(os-set)
insert_into_libgw(os-mem)
insert_into_libgw(prmtvs)
insert_into_libgw(chars)
insert_into_libgw(utlts0)
insert_into_libgw(utlts1)
insert_into_libgw(utlts2)
insert_into_libgw(utlts3)
insert_into_libgw(osrrr)
insert_into_libgw(launch)
insert_into_libgw(ntwrks)
insert_into_libgw(int1)
insert_into_libgw(int2)
insert_into_libgw(int3)
insert_into_libgw(int4)
insert_into_libgw(gscmn)
insert_into_libgw(rpcmn1)
insert_into_libgw(rpcmn2)
insert_into_libgw(gsi)
insert_into_libgw(gsrpc1)
insert_into_libgw(gsrpc2)
insert_into_libgw(tran)
insert_into_libgw(gw_main)
insert_into_libgw(gw_tcp)
insert_into_libgw(lgsi_support)
insert_into_libgw(pthnms) 
insert_into_libgw(flprse) 
insert_into_libgw(strms)
insert_into_libgw(bridge)
insert_into_libgw(buffer)
insert_into_libgw(htmlgn)
insert_into_libgw(server)
insert_into_libgw(thread)
insert_into_libgw(wbgsi)
insert_into_libgw(web)

#### Object Modules

#### Make the object modules


compile_c_file(symtab,CDIR)
compile_c_and_h_file(userfuns,CDIR)
compile_c_file(userinit,CDIR)
compile_c_file(usersyms,CDIR)
compile_c_and_h_file(load,CDIR)
compile_c_and_h_file(btstrp,CDIR)
compile_c_and_h_file(systm,CDIR)
compile_c_and_h_file(delta,CDIR)
compile_c_and_h_file(gspts,CDIR)
compile_c_and_h_file(loop,CDIR)
compile_c_and_h_file(lspfxs,CDIR)
compile_c_and_h_file(glbscs,CDIR)
compile_c_and_h_file(osfrgn,CDIR)
compile_c_and_h_file(basics,CDIR)
compile_c_and_h_file(ostme,CDIR)
compile_c_and_h_file(os-set,CDIR)
compile_c_and_h_file(os-mem,CDIR)
compile_c_and_h_file(prmtvs,CDIR)
compile_c_and_h_file(chars,CDIR)
compile_c_and_h_file(utlts0,CDIR)
compile_c_and_h_file(utlts1,CDIR)
compile_c_and_h_file(utlts2,CDIR)
compile_c_and_h_file(utlts3,CDIR)
compile_c_and_h_file(osrrr,CDIR)
compile_c_and_h_file(launch,CDIR)
compile_c_and_h_file(ntwrks,CDIR)
compile_c_and_h_file(int1,CDIR)
compile_c_and_h_file(int2,CDIR)
compile_c_and_h_file(int3,CDIR)
compile_c_and_h_file(int4,CDIR)
compile_c_and_h_file(gscmn,CDIR)
compile_c_and_h_file(rpcmn1,CDIR)
compile_c_and_h_file(rpcmn2,CDIR)
compile_c_and_h_file(gsi,CDIR)
compile_c_and_h_file(gsrpc1,CDIR)
compile_c_and_h_file(gsrpc2,CDIR)
compile_c_and_h_file(tran,CDIR)
compile_c_and_h_file(pthnms,CDIR) 
compile_c_and_h_file(flprse,CDIR) 
compile_c_and_h_file(strms,CDIR)
compile_c_and_h_file(bridge,CDIR)
compile_c_and_h_file(buffer,CDIR)
compile_c_and_h_file(htmlgn,CDIR)
compile_c_and_h_file(server,CDIR)
compile_c_and_h_file(thread,CDIR)
compile_c_and_h_file(wbgsi,CDIR)
compile_c_and_h_file(web,CDIR)

compile_c_file(gsiannex,CDIR)
compile_c_and_h_file(lgsi_support,CDIR)
compile_c_and_h_file(gw_main,CDIR)
compile_c_and_h_file(gw_tcp,CDIR)
