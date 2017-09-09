$!********************************************************************
$! Gensym KITINSTAL procedure:
$!
$! PRODUCT: Gensym-NOL Version 4.0 Revision 1
$!
$! LAST REVISED: 12-November-1999
$!
$! DESCRIPTION:
$!   Each layered product is expected to supply two additional files
$!   for this procedure to use:
$!   1. A file alled APPL_FILES.DAT will contain the names of the
$!	software files to install.
$!   2. A file call HELP_FILES.DAT will contain the names of the
$!	help files to install.
$!*******************************************************************
$!
$!*** Setup error handling ***
$!
$  on control_y then vmi$callback control_y
$  on warning then exit $status
$!
$!*** Uncomment the following for KITINSTAL testing ***
$!  set verify
$!
$!*** Check against unhandled requests ***
$!
$  if p1 .eqs. "VMI$_INSTALL"
$  then
$	gosub INSTALL_NOL
$	exit vmi$_success
$  endif
$!
$  if p1 .eqs. "VMI$_IVP"
$  then
$	gosub NOL_IVP
$	exit vmi$_unsupported
$  endif
$!
$  exit vmi$_unsupported
$!
$!*** Gensym-NOL Installation ***
$!
$ INSTALL_NOL:
$!
$!*** Product configuration constants ***
$!
$  Product = "Gensym-NOL V4.0 Rev. 1"
$  InstallMsg = "''Product' for VMS/OpenVMS on"
$  MinSpace = 50000
$  MinSpaceStg = "50000 blocks, with temporary peak of 65000"
$  NOLdevice = f$trnlnm("sys$sysdevice")
$  MachineType = f$getsyi("arch_type")
$!
$  if MachineType .eq. 1
$  then
$	MinVersion = "062"
$	InstallMsg = InstallMsg + "VAX"
$	MinRam = 64
$  else
$	MinVersion = "062"
$	InstallMsg = InstallMsg + "Alpha AXP"
$	MinRam = 128
$  endif
$!
$  vmi$callback MESSAGE i info "''InstallMsg'"
$! 
$  vmi$callback SET purge yes	!*** Purge any superceded files ***
$!  vmi$callback SET ivp yes	!*** If IVP uncomment this ***	
$!
$  UpdateFiles = 0
$!
$  gosub CHECK_VMS_VERSION
$  gosub CHECK_SPACE
$  gosub SET_LOCATIONS
$  gosub MOVE_FILES
$  gosub GIVE_ADVICE
$!
$!*** Execute the startup procedure & exit***
$  @sys$startup:nolstart	
$  return
$!
$!*** Check if we are compatible with this version of VMS ***
$!     
$ CHECK_VMS_VERSION:
$!
$!*** We only run on VMS min_version or later ***
$!
$  if f$extr(0, 3, f$element(1, ",", vmi$vms_version)) .lts. MinVersion
$  then
$	MinVerName = "V" + f$extract(1, 1, MinVersion) + "."
$	MinVerName = MinVerName + f$extract(2, 2, MinVersion)
$	vmi$callback message e version -
	  "''Product' requires VMS version ''MinVerName' or later"
$	exit vmi$_failure
$  endif
$  return
$!
$!*** Check for minimum space requirements ***
$!
$ CHECK_SPACE:
$!
$  vmi$callback CHECK_NET_UTILIZATION NOLtest MinSpace
$  if .not. NOLtest
$  then
$    vmi$callback MESSAGE e nospace -
	"System disk has insufficient space to install ''Product'" -
	"Installation requires ''MinSpaceStg' blocks"
$    exit vmi$_failure
$  endif
$  return                                         
$!
$! Check if a Gensym-NOL is already present.  If so, find out
$! if the user would like to just overwrite the existing directories
$! (the default) or whether new directories are wanted.
$!
$ SET_LOCATIONS:
$!
$  if f$trnlnm ("g251$dir") .nes. ""
$  then
$    vmi$callback ASK NOLanswer "Use existing G2 directory tree" "N" BD
$    if NOLanswer
$    then
$      NOLdirectory = f$trnlnm ("g251$dir")
$      NOLdefault = NOLdirectory - "]" + ".nol_40r1]"
$    else
$      NOLdevice = f$trnlnm ("sys$sysdevice")
$      NOLdirectory = "[nol_40r1]"
$      NOLdefault = NOLdevice + NOLdirectory
$    endif
$  endif
$!
$  if f$trnlnm("gensym_nol$dir") .nes. ""
$  then		!*** Gensym-NOL currently exists ***
$	vmi$callback ASK NOLquery -
	    "Prior Gensym-NOL found - replace" "N" BD
$	if NOLquery
$	then
$	    UpdateFiles = 1
$	    NOLdefault = f$trnlnm("gensym_nol$dir")
$	endif
$  endif
$  gosub GET_DIRECTORIES
$  NOLpath = f$trnlnm("gensym_nol$dir")
$  return
$!
$!*** Ask user for any installation directories ***
$!
$ GET_DIRECTORIES:
$!
$  vmi$callback ASK NOLpath -
     "Please enter the directory for the NOL software" "''NOLdefault'" D
$!
$  if f$parse(NOLpath) .eqs. ""
$  then
$	create/directory/prot=(w:rwe) 'NOLpath'
$	write sys$output "Created directory: ''NOLpath'"
$  endif
$!
$  NOLscratch = NOLpath - "]" + ".tmp]"
$  if f$parse(NOLscratch) .eqs. ""
$  then
$	create/directory/prot=(w:rwe) 'NOLscratch'
$	set directory/version=5 'NOLscratch'
$	write sys$output "Created directory: ''NOLscratch'"
$  endif
$  define/nolog gensym_nol$dir 'NOLpath'
$  define/proc/nolog appl$dir 'NOLpath'
$!
$  vmi$callback ASK HelpWanted -
       "Install Help files Y/N" "Y" BD
$  if HelpWanted
$  then
$    HelpDirectory = NOLpath - "]" + ".noldoc]"
$    if f$parse(HelpDirectory) .eqs. ""
$    then
$	create/directory/prot=(w:rwe) 'HelpDirectory'
$	write sys$output "Created directory: ''HelpDirectory'"
$    endif
$    define/proc/nolog nolhelp$dir "''HelpDirectory'"
$  endif
$!
$  return
$!
$!*** Move product files to correct directories ***
$!
$ MOVE_FILES:
$!
$  NOLRootTree = f$trnlnm("gensym_nol$dir") - "]" + "...]"
$!
$  set noon
$  write sys$output ""
$  write sys$output "Copying NOL application files..."
$  vmi$callback PROVIDE_FILE "" appl_files.dat "" T
$!
$  if HelpWanted
$  then
$    write sys$output "Copying Help files..."
$    vmi$callback PROVIDE_FILE "" help_files.dat "" T
$  endif
$  gosub SET_STARTUP
$  set on
$!
$  if UpdateFiles
$  then
$	purge 'NOLRootTree'
$	purge vmi$root:[sys$startup]nolstart.com
$  endif
$!
$  set file/protection=(s:rwed,o:rwed,g:rwe,w:rwe) 'NOLRootTree'*.*
$  set file/protection=(s:rwed,o:rwed,g:rwe,w:re) -
	vmi$root:[sys$startup]nolstart.com
$  return
$!
$!*********************************************************************
$! Place the call to the Gensym-NOL startup command procedure,
$! nolstartup.com, in the "proper" location.  This will either be in
$! specific login.com files or sys$startup:g250-startup.com.  
$! The latter is recommended.
$!*********************************************************************
$!
$ SET_STARTUP:
$  gosub UPDATE_STARTUP_FILE
$  gosub INSERT_STARTUP_CALL
$  return
$!
$!*** Set the correct disk and paths in the nol-startup ***
$    !*** file (nolstart) and write this file to sys$startup ***
$!
$ UPDATE_STARTUP_FILE:
$!
$  NOLdevice = f$parse("gensym_nol$dir",,,"DEVICE")
$!
$  open/read OldStartup vmi$kwd:nolstart.com
$  open/write NewStartup vmi$root:[sys$startup]nolstart.com
$!
$ WRITE_LOOP:
$!
$  read/end_of_file=END_WRITE_LOOP OldStartup Line
$!
$  Pos = f$locate("##dev##", Line)
$  if Pos .ne. f$length(Line)
$  then
$	Line = f$extract(0, Pos, Line) + NOLdevice
$  endif
$!
$  Pos = f$locate("##dir##", Line)
$  if Pos .ne. f$length(Line)
$  then
$	Line = f$extract(0, Pos, Line) + NOLRootTree - "..."
$  endif
$!
$  Pos = f$locate("##tmp##", Line)
$  if Pos .ne. f$length(Line)
$  then
$	Line = f$extract(0, Pos, Line) + NOLscratch
$  endif
$!
$  write NewStartup Line
$  goto WRITE_LOOP
$!
$ END_WRITE_LOOP:
$!
$  close OldStartup
$  close NewStartup
$  return
$!
$ INSERT_STARTUP_CALL:
$!
$  ComFile = f$search("vmi$root:[sys$startup]g250-startup.com")
$  if ComFile .eqs. "" then -
	ComFile = "vmi$root:[sysmgr]sylogin.com"
$  ComFile = f$extract(0, f$locate(";", ComFile), ComFile)
$!
$!*** Make sure NOL startup has not already been added ***
$!*** to g250-startup; Add if necessary ***
$!
$ search/nowarn/nooutput vmi$root:[sys$startup]g250-startup.com -
	"@sys$startup:nolstart"
$ if $status .EQ. 1 then -
	return
$!
$!*** NOL startup has not been added so add it ***
$!
$  open/read OldG2Startup 'ComFile'
$  open/write NewG2Startup 'ComFile'
$!
$ APPEND_LOOP:
$!
$  read/end_of_file=END_APPEND_LOOP OldG2Startup Line
$!
$  Pos = f$locate("exit", Line)
$  if Pos .ne. f$length(Line)
$  then
$	goto END_APPEND_LOOP
$  else
$	write NewG2Startup Line
$	goto APPEND_LOOP
$  endif
$!
$ END_APPEND_LOOP:
$!
$  write NewG2Startup "$!"
$  write NewG2Startup "$      !*** Set logicals for Gensym-NOL ***"
$  write NewG2Startup "$      !"
$  write NewG2Startup "$      @sys$startup:nolstart"
$  close OldG2Startup
$  close NewG2Startup
$!
$  write sys$output ""
$  write sys$output "Inserted NOL Startup Command in ''ComFile'"
$  write sys$output ""
$!
$  return
$!
$ GIVE_ADVICE:	
$!
$  write sys$output ""
$  write sys$output -
	"**************************************************************"
$  write sys$output -
        "  Please note that:"
$  write sys$output ""
$  write sys$output -
        "1. NOL Version 4.0 Rev. 1 requires G2 Version 5.1 Rev. 3"
$  write sys$output ""
$  write sys$output -
	"2. Gensym recommends a minimum of ''MinRam' Megabytes of memory"
$  write sys$output ""
$  write sys$output -
	"3. The SYSGEN parameter WSMAX can cause premature swapping"
$  write sys$output "   if set too low"
$  write sys$output -
        "**************************************************************"
$  write sys$output ""
$!
$  return
$!
$!*** EXECUTE THE IVP ***
$!
$ NOL_IVP:
$  return
$!
