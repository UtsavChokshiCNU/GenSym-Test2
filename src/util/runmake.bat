@echo off

rem ***************************************************************************
rem  RUNMAKE.BAT

rem  Copyright (c) 1986 - 2017 Gensym Corporation.
rem  All Rights Reserved.

rem  Mike Colena
rem  based on the csh script runmake by Jim Allard

rem  The job of this script is to copy the appropriate premade makefile from the
rem  SRCBOX\gen\mfiles directory into the appropriate binary dir, cd into that
rem  directory, and then run make in that directory.  If there is a problem
rem  preparing to run the makefile or if make returns a bad status, this script
rem  exits with a non-zero status.

rem  Note that the only environment variables required by this script are SRCBOX
rem  DSTBOX, and MACHINE.  The makefile may only depend on the environment
rem  variables SRCBOX and DSTBOX.

rem  This script does not require, but will respond to the envirnoment variable
rem  NORUNMAKECP.  If this variable is set then this script will not copy the
rem  makefile.  This is intended to be used when hand work is being done on the
rem  makefiles, and the developer wants to ensure that his edits will not be
rem  overwritten.

rem  This script takes at least two arguments.  The first argument is the
rem  target to make, and the second argument is the type of compile to perform on
rem  that thing. Any additional arguments are passed on to the invocation of 
rem  make.

rem  The values of the target-to-make argument are one of the top level 
rem  directories in DSTBOX that contain object files.

rem  The values of the type-of-compile argument are either opt, o, or o-pg.
rem   These correspond to directory holding binaries, and stand for optimized,
rem   debuggable, and profiled compiles.
rem ***************************************************************************

rem ***************************************************************************
rem  Check arguments and set up variables.  The variable target holds the first
rem   argument to this script.  The variable compile_type holds the second
rem   argument.
rem  The variable target_dir holds the binary directory targeted for the make.
rem   The format of the target directory is 

rem      DSTBOX\$target\$compile_type

rem  The variable makefile holds the pathname of the generated makefile we
rem   expect to find.  It has the following format.

rem      SRCBOX\gen\mfiles\make-$target-$compile_type-$MACHINE
rem ***************************************************************************

if "%2" == "" goto usage

if NOT "%SRCBOX%" == "" goto got_srcbox
echo ERROR: The environment variable SRCBOX is not set
goto usage

rem
rem *** We've found the srcbox ***
rem
:got_srcbox

if NOT "%DSTBOX%" == "" goto got_dstbox
echo ERROR: The environment variable DSTBOX is not set
goto usage

rem
rem *** We've found the dstbox ***
rem
:got_dstbox
if NOT "%MACHINE%" == "" goto got_machine
echo ERROR: The environment variable MACHINE is not set.
goto usage

rem
rem *** We've found the machine name ***
rem
:got_machine
set TARGET=%1
set COMPILE_TYPE=%2

shift
shift

if "%COMPILE_TYPE%" == "opt" goto got_type
if "%COMPILE_TYPE%" == "o" goto got_type
if "%COMPILE_TYPE%" == "o-pg" goto got_type
echo ERROR: Bad compile_type %COMPILE_TYPE%.
goto usage

rem
rem *** Compile type is valid ***
rem
:got_type
set TARGET_DIR=%DSTBOX%\%TARGET%\%COMPILE_TYPE%
goto check_dir


rem
rem *** We've gotten all parameters and env vars. ***
rem *** We now need to ensure the directories exist. ***
rem
:check_dir
if exist %TARGET_DIR% goto getmake
echo ERROR: The target directory %TARGET_DIR% does not exist.
goto usage

:usage
echo usage: runmake target type [make args]
echo   target: rtl, g2, tw, etc.
echo   type: opt, o, o-pg
goto end 


rem
rem *** Set the variable makefile and check for its existance. ***
rem
:getmake
if NOT "%NORUNMAKECP%" == "" goto makeit1
set MAKEFILE=%SRCBOX%\gen\mfiles\%MACHINE%-%TARGET%-%COMPILE_TYPE%
if exist %MAKEFILE% goto copymake
echo ERROR: The makefile %MAKEFILE% does not exist, exiting.
goto end

rem
rem *** Everything's looking good, copy the makefile. ***
rem
:copymake
echo runmake: copy %MAKEFILE% %TARGET_DIR%\makefile
copy %MAKEFILE% %TARGET_DIR%\makefile
if NOT errorlevel 1 goto makeit1
echo ERROR: copy of %MAKEFILE% to %TARGET_DIR% failed.
goto end

rem
rem ** Makefile copied, run make. **
rem 
:makeit1
echo runmake: cd %TARGET_DIR%
cd %TARGET_DIR%
if NOT errorlevel 1 goto makeit2
echo ERROR: The cd to %TARGET_DIR% failed
goto end

:makeit2
echo runmake: nmake %1 %2 %3 %4 %5 %6 %7
nmake %1 %2 %3 %4 %5 %6 %7

:end
rem  Clean up all variables we've created.
set TARGET=
set COMPILE_TYPE=
set TARGET_DIR=
set MAKEFILE= 
