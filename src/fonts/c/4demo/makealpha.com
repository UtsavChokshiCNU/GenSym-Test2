$!
$!  This command file, make.com, will compile nsample.  Sources may be compiled 
$!  by entering "$ @make"
$!
$!  Then, to run this on our alpha, sabre, do
$!      $ demo4 == "$home$disc:[mhd.bitstream.4in1.4demo]4demo.exe"
$!      $ demo4 f.spd
$!      $ demo4 f.t1
$!      $ demo4 f.ttf
$!  Note that demo4 is chosen as the command symbol because a VMS command 
$!  symbol must start with a letter, not a number.
$!

$include_dirs = "[-.speedo],  [-.pcl5],  [-.type1], [-.tt], [-.fitutil], [-.4demo]"

$defines = "SPEEDO_CODE=1, INCL_KEYS=1, SHORT_LISTS=0, INCL_BLACK=1, INCL_2D=1, INCL_OUTLINE=1, INCL_SCREEN=1, INCL_WHITE=1, PROTOS_AVAIL=0, INCL_PFB=1, BASELINE_IMPROVE=1, HAVE_MSL2INDEX"

$! The above defines won't work with mhddemo; see makefile for further info. -mhd

$mhddefines = "-DSPEEDO_CODE=1, -DINCL_KEYS=1, -DSHORT_LISTS=0, -DINCL_BLACK=1, -DINCL_2D=1, -DINCL_OUTLINE=0, -DINCL_SCREEN=1, -DINCL_WHITE=0, -DPROTOS_AVAIL=0, -DINCL_PFB=1, -DBASELINE_IMPROVE=1, -DHAVE_MSL2INDEX"


$! use /standard=vaxc in order to compile on alpha -- don't do for regular old vaxes:
$! cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) 4demo.c

$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) 4demo.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) mhddemo.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) msl.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) frontend.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) cmt.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) cmtglob.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) msst.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) msstglob.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]tt_iface.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]tt_specs.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]fontscal.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]fsglue.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]fnt.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]sfntd.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]mapstrng.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]newscan.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.tt]fixed_pt.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.type1]tr_names.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.type1]tr_ldfnt.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.type1]tr_mkchr.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.type1]tr_trans.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]out_blk.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]out_util.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]out_outl.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]out_scrn.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]out_bl2d.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]out_wht.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]reset.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]do_char.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]do_trns.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]set_spcs.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]set_trns.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.speedo]set_keys.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.pcl5]hpfnt1.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) [-.pcl5]hpfnt2.c
$ cc/define=('mhddefines)/standard=vaxc/include_directory=('include_dirs) load_pcl.c

$ link 4demo, msl, frontend, cmt, cmtglob,  msst, msstglob, tt_iface, -
  tt_specs, fontscal, fsglue, fnt,  sfntd, mapstrng, newscan, -
  fixed_pt, tr_names, tr_ldfnt, tr_mkchr, tr_trans, out_blk, -
  out_util, out_outl, out_scrn,  out_bl2d, out_wht, reset, do_char, -
  do_trns, set_spcs, set_trns, set_keys, hpfnt1, hpfnt2, load_pcl


$ link mhddemo, msl, frontend, cmt, cmtglob,  msst, msstglob, tt_iface, -
  tt_specs, fontscal, fsglue, fnt,  sfntd, mapstrng, newscan, -
  fixed_pt, tr_names, tr_ldfnt, tr_mkchr, tr_trans, out_blk, -
  out_util, out_outl, out_scrn,  out_bl2d, out_wht, reset, do_char, -
  do_trns, set_spcs, set_trns, set_keys, hpfnt1, hpfnt2, load_pcl
