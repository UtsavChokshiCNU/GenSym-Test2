@echo off

setlocal enabledelayedexpansion

call set-env

SET "PORT=%~1"
set "N=%2"
if "" == "%~3" ( 
  echo UC name is invalid
  pause&goto :EOF
) else ( set "UC=%~3" )
set "AVERAGE=%~4"
set "UC_ID=%~5"
set "OUTPUT_FILE=%UC_ID%.txt"
set "UC_ITERATIONS=%~6"
set "UC_SHUTDOWN=%~7"
set "TWNG=%~8"
rem set "REPORT=%~dp0\results\%OUTPUT_FILE%"
set "REPORT=%~dp0%UC_ID%.txt"
set "RESULTREPORT=%~dp0\results\%UC_ID%.txt"

if exist %REPORT% del /q %REPORT%
if exist %RESULTREPORT% del /q %RESULTREPORT%
if exist %REPORT%.tmp del /q %REPORT%.tmp
if exist %RESULTREPORT%.tmp del /q %RESULTREPORT%.tmp

for /L %%x in (1,1,%N%) do (
    echo Launch [%UC%]
    call run-kb.bat %UC%.kb %TWNG%

    REM Accumulate test result into temporary file
    if exist %REPORT% type %REPORT% >> %RESULTREPORT%.tmp
    if exist %RESULTREPORT% type %RESULTREPORT% >> %RESULTREPORT%.tmp

    if exist %REPORT% del /q %REPORT%
    if exist %RESULTREPORT% del /q %RESULTREPORT%
)

move /y %RESULTREPORT%.tmp %RESULTREPORT% > nul

call tests-helper.bat average-of-floats %RESULTREPORT% %AVERAGE%
echo ---------------------------------------------- >> %RESULTREPORT%
echo Average time for kb  %UC% = !AVERAGE! >> %RESULTREPORT%

endlocal