@echo off

setlocal
set VERSION=x86
set VER=std
if "%1"=="build_64_ent" set VERSION=x64
if "%1"=="build_64_ent" set VER=ent

xcopy %SRCBOX%\gen\mfiles\intelnt-activex-opt-%VER% %SRCBOX%\gen\mfiles\intelnt-activex-opt /R /Y
call "%SRCBOX%/scripts/nt/set-boxes.bat"
call "%SRCBOX%/scripts/nt/vcvars.bat" x86
call "%SRCBOX%/scripts/nt/runmake.bat" activex opt > %SRCBOX%/../results/build-logs/activex.txt 2>&1
