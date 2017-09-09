$! promote-product.com
$! Author: Mike Colena
$!    Based loosely on promote-product by Mike Colena
$!
$! @promote-product -i <product> <machine-id> <source-dir> <release-id> [-NOCONFIRM]
$! @promote-product -e <product> <machine-id> <internal-id> <external-id> [<spin-id>]
$!
$! This script is used for promoting machine dependent products into the
$! directories visible within the [gensym.ut] directories on VMS
$! machines.  This is the place where testing of products should occur.
$!
$! The script is also used to copy VMS products from the testing machines to the
$! production machine (the eship machine).  That machine called PROD.  This
$! file is copied into the dist$com directory there from its home in
$! /gensym/tools/vms.
$!
$! See additional comments at the bottom of the file.
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$ MAIN:
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!
$! Initialization
$! --------------
$!
$    status = 0
$    builduser = "ship"
$    buildsandbox = "ship"
$    st_root = "gensym.st.ab"
$    alpha_machine = "IRAQ"
$    vax_machine   = "UGANDA"
$    eship_machine = "PROD"
$!
$! Parse Arguments
$! ---------------
$!
$    if p5 .eqs. "" then goto USAGE
$!
$    if p7 .nes. "" then goto USAGE
$!
$! Determine if its Iship or Eship
$!
$    if (p1 .eqs. "-I")
$    then
$        eship = 0
$    else
$      if  (p1 .eqs. "-E") .or. (p1 .eqs. "-TEST")
$      then
$        eship = 1
$      endif
$    endif
$!
$! Parse and validate the product argument.
$!
$    product = p2
$    if product .nes. "G2" .and. product .nes. "TW" .and. product .nes "GSI"
$    then
$      write sys$output "ERROR: Unknown product: ''product'. Must be g2, tw, or gsi"
$      status = 2
$      goto EXIT
$    endif
$!
$! Parse and validate the Machine-Id argument.
$!
$    machine_id = p3
$
$    if machine_id .nes. "VAX" .and. machine_id .nes. "ALPHAVMS"
$    then
$      write sys$output "ERROR: Unknown machine-id ''machine_id'. Must be vax or alphavms"
$      status = 2
$      goto EXIT
$    endif
$!
$! Parse the Source
$!
$   if eship
$   then
$     release_source = p4
$   else
$     source_dir = p4
$   endif
$!
$! Parse the Release ID
$! We should try to validate these in the future, but for now, they are whatever
$! the user puts in.  -jra 9/9/92
$!
$   release_id = p5
$!
$   if eship then goto ESHIP
$!
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$ ISHIP:
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!
$   ship_name          = "Internal"
$   test_dir           = "ut$disk:[gensym.ut.dev]"
$   tape_dir           = "ut$disk:[''st_root'.iship]"
$   product_id         = "''product'-''release_id'"
$   product_test       = "''test_dir'" -"]" +".''product_id']"
$   product_tape       = "''tape_dir'" +"''product_id'.bck"
$   backup_source      = "''source_dir'" -"]" + "...]"
$   backup_target_test = "''product_test'" -"]" +"...]"
$   backup_target_tape = "''product_tape'/sav"
$!
$! Check if the source exists
$!
$    file = f$search("''backup_source'*.*;*")
$    if file .eqs. ""
$    then
$       write sys$output  "WARNING: ''source_dir' does not exist."
$    endif
$!
$! Stop if the tape target already exists.
$!
$    file = f$search("''product_tape'")
$    if file .nes. ""
$    then
$       write sys$output  "ERROR: the directory to be created, ''product_tape',  already exists."
$       write sys$output  "   To remove it, use @remove-product -i ''product' ''release_id' ''machine_id'"
$       status = 2
$       goto EXIT
$    endif
$!
$! Stop if the test target already exists.
$!
$    file = f$search("''test_dir'''product_id'.dir")
$    if file .nes. ""
$    then
$       write sys$output  "ERROR: the directory to be created, ''product_test',  already exists."
$       status = 2
$       goto EXIT
$    endif
$!
$! Echo back to user and give him a chance to kill it.
$!
$    write sys$output  ""
$    write sys$output  "LOG: Promoting Machine Dependent Product for ''ship_name' Shipment"
$    write sys$output  "  Product:                  ''product'"
$    write sys$output  "  Release Id:               ''release_id'"
$    write sys$output  "  Machine Type:             ''machine_id'"
$    write sys$output  "  Product Directory:        ''source_dir'"
$    write sys$output  "  Target Directory (tape):  ''backup_target_tape'"
$    write sys$output  "  Target Directory (test):  ''product_test'"
$    write sys$output  ""
$!
$! Confirm with user
$!
$    if p6 .eqs. "-NOCONFIRM" then goto PROMOTE_ISHIP
$!
$    inquire answer "  Are you sure you want to promote this product? (y[es] or n[o])"
$    if .not. answer
$    then
$      write sys$output  "Abandoning promotion and exiting."
$      status = 2
$      goto EXIT
$    endif
$!
$!      We promote to both tape and test directory
$!
$!      mpc 05/27/94, To make copying the tape dir easier from iship to eship
$!      and between distribution and ab, we'll create a iship tape save set
$!      instead of a directory.  In the future we should copy it to eship and
$!      leave it a save set.
$!
$ PROMOTE_ISHIP:
$!
$   write sys$output  "LOG: Promoting ''product_id'..."
$   write sys$output  ""
$   backup 'backup_source 'backup_target_tape/log
$   write sys$output "LOG: Promotion to tape complete, promoting to test."
$   write sys$output  ""
$   backup 'backup_source 'backup_target_test/log
$!
$   goto EXIT
$!
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$ ESHIP:
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!
$! Parse the Spin ID, if given.
$!
$   if p6 .eqs. ""
$   then
$      spin_id = builduser
$   else
$      spin_id = p6
$   endif
$!
$! Before the introduction of the following if-then-else, this script
$! could not be used to promote GSI 3.2, because the script assumed
$! that "product" came from [bt.ab."product".tape].  This is a big-time
$! hack to temporarily allow GSI 3.2 to be promoted.  We need to find
$! a better solution, however.
$!
$   if release_id .eqs. "32R2"
$   then
$      select = "[bt.''spin_id'.ext.tape.''product'...]"
$   else
$      select = "[''spin_id'.dst.''machine_id'.''product'.tape...]"
$   endif
$!
$! Since the eship location is the same for both vms and alphavms, we
$! must distinguish between the two. Therefore the AlphaVMS product_id
$! will be prefixed with "alpha".  We also need to distinguish between
$! them so that we know which machine to get the files from.
$!
$   if machine_id .eqs. "ALPHAVMS"
$   then
$      alpha = 1
$      product_id = "alpha''product'''release_id'"
$      source_machine = "''alpha_machine'"
$   else
$      alpha = 0
$      product_id = "''product'''release_id'"
$      source_machine = "''vax_machine'"
$   endif
$!
$   ship_name          = "External"
$   iship_tape_dir     = "ut$disk:[''st_root'.iship]"
$   source_id          = "''product'-''release_source'"
$   source_bck         = "''iship_tape_dir'" +"''source_id'.bck"
$!
$   host_name = f$getsyi("nodename")
$   if host_name .eqs. eship_machine
$   then
$      backup_source      = "''source_machine'::''source_bck'/sav"
$      tape_dir           = "dist$disk:[usr.distribution.bridges]"
$   else
$      if p1 .eqs. "-TEST"
$      then
$         backup_source      = "''source_bck'/sav"
$         tape_dir           = "btdisk:[gensym.ut]"
$      else
$         write sys$output "ERROR: Sorry, you cannot promote to eship from this machine."
$         write sys$output "       You must use machine ''eship_machine'."
$         status = 2
$         goto EXIT
$      endif
$   endif
$!
$   product_tape       = "''tape_dir'" -"]" +".''product_id']"
$   backup_target_tape = "''product_tape'" -"]" +"...]"
$!
$! Since the save set is on a different machine, we cannot easily check for its existence.
$! The following commented out lines are how we sould do it.
$!
$!    file = f$search("''source_bck'")
$!    if file .eqs. ""
$!    then
$!       write sys$output  "ERROR: ''source_bck' does not exist or isn't a save set."
$        status = 2
$!       goto EXIT
$!    endif
$!
$! Stop if the target already exists.
$!
$    file = f$search("''tape_dir'''product_id'.dir")
$    if file .nes. ""
$    then
$       write sys$output  "ERROR: the directory to be created, ''product_tape',  already exists."
$       write sys$output  "   To remove it, use @remove-product -e ''product' ''release_id' ''machine_id'"
$       status = 2
$       goto EXIT
$    endif
$!
$! echo back to user and give him a chance to kill it.
$!
$    write sys$output  ""
$    write sys$output  "LOG: Promoting Machine Dependent Product for ''ship_name' Shipment"
$    write sys$output  "  Product:                  ''product'"
$    write sys$output  "  Release Id:               ''release_id'"
$    write sys$output  "  Machine Type:             ''machine_id'"
$    write sys$output  "  Source Backup Save Set:   ''backup_source'"
$    write sys$output  "  Target Directory (tape):  ''product_tape'"
$    write sys$output  "  Selecting Files From:     ''select'"
$    write sys$output  ""
$!
$    inquire answer "  Are you sure you want to promote this product? (y[es] or n[o])"
$    if .not. answer
$    then
$      write sys$output  "Abandoning promotion and exiting."
$      status = 2
$      goto EXIT
$    else
$      write sys$output  "LOG: Promoting ''product_id'..."
$      write sys$output  ""
$    endif
$!
$! Make the target directory and extract the files into it.
$!
$    create/dir 'product_tape
$    backup/select='select  'backup_source 'backup_target_tape/log
$!
$! Perform a little maintenance work to prepare the directory for external shipment
$!
$   parts_list  = "''product_tape'parts.list;*"
$   parts_list_search = f$search("''parts_list'")
$   if parts_list_search .nes. ""
$   then
$      set prot=(o:rwed) 'parts_list
$      write sys$output "del ''parts_list'"
$      del 'parts_list
$   else
$      contents_file = "''product_tape'contents.txt;*"
$      contents_file_search = f$search("''contents_file'")
$      if contents_file_search .nes. ""
$      then
$         set prot=(o:rwed) 'contents_file
$         write sys$output "del ''contents_file'"
$         del 'contents_file
$      endif
$   endif
$!
$   if (product .eqs. "TW") .or. (product .eqs. "G2")
$   then
$      gensym_site = "''product_tape'gensym-''product'.ok;*"
$      file = f$search("''gensym_site'")
$      if file .nes. ""
$      then
$          set prot=(o:rwed) 'gensym_site
$          write sys$output "del ''gensym_site'"
$          del 'gensym_site
$      endif
$   endif
$!
$   write sys$output "You must now create the version.txt file."
$!   open/write vers_txt VERSION.TXT
$!   write vers_txt "V''release_id;"
$!   write vers_txt product
$!   write vers_txt "''product'0''release_id'"
$!   close vers_txt
$!
$   goto EXIT
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$ USAGE:
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!
$    write sys$output "Usage: @promote-product -i <product> <machine-id> <source-dir> <release-id> [-NOCONFIRM]
$    write sys$output "  Or   @promote-product -e <product> <machine-id> <internal-id> <external-id> [<spin-id>]"
$    write sys$output "      where <spin-id> is the sandbox-id from which iship was promoted."
$    write sys$output "  E.g. @promote-product -i gsi alphavms sbxdisk:[''buildsandbox'.dst.vax.g2.tape] 40r2-BA20"
$    write sys$output "  Or   @promote-product -e gsi vax 10r2-BK07 10r2 ''builduser'"
$    status = 3
$    goto EXIT
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$ EXIT:
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!
$    write sys$output  ""
$    if status .eqs. 0
$    then
$      write sys$output  "LOG: Promote for ''ship_name' Shipment of ''product_id' succeeded."
$      write sys$output  ""
$    else
$      if status .eqs. 1
$      then
$         write sys$output  "ERROR: Promote for ''ship_name' Shipment FAILED for ''product_id'!"
$         write sys$output  "       You should remove this incomplete promotion."
$         write sys$output  "       To remove it, use @remove-product -i ''product' ''release_id' ''machine_id'"
$       endif
$    endif
$!
$    exit status
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$! Additional Comments
$! -------------------
$!
$! Note that each promotion uses up disk space on the servers, and so efforts
$! should be made to clean up old promotions when they are no longer useful.
$!
$! For the format of release identification numbers, see
$! /gensym/tools/readme-promoting.txt on a unix machine.
$!
$! It's an illusion that this script is a replica of the Unix
$! promote-product.  Savesets must be restored using the path from
$! which they were created. This script (now) creates savesets from
$!   [bt.<spinid>.dst.<platform>.<product>.tape]
$! This is used explicitly in the select statement.
$! Because only g2, gsi, and tw are built in such a directory, this script is
$! useless for other products.  There used to be more complex product
$! validation, but I removed it since it's unlikely that this script
$! will ever become more general.    - mes 11/22/99
