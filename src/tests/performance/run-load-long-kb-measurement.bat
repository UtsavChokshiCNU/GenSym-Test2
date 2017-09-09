@echo off
setlocal enabledelayedexpansion

call set-env

set REPORT=results\load-kb-time.txt
if exist %REPORT% del /q %REPORT%
if "%1"=="" (set N=1) else (set N=%1)
SET "PORT=%~2"

for /L %%x in (1,1,%N%) do (

    echo Launch [load-long-kb-measurement]
    echo Start time: [!TIME!] >> !REPORT!
    call run-kb ALL-G2-x64-abort-2.kb
    echo End time: [!TIME!] >> !REPORT!
)

set CENTISECONDS=0
set TIMESTAMP1=0
set TIMESTAMP2=0
set INTERVAL=0
for /f "tokens=3,4,5,6 delims=[]:. " %%i in (%REPORT%) do (

    if "!TIMESTAMP1!"=="0" (
        set /a TIMESTAMP1 = 360000 * 100 + 360000 * %%i + 6000 * 1%%j + 100 * 1%%k + 1%%l
    ) else (
        set /a TIMESTAMP2 = 360000 * 100 + 360000 * %%i + 6000 * 1%%j + 100 * 1%%k + 1%%l
        set /a INTERVAL = TIMESTAMP2 - TIMESTAMP1
    )

    if /i !INTERVAL! LSS 0 (
      set /a TIMESTAMP2 = !TIMESTAMP2! + 24 * 360000
      set /a INTERVAL = !TIMESTAMP2! - !TIMESTAMP1!
    )
    
    if /i !INTERVAL! GTR 0 (
      set /a CENTISECONDS = !CENTISECONDS! + !INTERVAL!
      set /a TIMESTAMP1 = 0
      set /a TIMESTAMP2 = 0
      set /a INTERVAL = 0
    )
)

set /a CENTISECONDSAVG = CENTISECONDS / N
set /a SECONDSAVG = CENTISECONDSAVG / 100
set /a SECONDSFRACAVG = CENTISECONDSAVG  - SECONDSAVG * 100
set /a HOURS   = SECONDSAVG / 3600
set /a SECONDS = SECONDSAVG - 3600 * HOURS
set /a MINUTES = SECONDS / 60
set /a SECONDS = SECONDSAVG - 60 * MINUTES

if /i !HOURS!   LEQ 9 set HOURS=0!HOURS!
if /i !MINUTES! LEQ 9 set MINUTES=0!MINUTES!
if /i !SECONDS! LEQ 9 set SECONDS=0!SECONDS!

echo ---------------------------------------------- >> %REPORT%
echo Average KB loading time = !HOURS!:!MINUTES!:!SECONDS! (!SECONDSAVG!.!SECONDSFRACAVG! s) >> %REPORT%
endlocal
