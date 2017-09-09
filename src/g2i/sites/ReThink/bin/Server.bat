@echo off
setlocal

echo ReThink and e-SCOR Server

rem
rem	This batch file launches the e-SCOR server and loads a default model.
rem	You may supply up to two arguments
rem		- 1st argument  = fullpathname of a model to load (.kb file extension)
rem		- 2nd argument = the tcp/ip port the server should use to listen for
rem			client conenctions.
rem

set ESCOR_RETHINK_HOME=%ROOTDIR%



rem
rem	Evaluate the default model to load
rem
set DEF_MODEL_= "%ESCOR_RETHINK_HOME%\kbs\eSCOR.kb"
set TITLE_="e-SCOR Server"

if exist %DEF_MODEL_%  goto escor_installation

set DEF_MODEL_= "%ESCOR_RETHINK_HOME%\kbs\rethink-online.kb"

if exist %DEF_MODEL_%  goto rethink_online_installation

set DEF_MODEL_= "%ESCOR_RETHINK_HOME%\kbs\rethink.kb"

:rethink_online_installation

set TITLE_="ReThink Server"


:escor_installation


set HM=%ESCOR_RETHINK_HOME%
set MODEL_=%DEF_MODEL_%
set TCP_EXACT=""

cd "%HM%\kbs"

rem	any argument specifed? If so must be model
rem
if  "%1" == "" goto start

if exist "%1" goto model1


rem 	if model file does not exist try appending 2nd argument in case we have a directory
rem	with spaces and the 2nd argument is part of the model pathname
rem
set MODEL_="%1 %2"

if exist %MODEL_%  goto tcpip3
set MODEL_=%DEF_MODEL_%
goto tcpip2


:model1

rem	first argument is a file that exists. Set it as the default model to load
rem	and then check for the 2nd tcpip exact argument
rem

set MODEL_="%1"
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


set PATH="%HM%\bin";"%HM%\javalink\bin";"%HM%\tw2\bin";"%HM%\gsi";"%HM%\activexlink";"%HM%\odbc";"%HM%\gw";%PATH%
set G2_PATH=%HM%\G2
set G2_MODULE_SEARCH_PATH=" '%HM%\kbs' '%HM%\activexlink' '%HM%\odbc\' '%HM%\oracle' '%HM%\g2\kbs\utils' '%HM%\protools\kbs'"
set G2V6_OK=%HM%\G2\g2.ok

set G2RGN1LMT=80000000
set G2RGN2LMT=4000000

start %TITLE_% /b /min "%G2_PATH%\g2" -nowindow  %TCP_EXACT% -log "%TMP%\g2log.txt" -icon %TITLE_% -name %TITLE_% -kb %MODEL_%
