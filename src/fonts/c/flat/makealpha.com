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
$!
$ cc/standard=vaxc 4demo.c
$ cc/standard=vaxc mhddemo.c
$!
$ cc/standard=vaxc ripdemo.c
$ cc/standard=vaxc fontrip.c
$!
$ cc/standard=vaxc msl.c
$ cc/standard=vaxc frontend.c
$ cc/standard=vaxc cmt.c
$ cc/standard=vaxc cmtglob.c
$ cc/standard=vaxc msst.c
$ cc/standard=vaxc msstglob.c
$ cc/standard=vaxc tt_iface.c
$ cc/standard=vaxc tt_specs.c
$ cc/standard=vaxc fontscal.c
$ cc/standard=vaxc fsglue.c
$ cc/standard=vaxc fnt.c
$ cc/standard=vaxc sfntd.c
$ cc/standard=vaxc mapstrng.c
$ cc/standard=vaxc newscan.c
$ cc/standard=vaxc fixed_pt.c
$ cc/standard=vaxc tr_names.c
$ cc/standard=vaxc tr_ldfnt.c
$ cc/standard=vaxc tr_mkchr.c
$ cc/standard=vaxc tr_trans.c
$ cc/standard=vaxc out_blk.c
$ cc/standard=vaxc out_util.c
$ cc/standard=vaxc out_outl.c
$ cc/standard=vaxc out_scrn.c
$ cc/standard=vaxc out_bl2d.c
$ cc/standard=vaxc out_wht.c
$ cc/standard=vaxc reset.c
$ cc/standard=vaxc do_char.c
$ cc/standard=vaxc do_trns.c
$ cc/standard=vaxc set_spcs.c
$ cc/standard=vaxc set_trns.c
$ cc/standard=vaxc set_keys.c
$ cc/standard=vaxc hpfnt1.c
$ cc/standard=vaxc hpfnt2.c
$ cc/standard=vaxc load_pcl.c
$!
$ link 4demo, msl, frontend, cmt, cmtglob,  msst, msstglob, tt_iface, -
  tt_specs, fontscal, fsglue, fnt,  sfntd, mapstrng, newscan, -
  fixed_pt, tr_names, tr_ldfnt, tr_mkchr, tr_trans, out_blk, -
  out_util, out_outl, out_scrn,  out_bl2d, out_wht, reset, do_char, -
  do_trns, set_spcs, set_trns, set_keys, hpfnt1, hpfnt2, load_pcl
$!
$ link mhddemo, msl, frontend, cmt, cmtglob,  msst, msstglob, tt_iface, -
  tt_specs, fontscal, fsglue, fnt,  sfntd, mapstrng, newscan, -
  fixed_pt, tr_names, tr_ldfnt, tr_mkchr, tr_trans, out_blk, -
  out_util, out_outl, out_scrn,  out_bl2d, out_wht, reset, do_char, -
  do_trns, set_spcs, set_trns, set_keys, hpfnt1, hpfnt2, load_pcl
