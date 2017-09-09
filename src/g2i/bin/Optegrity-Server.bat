echo on

rem
rem	Batch file to start g2i server.
rem	You may supply up to two arguments:
rem		1. the full pathname to a top level application to load
rem		2. the full pathname to a site setup
rem     The arguments are positional, so if you want to supply a site setup,
rem     you must supply a top level application to load.
rem
rem     This file relies on the following environment variables:
rem       G2_HOME -  the location where the utility kbs can be found;
rem                  note, this should be an installed G2 bundle
rem                  (e.g., C:\PROGRA~1\Gensym\g2-8.1r0)
rem       G2i_HOME - the location where the G2i kbs can be found; this
rem                  should be the g2i module of a sandbox
rem                  (e.g., C:\bt\ab\g2i)
rem     Additionally, you may define the environment variable G2EXE, which
rem     will be used as the location for the G2 executable.  If G2EXE is not
rem     defined, the G2 in %G2HOME% will be used instead.

setlocal
set G2_HOME=C:\Program Files\Gensym\g2-8.2r2
set G2i_HOME=C:\bt\g2i
set G2_OK=%G2_HOME%\g2\g2.ok

set G2HOME_=%G2_HOME%
set G2IHOME_=%G2i_HOME%

rem  Unless G2EXE was defined explicitly beforehand, use the same location
rem  as the kbs for g2.exe

if "%G2EXE%" == "" set G2EXE=%G2HOME_%\g2

set SITE_=%G2IHOME_%\sites\DevSite

if "%2" == "" goto kb
if exist "%2" set SITE_="%2"

:kb

set KB_=%G2IHOME_%\sites\Optegrity\kbs\Optegrity-dev.kb


if "%1" == "" goto site
if exist "%1" set KB_="%1"

:site

set G2_MODULE_SEARCH_PATH="'%G2IHOME_%\sites\Optegrity\kbs' '%G2IHOME_%\sites\nol\kbs' '%G2IHOME_%\sites\e-SCOR\kbs' '%G2IHOME_%\sites\ReThink\kbs' '%G2IHOME_%\sites\Integrity\kbs' '%G2IHOME_%\sites\DevSite\kbs' '%G2IHOME_%\kbs' '%G2HOME_%\activexlink\kbs' '%G2HOME_%\odbc\kbs' '%G2HOME_%\pi\kbs' '%G2HOME_%\opclink\kbs' '%G2HOME_%\jmail\kbs' '%G2HOME_%\jms\kbs' '%G2HOME_%\protools\kbs' '%G2HOME_%\gw\kbs' '%G2HOME_%\corbalink\kbs' '%G2HOME_%\javalink\kbs' '%G2HOME_%\tw2\kbs' '%G2HOME_%\g2\kbs\utils' '%G2HOME_%\g2\kbs\demos'"
set G2_MODULE_SEARCH_PATH="%G2_MODULE_SEARCH_PATH% 'C:\bt\kbs'"

set PATH=%G2EXE%;%PATH%

cd %SITE_%\kbs
start g2 -background gray -log '%SITE_%\Logs\g2log.txt' -icon "G2i Dev" -name "G2i Dev Server" -kb %KB_% 
