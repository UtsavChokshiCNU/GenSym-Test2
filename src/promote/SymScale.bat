@echo off
setlocal

rem
rem	This batch file launches G2 with a full -module-search-path provided.
rem	You may supply all valid G2 commandline arguments.

set SITE_=%ROOTDIR%

rem
rem	Set default settings
rem

set G2_EXEC=SymScale
set HM=%SITE_%
set G2_PATH=%HM%\g2
rem set "G2_ARGS=-threads 2"
rem set "G2_ARGS=-legacy"

call "%G2_PATH%\StartServer.bat" %*
