rem ********************************************
rem * REPORT_DIR - directory to save report in *
rem * %1 - KB to run                           *
rem * %2 - additional arguments                *
rem ********************************************
@echo off

if not defined GENSYM_HOME set GENSYM_HOME=%CD%\..\..\..

if defined UC_SETUP call %UC_SETUP%
rem del %UC_ID%.txt

set StartServer=%GENSYM_HOME%\src\scripts\nt\StartServer.bat
set PATH=%GENSYM_HOME%\src\scripts\nt;%GENSYM_HOME%\src\promote\bin;%PATH%

if "%StartServer%" == "" set StartServer=StartServer
if "%PORT%" == "" set PORT=1111
if "%UC_ITERATIONS%" == "" set UC_ITERATIONS=1
if "%UC_SHUTDOWN%" == "" set UC_SHUTDOWN=true

call "%StartServer%" -kb %~f1 -start -tcpport %PORT% -log log_g2_%PORT%.log -amount-of-iterations %UC_ITERATIONS% -autoshutdown %UC_SHUTDOWN%

rem Sleep to make sure G2 Server listening on ports
sleep 2

if "twng" == "%2" ( 
  SET "TWNG_PORT=%PORT%"
  call ant -buildfile %GENSYM_HOME%\src\tests\build.xml wait-port -Dwait.maxwait=30 -Dwait.port=%PORT%
  IF %ERRORLEVEL%==0 call StartTWNG.bat
)

rem exit /b
