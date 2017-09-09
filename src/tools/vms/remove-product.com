$! remove-product.com
$! Author: John Valente
$!
$! This script is used to remove platform dependent products from the
$! promotion directories.  A copy of this file is kept on machine PROD
$! in the dist$com directory.  Its repository version is kept in /gensym/tools/vms.
$!
$! See further comments at the bottom of this file.
$!
$! Initialization
$! --------------
$    status = 0
$    eship_machine = "PROD"
$!
$! Argument Parsing
$! ----------------
$! The script requires at least three arguments:
$!   1) iship or eship - see comments below regarding eship
$!   2) product
$!   3) release number
$! If the command line contains less than three arguments, we can quickly jump
$! out and fail.
$!
$    if p3 .eqs. "" then goto USAGE
$!
$! Determine if it's iship or eship.  
$!
$    if (p1 .eqs. "-I")
$    then
$      eship = 0
$    else
$      if (p1 .eqs. "-E") .or. (p1 .eqs. "-TEST")
$      then
$        eship = 1
$      else
$        write sys$output "ERROR:  The first argument, ''p1', must be -i."
$        goto USAGE
$      endif
$   endif
$!
$! Parse the product argument
$!
$   product    = p2
$   release_id = p3
$!
$!
$  if eship then goto ESHIP
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$ ISHIP:
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$!
$   ship_name     = "Internal"
$   builduser     = "ab"
$   product_id    = "''product'-''release_id'"
$   test_dir      = "btdisk:[gensym.ut.dev.''product_id']"
$   test_name     = "btdisk:[gensym.ut.dev]''product_id'.dir"
$   test_inside   = "btdisk:[gensym.ut.dev.''product_id'...]"
$   test_contents = "btdisk:[gensym.ut.dev.''product_id'...]*.*;*"
$   tape_file     = "btdisk:[gensym.st.''builduser'.iship]''product_id.bck;"
$!
$! Tell the user what you're about to do
$!
$   write sys$output ""
$   write sys$output "LOG: Removing Product from ''ship_name' Ship Directory"
$   write sys$output "  Product:           ''product'"
$   write sys$output "  Release Id:        ''release_id'"
$   write sys$output "  Product Directory: ''test_dir'"
$   write sys$output "  Product Dir Name:  ''test_name'"
$   write sys$output "  Product Contents:  ''test_contents'"
$   write sys$output "  Backup Save Set:   ''tape_file'"
$!
$! ... and get confirmation
$!
$  write sys$output " "
$  inquire answer "  Are you sure you want to remove this product? (y[es] or n[o])"
$  if .not. answer
$  then
$      write sys$output "Leaving ''product_id' intact and exiting."
$      write sys$output ""
$      status = 2
$      goto EXIT
$  else
$      write sys$output "LOG: Removing ''product_id'..."
$      write sys$output ""
$  endif
$!
$! Start removing test. (i.e., btdisk:[gensym.ut.dev])
$!
$  file = f$search("''test_name'")
$  if file .eqs. ""
$  then
$      write sys$output "    ''test_dir' not found"
$  else
$      file = f$search("''test_contents'")
$      if file .nes. ""
$      then
$         write sys$output  "    making writable..."
$         set prot=(o:rwed) 'test_contents
$         write sys$output  "    deleting product..."
$         write sys$output "del ''test_contents'"
$         del 'test_contents
$      endif
$!
$! See note below, "Double Deleting"
$!
$      file = f$search("''test_contents'")
$      if file .nes. ""
$      then
$         write sys$output "del ''test_contents'"
$         del 'test_contents
$      endif
$!
$      set prot=(o:rwed) 'test_name
$      write sys$output "del ''test_name';*"
$      del 'test_name;*
$  endif
$!
$!
$! Remove tape. (i.e., for iship, btdisk:[gensym.st.ab.iship])
$!
$  file = f$search("''tape_file'")
$  if file .eqs. ""
$  then
$    write sys$output "    ''tape_file' not found"
$  else
$    set prot=(o:rwed) 'tape_file'
$    write sys$output "del ''tape_file'"
$    del 'tape_file'
$  endif
$!
$  write sys$output "LOG: Done removing ''product_id'.
$  write sys$output ""
$!
$  goto EXIT
$!
$!
$! Eship stuff...
$!
$ ESHIP:
$!
$    if p4 .eqs. ""
$    then
$      write sys$output "ERROR: machine must be specified for eship."
$      write sys$output ""
$      goto USAGE
$    else
$      platforms = p4
$    endif
$!
$   host_name = f$getsyi("nodename")
$   if host_name .eqs. eship_machine
$   then
$      tape_base = "dist$disk:[usr.distribution.bridges]"
$   else
$     if p1 .eqs. "-TEST"
$     then
$        tape_base = "btdisk:[gensym.ut]"
$     else
$!!
$! The following line might be helpful if we were on the same cluster.
$! Actually, I don't know enough about it to say what is the exact
$! problem. - jv 1/30/96
$!!
$        tape_base = "prod::dist$disk:[usr.distribution.bridges]"
$        write sys$output ""
$        write sys$output "ERROR:  Sorry, this machine is not able to access the eship directories."
$        write sys$output ""
$      goto USAGE
$      endif
$   endif
$!
$!  We may want to allow both to be done.  So we would do whatever
$!  is the equivalent of foreach platform ( $platforms )
$!
$   platform      = "''platforms'"
$!
$   if platform .eqs. "ALPHAVMS"
$   then
$      product_id    = "alpha''product'''release_id'"
$   else
$      product_id    = "''product'''release_id'"
$   endif
$!
$   tape_dir      = "''tape_base'" -"]" +".''product_id']"
$   tape_name     = "''tape_base'''product_id'.dir"
$   tape_inside   = "''tape_base'" -"]" +".''product_id'...]"
$   tape_contents = "''tape_inside'*.*;*"
$   ship_name     = "External"
$!
$! Since there is no test for eship, if the tape is not found, we
$! may as well not go through with the confirmation process.
$!
$   file = f$search("''tape_name'")
$   if file .eqs. ""
$   then
$      write sys$output ""
$      write sys$output "    ''tape_dir' not found"
$      write sys$output ""
$      status = 1
$      goto EXIT
$   endif
$!
$! Tell the user what you're about to do
$!
$   write sys$output "LOG: Platform ''platform' ..."
$   write sys$output ""
$   write sys$output "LOG: Removing Product from ''ship_name' Ship Directory"
$   write sys$output "  Product:           ''product'"
$   write sys$output "  Release Id:        ''release_id'"
$   write sys$output "  Product Directory: ''tape_dir'"
$   write sys$output "  Product Dir Name:  ''tape_name'"
$   write sys$output "  Product Contents:  ''tape_contents'"
$   write sys$output "  Platforms:         ''platform'"
$!
$! ... and get confirmation
$!
$  write sys$output " "
$  inquire answer "  Are you sure you want to remove this product? (y[es] or n[o])"
$  if .not. answer
$  then
$      write sys$output "Leaving ''product_id' intact and exiting."
$      status = 2
$      goto EXIT
$  else
$      write sys$output "LOG: Removing ''product_id'..."
$  endif
$!
$! Remove eship tape
$!
$   file = f$search("''tape_contents'")
$   if file .nes. ""
$   then
$      write sys$output  "    making writable..."
$      set prot=(o:rwed) 'tape_contents
$      write sys$output  "    deleting product..."
$      write sys$output "del ''tape_contents'"
$      del 'tape_contents
$   endif
$!
$! See note below, "Double Deleting"
$!
$   file = f$search("''tape_contents'")
$   if file .nes. ""
$   then
$      write sys$output "del ''tape_contents'"
$      del 'tape_contents
$   endif
$!
$   set prot=(o:rwed) 'tape_name
$   write sys$output "del ''tape_name';*"
$   del 'tape_name;*
$!
$  write sys$output "LOG: Done removing ''product_id'.
$!
$  goto EXIT
$!
$ USAGE:
$!
$    write sys$output "Usage: @remove-product -i <product> <release-number>"
$    write sys$output "   or: @remove-product -e <product> <release-number> <platform>"
$    write sys$output " e.g.: remove-product -i g2 40r2-A01"
$    write sys$output " e.g.: remove-product -e g2 40r2 alphavms"
$    write sys$output "To use -e you must be on machine PROD."
$    write sys$output ""
$    status = 1
$!
$ EXIT:
$!
$  exit status
$!
$!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
$! Differences vs. Unix Version
$! ----------------------------
$! Completely deleted stuff about symbolic links, since VMS doesn't have
$! them and never will.
$!
$! Double Deleting
$! ---------------
$! G2 and TW have a level of subdirectories; for example, G2 has a 
$! subdirectory called 'fonts'.  When you use the del [x.y.z...]*.*;*
$! syntax on VMS, it will delete all files under [x.y.z], but not
$! subdirectories with files in them.  For example, when you say
$!   del [.g2-40r1-H30...]*.*;*
$! it will not delete the subdirectory 'fonts'.  I believe that it only
$! deletes the "leaves".  So it will delete the files inside of fonts,
$! as well as any files which are at the same level as fonts, and even
$! any EMPTY directories at the same level as fonts.  But to delete fonts
$! itself, we need to do it again.
$!
$! On the other hand, GSI does not have this problem.  And if you try to
$! delete the contents of an empty directory, you get an error which stops
$! the script.
$! 
$! So it is necessary to determine whether or not a directory is empty
$! before attempting to delete its contents, and then to repeatedly
$! delete its contents until it is empty.  At this point (1/29/96), I
$! don't know how to do this, except to "just know" that a directory
$! for any of our products does not contain any sub-subdirectories.
$! I do not have a loop; I just check twice for contents, and delete
$! each time if there are any.
$!
$! Eship
$! -----
$! At this time we cannot access eship from the build machines 
$! (due to some kind of disagreement between the Platform Engineering
$! manager and the Computing Resources manager over how the cluster
$! should be configured.)   This script will 
$! However, for compatibility with the Unix
$! version and, I hope, for future use, we will still require the user
$! to specify iship.  If the user requests iship, we will proceed;
$! otherwise, we print a message and fail.  I have left in (as comments)
$! some of the relevant code to handling the eship vs. iship distinction
$!
