$!	Gensym KITINSTAL procedure:
$!
$!	PRODUCT:	GW 1.*
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
$	    gosub gw_install
$!	    set noverify
$	    exit  vmi$_success
$	else
$	    ! When we get an IVP, build this section
$	    !
$	    !gosub gw_ivp
$	    exit vmi$_unsupported
$	endif
$!
$!
$!
$!	*** GW Installation ***
$!
$ GW_INSTALL:
$!
$	if f$getsyi("arch_type") .eq. 1      ! 1 for VAX and 2 for AXP
$       then
$		vmi$callback message i info "G2 Internet Bridge 1.0 Beta 1 for VAX VMS/OpenVMS"
$	else
$		vmi$callback message i info "G2 Internet Bridge 1.0 Beta 1 for Alpha AXP OpenVMS"
$	endif
$
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
$		minimum_version		= "055"
$		product 		= "GW 1.0"
$		min_space		= 5000
$		min_space_stg		= "5000 blocks, with temporary peak of 10000"
$
$		min_pagefile		= 30000  ! 15 MB
$		min_virpagecnt		= 30000  ! 15 MB
$		min_wsmax		= 2000   !  1 MB
$		best_pagefile		= 50000  ! 25 MB
$		good_pagefile		= 40000  ! 20 MB
$		suggested_wsmax		= 4000   !  2 MB
$		account_wsquo		= 2000   !  5 MB
$	else
$		! Alpha AXP
$		minimum_version		= "061"
$		product 		= "GW 1.0"
$		min_space		= 9000
$		min_space_stg		= "9000 blocks, with temporary peak of 18000"
$
$		min_pagefile		= 50000  !  25 MB
$		min_virpagecnt		= 50000  !  25 MB
$		min_wsmax		= 4000   !   2 MB
$		best_pagefile		= 100000 !  50 MB
$		good_pagefile		= 80000  !  40 MB
$		suggested_wsmax		= 8000   !   4 MB
$		account_wsquo		= 4000   !   2 MB
$	endif
$
$	gw_device		= f$trnlnm("sys$sysdevice")
$	product_startup_line	= "$      @sys$startup:gw10-startup"
$
$	pagefile_name		= "vmi$specific:[sysexe]pagefile.sys"
$	satellite_pagecom_name	= "vmi$kwd:gwshowmem.txt"
$	action_item_file_name	= "gw$root:installation_action_items.com"
$	gen_modparams_name	= "vmi$specific:[sysexe]gensym_modparams.dat"
$
$	gw_update_files		= 0
$	new_top_level_dir	= 0
$	gw_sys_resource_change  = 0
$
$	! These are computed during installation
$	!
$	actual_pagefile		= 0
$	action_count		= 0
$
$	! Templates of strings that go into our generated MODPARAMS.DAT
$	!
$	modparams_wsmax		= "WSMAX          =    !SL"
$	modparams_virpagecnt	= "VIRTUALPAGECNT =    !SL"
$	modparams_pagefile	= "PAGEFILE       =    0	! Prevent AUTOGEN from recalculating"
$	modparams_swapfile	= "SWAPFILE       =    0	! Prevent AUTOGEN from recalculating"
$
$	! Template for user account qualifiers
$	!
$	qualifiers = "/uic=!AS/password=!AS/wsquo=!SL/wsextent=!SL/pgflquo=!SL"
$	qualifiers = qualifiers + "/nopwdexpired/flags=(nodisuser)"
$	qualifiers2 = "/fillm=100/bytlm=32768/biolm=50/diolm=50/astlm=30"
$	qualifiers2 = qualifiers2 + "/tqelm=30/priv=(sysnam,detach,prmmbx)/def=(sysnam,detach,prmmbx)"
$!
$!
$!
$	gosub check_vms_version
$	gosub check_minimum_space
$	gosub setup_locations_and_logicals
$	gosub set_and_move_files
$	gosub check_system_resources
$	gosub build_gensym_modparams
$	gosub insert_gw_startup_call
$	gosub build_gw_user_account
$
$	@sys$startup:gw10-startup
$	type sys$input

	The following action items file was produced.  If the file
	is not empty (there are items to perform), you can type the
	file out and perform the actions manually or you can run the
	file when you are finished with VMSINSTAL.

	To type the file, from the "$" prompt, type
	$ type gw10$root:installation_action_items.com

	To perform the actions automatically, from the "$" prompt, type
	$ @gw10$root:installation_action_items

	**** NOTE: running the file will REBOOT YOUR MACHINE ****
	
$	type  'action_item_file_name'
$
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
$	vmi$callback check_net_utilization gw_test min_space
$	if .not. gw_test
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
$	if .not. gw_update_files
$	then
$	    vmi$callback ask gw_directory "GW directory" "''gw_device'[gw10]" D
$	endif
$
$
$	if f$parse(gw_directory) .eqs. ""
$	then
$	    create/directory/prot=(w:rwe)/owner=[200,100] 'gw_directory'
$           new_top_level_dir = 1
$	endif
$
$	define/nolog gw$root  'gw_directory'
$	return
$!
$!
$!
$	! Check if a GW is already present.  If so, find out
$	! if the user would like to just overwrite the existing directories
$	! (the default) or whether new directories are wanted.
$	!
$	setup_locations_and_logicals:
$
$ 	if f$trnlnm("gw10$root")  .nes. ""
$	then
$	    ! GW currently exists
$	    !
$	    vmi$callback ask gw_answer "Prior GW found - replace" "N" BD
$	    if .not. gw_answer
$	    then
$	        gosub get_directories
$	    else
$	        gw_update_files = 1
$		gw_directory = f$trnlnm("gw10$root")
$	        gosub get_directories
$	    endif
$	else
$	    gosub get_directories
$	endif
$	gw_directory     = f$trnlnm("gw$root")
$	return
$!
$!
$!
$	! Set the correct disk and paths in the gw-startup file and write
$	! this file to sys$startup.
$	!
$	write_gw_startup:
$
$	gw_device = f$parse("gw$root",,,"DEVICE")
$
$	open/read  gwkitstartup	 vmi$kwd:gw10-startup.com
$	open/write gwstartup     vmi$root:[sys$startup]gw10-startup.com
$
$	l6:
$	    read/end_of_file=end_l6 gwkitstartup line
$	    pos = f$locate("????", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + gw_device
$	    endif
$	    pos = f$locate("yyyy", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + gw_directory
$	    endif
$	    write gwstartup line
$	    goto l6
$	end_l6:
$
$	close gwkitstartup
$	close gwstartup
$	return
$!
$!
$!
$	! Move product files to gw$root directory:
$	!
$	set_and_move_files:
$
$	! First move in the DCL commands and HELP
$	!
$!	vmi$callback provide_dcl_command	gw.cld
$!	vmi$callback provide_dcl_help		gw.hlp
$
$	gw_root_tree = f$trnlnm("gw$root") - "]" + "...]"
$
$	gosub   write_gw_startup
$	copy	vmi$kwd:*.exe		gw$root:*
$	copy	vmi$kwd:*.gif		gw$root:*
$	copy	vmi$kwd:*.htm		gw$root:*
$	copy	vmi$kwd:*.kb     	gw$root:*
$
$	if gw_update_files
$	then
$	    purge 'gw_root_tree'
$	    purge vmi$root:[sys$startup]gw10-startup.com
$	endif
$	!
$	set file/protection=(s:rwed,o:rwed,g:rwe,w:re) 'gw_root_tree'*.*
$	set file/protection=(s:rwed,o:rwed,g:rwe,w:re)  vmi$root:[sys$startup]gw10-startup.com
$	return
$!
$!
$!
$	! Obtain the total pagefile space available to this system.
$	! The value is returned in ACTUAL_PAGEFILE
$	!
$	get_pagefile_size:
$
$	show memory/file/output='satellite_pagecom_name'
$	open/read sat_pagefile_com 'satellite_pagecom_name'
$	len = 0
$	actual_pagefile = 0
$	l1:
$	    read/end_of_file=end_l1 sat_pagefile_com line
$	    pos = f$locate("PAGEFILE", line)
$	    if pos .eq. f$length(line)
$	    then
$		goto l1
$	    else
$		! Found one, add its size to the total
$		!
$		line = f$edit(line, "TRIM")
$		startpos = 0
$		len = f$locate(" ", line) - startpos
$		line = f$extract(startpos, len, line)
$		len = f$locate(";", line) - startpos
$		pagefile_name = f$extract(startpos, len, line)
$		actual_pagefile = f$file_attributes(pagefile_name, "ALQ") + actual_pagefile
$		goto l1
$	    endif
$	end_l1:
$	close sat_pagefile_com
$	if len .eq. 0
$	then
$	    vmi$callback message e nopagefile "Cannot find pagefile!"
$	    exit vmi$failure
$	endif
$	delete 'satellite_pagecom_name';*
$	return
$!                                    
$!
$!
$	! Write out a current action item.  The item is in the global symbol
$	! ACTION, which must be set just prior to the call to this routine.
$	! This routine also assumes that the action item file is already
$	! for writing.  This SHOULD be a safe assumption as this routine
$	! should ONLY be called from CHECK_SYSTEM_RESOURCES.
$	!
$	write_action_item:
$
$	if gw_sys_resource_change
$	then
$	    action_count = action_count + 1
$	    write action_items action
$	    write action_items "$"
$	endif
$	return
$!
$!
$!
$	! Check system resources and build a new MODPARAMS.DAT file
$	! if necessary.  All resources are defined in the configuration
$	! section of this installation procedure.
$	!
$	check_system_resources:
$
$	! We will write an action item file for any installation wrapup details
$	! The file is gw$root:installation_action_items.com
$	!
$	open/write action_items 'action_item_file_name'
$
$	! Get current system numbers of interest to us
$	!
$	gosub get_pagefile_size
$	vmi$callback get_system_parameter actual_virpagecnt virtualpagecnt
$	vmi$callback get_system_parameter actual_wsmax      wsmax
$
$	! "Force" a minimum pagefile size
$	!
$	l7:
$	if actual_pagefile .lt. min_pagefile
$	then
$	    gw_sys_resource_change = 1
$	    sysgen == "$sysgen"
$	    msg1 = f$fao("Current = !SL, minimum = !SL, recommended = !SL", actual_pagefile, min_pagefile, best_pagefile)
$	    vmi$callback message w minpagefile -
		"Current PAGEFILE is below minimums" -
		"''msg1'"
$	    vmi$callback ask ask_pagefile "PAGEFILE size to use" 'best_pagefile ID
$	    actual_pagefile = ask_pagefile
$	    goto l7
$	else
$	    action = f$fao("$!! Increase pagefile size to !SL:", actual_pagefile)
$	    gosub write_action_item
$	    action = "$ sysgen := $sysgen"
$	    gosub write_action_item
$	    action = f$fao("$ sysgen create ''pagefile_name'/size=!SL", actual_pagefile)
$	    gosub write_action_item
$	endif
$
$	! Force a minimum WSMAX size
$	!
$	l2:
$	if actual_wsmax .lt. min_wsmax
$	then
$	    gw_sys_resource_change = 1
$	    msg1 = f$fao("Current = !SL, minimum = !SL, recommended = !SL", actual_wsmax, min_wsmax, suggested_wsmax)
$	    vmi$callback message w minwsmax -
		"Current WSMAX is below minimums" -
		"''msg1'"
$	    vmi$callback ask actual_wsmax "WSMAX size to use" 'min_wsmax ID
$	    goto l2
$	else
$	    modparams_wsmax = f$fao(modparams_wsmax, actual_wsmax)
$	endif
$
$	! Force a minimum VIRTUALPAGECNT
$	!
$	l3:
$	if actual_virpagecnt .lt. min_virpagecnt
$	then
$	    gw_sys_resource_change = 1
$	    msg1 = f$fao("Current = !SL, minimum = !SL, recommended = !SL", actual_virpagecnt, min_virpagecnt, good_pagefile)
$	    vmi$callback message w minwsmax -
		"Current VIRTUALPAGECNT is below minimums" -
		"''msg1'"
$ 	    vmi$callback ask actual_virpagecnt -
		"VIRTUALPAGECNT size to use" 'good_pagefile ID
$	    goto l3
$	else
$	    modparams_virpagecnt = f$fao(modparams_virpagecnt, actual_virpagecnt)
$	endif
$
$	if gw_sys_resource_change
$	then
$	    action = "$ rename SYS$SPECIFIC:[SYSEXE]GENSYM_MODPARAMS.DAT MODPARAMS.DAT"
$	    gosub write_action_item
$	    action = "$!! Run AUTOGEN from SYS$UPDATE:"
$	    gosub write_action_item
$	    action = "$ @AUTOGEN GETDATA REBOOT NOFEEDBACK"
$	    gosub write_action_item
$	endif
$
$	! Close the action item file
$	!
$	close action_items
$
$	return
$!
$!
$!
$	! Build GENSYM_MODPARAMS.DAT.  This is a concatenation of the
$	! existing MODPARAMS.DAT with our requirements for PAGEFILE, SWAPFILE,
$	! VIRTUALPAGECNT and WSMAX.
$	!
$	build_gensym_modparams:
$
$	if .not. gw_sys_resource_change
$	then
$	    ! No changes to write out!
$	    !
$	    return
$	endif
$
$	open/read  modparams	 vmi$specific:[sysexe]modparams.dat
$	open/write gen_modparams 'gen_modparams_name'
$
$	l4:
$	    read/end_of_file=end_l4 modparams line
$	    write gen_modparams line
$	    goto l4
$	end_l4:
$
$	close modparams
$
$	write gen_modparams "!   **** Start Gensym parameter values ****"
$	write gen_modparams "!"
$	write gen_modparams modparams_pagefile
$	write gen_modparams modparams_swapfile
$	write gen_modparams modparams_wsmax
$	write gen_modparams modparams_virpagecnt
$	write gen_modparams "!"
$	write gen_modparams "!   **** End Gensym parameter values ****"
$	
$	close gen_modparams
$	return
$!
$!
$!
$	! Place the call to the gw startup command procedure in the
$	! "proper" location.  This will either be in specific login.com
$	! files or sys$manager:sylogin.com.  The latter is recommended.
$	!
$	insert_gw_startup_call:
$
$	vmi$callback ask gw_answer "Place startup call in SYLOGIN.COM" "Y" BD
$	if gw_answer
$	then
$	    open/read  sylogin     vmi$root:[sysmgr]sylogin.com
$	    open/write newsylogin  vmi$root:[sysmgr]sylogin.com
$	    l5:
$		read/end_of_file=end_l5 sylogin line
$		write newsylogin line
$		goto l5
$	    end_l5:
$	    write newsylogin "$!
$	    write newsylogin "$      ! Set logicals for GW
$	    write newsylogin "$      !
$	    write newsylogin product_startup_line                      
$	    close sylogin
$	    close newsylogin
$	endif
$	return
$!
$!
$!
$	! Build a GW user account.  This account will have a correct
$	! set of quotas, privileges and permissions.
$	!
$	build_gw_user_account:
$
$	vmi$callback ask gw_answer "Create a GW user account" "Y" BD
$	if gw_answer
$	then
$	    ! Create an account...
$	    !
$	    if f$search("vmi$kwd:sysuaf.lis") .eqs. ""
$	    then
$		vmi$callback message i info "Ignore any -I- information messages"
$		set default vmi$kwd
$		define/user sysuaf 'f$parse("sysuaf","sys$system:.dat",,,"SYNTAX_ONLY")'
$		define/user netproxy 'f$parse("netproxy","sys$system:.dat",,,"SYNTAX_ONLY")'
$		gw_authorize = "$authorize"
$		gw_authorize list/brief
$	    endif
$
$	    vmi$callback ask account_name "Name of account" "GWUSER" D
$	    search sysuaf.lis 'account_name'/output=nl:
$	    if $status .eq. 1
$	    then
$		vmi$callback message e gwuser "''account_name' already exists"
$		goto build_gw_user_account
$	    endif
$	    
$	    vmi$callback ask account_uic  "UIC of account" "[200,110]" D
$	    search sysuaf.lis "''account_uic'"/output=nl:
$	    if $status .eq. 1
$	    then
$		vmi$callback message e gwuser "''account_uic' already exists"
$		goto build_gw_user_account
$	    endif
$
$ 	    vmi$callback ask account_pwd  "Password of account" "gensym" D
$
$	    qualifiers = f$fao(qualifiers, account_uic, account_pwd, account_wsquo, actual_wsmax, min_pagefile)
$
$	    gw_device = f$parse("gw$root",,,"DEVICE")
$	    gw_dir    = f$parse("gw$root",,,"DIRECTORY")
$	    qualifiers = qualifiers + "/dev=''gw_device'/dir=''gw_dir'"
$	    vmi$callback create_account "''account_name'" "''qualifiers'"
$	    vmi$callback update_account "''account_name'" "''qualifiers2'"
$
$	    if $status .eq. vmi$_failure                        
$	    then
$		vmi$callback message e gwuser "Unable to create GWUSER!"
$		goto build_gw_user_account
$	    else
$		set file/owner='account_name' 'gw_root_tree'*.*
$	    endif
$	else
$           if new_top_level_dir
$           then
$               type sys$input

	When the installation script is complete, you should set the
	ownership of the installed files appropriately.  Use
	the "set file/owner=" command to do this.  For example, if you have
       	installed the files in dka300:[gensym], type both of the following
       	commands, replacing <owner> with the account of your choice.
	$ set file/owner=<owner> dka300:[000000]gensym.dir
	$ set file/owner=<owner> dka300:[gensym...]*.*
$		vmi$callback ask user_answer "Press RETURN to acknowledge" "OK" D
$           endif
$	endif
$	return
$!
