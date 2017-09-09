@echo off
setlocal

rem
rem This batch file launches LW 7 with a full -module-search-path provided.
rem You may supply all valid G2 commandline arguments.

call %~dp0\StartLW-common.bat
set SBCL_HOME=%SRCBOX%\tools\lisp\sbcl-1.3.7\

cd C:/G2/src/lisp
"%SRCBOX%\tools\lisp\sbcl-1.3.7\sbcl.exe" %G2_ARGS%
