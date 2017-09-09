@echo off
rem %1 - Launcher
rem
rem %2 - Working copy (e.g. c:\g2) 
rem      or installed version (e.g. "C:\Program Files (x86)\Gensym\g2-8.3r1") 
rem      home directory
rem %3 - nonempty argument means to run performance test against installer 
rem      (e.g. installer)
rem 

setlocal
SETLOCAL ENABLEDELAYEDEXPANSION

set G2EXE=g2.exe

if ([%2]==[]) goto nosite
set WORKING_COPY=%~2
set G2_MODULE_SEARCH_PATH=
rem ADD NON STANDARD KB SEARCH PATHS HERE:
if exist "%WORKING_COPY%\integrity\examples" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%WORKING_COPY%\integrity\examples'

:nosite

call :count-g2-procs
set ORIG_CNT=%NUM_OF_G2_PROCS%

call %1 %2 %3
timeout 4 /nobreak 1>NUL

:still_running
timeout 1 /nobreak 1>NUL
call :count-g2-procs
if %NUM_OF_G2_PROCS% gtr %ORIG_CNT% goto still_running

goto :EOF

:count-g2-procs
set NUM_OF_G2_PROCS=0
for /F "tokens=1-2" %%A in ('tasklist.exe /nh /fi "imagename eq %G2EXE%"') do (
  set /A NUM_OF_G2_PROCS=!NUM_OF_G2_PROCS!+1
)
goto :EOF
