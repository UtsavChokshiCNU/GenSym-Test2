#
# Unix make file to make nsample which reads any of 4 font technologies:
#
#

# compiler options
options = -w -c 

# linker options
link_options =

#sdef = -DAPOLLO -DSPEEDO_CODE=1 -DINCL_KEYS=1 -DSHORT_LISTS=0 -DINCL_BLACK=1 \
#		-DINCL_2D=1 -DINCL_OUTLINE=1 -DINCL_SCREEN=1 -DINCL_WHITE=1 \
#		-DPROTOS_AVAIL=0 -DINCL_PFB=1 -DBASELINE_IMPROVE=1 -DHAVE_MSL2INDEX
sdef =  -DSPEEDO_CODE=1 -DINCL_KEYS=1 -DSHORT_LISTS=0 -DINCL_BLACK=1 \
		-DINCL_2D=1 -DINCL_OUTLINE=1 -DINCL_SCREEN=1 -DINCL_WHITE=1 \
		-DPROTOS_AVAIL=0 -DINCL_PFB=1 -DBASELINE_IMPROVE=1 -DHAVE_MSL2INDEX


# NOTE: if you change back to sdefs, do it globally [in this file]; however,
# when you do that, mhddemo will no longer compile; it is missing some definitions,
# which prevents linking. -mhd

mhddemodefs =  -DSPEEDO_CODE=1 -DINCL_KEYS=1 -DSHORT_LISTS=0 -DINCL_BLACK=1 \
		-DINCL_2D=1 -DINCL_OUTLINE=0 -DINCL_SCREEN=1 -DINCL_WHITE=0 \
		-DPROTOS_AVAIL=0 -DINCL_PFB=1 -DBASELINE_IMPROVE=1 -DHAVE_MSL2INDEX

# source directories
# we use these directories for the development environment setup:
#sd = //ninja/archive/src/speedo
#pcl_dir = //ninja/archive/src/pcl5/hpreader
#type1_dir = //ninja/archive/src/type1
#tt_dir = //ninja/archive/src/true_type
#fit_dir = //ninja/archive/src/pcl5/fit

# you should use these directories for the delivery diskette setup:
sd = ../speedo
pcl_dir = ../pcl5
type1_dir = ../type1
tt_dir = ../tt
fit_dir = ../fitutil

#
Math_Lib = -lm
#

# list of object modules 

4demo_objs = 4demo.o msl.o frontend.o cmt.o cmtglob.o msst.o msstglob.o
mhddemo_objs = mhddemo.o msl.o frontend.o cmt.o cmtglob.o msst.o msstglob.o
tt_objs = tt_iface.o tt_specs.o fontscal.o fsglue.o fnt.o sfntd.o mapstrng.o newscan.o fixed_pt.o
type1_objs = tr_names.o tr_ldfnt.o tr_mkchr.o tr_trans.o
speedo_objs = reset.o do_char.o do_trns.o set_spcs.o set_trns.o set_keys.o
hp_objs = hpfnt1.o hpfnt2.o load_pcl.o
out_objs = out_blk.o out_util.o out_outl.o out_scrn.o out_bl2d.o out_wht.o

inc = -I$(sd) -I$(pcl_dir) -I$(type1_dir) -I$(tt_dir) -I$(fit_dir) -I.

all: 4demo



# Misc. dependencies
$(tt_dir)/sc.h : $(tt_dir)/sfnt.h
$(tt_dir)/sfnt.h : $(tt_dir)/sfntenum.h

# Type1
tr_names.o: $(type1_dir)/tr_names.c \
		$(sd)/spdo_prv.h  \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		$(type1_dir)/type1.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(type1_dir)/tr_names.c

tr_ldfnt.o: $(type1_dir)/tr_ldfnt.c\
		$(sd)/spdo_prv.h  \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		$(type1_dir)/stdef.h \
		$(type1_dir)/type1.h \
		$(type1_dir)/fnt_a.h\
		$(type1_dir)/errcodes.h \
		$(type1_dir)/tr_fdata.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(type1_dir)/tr_ldfnt.c

tr_mkchr.o:$(type1_dir)/tr_mkchr.c\
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		$(type1_dir)/type1.h \
		$(type1_dir)/fnt_a.h \
		$(type1_dir)/tr_fdata.h  fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(type1_dir)/tr_mkchr.c

tr_trans.o: $(type1_dir)/tr_trans.c\
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		$(type1_dir)/stdef.h \
		$(type1_dir)/type1.h \
		$(type1_dir)/fnt_a.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(type1_dir)/tr_trans.c

# Out_??? modules 
out_util.o: $(sd)/out_util.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/out_util.c

out_blk.o:  $(sd)/out_blk.c  \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/out_blk.c

out_wht.o:  $(sd)/out_wht.c  \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/out_wht.c

out_outl.o:  $(sd)/out_outl.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/out_outl.c

out_scrn.o:  $(sd)/out_scrn.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/out_scrn.c

out_bl2d.o:  $(sd)/out_bl2d.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h  \
		$(sd)/useropt.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/out_bl2d.c

# Truetype
tt_iface.o: $(tt_dir)/tt_iface.c\
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fscdefs.h \
		$(tt_dir)/fontscal.h \
		$(tt_dir)/sfnt.h \
		$(tt_dir)/fserror.h\
		$(tt_dir)/truetype.h  fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/tt_iface.c

tt_specs.o: $(tt_dir)/tt_specs.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fscdefs.h \
		$(tt_dir)/fontscal.h \
		$(tt_dir)/truetype.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/tt_specs.c

fontscal.o: $(tt_dir)/fontscal.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fserror.h \
		$(tt_dir)/fscdefs.h  \
		$(tt_dir)/fontmath.h \
		$(tt_dir)/sfnt.h \
		$(tt_dir)/sc.h \
      		$(tt_dir)/fnt.h \
		$(tt_dir)/fontscal.h \
		$(tt_dir)/fsglue.h \
		$(tt_dir)/privsfnt.h \
		$(tt_dir)/privfosc.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/fontscal.c

fsglue.o: $(tt_dir)/fsglue.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fserror.h \
		$(tt_dir)/fscdefs.h \
		$(tt_dir)/fontmath.h \
		$(tt_dir)/sfnt.h \
		$(tt_dir)/sc.h \
		$(tt_dir)/fnt.h \
		$(tt_dir)/fontscal.h \
		$(tt_dir)/fsglue.h \
		$(tt_dir)/privsfnt.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/fsglue.c


fnt.o: $(tt_dir)/fnt.c \
	$(sd)/spdo_prv.h \
	$(sd)/speedo.h \
	$(sd)/useropt.h \
	$(tt_dir)/fscdefs.h \
	$(tt_dir)/fontmath.h \
	$(tt_dir)/sc.h \
	$(tt_dir)/fnt.h \
	$(tt_dir)/fserror.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/fnt.c

sfntd.o: $(tt_dir)/sfntd.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fserror.h \
		$(tt_dir)/fscdefs.h \
		$(tt_dir)/fontmath.h \
		$(tt_dir)/sfnt.h \
		$(tt_dir)/fnt.h \
		$(tt_dir)/sc.h \
		$(tt_dir)/fontscal.h \
		$(tt_dir)/fsglue.h \
		$(tt_dir)/privsfnt.h \
		$(tt_dir)/mapstrng.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/sfntd.c

			

mapstrng.o: $(tt_dir)/mapstrng.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fscdefs.h \
		$(tt_dir)/mapstrng.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/mapstrng.c

newscan.o: $(tt_dir)/newscan.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fscdefs.h \
		$(tt_dir)/fontscal.h  fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/newscan.c

fixed_pt.o: $(tt_dir)/fixed_pt.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(tt_dir)/fixed.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(tt_dir)/fixed_pt.c


# Speedo

reset.o: $(sd)/reset.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(sd)/keys.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/reset.c

do_char.o:	$(sd)/do_char.c \
			$(sd)/spdo_prv.h \
			$(sd)/speedo.h \
			$(sd)/useropt.h \
			fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/do_char.c

do_trns.o:	$(sd)/do_trns.c \
			$(sd)/spdo_prv.h \
			$(sd)/speedo.h \
			$(sd)/useropt.h \
			fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/do_trns.c

set_spcs.o: $(sd)/set_spcs.c \
			$(sd)/spdo_prv.h \
			$(sd)/speedo.h \
			$(sd)/useropt.h \
			fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/set_spcs.c

set_trns.o: $(sd)/set_trns.c \
			$(sd)/spdo_prv.h \
			$(sd)/speedo.h \
			$(sd)/useropt.h \
			fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/set_trns.c

set_keys.o: $(sd)/set_keys.c \
			$(type1_dir)/stdef.h \
			$(sd)/speedo.h \
			$(sd)/useropt.h \
			fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(sd)/set_keys.c

# HP modules

hpfnt1.o: $(pcl_dir)/hpfnt1.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(pcl_dir)/hp_readr.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(pcl_dir)/hpfnt1.c

hpfnt2.o: $(pcl_dir)/hpfnt2.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(pcl_dir)/hp_readr.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) $(pcl_dir)/hpfnt2.c

load_pcl.o: load_pcl.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(pcl_dir)/hp_readr.h\
		pcl5fnt.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) load_pcl.c

# main modules
4demo.o: 4demo.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(type1_dir)/stdef.h \
		$(type1_dir)/type1.h \
		$(type1_dir)/fnt_a.h \
		$(type1_dir)/tr_fdata.h \
		$(type1_dir)/errcodes.h \
		$(pcl_dir)/hp_readr.h \
		ufe.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) 4demo.c

# mhddemo (MHD@GENSYM)
mhddemo.o: mhddemo.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		$(type1_dir)/stdef.h \
		$(type1_dir)/type1.h \
		$(type1_dir)/fnt_a.h \
		$(type1_dir)/tr_fdata.h \
		$(type1_dir)/errcodes.h \
		$(pcl_dir)/hp_readr.h \
		ufe.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) mhddemo.c

msl.o: msl.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		ufe.h \
		$(type1_dir)/type1.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) msl.c

frontend.o: frontend.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		ufe.h $(type1_dir)/type1.h fino.h
	cc  $(mhddemodefs) $(inc) $(options) frontend.c

cmt.o: cmt.c $(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		ufe.h \
		$(type1_dir)/type1.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) cmt.c

cmtglob.o: cmtglob.c $(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		ufe.h \
		$(type1_dir)/type1.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) cmtglob.c

msst.o: msst.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		ufe.h \
		$(type1_dir)/type1.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) msst.c

msstglob.o: msstglob.c \
		$(sd)/spdo_prv.h \
		$(sd)/speedo.h \
		$(sd)/useropt.h \
		ufe.h \
		$(type1_dir)/type1.h \
		fino.h
	cc  $(mhddemodefs) $(inc) $(options) msstglob.c


# EXE's
4demo:  $(4demo_objs) $(tt_objs) $(type1_objs) $(out_objs) $(speedo_objs) $(hp_objs)
	cc -o 4demo $(link_options) $(4demo_objs) $(tt_objs) $(type1_objs) $(out_objs) $(speedo_objs) $(hp_objs) $(Math_Lib)


mhddemo:  $(mhddemo_objs) $(tt_objs) $(type1_objs) $(out_objs) $(speedo_objs) $(hp_objs)
	cc -o mhddemo $(link_options) $(mhddemo_objs) $(tt_objs) $(type1_objs) $(out_objs) $(speedo_objs) $(hp_objs) $(Math_Lib)

# other targets

clean:
	rm *.o
