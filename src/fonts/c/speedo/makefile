################### SPEEDO MAKEFILE:######################
#  Unix make file to make the following applications:
#                  speedo.o
#                  nsample
#                  vfont
#
#  $Log: not supported by cvs2svn $
#  Revision 1.2  1993/04/19 15:31:02  mpc
#  Changed //ninja/archive dirs to local references.
#  Removed compile flag -DAPOLLO=1, per bitstream.
#
# Revision 1.1.1.1  1993/04/15  20:14:17  mhd
# Initial checkin of Version 2.1 of 4-in-1 from Bitstream.  -jra & mpc
#
#  Revision 28.38  93/03/16  10:53:19  roberte
#  Removed "utils_dir" for clarity, replacing with t1_dir (stdef.h).
#  
#  Revision 28.37  93/03/15  13:02:38  roberte
#  Release
#  
#  Revision 1.5  93/03/03  09:21:20  roberte
#  Changed target directory "true_typ" to "tt"
#  
#  Revision 1.4  93/02/23  13:27:37  roberte
#  Removed htest and test targets from this makefile.
#  Added space which was missing before -DINCL_WHITE.
#  Removed -g option. Added "clean" target.
#  Replaced "ld" link with "cc" link.
#  
#  Revision 1.3  93/02/17  11:31:01  roberte
#  Removed unneeded dependency for /sys/ins/base.ins.c for set_keys.o
#  
#  Revision 1.2  93/02/11  14:27:55  roberte
#  Removed -Tbsd4.2 "unix_define" command line flag.
#  
#  Revision 1.1  93/02/02  14:27:08  roberte
#  Initial revision
#  
#       Revision 28.13  93/01/12  12:20:44  roberte
#       Added t1_dir to include path.
#
#       Revision 28.12  93/01/11  10:46:21  roberte
#       Added pcl directory to include path list.
#
#       Revision 28.11  93/01/07  10:12:30  roberte
#       Added dependencies on speedo.h to most objects
#
#       Revision 28.10  93/01/06  13:52:13  roberte
#       Changed file dependencies to include fscdefs.h and
#       fontscal.h from truetype.
#
#       Revision 28.9  92/12/14  15:48:18  weili
#       integrated white writer into nsample
#
#       Revision 28.8  92/12/02  14:34:44  laurar
#       update dependency list.
#
#       Revision 28.7  92/12/01  17:38:37  laurar
#       defined APOLLO and changed directory path for 4d
#        variable.
#
#       Revision 28.6  92/11/24  12:34:11  laurar
#       add fino.h as a dependency to all object files.
#
#       Revision 28.5  92/11/19  15:14:27  roberte
#       Release
#
#       Revision 28.1  92/06/25  13:39:13  leeann
#       Release
#
#       Revision 27.2  92/04/07  17:20:10  tamari
#       Update "utils_dir" to look on ninja.
#
#       Revision 27.1  92/03/23  13:58:57  leeann
#       Release
#       Revision 26.1  92/01/30  16:57:21  leeann
#       Release
#
#       Revision 25.1  91/07/10  11:03:47  leeann
#       Release
#
#       Revision 24.1  91/07/10  10:37:17  leeann
#       Release
#
#       Revision 23.1  91/07/09  17:58:21  leeann
#       Release
#
#       Revision 22.1  91/01/23  17:16:55  leeann
#       Release
#
#       Revision 21.1  90/11/20  14:36:57  leeann
#       Release
#
#       Revision 20.1  90/11/12  09:28:06  leeann
#       Release
#
#       Revision 19.1  90/11/08  10:19:13  leeann
#       Release
#
#       Revision 18.2  90/10/12  10:54:40  joyce
#       Changed to standard format
#
#       Revision 18.1  90/09/24  10:04:15  mark
#       Release
#
#       Revision 17.1  90/09/13  16:02:26  mark
#       Release name rel0913
#
#       Revision 16.1  90/09/11  13:07:12  mark
#       Release
#
#       Revision 15.1  90/08/29  10:06:15  mark
#       Release name rel0829
#
#       Revision 14.1  90/07/13  10:43:25  mark
#       Release name rel071390
#
#       Revision 13.1  90/07/02  10:42:22  mark
#       Release name REL2070290
#
#       Revision 12.3  90/06/18  14:20:46  arg
#       cleaned up makefile including:
#          more macros
#          speedo.o core
#          automatic dependency generation: 
#        	type "make depend"
#
#       Revision 12.2  90/05/16  16:55:58  mark
#       change bind to ld for test to fix sr 10 problem
#
#       Revision 12.1  90/04/23  12:14:40  mark
#       Release name REL20
#
#       Revision 11.1  90/04/23  10:14:56  mark
#       Release name REV2
#
#       Revision 10.3  90/03/30  14:55:59  mark
#       remove out_wht and add out_scrn and out_util
#

#       Revision 10.1  89/07/28  18:13:37  mark
#       Release name PRODUCT
#
#       Revision 9.1  89/07/27  10:27:16  mark
#       Release name PRODUCT
#
#       Revision 8.1  89/07/13  18:22:54  mark
#       Release name Product
#
#       Revision 7.1  89/07/11  09:05:41  mark
#       Release name PRODUCT
#
#       Revision 6.1  89/06/19  08:38:24  mark
#       Release name prod
#
#       Revision 5.2  89/06/16  16:46:24  mark
#       make SHORT_LISTS false so stuff works
#
#       Revision 5.1  89/05/01  17:58:25  mark
#       Release name Beta
#
#       Revision 4.1  89/04/27  12:21:02  mark
#       Release name Beta
#
#       Revision 3.1  89/04/25  08:34:14  mark
#       Release name beta
#
#       Revision 2.1  89/04/04  13:40:08  mark
#       Release name EVAL
#
#       Revision 1.9  89/04/03  14:32:17  mark
#       renamed output modules
#
#       Revision 1.8  89/03/31  11:59:49  mark
#       added test and fixed htest procedures
#
#       Revision 1.7  89/03/31  11:54:56  mark
#       *** empty log message ***
#
#       Revision 1.6  89/03/31  09:04:30  mark
#       added vfont to list
#
#       Revision 1.5  89/03/29  16:17:11  mark
#       get rid of path.c and change out_3a.c to out_bl2d.c
#
#       Revision 1.4  89/03/22  10:40:20  mark
#       *** empty log message ***
#
#       Revision 1.3  89/03/21  14:54:40  mark
#       added symbol to allow for definition of
#       conditional compile symbols at
#       runtime
#
#       Revision 1.2  89/03/21  13:00:35  mark
#       change include name from oemfw.h to speedo.h
#
#       Revision 1.1  89/03/20  14:38:24  mark
#       Initial revision
#
#  This makefile  can  be used to  create  any  Speedo test 
#  application  by  specifying the runfile  name. 
#  Specifying no  application, or the  dummy
#  node all  will cause all   applications to be 
#  updated.   To  add a  new
#  definition,  add the name of  the runfile to 
#  the 'all' dependency list,
#  run 'make depend', and update rcs archives.
#

debug = -O

#
# we use these directories for development:
#tt_dir = //ninja/archive/src/true_type
#eo_dir = //ninja/archive/src/pcl5/hpreader
#t1_dir = //ninja/archive/src/type1
#4demo_dir = //ninja/archive/src/4in1
# you should use these directories to match delivery diskettes:
tt_dir = ../tt
eo_dir = ../pcl5
t1_dir = ../type1
4demo_dir = ../4demo

#speedo_defines = -DINCL_OUTLINE -DINCL_2D -DINCL_KEYS \
#     -DINCL_SCREEN -DINCL_WHITE -USHORT_LISTS -DAPOLLO=1  \
#     -DPROC_PCL=0 -DPROC_TRUETYPE=0

speedo_defines = -DINCL_OUTLINE -DINCL_2D -DINCL_KEYS \
	 -DINCL_SCREEN -DINCL_WHITE -USHORT_LISTS  \
	 -DPROC_PCL=0 -DPROC_TYPE1=0 -DPROC_TRUETYPE=0

unix_defines = -c

#
includes = -I$(tt_dir) -I$(eo_dir) \
           -I$(t1_dir) -I$(4demo_dir) 

#
speedo_objs = reset.o do_char.o do_trns.o set_spcs.o \
			 set_trns.o  out_bl2d.o out_blk.o out_outl.o \
			 out_util.o out_scrn.o out_wht.o  set_keys.o

nsample = nsample.o $(speedo_objs)

#
all : nsample speedo.o

speedo.o : $(speedo_objs)
	ld -r -o $@ $(speedo_objs) && chmod -x $@

nsample : $(nsample)
	cc -o $@ $(nsample)

#
speedo.h: useropt.h \
            $(tt_dir)/fscdefs.h \
            $(tt_dir)/fontscal.h
spdo_prv.h : speedo.h

#
do_char.o:  do_char.c \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

do_trns.o:  do_trns.c \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

nsample.o:  nsample.c \
            keys.h \
            speedo.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

out_bl2d.o: out_bl2d.c \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

out_blk.o:  out_blk.c \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

out_outl.o: out_outl.c \
            spdo_prv.h \
            speedo.h \
            useropt.h\
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

out_scrn.o: out_scrn.c \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

out_wht.o: out_wht.c \
	     spdo_prv.h \
            speedo.h \
	     $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

out_util.o: out_util.c \
            speedo.h \
            spdo_prv.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

reset.o:    reset.c \
            keys.h \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

set_keys.o: set_keys.c \
            $(t1_dir)/stdef.h \
             speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

set_spcs.o: set_spcs.c \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

set_trns.o: set_trns.c \
            spdo_prv.h \
            speedo.h \
	    $(4demo_dir)/fino.h
	cc $(DEBUG) $(includes) $(speedo_defines) $(unix_defines) $*.c

# misc. targets:

clean:
	rm *.o
	rm nsample
