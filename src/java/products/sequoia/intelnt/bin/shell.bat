@echo off

if "%OS%" == "Windows_NT" setlocal

if not exist envvars.bat goto problem

call envvars.bat

echo "Starting the Telewindows2 Toolkit default shell. Please wait..."

java com.gensym.shell.Shell -title "Default Application Shell" %*

goto end
:problem
echo Please run this example from the Telewindows 2 Toolkit "bin" directory
echo Please use the CD command to change to that directory.
:end
