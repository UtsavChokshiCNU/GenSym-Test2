@echo off

set SRCBOX=%~dp0../../..
call "%SRCBOX%/scripts/nt/set-boxes.bat"
call "%SRCBOX%/scripts/nt/vcvars.bat" x86

call nmake -f %SRCBOX%\g2db\java\G2JDBC\mak\intelnt-auth
