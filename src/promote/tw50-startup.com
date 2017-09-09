$	! Startup file for TW 5.*
$	!
$!
$	! The directory where TW is installed
$	!
$	define/nolog tw51$disk	????:
$	define/nolog tw51$root	yyyy
$	define/nolog tw51$dir	yyyy
$!
$	tw51    == "$tw51$dir:tw"
$!                            
$	exit
