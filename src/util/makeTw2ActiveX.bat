@echo off
if "%SRCBOX%" == "" goto need_env

cd "%SRCBOX%\Java"

nmake -f mkfiles\intelnt-controls-o %1
nmake -f mkfiles\intelnt-wksp-o %1

goto end:

:need_env
echo ERROR: The following environment variables need to be set
echo    SRCBOX

:end
