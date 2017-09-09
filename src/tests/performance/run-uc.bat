@echo off
rem 
rem %1 - Working copy (e.g. c:\g2) 
rem      or installed version (e.g. "C:\Program Files (x86)\Gensym\g2-8.3r1") 
rem      home directory
rem %2 - nonempty argument means to run performance test against installer 
rem      (e.g. installer)
rem 

setlocal

set GENSYM_HOME=%~1
set USE_INSTALLED_VERSION=%~2
if not defined GENSYM_HOME set GENSYM_HOME=%CD%\..\..\..

if defined UC_SETUP call %UC_SETUP%

del %UC_ID%.txt

if defined USE_INSTALLED_VERSION goto begin_installed 
set StartServer=%GENSYM_HOME%\src\scripts\nt\StartServer.bat
set PATH=%GENSYM_HOME%\src\scripts\nt;%PATH%
goto end_installed

:begin_installed
set StartServer=%GENSYM_HOME%\g2\StartServer.bat
:end_installed

call "%StartServer%" -start -kb %UC_KB% -amount-of-iterations %UC_ITERATIONS% -autoshutdown %UC_SHUTDOWN%
