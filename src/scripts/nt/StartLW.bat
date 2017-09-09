@echo off
setlocal

rem
rem This batch file launches LW with a full -module-search-path provided.
rem You may supply all valid G2 commandline arguments.

call %~dp0\StartLW-common.bat

cd C:/G2/src/lisp
start "LW" "C:\Program Files\LispWorks\lispworks-6-0-0-x64-windows.exe" %G2_ARGS%
