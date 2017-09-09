$! COM FILE TO EITHER COMPILE OR LINK FILES
$!
$! P1: file-spec of C source WITHOUT the .C!!!
$! P2: "COMPILE" | "LINK" | NIL
$! P3: "LINK"    | NIL
$!
$! EXAMPLE USE:
$!	$ @make_example corr compile link
$!
$!
$	main = f$extract(0, f$locate(",", p1), p1)
$	p1 = p1 - "GSI_MAIN,"
$	p1 = p1 - ".C"
$	p1 = p1 - "GSI$SRCS:"
$	if p2 .eqs. "COMPILE" then goto COMPILE
$	if p2 .eqs. "LINK" then goto LINK
$	if p2 .eqs. "" then goto LINK
$!
$	write sys$output "usage: make_extension [file] [COMPILE] [LINK]"
$	exit
$!
$COMPILE:
$!
$! Compile C Files
$!
$	write sys$output "Compiling C files..."
$	write sys$output "compiling file: gsi_main.c"
$	!
$	! The lexical function f$getsyi("arch_type") call returns 1 for a vax
$	! and 2 for an axp.
$	!
$       if f$getsyi("arch_type") .eq. 1
$	then
$		cc/obj=gsi$objs  gsi$srcs:gsi_main.c
$	else
$       	cc/standard=vaxc/float=ieee_float/extern=common/share/obj=gsi$objs gsi$srcs:gsi_main.c
$	endif
$!
$	write sys$output "compiling file: ''p1'"
$!
$       if f$getsyi("arch_type") .eq. 1
$	then
$		cc/obj=gsi$objs  gsi$srcs:'p1
$	else
$       	cc/standard=vaxc/float=ieee_float/extern=common/share/obj=gsi$objs gsi$srcs:'p1
$	endif

$!
$	if p3 .nes. "LINK" then goto END
$LINK:
$!
$! Link Object Modules
$!
$	write sys$output "Linking object modules for GSI 3.2 ..."
$	!
$	link/exe=gsi$exes:'main.exe gsi$objs:gsi_main, gsi$objs:'p1, -
		gsi$options/opt
$!
$END:
$exit
