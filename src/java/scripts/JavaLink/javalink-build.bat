@echo off


set PATH=%JAVA_HOME%/bin;%PATH%
set SRCBOX=%~dp0../../..
call "%SRCBOX%/scripts/nt/set-boxes.bat"
call "%SRCBOX%/scripts/nt/vcvars.bat" x86

set SCRIPTSBOX=%SRCBOX%
set MACHINE=Intelnt
set DISPLAY=X
set GSIBOX=%DSTBOX%\gsi\opt

md %DSTBOX%\javalink\lib
md %DSTBOX%\javalink\opt

cd %SRCBOX%\java
call nmake -f mkfiles\intelnt-jgilib-opt
