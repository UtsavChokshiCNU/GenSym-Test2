@echo off
setlocal

rem
rem	This batch file launches G2 with a full -module-search-path provided.
rem	You may supply all valid G2 commandline arguments.

set SITE_=%ROOTDIR%

rem
rem	Set default settings
rem

set TITLE_="Gensym NeurOn-Line Rev. 1 Server"
set HM=%SITE_%
set G2_PATH=%HM%\g2


:start


set PATH=%HM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%HM%\activexlink\bin;%HM%\odbc\bin;%HM%\oracle\bin;%HM%\sybase\bin;%HM%\pi\bin;%HM%\opclink;%HM%\gw;%HM%\g2i\bin;%HM%\corbalink;%HM%\g2;%HM%\jre\bin;%PATH%

if exist "%HM%\g2i\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\g2i\kbs'
if exist "%HM%\jmail\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\jmail\kbs'
if exist "%HM%\jms\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\jms\kbs'
if exist "%HM%\g2\kbs\utils" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\g2\kbs\utils'
if exist "%HM%\gda\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\gda\kbs'
if exist "%HM%\activexlink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\activexlink\kbs'
if exist "%HM%\odbc\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\odbc\kbs'
if exist "%HM%\oracle\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\oracle\kbs'
if exist "%HM%\pi\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\pi\kbs'
if exist "%HM%\sybase\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\sybase\kbs'
if exist "%HM%\opclink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\opclink\kbs'
if exist "%HM%\protools\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\protools\kbs'
if exist "%HM%\gw\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\gw\kbs'
if exist "%HM%\corbalink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\corbalink\kbs'
if exist "%HM%\javalink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\javalink\kbs'
if exist "%HM%\sockman\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\sockman\kbs'
if exist "%HM%\tw2\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\tw2\kbs'
if exist "%HM%\optegrity\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\optegrity\kbs'
if exist "%HM%\nol\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\nol\kbs'
if exist "%HM%\rethink\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\rethink\kbs'
if exist "%HM%\escor\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\escor\kbs'
if exist "%HM%\integrity\kbs" set G2_MODULE_SEARCH_PATH=%G2_MODULE_SEARCH_PATH% '%HM%\integrity\kbs'


if "%G2_OK%" == "" set G2_OK=%HM%\G2\g2.ok

if "%G2RGN1LMT" == "" set G2RGN1LMT=40000000
if "%G2RGN2LMT" == "" set G2RGN2LMT=3500000

cd %G2_PATH%

start %TITLE_% /b "%G2_PATH%\g2"  %1 %2 %3 %4 %5 %6 %7 %8 %9 -icon %TITLE_% -name %TITLE_% -resourcefile '%SITE_%\g2i\kbs\resources-*.txt' -configfile '%SITE_%\g2i\kbs\config.txt'

