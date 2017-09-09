@echo off

rem ***************************************************************************
rem  RUNMAKEJNTW.BAT
rem  Author Paul B. Konigsberg
rem  Based on runmake.bat by Mike Colena
rem  Copyright (c) 1986 - 2017 Gensym Corporation.
rem  All Rights Reserved.

rem ***************************************************************************

if "%SRCBOX%" == "" goto need_env
if "%DSTBOX%" == "" goto need_env
if "%SPIN_ID%" == "" goto need_env
if "%MACHINE%" == "" goto need_env

rem
rem *** We've found the spin id ***
rem
set JNTW_COMPILE_TYPE=%1

shift

if "%JNTW_COMPILE_TYPE%" == "opt" goto got_type
if "%JNTW_COMPILE_TYPE%" == "o" goto got_type
if "%JNTW_COMPILE_TYPE%" == "clean" goto do_clean
echo ERROR: Bad COMPILE TYPE %JNTW_COMPILE_TYPE%.
goto usage


:do_clean

cd %DSTBOX%\java\o
del *.obj *.c *.h *.RES *.exe
cd %DSTBOX%\java\lib
del *.dll *.exp *.ilk *.lib *.pdb
cd %DSTBOX%\java
del /s *.class
goto end


:got_type

rem
rem *** Set the variables jutilmakefile, jgimakefile, rmimakefile, and
rem     commakefile; check for their existance. ***
rem

:setjutilmake
set JUTILMAKEFILE=%SRCBOX%\java\mkfiles\%MACHINE%-jutil
if exist %JUTILMAKEFILE% goto setjgimakefile
echo ERROR: The makefile %JUTILMAKEFILE% does not exist, exiting.
goto end

:setjgimakefile
set JGIMAKEFILE=%SRCBOX%\java\mkfiles\%MACHINE%-jgi-%JNTW_COMPILE_TYPE%
if exist %JGIMAKEFILE% goto setrmimakefile
echo ERROR: The makefile %JGIMAKEFILE% does not exist, exiting.
goto end

:setrmimakefile
set JGIRMIMAKEFILE=%SRCBOX%\java\mkfiles\%MACHINE%-jgi-rmi
set NTWRMIMAKEFILE=%SRCBOX%\java\mkfiles\%MACHINE%-ntw-rmi
if exist %JGIRMIMAKEFILE% goto setcommakefile
echo ERROR: The makefile %RMIMAKEFILE% does not exist, exiting.
goto end

:setcommakefile
set COMMAKEFILE=%SRCBOX%\java\mkfiles\%MACHINE%-container-%JNTW_COMPILE_TYPE%
if exist %COMMAKEFILE% goto makelibs
echo ERROR: The makefile %COMMAKEFILE% does not exist, exiting.
goto end


:makelibs

:makertl
call runmake.bat rtl %JNTW_COMPILE_TYPE%

:makeext
call runmake.bat ext %JNTW_COMPILE_TYPE% libtcp.lib

:makegsi
call runmake.bat gsi %JNTW_COMPILE_TYPE% libgsi.lib

:makejavaclassfiles
cd %SRCBOX%\java
call jmake.bat %SRCBOX%\java sequoia

:makermi
echo nmake -E -f %JGIRMIMAKEFILE%
nmake -E -f %JGIRMIMAKEFILE%
echo nmake -E -f %NTWRMIMAKEFILE%
nmake -E -f %NTWRMIMAKEFILE%

:makejutil
erase %SRCBOX%\java\lib\libwinutils.*
echo nmake -E -f %JUTILMAKEFILE%
nmake -E -f %JUTILMAKEFILE%

:makejgi
echo nmake -E -f %JGIMAKEFILE%
nmake -E -f %JGIMAKEFILE%

:makecom
echo nmake -f %COMMAKEFILE%
nmake -f %COMMAKEFILE%

goto end


:need_env

echo ERROR: The following environment variables need to be set
echo    SRCBOX, DSTBOX, SPIN_ID, MACHINE


:usage

echo Usage: runmakejntw.bat [o|opt|clean]



:end
rem  Clean up all variables we've created.
set JNTW_COMPILE_TYPE=
set COMMAKEFILE= 
set JGIMAKEFILE= 
set JUTILMAKEFILE=

