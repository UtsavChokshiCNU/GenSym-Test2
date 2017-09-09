$	! Startup procedure for Gensym-NOL.
$	!
$	define/nolog	gensym_nol$disk		##dev##:
$	define/nolog	gensym_nol$dir		##dir##
$	define/nolog	gensym_nol$tmp		##tmp##
$!
$!
$!	Define symbols
$!
$	x = f$getsyi("hw_name")
$	if f$locate("VAX",x) .ne. f$length(x)
$	then
$	    nol_rpc == "$gensym_nol$dir:vaxnol"
$	else
$	    nol_rpc == "$gensym_nol$dir:alphanol"
$	endif


