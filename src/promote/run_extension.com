$! This file runs the executable image
$! 
$!
$	gsi$cur = f$environment("DEFAULT")
$	define/nolog run$path 'gsi$cur',gsi$root
$	'p1 == "$run$path:''p1'"
$!	write sys$output "''p1' ''p2'"
$	'p1 'p2
