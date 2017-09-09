$	! Startup file for TW 4.*
$	!
$!
$	! The directory where TW is installed
$	!
$	define/nolog tw40$disk	????:
$	define/nolog tw40$root	yyyy
$	define/nolog tw40$dir	yyyy
$!
$	tw40    == "$tw40$dir:tw"
$!                            
$	exit
