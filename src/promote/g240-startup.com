$	! Startup file for G2 4.*
$	!
$!
$	! The directory where G2 is installed
$	!
$	define/nolog g240$disk	????:
$	define/nolog g240$rt	xxxx
$	define/nolog g240$dir	yyyy
$	define/nolog g240$ext 	g240$rt:[ext]
$	define/nolog g240$kbs   g240$rt:[kbs]
$!
$	old_g2 = f$trnlnm("g2$root")
$	if old_g2 .nes. ""
$	then
$	    old_g2 = "," + old_g2
$	endif
$	define/nolog g240$root	g2$disk:[g240.kbs]'old_g2'
$!
$	g240    == "$g240$dir:g2"
$	overlay == "$g240$ext:overlay"
$!                            
$	exit
