$ ! jh, 3/3/92.  Form a simple GSI image on VMS.  Revised from 11/91.
$ !
$ ! almost works on the vax, after doing "$ domain ext vax" or logging in as Chestntut
$ !
$ ! use /g_float if SetIcpMode(ICP_USE_GFLOAT) happens in your main().
$ cc /nowarn /inc=ext$srcs gsi_benchmark
$ cc /nowarn /inc=ext$srcs gsi_regress_for_benchmark
$ !
$ ! link /exe=bench bench/opt, -
  ! ext$opt:libgsi/lib, -
  ! ext$opt:libdec/lib, -
  ! sys$library:ucx$ipc/lib
$ link /exe=bench bench/opt, -
  gsi$liball/lib, -
  sys$library:ucx$ipc/lib
$ !  
$ ! don't forget commas between each filespec in the link command
$ ! (including the post-qualified ones like xxx/lib and xxx/opt).
$ !
$ ! link against ext21$objlib to make a GSI 2.1 extension
$ !