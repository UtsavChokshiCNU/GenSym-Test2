@echo off

rem * This script will compile all of the java files necessary to run T2
rem * out of a sandbox.  For this first revision, it does no error checking.

cd %SRCBOX%\java

echo devtools
call %SCRIPTSBOX%\scripts\nt\jmake.bat com/gensym/devtools devtools

echo javalink
call %SCRIPTSBOX%\scripts\nt\jmake.bat . javalink

echo sequoia
call %SCRIPTSBOX%\scripts\nt\jmake.bat . sequoia

if not "%1" == "g2studio" goto end
echo g2studio
call %SCRIPTSBOX%\scripts\nt\jmake.bat . g2studio

:end
