@echo off
setlocal

echo ReThink and e-SCOR Client

rem
rem	This batch file launches the ReThink and e-SCOR client.
rem	You may supply up to one argument
rem	   - the server to connect to using the format <server-name>:<server-port-number>
rem

set ESCOR_RETHINK_HOME=%ROOTDIR%


rem
rem	Evaluate the default model to load
rem

set DEF_MODEL_= "%ESCOR_RETHINK_HOME%\kbs\eSCOR.kb"

set TITLE_="e-SCOR Server"
set SERVER_=localhost:1111
set HM=%ESCOR_RETHINK_HOME%

if exist %DEF_MODEL_%  goto escor_installation

set DEF_MODEL_= "%ESCOR_RETHINK_HOME%\kbs\rethink-online.kb"

if exist %DEF_MODEL_%  goto rethink_online_installation

set DEF_MODEL_= "%ESCOR_RETHINK_HOME%\kbs\rethink.kb"

:rethink_online_installation

set TITLE_="ReThink Server"
set SERVER_=%RETHINK_SERVER%

if not "%SERVER_%"=="" goto testarg

:escor_installation


rem
rem
rem
set SERVER_=%ESCOR_SERVER%

if not "%SERVER_%"=="" goto testarg

set SERVER_=localhost:1111

: testarg
if "%1" == "" goto start
set SERVER_=%1

:start


set PATH="%HM%\bin";"%HM%\javalink\bin";"%HM%\tw2\bin";"%HM%\gsi";"%HM%\activexlink";"%HM%\odbc";"%HM%\gw";%PATH%
set JVM=%HM%\jre
set CLASSES=%HM%\classes
set CLASSPATH=%CLASSES%\escor-rethink.jar;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar;%HM%\tw2\classes\coreui.jar;%HM%\tw2\classes\sequoia.jar;%CLASSES%\jh.jar;%CLASSES%\jhall.jar;%CLASSES%\jhtools.jar;%CLASSES%\jsearch.jar;%CLASSES%\ntw-uitools.jar;%CLASSES%\generic-uitools.jar



cd  "%HM%"

start %TITLE_% /b "%JVM%\bin\javaw" -cp "%CLASSPATH%" -Dclient.server=%SERVER_% -Dclient.home="%HM%" -Dclient.defModel=%DEF_MODEL% -Djava.library.path="%HM%\javalink\bin" -Dcom.gensym.class.g2.repository="%CLASSES%" -Dcom.gensym.class.user.repository="%CLASSES%" -Dcom.gensym.class.g2.package=com.gensym.classes -Dcom.gensym.resourcecache.repository=c:\\temp -Djava.protocol.handler.pkgs=com.gensym.net -Djava.content.handler.pkgs=com.gensym.net.contents com.gensym.escor.eSCOR
