@echo off
setlocal

echo ReThink Client

rem
rem	This batch file launches the ReThink Client.
rem	You may supply up to two arguments
rem		- 1st argument  = Server
rem		- 2nd argument = the tcp/ip port the server should use to listen for
rem			client conenctions.
rem

set SITE_=%ROOTDIR%




rem
rem	Set default settings
rem

set TITLE_="ReThink 5.0 Alpha 0 Client"
set TCP_EXACT=
set HM=%SITE_%
set TW_PATH=%HM%\g2
set HOSTNAME=localhost
set PORTNUM=1111

rem	any argument specifed? If so must be model
rem
if  "%1" == "" goto start
set HOSTNAME=%1
if  "%2" == "" goto usage
set PORTNUM=%2

:start

echo hostname = %hostname%
echo portnum = %portnum%

set PATH=%HM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%HM%\activexlink;%HM%\odbc;%HM%\oracle;%HM%\sybase;%HM%\pi;%HM%\opclink;%HM%\gw;%HM%\g2i\bin;%HM%\corbalink;%HM%\g2;%HM%\jre\bin;%PATH%
set G2_MODULE_SEARCH_PATH=" '%HM%\optegrity\kbs' '%HM%\g2i\kbs' '%HM%\jmail\kbs' '%HM%\jms\kbs' '%HM%\g2\kbs\utils' '%HM%\gda' '%HM%\activexlink' '%HM%\odbc\kbs' '%HM%\oracle' '%HM%\pi' '%HM%\sybase' '%HM%\opclink\kbs' '%HM%\protools\kbs' '%HM%\gw' '%HM%\corbalink\kbs' '%HM%\javalink\kbs' '%HM%\tw2\kbs' '%HM%\rethink\examples' '%HM%\sockman\kbs' "
set G2_OK=%HM%\G2\g2.ok

cd %SITE_%\rethink\kbs
start %TITLE_% /b "%TW_PATH%\twng" %HOSTNAME% %PORTNUM% -background gray -log "%HM%\rethink\logs\clientlog.txt" -icon %TITLE_% -name %TITLE_%

goto end

:usage
echo Usage: %0 hostname portnum
echo   where hostname = the hostname of the machine running G2
echo         portnum = the portnumber G2 is listening on.

:end
