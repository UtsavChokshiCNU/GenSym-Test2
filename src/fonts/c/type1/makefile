############### TYPE1 MAKEFILE:###################
#
# Unix make file to make nsample which reads Type 1 fonts:
#
#
# $Log: not supported by cvs2svn $
# Revision 1.3  1993/04/20 15:42:39  mhd
# Makefile in the type1 directory contains backslash (\) line continuations,
# which the make processor cannot handle.  We have worked around these by removing the
# backslashes and moving the continuation lines up.  Lines are
#
# 	#type1_defines = -DRESTRICTED_ENVIRON -DINCL_PFB -DRESTRICTED_STATS
# 	#type1_defines = -DINCL_PFB -DEDGE_ALIGN=1 -DNAME_STRUCT -DPROTOTYPE
#
# Revision 1.2  1993/04/19  15:24:21  mpc
# Changed //ninja/archive dirs to relative reference.
# Removed reference to fi_proto.h, it no longer exists, per bitstream.
#
# Revision 1.1.1.1  1993/04/15  20:14:28  mhd
# Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
#
#  Revision 28.24  93/03/15  13:12:44  roberte
#  Release
#  
#  Revision 1.4  93/02/23  12:20:16  roberte
#  Added define of Math_Lib, changed link statement to call cc rather than ld. Added Math_Lib to link list.
#  Removed -g flag from debug_defines. 
#  
#  Revision 1.3  93/02/17  11:39:11  roberte
#  Removed TAB from end of line following BACKSLASH in out_bl2d.o build command.
#  
#  Revision 1.2  93/02/11  14:27:07  roberte
#  Removed -Tbsd4.2 "unix_define" command line flag.
#  
#  Revision 1.1  93/02/02  14:40:32  roberte
#  Initial revision
#  
# Revision 28.15  93/01/21  13:18:30  roberte
# Turned on -g debug option.  Added clean: target to remove * o's.
#
# Revision 28.14  93/01/19  10:37:48  davidw
# *** empty log message ***
#
# Revision 28.13  93/01/14  11:00:47  roberte
# Changed definitions of type1_dir, speedo_dir and 4in1_dir
# to archive path.
# Added include of type1_dir to compiles of all speedo
# modules.
#
# Revision 28.12  93/01/11  13:20:12  roberte
# Moved -D's of PROC_PCL and PROC_TRUETYPE to macro
# speedo_defines.
#
# Revision 28.11  93/01/11  12:10:30  roberte
# Changed command line defines -D options to shut off
#  PROC_PCL and
#  PROC_TRUETYPE.
#
# Revision 28.10  92/12/08  09:39:39  davidw
# *** empty log message ***
#
# Revision 28.9  92/12/02  17:49:30  laurar
# add speedo.h to tr_trans.obj dependency list.
#
# Revision 28.8  92/12/02  15:08:58  laurar
# update dependency list.
#
#  Revision 28.8  92/11/24  13:13:17  laurar
#  add 4in1 as an include directory, so make can find fino.h
#
#  Revision 28.7  92/11/19  15:23:17  weili
#  Release
#
#  Revision 26.4  92/11/16  18:33:42  laurar
#  define UNIX under the unix_defines variable.
#
#  Revision 26.3  92/11/16  12:13:38  laurar
#  Add UNIX define.
#
#  Revision 26.2  92/10/19  17:36:54  laurar
#  change fnt.h to fnt_a.h for nsample dependency.
#
#  Revision 26.1  92/06/26  10:22:01  leeann
#  Release
#
#  Revision 25.1  92/04/06  11:38:44  leeann
#  Release
#
#  Revision 24.1  92/03/23  14:06:11  leeann
#  Release
#
#  Revision 23.2  92/03/23  14:05:07  leeann
#  spell out source file names in "cc" command line
#
#  Revision 23.1  92/01/29  16:57:22  leeann
#  Release
#
#  Revision 22.2  92/01/29  16:54:11  leeann
#  add PROTOTYPE turned on when NAME_STRUCT is turned on
#
#  Revision 22.1  92/01/20  13:28:36  leeann
#  Release
#
#  Revision 21.1  91/10/28  16:40:58  leeann
#  Release
#
#  Revision 20.1  91/10/28  15:24:43  leeann
#  Release
#
#  Revision 19.2  91/10/28  15:24:10  leeann
#  Release
#
#  Revision 19.1  91/10/23  17:27:23  leeann
#  Release
#
#  Revision 18.1  91/10/17  11:36:22  leeann
#  Release
#
#  Revision 17.1  91/06/13  10:40:54  leeann
#  Release
#
#  Revision 16.1  91/06/04  15:31:30  leeann
#  Release
#
#  Revision 15.1  91/05/08  18:04:02  leeann
#  Release
#
#  Revision 14.1  91/05/07  16:25:05  leeann
#  Release
#
#  Revision 13.1  91/04/30  16:59:38  leeann
#  Release
#
#  Revision 12.1  91/04/29  14:50:38  leeann
#  Release
#
#  Revision 11.5  91/04/29  14:27:34  leeann
#  make paths relative to current directory
#
#  Revision 11.3  91/04/10  13:22:41  leeann
#  cleanup
#
#  Revision 11.2  91/04/04  10:53:42  leeann
#  Release
#
#  Revision 11.1  91/04/04  10:53:08  leeann
#  Release
#
#  Revision 10.2  91/04/04  10:51:21  leeann
#  EDGE_ALIGN is an option
#  .'
#
#  Revision 10.1  91/03/14  14:23:50  leeann
#  Release
#
#  Revision 9.1  91/03/14  10:02:24  leeann
#  Release
#
#  Revision 8.3  91/03/13  17:37:33  leeann
#  add RESTRICTED_ENVIRON defines
#
#  Revision 8.2  91/02/12  13:09:02  leeann
#  put in perf_test
#
#  Revision 8.1  91/01/30  18:59:14  leeann
#  Release
#
#  Revision 7.1  91/01/22  14:22:47  leeann
#  Release
#
#  Revision 6.2  91/01/17  17:01:11  joyce
#  *** empty log message ***
#
#  Revision 6.1  91/01/16  10:49:43  leeann
#  Release
#
#  Revision 5.1  90/12/12  17:16:39  leeann
#  Release
#
#  Revision 4.1  90/12/12  14:42:14  leeann
#  Release
#
#  Revision 3.2  90/12/12  14:13:01  leeann
#  remove iface compilation
#
#  Revision 3.1  90/12/06  10:24:51  leeann
#  Release
#
#  Revision 2.1  90/12/03  12:53:30  mark
#  Release
#
#  Revision 1.4  90/11/30  12:49:22  joyce
#  Another name change
#  tr_mk_chr.c to tr_mkchr.c
#  tr_ld_fnt. to tr_ldfnt.c
#  The previous names are too long for the PC
#
#  Revision 1.3  90/11/30  12:16:46  joyce
#  renamed four C files and two header files:
#  1. chr_nmes.c to tr_names.c
#  2. ld_fnt_a.c to tr_ld_fnt.c
#  3. mk_chr_a.c to tr_mk_chr.c
#  4. trans_a.c to tr_trans.c
#  5. fnt_a.h to fnt.h
#  6. ps_qem.h to type1.h
#  This is the makefile that should be used to build
#  the type1 rasterizer. The other makefile, "makefile"
#  contains obsolete file names.
#
#  Revision 1.2  90/11/29  18:03:02  leeann
#  simplify makefile
#
#  Revision 1.1  90/08/13  15:25:07  arg
#  Initial revision
#
#
# we use this directory structure for development:
#speedo_dir = //ninja/archive/src/speedo
#type1_dir = //ninja/archive/src/type1
#4demo_dir = //ninja/archive/src/4in1
# you should use this directory structure to match delivery diskettes:
speedo_dir = ../speedo
type1_dir = ../type1
4demo_dir = ../4demo
#
Math_Lib = -lm
#
speedo_includes = -I$(speedo_dir)
type1_includes = -I$(type1_dir)
4demo_includes = -I$(4demo_dir)
#
speedo_defines = -DINCL_KEYS -USHORT_LISTS -DINCL_BLACK \
	 -DINCL_2D-DINCL_OUTLINE -DINCL_SCREEN -DPROC_PCL=0 \
	 -DPROC_TRUETYPE=0 

unix_defines = -c -DUNIX=1 -w
#
# Optional Configurations (pick 1)
type1_defines =  -DINCL_PFB
#type1_defines = -DINCL_PFB -DEDGE_ALIGN=1 -DNAME_STRUCT -DPROTOTYPE
#type1_defines = -DINCL_PFB -DTIMEIT
#type1_defines = -DINCL_PFB -DRESTRICTED_ENVIRON -DTIMEIT
#type1_defines = -DRESTRICTED_ENVIRON -DINCL_PFB -DRESTRICTED_STATS
#
# Profiler debug
#debug_defines = -g -pg
#
# Debugger option
#debug_defines = -O
debug_defines = 
#
type1_objs = tr_names.o tr_ldfnt.o tr_mkchr.o tr_trans.o
speedo_objs = out_blk.o out_util.o out_outl.o out_scrn.o \
		 out_bl2d.o

nsample_objs = $(speedo_objs) $(type1_objs) nsample.o
perf_objs = $(speedo_objs) $(type1_objs) perf_test.o
#
nsample : ${nsample_objs}
	cc -o $@ ${nsample_objs} ${Math_Lib}
perf_test: ${perf_objs}
	cc -o $@ ${perf_objs}
#profile load
#	cc -pg -o $@ ${nsample_objs}

#
# Header Files
#
$(speedo_dir)/speedo.h: $(speedo_dir)/useropt.h
$(speedo_dir)/spdo_prv.h: $(speedo_dir)/speedo.h
#
#TYPE 1
#
tr_names.o: $(type1_dir)/tr_names.c \
               $(speedo_dir)/spdo_prv.h \
                $(4demo_dir)/fino.h \
                type1.h
	cc $(debug_defines) $(4demo_includes) $(speedo_includes) $(type1_includes) \
		$(speedo_defines) $(type1_defines) $(unix_defines) $(type1_dir)/tr_names.c

tr_ldfnt.o: $(type1_dir)/tr_ldfnt.c \
                $(speedo_dir)/spdo_prv.h \
                $(4demo_dir)/fino.h \
                stdef.h type1.h fnt_a.h \
                errcodes.h tr_fdata.h
	cc $(debug_defines) $(4demo_includes) $(speedo_includes) $(type1_includes) \
		$(speedo_defines) $(type1_defines) $(unix_defines) $(type1_dir)/tr_ldfnt.c


tr_mkchr.o: $(type1_dir)/tr_mkchr.c \
            $(speedo_dir)/spdo_prv.h \
	    $(speedo_dir)/speedo.h\
            $(type1_dir)/type1.h \
            $(type1_dir)/fnt_a.h
	cc $(debug_defines) $(4demo_includes) $(speedo_includes) $(type1_includes) \
		$(speedo_defines) $(type1_defines) $(unix_defines) $(type1_dir)/tr_mkchr.c

tr_trans.o: $(type1_dir)/tr_trans.c  \
                $(speedo_dir)/speedo.h\
                $(4demo_dir)/fino.h \
                type1.h
	cc $(debug_defines) $(4demo_includes) $(speedo_includes) $(type1_includes) \
		$(speedo_defines) $(type1_defines) $(unix_defines) $(type1_dir)/tr_trans.c
#
# SPEEDO
#
out_util.o: $(speedo_dir)/out_util.c \
            $(speedo_dir)/spdo_prv.h \
            $(4demo_dir)/fino.h
	cc  $(4demo_includes) $(speedo_includes) $(type1_includes) $(debug_defines) \
		$(speedo_defines) $(type1_defines) $(unix_defines) $(speedo_dir)/out_util.c

out_blk.o:  $(speedo_dir)/out_blk.c \
            $(speedo_dir)/spdo_prv.h \
            $(4demo_dir)/fino.h
	cc  $(4demo_includes) $(speedo_defines) $(debug_defines) $(unix_defines) \
		$(speedo_includes) $(type1_includes) $(speedo_dir)/out_blk.c

out_outl.o:  $(speedo_dir)/out_outl.c \
            $(speedo_dir)/spdo_prv.h \
            $(4demo_dir)/fino.h
	cc  $(4demo_includes) $(speedo_defines) $(debug_defines) $(unix_defines) \
		$(speedo_includes) $(type1_includes) $(speedo_dir)/out_outl.c

out_scrn.o:  $(speedo_dir)/out_scrn.c \
            $(speedo_dir)/spdo_prv.h \
           $(4demo_dir)/fino.h
	cc  $(4demo_includes) $(speedo_defines) $(debug_defines) $(unix_defines) \
		$(speedo_includes) $(type1_includes) $(speedo_dir)/out_scrn.c

out_bl2d.o:  $(speedo_dir)/out_bl2d.c \
            $(speedo_dir)/spdo_prv.h \
           $(4demo_dir)/fino.h
	cc  $(4demo_includes) $(speedo_defines) $(debug_defines) $(unix_defines) \
		$(speedo_includes) $(type1_includes) $(speedo_dir)/out_bl2d.c
#
#NSAMPLE
#
nsample.o: $(type1_dir)/nsample.c\
	$(speedo_dir)/speedo.h \
	$(speedo_dir)/useropt.h \
        stdef.h type1.h fnt_a.h tr_fdata.h errcodes.h
	cc $(debug_defines) $(speedo_defines) $(unix_defines) $(speedo_includes) \
		$(type1_includes) $(type1_defines) $(type1_dir)/nsample.c

perf_test.o: $(type1_dir)/perf_test.c\
	$(speedo_dir)/spdo_prv.h \
	$(speedo_dir)/speedo.h \
	$(speedo_dir)/useropt.h
	cc $(debug_defines) $(speedo_defines) $(unix_defines) $(speedo_includes) \
		$(type1_includes) $(type1_dir)/$*.c

clean:
	rm *.o
