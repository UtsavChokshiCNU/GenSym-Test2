@echo off

rem * dbt.bat -- see comments in bt.bat

%BT_DRIVE%

if "%1" == "" goto toplevel

cd %DSTBOX%\%1
goto end

:toplevel
cd %DSTBOX%

:end
