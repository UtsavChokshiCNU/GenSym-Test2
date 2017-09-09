@echo off
setlocal

rem this batch file starts the mill demo and then starts Telewindows to connect to it

set G2_HOME=%ROOTDIR%

set MODEL_="%G2_HOME%\g2\kbs\demos\mill.kb"
set TITLE_="Mill Demo"

set TCPPORT=1212

set G2_PATH=%G2_HOME%\G2

set G2RGN1LMT=50000000
set G2RGN2LMT=5000000

call "%G2_PATH%\StartServer.bat" -tcpport %TCPPORT% -tcpipexact -icon %TITLE_% -name %TITLE_% -kb %MODEL_%

cd %G2_PATH%
call kbs\demos\sleep.exe 10

start tw.exe "Localhost" %TCPPORT%  -fullscreen -name "Mill Demo" -ui multiwindow
