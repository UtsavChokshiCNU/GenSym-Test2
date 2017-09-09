@echo off
if "%SEQUOIA_G2%" == "" goto g2_in_path
rem if they aren't using SEQUOIA_G2, then we assume that they also are
rem handling module search path
setlocal
rem setup module search path to include the KBs provided with the bundle
rem note the single quotes, which will handle spaces in filenames,
rem e.g. "Program Files"
if exist "%SEQUOIA_G2%\kbs\utils" set SEQUOIA_MODULE_PATH='%SEQUOIA_G2%\kbs\utils'
set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% %SEQUOIA_MODULE_PATH%
start "G2" "%SEQUOIA_G2%\g2" %*
goto end

:g2_in_path

start "G2" g2 %*

:end
