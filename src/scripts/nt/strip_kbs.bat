echo "*** Starting Utilities Release Process ***"
echo "*** Please make sure that SRCBOX and DSTBOX has been set"
REM
echo off
REM
REM *** Check & Update sb\kbs\tools\build-data.txt!! ***
REM
REM *** Definitions - VERIFY BEFORE EXECUTING!! ***
call set-boxes.bat
call setrunenv.bat
set UTILS=%SRCBOX%\kbs\tools
set G2EXE=%DSTBOX%\g2\opt\g2.exe
set OKFILE=%SRCBOX%\..\license\g2sitev83.ok
REM
REM *******************
echo .
echo "Sandbox Path:" %SRCBOX%
echo "Utility Path:" %UTILS%
echo "G2 Executable:" %G2EXE%
echo "OK File:" %OKFILE%
echo .
type %SRCBOX%\kbs\tools\build-data.txt
pause
echo .
REM
REM *******************
REM
REM *******************
REM
REM *** Build Sys-mod, Gfr, Gxl & Gms ***
%G2EXE% -start -kb %SRCBOX%\kbs\tools\release-gxl.kb -ok %OKFILE%
REM
REM *** Build Guide, Uil, etc. ***
%G2EXE% -start -kb %SRCBOX%\kbs\tools\guidepro.kb -ok %OKFILE%
REM
REM *** Build Protools & Ptroot ***
%G2EXE% -start -kb %SRCBOX%\kbs\tools\release-protools.kb -ok %OKFILE%
REM
REM *** Copy Utils to kbs (this copies distribution files to CVS (kbs)) ***
REM %G2EXE% -kb %SRCBOX%\kbs\tools\release-launch-copy.kb -module-map %UTILS%\%MODMAP% -ok %OKFILE%
REM
REM *** All Done ***
echo .
echo "*** Build Completed ***"
echo "Please check build log %SRCBOX%\kbs\tools\utilities-build-log.txt"
pause


