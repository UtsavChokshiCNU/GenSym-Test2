@echo off
call :%1 %2 %3 %4 
exit /b

:wait-for-result
:: Wait while file %1 does not exist
if not exist %1 (
	@REM[tam.srogatch][2011-01-08]: CPU usage console output helps to determine when a use-case hangs
	@typeperf -si 50 -sc 1 "\\localhost\processor(_Total)\%% Processor Time"
    goto :wait-for-result
)
exit /b

:kill-g2-and-twng
:: Wait about 5 seconds while G2 and TWNG closing
ping localhost -w 1000 -n 6 > nul
REM Kill them if they still present
taskkill /F /IM g2.exe /T > nul 2>&1
taskkill /F /IM twng.exe /T > nul 2>&1
exit /b

:wait-for-g2-closing
for /f "tokens=1 usebackq" %%t in (`tasklist /NH /FI "IMAGENAME EQ G2.exe"`) do (
  if "%%t"=="g2.exe" goto :wait-for-g2-closing
)
exit /b

:average-of-integers
:: Read specified column of integers from file and calculate its average
:: Input parameters:
::      %1 - file with data
::      %2 - Position of column containing data
:: Result:
::      AVERAGE variable is containing average of integers

REM Read numbers and sum them
set SUM=0
for /f "delims==:, tokens=%2" %%a in (%1) do (set /a SUM = SUM + %%a)

REM We have sum (SUM) and count (N) of integers. With this we may calculate average.
REM Calculating and rounding
set /a AVERAGE = ((10 * SUM) / N + 5) / 10
exit /b

:average-of-floats
:: Read specified column of floats from file and calculate its average
:: Input parameters:
::      %1 - file with data
::      %2 - position of column containing data
:: Result:
::      AVERAGE variable is containing average of floats

set SUM_1000=0
REM Read numbers and sum them
for /f "delims==:, tokens=%2" %%a in (%1) do (
    call :remove-point-and-leading-zeros %%a
    set /a SUM_1000 = SUM_1000 + VALUE
)
REM We have sum of whole parts and sum of fractional (thousandth) parts 
REM With this we calculate average

REM Calculating and rounding
set /a AVERAGE_1000 = ((10 * SUM_1000) / N + 5) / 10
set /a WHOLE = AVERAGE_1000 / 1000
set /a FRACT = AVERAGE_1000 - 1000 * WHOLE

REM Appending zeroes after decimal point
set FRACT_LEN=3
if /i %FRACT% LSS 100 set FRACT_LEN=2
if /i %FRACT% LSS  10 set FRACT_LEN=1
if %FRACT_LEN%==2 set FRACT=0%FRACT%
if %FRACT_LEN%==1 set FRACT=00%FRACT%

set AVERAGE=%WHOLE%.%FRACT%
exit /b

:remove-point-and-leading-zeros
:: Remove decimal point and leading zero from float number
:: Input parameters:
::      %1 - float number to remove point
:: Result:
::      Decimal point and leading zeroes is removed from float and result is stored to VALUE variable
set VALUE=%1
set VALUE=%VALUE:.=%
if %VALUE:~0,1%==0 set VALUE=%VALUE:~1%
if %VALUE:~0,1%==0 set VALUE=%VALUE:~1%
if %VALUE:~0,1%==0 set VALUE=%VALUE:~1%
exit /b
