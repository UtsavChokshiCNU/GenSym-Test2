$!	Gensym KITINSTAL procedure:
$!
$!	PRODUCT:	Gensym OnLine Documentation
$!
$!
$	! Setup error handling
$	!
$	on control_y	then vmi$callback control_y
$	on warning	then exit $status
$!
$!
$	! Check against unhandled requests
$	!
$	if    p1 .nes. "VMI$_INSTALL" -
	.and. p1 .nes. "VMI$_IVP
$	then
$	    exit vmi$_unsupported
$	endif;
$!
$!
$	if p1 .eqs. "VMI$_INSTALL"
$	then
$	    gosub product_install
$	    exit  vmi$_success
$	else
$	    exit vmi$_unsupported
$	endif
$!
$!
$!
$!	*** Product Installation ***
$!
$ PRODUCT_INSTALL:
$!
$	vmi$callback message i info "Gensym OnLine Documentation"
$
$	! Purge any superceded files
$	!  
$	vmi$callback set purge yes
$!
$!
$	! If we come up with an IVP uncomment this...
$	!
$!	vmi$callback set ivp yes
$!
$!
$	! Product configuration constants...
$	! Some are set conditionally for the architecture.
$	! 
$	if f$getsyi("arch_type") .eq. 1      ! 1 for VAX and 2 for AXP
$	then
$		! VAX
$		minimum_version         = "062"
$	else
$		! Alpha AXP
$               minimum_version         = "062"
$	endif
$!
$!
$!
$	product = vmi$product
$	product_device		= f$trnlnm("sys$sysdevice")
$	product_update_files	= 0
$	new_top_level_dir	= 0
$ 	product_exists 		= 0
$
$!      ! Provide some reasonable defaults so that we can install
$!      ! an arbitrary product.
$	min_space      =  200000
$	min_space_stg  =  "200000 blocks"
$!
$!      ! Define specifics for known products
$	if product .eqs. "G2DOC"
$	then
$		min_space               = 40000
$		min_space_stg           = "40000 blocks"
$	endif
$
$	if product .eqs. "G2STKDOC"
$	then
$		min_space               = 12000
$		min_space_stg           = "12000 blocks"
$	endif
$
$	if product .eqs. "G2UTLDOC"
$	then
$		min_space               = 25000
$		min_space_stg           = "25000 blocks"
$	endif
$
$	if product .eqs. "G2PS"
$	then
$		min_space               = 290000
$		min_space_stg           = "290000 blocks"
$	endif
$
$	if product .eqs. "G2STKPS"
$	then
$		min_space               = 85000
$		min_space_stg           = "85000 blocks"
$	endif
$
$	if product .eqs. "G2UTLPS"
$	then
$		min_space               = 180000
$		min_space_stg           = "180000 blocks"
$	endif
$!
$!
$!
$	gosub check_vms_version
$	gosub check_minimum_space
$	gosub set_locations_and_logicals
$	gosub set_and_move_files
$!
$	if new_top_level_dir
$	then
$	    type sys$input

	When the installation script is complete, you should set the
	ownership of the installed files appropriately.  Use
	the "set file/owner=" command to do this.  For example, if you have
       	installed the files in dka300:[gensym], type both of the following
       	commands, replacing <owner> with the account of your choice.
	$ set file/owner=<owner> dka300:[000000]gensym.dir
	$ set file/owner=<owner> dka300:[gensym...]*.*
$!
$	    vmi$callback ask user_answer "Press RETURN to acknowledge" "OK" D
$	endif
$
$	return
$!
$!
$!
$	! Check if we are compatible with this version of VMS
$	!     
$	check_vms_version:
$!
$	! We only run on VMS minimum_version or later
$	!
$	if f$extr(0, 3, f$element(1, ",", vmi$vms_version)) .lts. minimum_version
$	then
$	    min_ver_name = "V" + f$extract(1, 1, minimum_version) + "."
$	    min_ver_name = min_ver_name + f$extract(2, 2, minimum_version)
$	    vmi$callback message e version -
		"''product' requires VMS version ''min_ver_name' or later"
$	    exit vmi$_failure
$	endif
$	return
$!
$!
$!
$	! Check for minimum space requirements
$	!
$	check_minimum_space:
$
$	vmi$callback check_net_utilization product_test min_space
$	if .not. product_test
$	then
$	    vmi$callback message e nospace -
		"System disk has insufficient space to install ''product'" -
		"Installation requires ''min_space_stg' blocks"
$	    exit vmi$failure
$	endif
$	return                                         
$!
$!
$!
$	! Ask user for a directory in which to install the product.
$	! Check if it is already present, and if so, find out
$	! if the user would like to use it.  If not, create it.
$	!
$	set_locations_and_logicals:
$
$	vmi$callback ask product_directory "''product' directory" "''product_device'[''product']" D
$
$	define/nolog product$root 'product_directory'
$	gosub check_product_existence
$ 	if product_exists .eq. 1
$	then
$	    ! directory already exists
$	    vmi$callback ask product_answer "Prior ''product_directory' found - replace it" "N" BD
$	    if .not. product_answer
$	    then
$		goto set_locations_and_logicals
$	    else
$		write sys$output ""
$		write sys$output "Please delete and backup ''product_directory', then reinstall."
$		write sys$output ""
$	        exit vmi$_unsupported
$	    endif
$	else
$	    ! directory does not exist
$	    create/directory/prot=(w:rwe)/owner=[200,100] 'product_directory'
$           new_top_level_dir = 1
$	endif
$	return
$
$!	! The following routine checks whether the
$!	! directory path in global logical "product$root" already
$!	! exists.  It sets the global symbol "product_exists"
$!	! to 1 if it exists and 0 if not.
$!	!
$	check_product_existence:
$
$!	! Save and suppress messages and error handling.
$	message_settings = f$environment("message")
$	set message/nofacility/noseverity/noid/notext
$	set noon
$
$!	! Check for existence by checking whether DIR gets an error
$	dir/out=nl: product$root
$	product_exists = $severity .AND. 1
$
$!	! Restore error handling and message output
$	set on
$	set message 'message_settings
$	return
$!
$!
$!
$	! Move product files to correct directories:
$	!
$	set_and_move_files:
$
$	product_root_tree = f$trnlnm("product$root") - "]" + "...]"
$
$	backup/select=[saveset.'product'...] vmi$kwd:'product'.sav/save 'product_root_tree'
$	!
$	set file/protection=(s:rwed,o:rwed,g:rwe,w:re) 'product_root_tree'*.*
$	return
