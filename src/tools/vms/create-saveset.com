$! create-saveset.com
$! Author: Mark Staknis
$!
$! usage: @create-saveset <product> <sourcedir_ellip> <destdir>
$!
$!   This script creates a saveset of the given source directory in
$! in a form suitable for restoration with the full directory hierarchy.
$! To achieve this the backup save set is created from a well known
$! directory device:[saveset.<product>] so the a backup command of form
$!  backup/select=[saveset.<product>...] <product>.sav/save <destdir_ellip>
$! can be used to restore it.
$!   Once the backup save set has been created, it can be saved on a
$! tape and restored within a kitinstal script using a little kitinstal
$! voodoo.
$!
$! Notes:
$!   The <sourcedir_ellip> should have the product as the final directory
$! within it.  The ellipsis is needed to allow the backup command to
$! preserve the directory hierarchy.
$!
$!
$    product   = p1
$    sourcedir = p2
$    destdir   = p3
$    savefile  = "''destdir'" + "''product'.sav"
$!
$! Clean out the temporary creation location first, just in case.
$!
$!   set prot=(o:rwed) [saveset.'product'...]*.*;*
$    del [saveset.'product'...]*.*;*
$    del [saveset.'product'...]*.*;*
$    del [saveset.'product'...]*.*;*
$!
$! Copy all the files from the source directory to the creation location.
$    backup 'sourcedir'*.*;* [saveset.'product'...]*.*;*
$!
$! Put the files into a save set called <product>.sav with the directory
$! hierarchy preserved.  The .sav file must not previously exist, or the
$! newly created save set will have a bad format.
$!
$    file = f$search("''savefile'")
$    if file .nes. ""
$    then
$       del 'savefile';*
$    endif
$!
$    backup [saveset.'product'...] 'savefile'/save
$!
$! Clean out the temporary build location, since it's no longer needed.
$!
$!   set prot=(o:rwed) [saveset.'product'...]*.*;*
$!   del [saveset.'product'...]*.*;*
$!   del [saveset.'product'...]*.*;*
$!   del [saveset.'product'...]*.*;*
