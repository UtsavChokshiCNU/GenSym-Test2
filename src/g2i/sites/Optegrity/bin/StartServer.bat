rem @echo off
setlocal

echo Optegrity Server

rem
rem	This batch file launches the Optegrity server and load a default solution.
rem	You may supply up to two arguments
rem		- 1st argument  = fullpathname of a model to load (.kb file extension)
rem		- 2nd argument = the tcp/ip port the server should use to listen for
rem			client conenctions.
rem

set SITE_=%ROOTDIR%


rem
rem	Set default settings
rem

set TITLE_="Optegrity 4.2 Rev. 1 Server"
set TCP_EXACT=
set HM=%SITE_%
set G2_PATH=%HM%\g2

set DEF_KB_="%SITE_%\optegrity\kbs\Optegrity.kb"
set KB_=%DEF_KB_%

rem	any argument specifed? If so must be model
rem
if  "%1" == "" goto start

if exist "%1" goto kb1


rem 	if model file does not exist try appending 2nd argument in case we have a directory
rem	with spaces and the 2nd argument is part of the model pathname
rem
set KB_="%1 %2"

if exist %KB_%  goto tcpip3
set KB_=%DEF_KB_%
goto tcpip2


:kb1

rem	first argument is a file that exists. Set it as the default model to load
rem	and then check for the 2nd tcpip exact argument
rem

set KB_="%1"
goto tcpip2



:tcpip3
 
rem	check 3rd argument if could be the tcpip port number
rem
if "%3" == "" goto start
set TCP_EXACT=-tcpipexact -tcpport %3
goto start


:tcpip2
 
rem	check 2nd argument if could be the tcpip port number
rem
if "%2" == "" goto start
set TCP_EXACT=-tcpipexact -tcpport %2


:start


set PATH=%HM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%HM%\activexlink;%HM%\odbc;%HM%\oracle;%HM%\sybase;%HM%\pi;%HM%\opclink;%HM%\gw;%HM%\g2i\bin;%HM%\corbalink;%HM%\g2;%HM%\jre\bin;%PATH%
set G2_MODULE_SEARCH_PATH=" '%HM%\optegrity\kbs' '%HM%\g2i\kbs' '%HM%\jmail\kbs' '%HM%\jms\kbs' '%HM%\g2\kbs\utils' '%HM%\gda' '%HM%\activexlink' '%HM%\odbc\' '%HM%\oracle' '%HM%\pi' '%HM%\sybase' '%HM%\opclink\kbs' '%HM%\protools\kbs' '%HM%\gw' '%HM%\corbalink\kbs' '%HM%\javalink\kbs' '%HM%\tw2\kbs' '%HM%\optegrity\examples' '%HM%\sockman\kbs' "
set G2_OK=%HM%\G2\g2.ok

set G2RGN1LMT=40000000
set G2RGN2LMT=3500000


cd %SITE_%\optegrity\kbs
start  %TITLE_% /b "%G2_PATH%\g2" -background gray %TCP_EXACT% -log "%HM%\optegrity\logs\g2log.txt" -icon %TITLE_% -name %TITLE_% -resourcefile "%SITE_%\g2i\kbs\resources-*.txt" -configfile "%SITE_%\g2i\kbs\config.txt" -nowindow -kb %KB_%
