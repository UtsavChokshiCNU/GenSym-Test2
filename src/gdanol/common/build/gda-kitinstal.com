$!********************************************************************
$!  Gensym KITINSTAL procedure:
$!
$!  PRODUCT: GDA Version 4.0 Rev. 1
$!
$!  LAST REVISED: 12-November-1999
$!
$!  DESCRIPTION:
$!    Each layered product is expected to supply two additional files:
$!    1. A file called APPL_FILES.DAT will contain the names of the 
$!	 software files to install.
$!    2. A file called HELP_FILES.DAT will contain the names of the 
$!	 help files to install.
$!**********************************************************************
$!
$! Setup error handling
$!
$  on control_y then vmi$callback control_y
$  on warning then exit $status
$!
$!*** Uncomment the following for KITINSTAL testing ***
$!  set verify
$!
$!Check against unhandled requests
$!
$  if p1 .eqs. "VMI$_INSTALL" 
$  then
$	gosub INSTALL_GDA
$	exit vmi$_success
$  endif
$!
$  if p1 .eqs. "VMI$_IVP"
$  then
$	gosub GDA_IVP
$	exit vmi$_unsupported
$  endif
$!
$  exit vmi$_unsupported
$!
$!*** Gensym-GDA Installation ***
$!
$ INSTALL_GDA:
$!
$!*** Product configuration constant & symbols ***
$!
$  Product = "Gensym-GDA V4.0 Rev. 1"
$  InstallMsg = "''Product' for VMS/OpenVMS on"
$  MinSpace = 50000
$  MinSpaceStg = "65000 blocks, with temporary peak of 50000"
$  MachineType = f$getsyi ("arch_type")
$!
$  if MachineType .eq. 1	!*** VAX/VMS *** 
$  then
$	MinVersion = "062"
$	InstallMsg = InstallMsg + "VAX"
$	MinRam = 64	  
$  else				!*** Open VMS ***
$	MinVersion = "062"
$	InstallMsg = InstallMsg + "Alpha AXP"
$	MinRam = 128
$  endif
$!
$  vmi$callback MESSAGE i info "''InstallMsg'" 
$  vmi$callback SET purge yes	!*** Purge any superceded files ***
$!  vmi$callback SET ivp yes	!*** If IVP uncomment this ***
$!
$  gosub CHECK_VMS_VERSION
$  gosub CHECK_SPACE
$  gosub SET_LOCATIONS
$  gosub MOVE_FILES
$  gosub GIVE_ADVICE
$  return
$!
$ CHECK_VMS_VERSION:
$!
$! We only run on VMS MinVersion or later
$!
$  if f$extr(0, 3, f$element(1, ",", vmi$vms_version)) .lts. MinVersion
$  then 
$	MinVerName = "V" + f$extract(1, 1, MinVersion) + "."
$       MinVerName = MinVerName + f$extract(2, 2, MinVersion)
$	vmi$callback MESSAGE e version -
	  "''Product' requires VMS version ''MinVerName' or later"
$	exit vmi$_failure
$  endif
$!
$  return
$!
$!*** Check for minimum space requirements ***
$!
$ CHECK_SPACE:
$!
$  vmi$callback CHECK_NET_UTILIZATION SpaceTest MinSpace
$!
$  if .not. SpaceTest
$  then
$	vmi$callback MESSAGE e nospace -
	  "System disk has insufficient space to install ''Product'" -
	  "Installation requires ''MinSpace' blocks"
$	exit vmi$failure
$  endif
$!
$  return                                         
$!
$ SET_LOCATIONS:
$!
$  if f$trnlnm ("g251$dir") .nes. ""
$  then
$    vmi$callback ASK GDAanswer "Use existing G2 directory tree" "N" BD
$    if GDAanswer
$    then
$      GDAdirectory = f$trnlnm ("g251$dir")
$      GDAdefault = GDAdirectory - "]" + ".gda_40r1]"
$    else
$      GDAdevice = f$trnlnm("sys$sysdevice")
$      GDAdirectory = "[gda_40r1]"
$      GDAdefault = GDAdevice + GDAdirectory
$    endif
$  endif
$!
$  gosub GET_DIRECTORIES
$  return
$!
$!*** Ask user for installation directories ***
$!
$ GET_DIRECTORIES:
$!
$  vmi$callback ASK GDApath -
     "Please enter the directory for the GDA software" "''GDAdefault'" D
$!
$  if f$parse (GDApath) .eqs. ""
$  then
$	create/directory/prot=(w:rwe) 'GDApath'
$	write sys$output "Created directory: ''GDApath'"
$  endif
$  define/proc/nolog appl$dir "''GDApath'"
$!
$  vmi$callback ASK HelpWanted -
       "Install Help files Y/N" "Y" BD
$  if HelpWanted
$  then
$    HelpDirectory = GDApath - "]" + ".gdadoc]"
$    if f$parse(HelpDirectory) .eqs. ""
$    then
$       create/directory/prot=(w:rwe) 'HelpDirectory'
$       write sys$output "Created directory: ''HelpDirectory'"
$    endif
$    define/proc/nolog gdahelp$dir "''HelpDirectory'"
$  endif
$!
$  return
$!
$!*** Move files to their target directories
$!
$ MOVE_FILES:
$!
$  write sys$output ""
$  write sys$output "Copying GDA application files..."
$  vmi$callback PROVIDE_FILE "" appl_files.dat "" T
$!
$  if HelpWanted
$  then
$    write sys$output "Copying Help files..."
$    vmi$callback PROVIDE_FILE "" help_files.dat "" T
$  endif
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
     "1. GDA Version 4.0 Rev. 1 requires G2 Version 5.1 Rev. 3"
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
$! When we get an IVP, build this section
$!
$ GDA_IVP:
$  return
$!

