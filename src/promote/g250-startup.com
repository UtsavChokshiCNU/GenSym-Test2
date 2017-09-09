$	! Startup file for G2 5.*
$	!
$!
$	! The directory where G2 is installed
$	!
$	define/nolog g251$disk	????:
$	define/nolog g251$rt	xxxx
$	define/nolog g251$dir	yyyy
$	define/nolog g251$ext 	g251$rt:[ext]
$	define/nolog g251$kbs   g251$rt:[kbs]
$!
$	old_g2 = f$trnlnm("g2$root")
$	if old_g2 .nes. ""
$	then
$	    old_g2 = "," + old_g2
$	endif
$	define/nolog g251$root	g2$disk:[g251.kbs]'old_g2'
$!
$	g251     == "$g251$dir:g2"
$	overlay  == "$g251$ext:overlay"
$	g2passwd == "$g251$dir:g2passwd"
$!                            
$	exit
