$!	This file links an extension written in Ada with the
$!	standard GSI modules. 
$!
$!	p1 = <main library unit procedure>
$!      p2 = "DEBUG" => link with debug
$!
$	main_rtn = p1
$       show symbol main_rtn
$ l1:
$	if main_rtn .eqs. ""
$	then
$	    inquire main_rtn "main? "
$	    goto l1
$	endif
$!
$	debopt = ""
$	if p2 .eqs. "DEBUG"
$	then
$	    debopt = "/" + p2
$	endif
$!
$	acs link 'debopt 'main_rtn gsi$options/opt
$ exit:
$	write sys$output "Link Complete"
