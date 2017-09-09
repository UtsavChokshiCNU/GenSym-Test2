$!  Make a G2/GSI/Bridge product tape for distribution...
$!
$!  This file is used on machine PROD in the dist$com directory.
$!  Its original repository version is maintained in /gensym/tools/vms.
$!
$!  Overview:
$!	This program is given as parameters a list (up to 6) of product names
$!	that are to be put on a [VAX | Alpha] distribution tape. If no 
$!	parameters are given, or if a parameter is deemed invalid, the program
$!	lists the valid product names and a brief description of each.
$!
$!  Technical Summary:
$!	Product names correspond to the names of subdirectories under the
$!	current BRIDGE$DIR. Also, each product dir must contain a valid
$!	VERSION.TXT file. The VERSION.TXT format is as follows:
$!
$!		<format>			| <example>
$!	(VERSION INFO)				| V3.0R1
$!	(PRODUCT NAME/DESCRIPTION)		| G2 Alpha AXP OpenVMS
$!	(OPTIONAL EXPLICIT DELIVERABLE NAME)	| G2030
$!
$!	Note that the third line is optional. If not present, this tape making
$!	program will use the product name (directory name) as the name that
$!	VMS Installation procedures will reference on the tape. (i.e. the 
$!	customer will see this name!)
$!
$!  Program History:
$!	mpc  26-MAY-93	Added this header section. Added the functionality
$!		to read an explicit deliverable name from the version.txt
$!		file. (This was added to solve the problem of Alpha tapes
$!		being shipped with product names that started with "alpha",
$!		which confused the customer. This was due to using dir names
$!		as deliverable product names. This also had forced tape
$!		makers to rename/move around products into properly named
$!		directories.)
$!
$!  p1 [ p2 [ p3 ...]]] :== product_list
$!
$	max_tape_label_len = 6
$	true = 1
$	false = 0
$	opened = false
$	mounted = false
$	allocated = false
$	io_redirected = false
$
$	! If we get an error or user aborts, clean things up!!
$	!
$	on error then goto cleanup
$	on control_y then goto cleanup
$
$	if   p1 .eqs. ""   -
	.or. p1 .eqs. "?"
$	then
$	    write sys$output ""
$	    write sys$output "Usage: make <product [product [product ...]]>"
$	    gosub write_products_available
$	    exit
$	endif
$
$	gosub	check_products_ok
$
$	if found_bad_product
$	then
$	    gosub write_products_available
$	    exit
$	endif
$
$	gosub process_product_list
$
$	purge dist$dir:*.lis
$	purge dist$dir:*.log
$	write sys$output " "
$	search/nohighlight dist$dir:output.log kit
$	write sys$output " "
$	exit
$!
$!
$!
$!
$ 	! Output the list of available products
$ 	!
$	write_products_available:
$
$	write sys$output "Products available:"
$	write sys$output "  <Product Name>     <Shipped Name>     <Version/Description>"
$	l2:
$	    file = f$search("bridge$dir:[000000]*.dir", 1)
$	    if file .nes. ""
$	    then
$		pdir = f$parse(file,,,"name")
$		vfile = f$search("bridge$dir:[''pdir']version.txt")
$		if vfile .nes. ""
$		then
$		    opened = true
$		    open  vf 'vfile
$		    read  vf the_version
$		    read  vf the_product
$		    read/end_of_file=NO_NAME  vf shipped_name
$		    if shipped_name .nes. "" 
$		    then
$		        goto PROCEED
$		    endif
$		    NO_NAME:
$			shipped_name = ""
$!
$		    PROCEED:
$		    close  vf
$		    opened = false
$		    line = "          "
$		    line[3,19] := 'pdir'
$		    line[22,19] := 'shipped_name' 
$		    endlen = f$length(the_version) + f$length(the_product) + 1
$		    line[41,endlen] := "''the_version' ''the_product'"
$!
$		    write sys$output line
$		endif
$		goto l2
$	    endif
$	end_l2:
$	return
$!
$!
$!
$	! Check if the given set of products exist and are "legal"
$	!
$	check_products_ok:
$
$	prod_list = p1 + "," + p2 + "," + p3 + "," + p4 + "," + p5 + "," + p6
$	n = 0
$	found_bad_product = 0
$	l1:
$	    p1 = f$element(n, ",", prod_list)
$	    if   p1 .eqs. "," -
	    .or. p1 .eqs. ""
$	    then
$		goto end_l1
$	    else
$		if f$search("bridge$dir:[000000]''p1'.dir") .eqs. ""
$		then
$		    found_bad_product = 1
$		    write sys$output ""
$		    write sys$output "Product ''p1' is unknown"
$		    write sys$output ""
$		else
$		    if f$search("bridge$dir:[''p1']version.txt") .eqs. ""
$		    then
$			found_bad_product = 1
$			write sys$output "The product version file for ''p1' is not available."
$			write sys$output "Please contact platform support or the developer."
$			write sys$output ""
$		    endif
$		endif
$	    endif
$	    n = n + 1
$	    goto l1
$	end_l1:
$	return
$!
$!
$!
$	! Place a given product kit onto the current tape.
$	! Assumes that the product name is in shipped_name
$	!
$	make_one:
$
$	purge  bridge$dir:['p1']
$
$	if first_product
$	then
$	    rewind_switch = "/rewind"
$	    label_switch  = "/label=''tape_label'"
$	else
$	    rewind_switch = ""
$	endif
$
$	backup 'rewind_switch'/list=dist$dir:'p1'.lis -
	      	bridge$dir:['p1'...]*.*		      -
		mt:'shipped_name'.a/save'label_switch'
$
$	type dist$dir:'p1'.lis
$	write sys$output "*** The ''the_version' ''the_product' kit was completed. ***"
$	write sys$output ""
$	return
$!
$!
$!
$	! Build a tape with kits for all products in product_list
$	!
$	process_product_list:
$
$	tape_drive = "mka500"
$	inquire/nopunct junk "Tape drive [mka500]: "
$	if junk .nes. ""
$	then
$	    tape_drive = junk
$	endif
$	inquire/nopunct junk "Mount new tape in drive and press RETURN: "
$
$	! First product to go on tape, labels it.
$	!
$	tape_label = f$element(0, ",", prod_list)
$	if f$length(tape_label) .gt. max_tape_label_len
$	then
$	    tape_label = f$extract(0, max_tape_label_len, tape_label)
$	endif
$	allocated  = true
$	allocate   'tape_drive' mt
$	init       mt 'tape_label'
$	mounted	   = true
$	mount/for  mt
$
$	io_redirected = true
$	define sys$output dist$dir:output.log
$
$	n = 0
$	l3:
$	    first_product = n .eq. 0
$	    p1 = f$element(n, ",", prod_list)
$
$	    if   p1 .eqs. ","  -
	    .or. p1 .eqs. ""
$	    then
$		goto end_l3
$	    else
$		vfile = f$search("bridge$dir:[''p1']version.txt")
$		opened = true
$		open  vf 'vfile
$		read  vf the_version
$		read  vf the_product
$		read/end_of_file=NO_NAME  vf shipped_name
$		if shipped_name .nes. "" 
$		then
$			goto PROCEED
$		endif
$		NO_NAME:
$		   shipped_name = p1
$!
$		PROCEED:
$		close vf
$		opened = false
$		gosub make_one
$	    endif
$
$	    n = n + 1
$	    goto l3
$	end_l3:
$
$	dismount   mt
$	mounted 	= false
$	deallocate mt
$	allocated	= false
$	deassign sys$output
$	io_redirected	= false
$	return
$!
$!
$!                      
$	! Close any open files, deallocate tape drive, etc.
$	!
$	cleanup:
$
$	set noon
$	if opened then close vf
$	if mounted then dismount mt
$	if allocated then deallocate mt
$	if io_redirected then deassign sys$output
$	set on
$	exit
$!
