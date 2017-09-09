$!  This provides an easy-to-use interface to write_vms_tape.com.  It
$!  invokes the utility with the correct products to be placed on a tape.
$!
$!  This file is used on machine PROD in the dist$com directory.
$!  Its original repository version is maintained in /gensym/tools/vms.
$!
$!  usage: writecore { vax | alpha } { 3.0 | 4.0 }
$!
$   set noverify
$
$!  ! Check that arguments are legal
$!  !
$   if p1 .nes. "VAX" .and. p1 .nes. "ALPHA" then goto usage_error
$   if   p2 .nes. "3.0" .and. p2 .nes. "4.0"   then goto usage_error
$
$!  ! Set "products" to the list of products to put on the tape
$!  !
$   if   p1 .eqs. "VAX" .and. p2 .eqs. "3.0"
$    then
$        products = "g2030r3 gsi030r3 tw030r3 gsi031r0"
$    endif
$   if   p1 .eqs. "ALPHA" .and. p2 .eqs. "3.0"
$       then
$           products = "alphag2030r6 alphagsi030r6 alphatw030r6 alphagsi031r1"
$       endif
$   if   p1 .eqs. "VAX" .and. p2 .eqs. "4.0"
$       then
$           products ="g240b33 tw40b33 gsi32b33 gsi40b33 guide40b19"
$       endif
$   if   p1 .eqs. "ALPHA" .and. p2 .eqs. "4.0"
$   then
$       products = "alphag240b33 alphatw40b33 alphagsi32b33 alphagsi40b33 guide40b19"
$   endif
$
$!  ! Put the products on the tape.  Note that "make" is the symbol that
$!  ! references write_vms_tape.com
$!  !
$   set verify
$   make 'products'
$   set noverify
$
$   exit
$
$ usage_error:
$   write sys$output ""
$   write sys$output "Usage: writecore { vax | alpha } { 3.0 | 4.0 }"
$   exit
