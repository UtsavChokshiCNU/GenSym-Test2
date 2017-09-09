$!	Gensym KITINSTAL procedure:
$!
$!	PRODUCT:	G2 5.*
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
$	    gosub g2_install
$!	    set noverify
$	    exit  vmi$_success
$	else
$	    ! When we get an IVP, build this section
$	    !
$	    !gosub g2_ivp
$	    exit vmi$_unsupported
$	endif
$!
$!
$!
$!
$!	*** G2 Installation ***
$!
$ G2_INSTALL:
$!
$	if f$getsyi("arch_type") .eq. 1      ! 1 for VAX and 2 for AXP
$	then
$		vmi$callback message i info "Gensym G2 5.1 for VAX VMS/OpenVMS"
$	else
$		vmi$callback message i info "Gensym G2 5.1 for Alpha AXP OpenVMS"
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
$		minimum_version		= "062"
$		min_space		= 35000
$		min_space_stg		= "35000 blocks, with temporary peak of 70000"
$
$		min_pagefile		= 100000 ! 50 MB
$		min_virpagecnt		= 90000  ! 45 MB
$		min_wsmax		= 16400  !  8 MB
$		best_pagefile		= 150000 ! 75 MB
$		good_pagefile		= 120000 ! 60 MB
$		suggested_wsmax		= 26600  ! 13 MB
$		account_wsquo		= 10240  !  5 MB
$	else
$		! Alpha AXP
$		minimum_version		= "062"
$		min_space		= 40000
$		min_space_stg		= "40000 blocks, with temporary peak of 80000"
$
$		min_pagefile		= 150000 !  75 MB
$		min_virpagecnt		= 120000 !  60 MB
$		min_wsmax		= 21500  !  11 MB
$		best_pagefile		= 250000 ! 125 MB
$		good_pagefile		= 200000 ! 100 MB
$		suggested_wsmax		= 32800  !  16 MB
$		account_wsquo		= 14000  !   7 MB
$	endif
$
$	product 		= "G2 5.1"
$	g2_device		= f$trnlnm("sys$sysdevice")
$	product_startup_line	= "$      @sys$startup:g250-startup"
$
$	pagefile_name		= "vmi$specific:[sysexe]pagefile.sys"
$	satellite_pagecom_name	= "vmi$kwd:g2showmem.txt"
$	action_item_file_name	= "g2$root:installation_action_items.com"
$	gen_modparams_name	= "vmi$specific:[sysexe]gensym_modparams.dat"
$
$	g2_update_files		= 0
$	new_top_level_dir	= 0
$	g2_sys_resource_change  = 0
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
$	gosub insert_g2_startup_call
$	gosub build_g2_user_account
$
$	@sys$startup:g250-startup
$	type sys$input

	The following action items file was produced.  If the file
	is not empty (there are items to perform), you can type the
	file out and perform the actions manually or you can run the
	file when you are finished with VMSINSTAL.

	To type the file, from the "$" prompt, type
	$ type g251$dir:installation_action_items.com

	To perform the actions automatically, from the "$" prompt, type
	$ @g251$dir:installation_action_items

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
$	vmi$callback check_net_utilization g2_test min_space
$	if .not. g2_test
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
$	if .not. g2_update_files
$	then
$	    vmi$callback ask g2_directory "G2 directory" "''g2_device'[g251]" D
$	endif
$
$	g2_ext_dir = g2_directory - "]" + ".ext]"
$	g2_fonts_dir = g2_directory - "]" + ".fonts]"
$
$	if f$parse(g2_directory) .eqs. ""
$	then
$	    create/directory/prot=(w:rwe)/owner=[200,100] 'g2_directory'
$	    new_top_level_dir = 1
$	endif
$	if f$parse(g2_ext_dir) .eqs. ""
$	then
$	    create/directory/prot=(w:rwe) 'g2_ext_dir'
$	endif
$	if f$parse(g2_fonts_dir) .eqs. ""
$	then
$	    create/directory/prot=(w:rwe) 'g2_fonts_dir'
$	endif
$
$	define/nolog g2$root  'g2_directory'
$	define/nolog g2$ext   'g2_ext_dir'
$	define/nolog g2$fonts 'g2_fonts_dir'
$	return
$!
$!
$!
$	! Check if a G2 is already present.  If so, find out
$	! if the user would like to just overwrite the existing directories
$	! (the default) or whether new directories are wanted.
$	!
$	setup_locations_and_logicals:
$
$	if f$trnlnm("g251$dir")  .nes. ""
$	then
$	    ! G2 currently exists
$	    !
$	    vmi$callback ask g2_answer "Prior G2 found - replace" "N" BD
$	    if .not. g2_answer
$	    then
$	        gosub get_directories
$	    else
$	        g2_update_files = 1
$		g2_directory = f$trnlnm("g251$dir")
$	        gosub get_directories
$	    endif
$	else
$	    gosub get_directories
$	endif
$	g2_directory     = f$trnlnm("g2$root")
$	return
$!
$!
$!
$	! Set the correct disk and paths in the g2-startup file and write
$	! this file to sys$startup.
$	!
$	write_g2_startup:
$
$	g2_device = f$parse("g2$root",,,"DEVICE")
$
$	open/read  g2kitstartup	 vmi$kwd:g250-startup.com
$	open/write g2startup     vmi$root:[sys$startup]g250-startup.com
$
$	l6:
$	    read/end_of_file=end_l6 g2kitstartup line
$
$	    pos = f$locate("????", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + g2_device
$	    endif
$
$	    pos = f$locate("xxxx", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + g2_root_tree - ".." + "/tran=con"
$	    endif
$
$	    pos = f$locate("yyyy", line)
$	    if pos .ne. f$length(line)
$	    then
$		line = f$extract(0, pos, line) + g2_root_tree - "..."
$	    endif
$
$	    write g2startup line
$	    goto l6
$	end_l6:
$
$	close g2kitstartup
$	close g2startup
$	return
$!
$!
$!
$	! Move product files to correct directories:
$	!
$	! Most files are allocated to directories by suffix,
$       ! but g2.exe and overlay.exe (and all .exe files) are treated 
$       ! specially.
$	!
$	set_and_move_files:
$
$	! First move in the DCL commands and HELP
$	!
$!	vmi$callback provide_dcl_command	g2.cld
$!	vmi$callback provide_dcl_help		g2.hlp
$!	vmi$callback provide_dcl_help		gsi.hlp
$
$	g2_root_tree = f$trnlnm("g2$root") - "]" + "...]"
$
$	gosub   write_g2_startup
$	copy	vmi$kwd:g2.exe		g2$root:*
$	copy	vmi$kwd:g2passwd.exe	g2$root:*
$	copy	vmi$kwd:*.ok,*.dic	g2$root:*
$	copy	vmi$kwd:overlay.exe	g2$ext:*
$	copy	vmi$kwd:*.olb,*.h	g2$ext:*
$	copy	vmi$kwd:*.gb		g2$fonts:*
$	copy	vmi$kwd:*.spd		g2$fonts:*
$       backup/select=[saveset...] vmi$kwd:kbs.sav/save 'g2_root_tree'
$
$	if g2_update_files
$	then
$	    purge 'g2_root_tree'
$	    purge vmi$root:[sys$startup]g250-startup.com
$	endif
$	!
$	set file/protection=(s:rwed,o:rwed,g:rwe,w:re) 'g2_root_tree'*.*
$	set file/protection=(s:rwed,o:rwed,g:rwe,w:re)  vmi$root:[sys$startup]g250-startup.com
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
$	if g2_sys_resource_change
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
$	! The file is g2$root:installation_action_items.com
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
$	    g2_sys_resource_change = 1
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
$	    g2_sys_resource_change = 1
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
$	    g2_sys_resource_change = 1
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
$	if g2_sys_resource_change
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
$	if .not. g2_sys_resource_change
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
$	! Place the call to the g2 startup command procedure in the
$	! "proper" location.  This will either be in specific login.com
$	! files or sys$manager:sylogin.com.  The latter is recommended.
$	!
$	insert_g2_startup_call:
$
$	vmi$callback ask g2_answer "Place startup call in SYLOGIN.COM" "Y" BD
$	if g2_answer
$	then
$	    open/read  sylogin     vmi$root:[sysmgr]sylogin.com
$	    open/write newsylogin  vmi$root:[sysmgr]sylogin.com
$	    l5:
$		read/end_of_file=end_l5 sylogin line
$		write newsylogin line
$		goto l5
$	    end_l5:
$	    write newsylogin "$!
$	    write newsylogin "$      ! Set logicals for G2/GSI/TW
$	    write newsylogin "$      !
$	    write newsylogin product_startup_line                      
$	    close sylogin
$	    close newsylogin
$	endif
$	return
$!
$!
$!
$	! Build a G2 user account.  This account will have a correct
$	! set of quotas, privileges and permissions.
$	!
$	build_g2_user_account:
$
$	vmi$callback ask g2_answer "Create a G2 user account" "Y" BD
$	if g2_answer
$	then
$	    ! Create an account...
$	    !
$	    if f$search("vmi$kwd:sysuaf.lis") .eqs. ""
$	    then
$		vmi$callback message i info "Ignore any -I- information messages"
$		set default vmi$kwd
$		define/user sysuaf 'f$parse("sysuaf","sys$system:.dat",,,"SYNTAX_ONLY")'
$		define/user netproxy 'f$parse("netproxy","sys$system:.dat",,,"SYNTAX_ONLY")'
$		g2_authorize = "$authorize"
$		g2_authorize list/brief
$	    endif
$
$	    vmi$callback ask account_name "Name of account" "G2USER" D
$	    search sysuaf.lis 'account_name'/output=nl:
$	    if $status .eq. 1
$	    then
$		vmi$callback message e g2user "''account_name' already exists"
$		goto build_g2_user_account
$	    endif
$	    
$	    vmi$callback ask account_uic  "UIC of account" "[200,100]" D
$	    search sysuaf.lis "''account_uic'"/output=nl:
$	    if $status .eq. 1
$	    then
$		vmi$callback message e g2user "''account_uic' already exists"
$		goto build_g2_user_account
$	    endif
$
$ 	    vmi$callback ask account_pwd  "Password of account" "gensym" D
$
$	    qualifiers = f$fao(qualifiers, account_uic, account_pwd, account_wsquo, actual_wsmax, min_pagefile)
$
$	    g2_device = f$parse("g2$root",,,"DEVICE")
$	    g2_dir    = f$parse("g2$root",,,"DIRECTORY")
$	    qualifiers = qualifiers + "/dev=''g2_device'/dir=''g2_dir'"
$
$	    on warning then goto account_create_error
$	    vmi$callback create_account "''account_name'" "''qualifiers'"
$	    vmi$callback update_account "''account_name'" "''qualifiers2'"
$
$	    if $status .eq. vmi$_failure                        
$	    then
$		account_create_error:
$		on warning then exit $status
$		vmi$callback message e g2user "Unable to create G2USER!"
$		goto build_g2_user_account
$	    else
$		on warning then exit $status
$		set file/owner='account_name' 'g2_root_tree'*.*
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
