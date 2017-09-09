@echo off

if "" neq "%~1" ( set TWNG_PORT=%1 )
if "" == "%TWNG_PORT%" ( set TWNG_PORT=1111 )

call %~dp0\set-boxes.bat

shift
start "TWNG" %TWNG_PATH%\twng.exe localhost %TWNG_PORT% -verbose -log "log_twng_%TWNG_PORT%.log" -fonts '%SRCBOX%\promote\fonts' %1 %2 %3 %4 %5 %6 %7 %8 %9
