@echo off

echo "sbrunmake.bat %1 %2 %3 %4 %5" > C:\SFU\tmp\last-sbrunmake.bat

rem Old version (which never existed) would say util_name=util
set util_name=scripts\nt

if "%5" == "" goto usage

set SRCBOX=%1
shift

set DSTBOX=%1
shift

set SITE_HOME=%1
shift

set target=%1
shift

set type=%1
shift

%SITE_HOME%\%util_name%\runmake.bat %target% %type% %1 %2 %3 %4 %5 %6 %7 %8
goto end

:usage
echo usage: sbrunmake SRCBOX DSTBOX toolsdir target type [make args]
echo   target: rtl, g2, tw, etc.
echo   type: opt, o, o-mt, o-pg, opt-intc
goto end 

:end
rem  Clean up all variables we've created.
set SRCBOX=
set DSTBOX=
set SITE_HOME=
set util_name=
set target=
set type=
