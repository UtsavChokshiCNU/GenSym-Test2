$	!	Startup file for GSI
$	!
$	define/nolog	gsi$disk	????
$	define/nolog	gsi$root	xxxx
$!
$	define/nolog	gsi$libgsi	gsi$root:libgsi.olb
$	define/nolog	gsi$libdec	gsi$root:libdec.olb
$	define/nolog	gsi$libnet	gsi$root:libnet.olb
$	define/nolog	gsi$libtcp	gsi$root:libtcp.olb
$	define/nolog	gsi$libgspan	gsi$root:libgspan.olb
$	define/nolog	gsi$options	gsi$root:gsioptions.opt
$!
$	define/nolog	gsi$srcs	[],gsi$root
$	define/nolog	gsi$objs	[],gsi$root
$	define/nolog	gsi$exes	[],gsi$root
$!
$!
$!	Define symbols
$!
$	linkada		== "@gsi$root:gsiadalink"
$	makec		== "@gsi$root:make_extension"
$	makeg		== "@gsi$root:make_gspan"
$	runext		== "@gsi$root:run_extension"
