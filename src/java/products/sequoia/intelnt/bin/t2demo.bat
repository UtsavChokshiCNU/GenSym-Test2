@echo off

if "%OS%" == "Windows_NT" setlocal

if not exist envvars.bat goto problem

call envvars.bat

echo "Starting G2, Please wait..."

call "%SEQUOIA_HOME%\bin\start_g2" -kb "%SEQUOIA_G2%\kbs\demos\mill.kb" -name "Mill" -rgn1lmt 40000000 -width 600 -height 500

echo Starting the Telewindow2 Toolkit default shell, please wait

java com.gensym.shell.Shell -title "Telewindows2 Demo (mill)" -geometry 600x500-0-0 -host localhost -port 1111

goto end
:problem
echo Please run this example from the Telewindows 2 Toolkit "bin" directory
echo Please use the CD command to change to that directory.
:end
