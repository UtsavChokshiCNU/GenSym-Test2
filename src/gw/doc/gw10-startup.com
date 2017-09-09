$	! Startup file for GW 1.*
$	!
$!
$	! The directory where GW is installed
$	!
$	define/nolog gw10$disk	????:
$	define/nolog gw10$root	yyyy
$	define/nolog gw10$dir	yyyy
$!
$	gw10    == "$gw10$dir:gw"
$!                            
$	exit
