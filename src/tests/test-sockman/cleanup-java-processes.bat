@echo off
set PID=-1
for /F "tokens=5 delims= " %%i in ('netstat -ano ^| findstr "22044"') do set PID=%%i
if "%PID%" == "-1" (
  echo do not find process use 22044 tcp port
  goto exit-tag
)
for /F "tokens=2 delims= " %%i in ('tasklist /FI "IMAGENAME eq java.exe" /FI "WINDOWTITLE ne N/A" /NH') do if "%%i" == "%PID%" (
  echo find java process with window title and use 22044 tcp port
  taskkill /PID %PID%
)
:exit-tag
