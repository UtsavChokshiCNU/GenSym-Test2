$!	Gensym KITINSTAL procedure:
$!
$!	PRODUCT:	GSI 3.*
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
$!	    show symbol vmi$vms_version
$!	    show logical vmi$root
$!	    show logical vmi$specific
$!	    set verify
$	    gosub gsi_install
$!	    set noverify
$	    exit  vmi$_success
$	else
$	    ! When we get an IVP, build this section
$	    !
$	    !gosub gsi_ivp
$	    exit vmi$_unsupported
$	endif
$!
$!
$!
$!	*** GSI Installation ***
$!
$ GSI_INSTALL:
$!
$	if f$getsyi("arch_type") .eq. 1      ! 1 for VAX and 2 for AXP
$       then
$		vmi$callback message i info "Gensym GSI 3.2 for VAX VMS/OpenVMS"
$	else
$		vmi$callback message i info "Gensym GSI 3.2 for Alpha AXP OpenVMS"
$	endif
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
$       then
$		! VAX
$		minimum_version		= "054"
$		product 		= "GSI 3.2"
$		min_space		= 1500
$		min_space_stg		= "1500 blocks, with temporary peak of 1500"
$	else
$		! AXP
$		minimum_version         = "010"
$		product                 = "GSI 3.2"
$		min_space               = 7000
$		min_space_stg           = "7000 blocks, with temporary peak of 14000"
$	endif
$
$	gsi_device		= f$trnlnm("sys$sysdevice")
$	product_startup_line	= "$      @sys$startup:gsi32-startup"
$
$	gsi_update_files	= 0
$	new_top_level_dir	= 0
$!
$!
$!
$	gosub check_vms_version
$	gosub check_minimum_space
$	gosub setup_locations_and_logicals
$	gosub set_and_move_files
$	gosub insert_gsi_startup_call
$
$       if new_top_level_dir
$       then
$           type sys$input

	When the installation script is complete, you should set the
	ownership of the installed files appropriately.  Use
	the "set file/owner=" command to do this.  For example, if you have
       	installed the files in dka300:[gensym], type both of the following
       	commands, replacing <owner> with the account of your choice.
	$ set file/owner=<owner> dka300:[000000]gensym.dir
	$ set file/owner=<owner> dka300:[gensym...]*.*
$		vmi$callback ask user_answer "Press RETURN to acknowledge" "OK" D
$       endif
$
$	@sys$startup:gsi32-startup
$	return
$!
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
$	vmi$callback check_net_utilization gsi_test min_space
$	if .not. gsi_test
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
$	! Ask user for any installation directories
$	!
$	get_directories:
$
$	vmi$callback ask gsi_directory "GSI directory" "''gsi_device'[gsi32]" D
$	if f$parse(gsi_directory) .eqs. ""
$	then
$	    create/directory/prot=(w:rwe)/owner=[200,100] 'gsi_directory'
$           new_top_level_dir = 1
$	endif
$	define/nolog gsi$root 'gsi_directory'
$	return
$!
$!
$!
$	! Check if a GSI is already present.  If so, find out
$	! if the user would like to just overwrite the existing directories
$	! (the default) or whether new directories are wanted.
$	!
$	setup_locations_and_logicals:
$
$	if f$trnlnm("gsi$root")  .nes. ""
$	then
$	    ! GSI currently exists
$	    !
$	    vmi$callback ask gsi_answer "Prior GSI found - replace" "N" BD
$	    if .not. gsi_answer
$	    then
$	        gosub get_directories
$	    else
$	        gsi_update_files = 1
$	    endif
$	else
$	    gosub get_directories
$	endif
$	gsi_directory     = f$trnlnm("gsi$root")
$	return
$!
$!
$!
$	! Set the correct disk and paths in the gsi-startup file and write
$	! this file to sys$startup.
$	!
$	write_gsi_startup:
$
$	gsi_device = f$parse("gsi$root",,,"DEVICE")
$
$	open/read  gsikitstartup  vmi$kwd:gsi32-startup.com
$	open/write gsistartup     vmi$root:[sys$startup]gsi32-startup.com
$
$	l6:
$	    read/end_of_file=end_l6 gsikitstartup line
$
$	    pos = f$locate("????", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + gsi_device
$	    endif
$
$	    pos = f$locate("yyyy", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + gsi_root_tree - ".." + "/tran=con"
$	    endif
$
$	    pos = f$locate("xxxx", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + gsi_root_tree - "..."
$	    endif
$
$	    write gsistartup line
$	    goto l6
$	end_l6:
$
$	close gsikitstartup
$	close gsistartup
$	return
$!
$!
$!
$	! Move product files to correct directories:
$	!
$	set_and_move_files:
$
$	! First move in the DCL commands and HELP
$	!
$!	vmi$callback provide_dcl_command	gsi.cld
$	vmi$callback provide_dcl_help		gsi.hlp
$
$	gsi_root_tree = f$trnlnm("gsi$root") - "]" + "...]"
$
$	gosub   write_gsi_startup
$	copy	vmi$kwd:*.c,*.h			gsi$root:*
$	copy	vmi$kwd:*.olb			gsi$root:*
$	copy	vmi$kwd:*.obj			gsi$root:*
$	copy	vmi$kwd:*.exe			gsi$root:*
$	copy	vmi$kwd:make*.*			gsi$root:*
$	copy	vmi$kwd:*.mms			gsi$root:*
$	copy	vmi$kwd:graphics.dat		gsi$root:*
$	copy	vmi$kwd:gsioptions.opt		gsi$root:*
$	copy	vmi$kwd:gsiadalink.com		gsi$root:*
$	copy	vmi$kwd:run_extension.com	gsi$root:*
$	copy	vmi$kwd:gsi_exam.kb		gsi$root:*
$
$	if gsi_update_files
$	then
$	    purge 'gsi_root_tree'
$	    purge vmi$root:[sys$startup]gsi32-startup.com
$	endif
$	!
$	set file/protection=(s:rwed,o:rwed,g:rwe,w:re) 'gsi_root_tree'*.*
$	set file/protection=(s:rwed,o:rwed,g:rwe,w:re)  vmi$root:[sys$startup]gsi32-startup.com
$	return
$!
$!
$!
$	! Place the call to the gsi startup command procedure in the
$	! "proper" location.  This will either be in specific login.com
$	! files or sys$manager:sylogin.com.  The latter is recommended.
$	!
$	insert_gsi_startup_call:
$
$	vmi$callback ask gsi_answer "Place startup call in SYLOGIN.COM" "Y" BD
$	if gsi_answer
$	then
$	    open/read  sylogin     vmi$root:[sysmgr]sylogin.com
$	    open/write newsylogin  vmi$root:[sysmgr]sylogin.com
$	    l5:
$		read/end_of_file=end_l5 sylogin line
$		write newsylogin line
$		goto l5
$	    end_l5:
$	    write newsylogin "$!
$	    write newsylogin "$      ! Set logicals for GSI/GSI/TW
$	    write newsylogin "$      !
$	    write newsylogin product_startup_line                      
$	    close sylogin
$	    close newsylogin
$	endif
$	return
