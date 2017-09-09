@echo off

rem * bt.bat -- This is, to an extent, one rare example where Windows wins.
rem * We cannot have a true bt script on Unix, because scripts run in their
rem * own process.  If you run a script which changes directories, it starts a
rem * brand new shell process, changes the working directory, and then exits,
rem * leaving your original shell exactly where it was.  Windows is not so
rem * smart, so a bt.bat batch file works just fine.

rem *
rem * On Windows, cd is a little strange.  It changes you to the requested
rem * directory on the requested drive, but doesn't change your "working drive."
rem * To change working drives, you issue a command consisting of the drive
rem * letter and a colon, and that's it.  If you have BT_DRIVE set to such a
rem * command, this script will change drives for you.  So, if your sandbox
rem * is k:\bt\ab, you should set BT_DRIVE to k: and SRCBOX to k:\bt\ab.  You
rem * could also just set SRCBOX to \bt\ab, but then you absolutely need to
rem * have BT_DRIVE set, and there's really no disadvantage to including the
rem * drive letter in the SRCBOX value.
rem *
%BT_DRIVE%

if "%1" == "" goto toplevel

rem *
rem * The idea here is, you can say "bt j wksp" and it will take you
rem * to ${SRCBOX}\java\com\gensym\wksp.  You shouldn't need to type
rem * "java\com\gensym" so often.  It's kind of a separate top-level.
rem *
if "%1" == "j" goto java

cd %SRCBOX%\%1
goto end

:java
cd %SRCBOX%\java\com\gensym\%2
goto end

:toplevel
cd %SRCBOX%

:end
