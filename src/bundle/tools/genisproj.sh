#!/bin/csh
# This script generates a Gensym Bundle InstallShield Project directory as 
# a .Zip file, suitable for production of a bundle setup using InstallGenerator
#
# How I (and I'm the typical user) personally typically use this:
#
# After I've edited one of the .rul or .h or .bmp or .txt files in my
# ishield CVS module (/bt/mhd/bundle/ishield), I do this to get them
# "compiled" into the .zip file.
#
#   cd /bt/mhd/bundle/ishield
#   rm *.zip
#   cvs up
#   /bt/mhd/bundle/tools/genisproj.sh /bt/mhd/bundle/ishield
#
# I may do this several times in a loop while editing and testing
# changes to the files in the ishield module. -mhd, 10/23/00

if ($1 == "-v") then
  shift
  set verbose = 1
endif

set sandbox_base = $SRCBOX

set master_dir = $1
if ($master_dir == "") then
  set master_dir = $sandbox_base/bundle/ishield
endif

if ($master_dir == "-h") then
  goto usage
endif

if (! -d $master_dir) then
  echo "no such directory: $master_dir"
  goto usage
endif

set master_zip = TemplateSetupProject.zip

set master_zip_full_path = $master_dir/$master_zip

if (! -e $master_zip_full_path) then
  echo "no such file: $master_zip_full_path"
  goto usage
endif



# Variable Setup

# Lists of preexisting files:
#
# Note: all the following files must preexist. Consider adding checks for
# existence of all these files.

set script_files = (BundleInfo.rul Path.rul ComponentEvents.rul \
  Precheck.rul Dialog.rul tools.rul Environment.rul Setup.rul \
  Watermarks.rul Dialog.h path.h tools.h \
  Setup.map)
set script_binary_files = (Setup.Inx Setup.Obs Setup.dbg)
set splash_files = (*-setup.bmp)
set license_files = (*license.txt)
set readme_files = (*-readme.txt)
set logo_file = gensym_logo.bmp

# Files previously registered as part of the setup script files, no longer
# to be used or to be present in the directory.  
# Currently no obsolete files.  yduJ, 11/04
set obs_script_files = ()


# Temporary directory/file names that will be created:

set temp_dir = /tmp/genisproj
set temp_zip_log_file = /tmp/genisproj-zip.log

# Locations of script, splash screen, license file, and readme in the
# unpacked project directory.  

set script_files_dir = "Script Files"

# NB: the following correspond to, and must be kept in synch with, 
# some #defines in bundle/c/InstallGenerator.c:
#
#   splash_screen_src  <=>  splash_screen_relative_dir_src
#   license_text_dir  <=>  license_text_relative_dir_path

set splash_screen_src = "Media"
set license_text_dir = "Setup Files/Compressed Files/Language Independent/OS Independent"
set readme_src = "Media"


# Misc.

# maybe make this selectable by arg.  0 to delete; 1 to not delete
set no_delete_p = 1

# occasionally/rarely, need to update the DLL file(s).  For now, just
# Gensym.dll file.  Here are notes on building it:
#
#   InstallGenerator.dsp is used to produce the InstallGenerator executable.
#   InstUtilDLL.dsp is used to produce the DLL built into our installers for
#   interpreting family file information and handling license keys.
#   
#   InstallGenerator can be simply run from the Debug directory directly.
#   
#   InstUtilDLL.dll should be copied as the following file in the Installshield
#   project:
#   
#     Setup Files/Compressed Files/Language Independent/Intel 32/Gensym.dll
#   
#   Before doing so, it should be compiled as a "release" (non-debuggable,
#   optimized) dll.  To switch, go to the Build menu. You have choices
#     
#     Build -> Set Active Configuration -> Gensym - Win32 Release
#     Build -> Set Active Configuration -> Gensym - Win32 Debug
#   
#   Choose the top one for the release.  Usually, you use the bottom one, for a
#   debuggable.


# Generally, you have to do the following by hand whenever the DLL changes.
# (Consider making that automated by this script!)
# cp -p $SRCBOX/bundle/c/Release/Gensym.dll .

set dll_files = (Gensym.dll dialog/Release/_IsUser.dll)
set dll_files_dir = "Setup Files/Compressed Files/Language Independent/Intel 32"


# Execute

goto execute

usage:
echo "usage: $0 [-v] [ishield-master-directory]"
exit 1

execute:

if (-d $temp_dir) then
  echo "Temporary directory '$temp_dir' exists, removing it."
  rm -rf $temp_dir
endif

mkdir $temp_dir
cd $master_dir
echo "unzip'ing ..."
unzip $master_zip -d $temp_dir >$temp_zip_log_file


# simple check to see if everything's ok:

if (! -d "$temp_dir/$script_files_dir") then
  echo "Error unzipping.  E.g., directory '$temp_dir/$script_files_dir' does not exist."
  exit 0
endif


# assumed unzipped OK now. no update the directory per the file lists.

cd $master_dir


# Copy files to their InstallShield Project Subdirectories

# copy each text file file with linefeed conversion:
foreach unix_text_file ($script_files)
  echo unix2dos -ascii $unix_text_file "$temp_dir/$script_files_dir/$unix_text_file"
  unix2dos -ascii $unix_text_file "$temp_dir/$script_files_dir/$unix_text_file"
end

foreach unix_text_file ($license_files)
  echo unix2dos -ascii $unix_text_file "$temp_dir/$license_text_dir/$unix_text_file"
  unix2dos -ascii $unix_text_file "$temp_dir/$license_text_dir/$unix_text_file"
end

foreach f ($readme_files)
  echo unix2dos -ascii $f "$temp_dir/$readme_src/$f"
  unix2dos -ascii $f "$temp_dir/$readme_src/$f"
end

# The gensym logo file can go in the same directory as license files
# "Setup Files/Compressed Files/Language Independent/OS Independent"

echo cp -p $logo_file "$temp_dir/$license_text_dir/$logo_file"
cp -p $logo_file "$temp_dir/$license_text_dir/$logo_file"

# normal copy (binary files):
echo cp -p $script_binary_files "$temp_dir/$script_files_dir"
cp -p $script_binary_files "$temp_dir/$script_files_dir"
echo cp -p $splash_files "$temp_dir/$splash_screen_src"
cp -p $splash_files "$temp_dir/$splash_screen_src"

foreach dll_file ($dll_files)
  if (-e $dll_file) then
    echo cp -p $dll_file "$temp_dir/$dll_files_dir"
    cp -p $dll_file "$temp_dir/$dll_files_dir"
  endif
end
# note: to remove a DLL, you must manually delete it from the temporary 
# directory created in this script and manually zip.

# remove obs script files, if present
echo cd "$temp_dir/$script_files_dir"
cd "$temp_dir/$script_files_dir"
foreach f ($obs_script_files)
  if (-e $f) echo rm $f  // OBSOLETE
  if (-e $f) rm $f
end

# all done updating the directory. now zip it up. move it back.  clean up.

cd $temp_dir
echo "zip'ing ..."
zip -r $master_dir/NEW-$master_zip * >>$temp_zip_log_file
if (! -e $master_dir/NEW-$master_zip) then
  echo "creation of new zip file $master_dir/NEW-$master_zip failed. Exiting"
  exit 0
endif
echo "renaming: $master_dir/$master_zip  =>  $master_dir/EX-$master_zip"
mv $master_dir/$master_zip $master_dir/EX-$master_zip 
echo "renaming: $master_dir/NEW-$master_zip  =>  $master_dir/$master_zip"
mv $master_dir/NEW-$master_zip $master_dir/$master_zip

echo "finished generating IS project directory as Zip file $master_dir/$master_zip"
cd $master_dir

# may be useful to comment out for debugging:
if (!($no_delete_p)) then
  echo "removing temporary directory $temp_dir & logfile $temp_zip_log_file"
  rm -rf $temp_dir
  rm -rf $temp_zip_log_file
endif

echo "DONE."

