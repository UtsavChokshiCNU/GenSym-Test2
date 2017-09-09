@echo off
SET "ERROR_MESSAGE=^<AARcontrol^>Internal error: wrong hardware was used ^(2 processors expected^)^</AARcontrol^>"

for /f "tokens=1,2,3 delims=: " %%a in ('systeminfo') do (
  if "Processor(s)" == "%%c" ( 
    if "2" neq "%%b" ( echo %ERROR_MESSAGE%&exit /b 1 )
  )
)