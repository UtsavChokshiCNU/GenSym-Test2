########TRUETYPE MAKEFILE:################################
#
# Unix make file to make ttsample which reads TrueType
# fonts:
#
# $Log: not supported by cvs2svn $
# Revision 1.2  1993/04/19 15:28:28  mpc
# Changed //ninja/archive dirs to local references.
# Changed ref of useropt.h to ../speedo/useropt.h, per bitstream.
# Removed compile flag -DAPOLLO=1, per bitstream.
#
# Revision 1.1.1.1  1993/04/15  20:14:38  mhd
# Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
#
#  Revision 6.44  93/03/15  13:23:27  roberte
#  Release
#  
#  Revision 1.3  93/03/04  11:54:55  roberte
#  Added define of Math_Lib and used throughout.  Replaced "ld" with "cc"
#  Replaced $* macros with pathnames macros preceeding with actual file root name.
#  
#  Revision 1.2  93/02/08  15:26:19  roberte
#  Removed sc.o from tt_objs.
#  
#  Revision 1.1  93/02/02  14:43:05  roberte
#  Initial revision
#  
#

debug = -g
#debug = -O

# we use these directories for development:
#spd_dir = //ninja/archive/src/speedo
#4demo_dir = //ninja/archive/src/4in1
# you should use these directories to matchi delicery diskettes:
spd_dir = ../speedo
4demo_dir = ../4demo

#defines = -DSHORT_LISTS=0 -DAPOLLO -DPROC_PCL=0 -DPROC_TYPE1=0 -w
defines = -DSHORT_LISTS=0 -DPROC_PCL=0 -DPROC_TYPE1=0 -w

includes = -I$(spd_dir) -I$(4demo_dir) -I.
Math_Lib = -lm

core_objs =  out_blk.o out_bl2d.o out_scrn.o out_outl.o \
			 out_util.o
tt_objs = tt_iface.o tt_specs.o fontscal.o fsglue.o \
			fnt.o sfntd.o mapstrng.o newscan.o \
			fixed_pt.o
spd_objs = do_trns.o do_char.o reset.o set_keys.o \
	 set_trns.o set_spcs.o

ttsample : truetype.o $(tt_objs) $(core_objs)
	cc -o $@ truetype.o $(tt_objs) $(core_objs) $(Math_Lib)

ttspeedo: ttspeedo.o $(tt_objs) $(core_objs) $(spd_objs)
	 cc -o $@ ttspeedo.o $(tt_objs) $(core_objs) $(spd_objs) $(Math_Lib)

stackchk : stackchk.o $(tt_objs)
	cc -o $@ stackchk.o  $(tt_objs) $(Math_Lib)

timetest : timetest.o $(tt_objs)
	cc -o $@ timetest.o  $(tt_objs) $(Math_Lib)

$(spd_dir)/speedo.h: $(spd_dir)/useropt.h
$(spd_dir)/spdo_prv.h : $(spd_dir)/speedo.h

truetype.o: truetype.c $(spd_dir)/useropt.h \
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        fscdefs.h fontscal.h sfnt.h fserror.h \
        truetype.h
	cc $(debug) $(defines) $(includes) -c $*.c

sc.o: sc.c $(spd_dir)/useropt.h $(4demo_dir)/fino.h\
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        fscdefs.h sc.h fserror.h
	cc $(debug) $(defines) $(includes) -c $*.c

tt_iface.o: tt_iface.c $(spd_dir)/useropt.h $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        $(4demo_dir)/fino.h fscdefs.h fontscal.h \
        sfnt.h fserror.h truetype.h
	cc $(debug) $(defines) $(includes) -c $*.c

tt_specs.o: tt_specs.c $(spd_dir)/useropt.h $(spd_dir)/spdo_prv.h \
        	$(spd_dir)/speedo.h \
            $(4demo_dir)/fino.h fscdefs.h \
           fontscal.h truetype.h
	cc $(debug) $(defines) $(includes) -c $*.c

fontscal.o: fontscal.c $(spd_dir)/useropt.h $(4demo_dir)/fino.h \
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        fserror.h fscdefs.h fontmath.h sfnt.h sc.h \
        fnt.h fontscal.h fsglue.h privsfnt.h privfosc.h
	cc $(debug) $(defines) $(includes) -c $*.c

fsglue.o: fsglue.c $(spd_dir)/useropt.h $(4demo_dir)/fino.h \
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        fserror.h fscdefs.h fontmath.h sfnt.h sc.h \
        fnt.h fontscal.h fsglue.h privsfnt.h
	cc $(debug) $(defines) $(includes) -c $*.c

fnt.o: fnt.c $(spd_dir)/useropt.h $(4demo_dir)/fino.h fscdefs.h \
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        fontmath.h sc.h fnt.h fserror.h
	cc $(debug) $(defines) $(includes) -c $*.c

sfntd.o: sfntd.c $(spd_dir)/useropt.h $(4demo_dir)/fino.h \
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        fserror.h fscdefs.h fontmath.h sfnt.h fnt.h \
        sc.h fontscal.h fsglue.h privsfnt.h mapstrng.h
	cc $(debug) $(defines) $(includes) -c $*.c

mapstrng.o: mapstrng.c $(spd_dir)/useropt.h $(4demo_dir)/fino.h \
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h \
        fscdefs.h mapstrng.h
	cc $(debug) $(defines) $(includes) -c $*.c

newscan.o: newscan.c $(spd_dir)/useropt.h $(4demo_dir)/fino.h \
        $(spd_dir)/speedo.h \
        $(spd_dir)/spdo_prv.h fscdefs.h fontscal.h
	cc $(debug) $(defines) $(includes) -c $*.c

fixed_pt.o: fixed_pt.c $(4demo_dir)/fino.h fixed.h \
        $(spd_dir)/spdo_prv.h \
        $(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) -c $*.c

out_blk.o: $(spd_dir)/out_blk.c $(spd_dir)/spdo_prv.h \
        		$(spd_dir)/speedo.h \
                $(4demo_dir)/fino.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/out_blk.c

out_bl2d.o: $(spd_dir)/out_bl2d.c $(spd_dir)/spdo_prv.h \
        		$(spd_dir)/speedo.h \
                $(4demo_dir)/fino.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/out_bl2d.c

out_scrn.o: $(spd_dir)/out_scrn.c $(spd_dir)/spdo_prv.h \
        		$(spd_dir)/speedo.h \
                $(4demo_dir)/fino.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/out_scrn.c

out_outl.o: $(spd_dir)/out_outl.c $(spd_dir)/spdo_prv.h \
        		$(spd_dir)/speedo.h \
                $(4demo_dir)/fino.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/out_outl.c

out_util.o: $(spd_dir)/out_util.c $(spd_dir)/spdo_prv.h \
        		$(spd_dir)/speedo.h \
                $(4demo_dir)/fino.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/out_util.c

do_char.o: $(spd_dir)/do_char.c \
       			$(spd_dir)/spdo_prv.h \
       			$(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/do_char.c

do_trns.o: $(spd_dir)/do_trns.c \
       			$(spd_dir)/spdo_prv.h \
       			$(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/do_trns.c

reset.o:   $(spd_dir)/reset.c \
       			$(spd_dir)/spdo_prv.h \
       			$(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/reset.c

set_keys.o:$(spd_dir)/set_keys.c \
       			$(spd_dir)/spdo_prv.h \
       			$(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) -I. -c $(spd_dir)/set_keys.c

set_trns.o: $(spd_dir)/set_trns.c \
       			$(spd_dir)/spdo_prv.h \
       			$(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/set_trns.c

set_spcs.o:  $(spd_dir)/set_spcs.c \
       			$(spd_dir)/spdo_prv.h \
       			$(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) -c $(spd_dir)/set_spcs.c

ttspeedo.o: ttspeedo.c \
       			$(spd_dir)/speedo.h
	cc $(debug) $(defines) $(includes) $*.c

clean:
	rm *.o

