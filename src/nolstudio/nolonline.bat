@echo off
TITLE NeurOn-Line Deployment
REM ------------------------------------------------------
REM updated February 09, 2002 by Gang Chen
REM ------------------------------------------------------

rem First setup environment variables for on line environment.

rem If the following command does not containing expanded G2 install home, then a problem 
rem occurred with the installer, and you should edit it to create the proper value
set NOL_INSTALL_HOME=%ROOTDIR%

if "%NOL_INSTALL_HOME%" == "" goto problem
set JAVALINK_HOME=%NOL_INSTALL_HOME%\javalink
set JAVA_HOME=%NOL_INSTALL_HOME%\jre
set NOLSTUDIO_HOME=%NOL_INSTALL_HOME%

set PATH=%JAVALINK_HOME%\bin;%JAVA_HOME%\bin;%PATH%
set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%NOLSTUDIO_HOME%\nolstudio\NolStudioMath.jar;%NOLSTUDIO_HOME%\nolstudio\NolStudioDeploy.jar;%NOLSTUDIO_HOME%\nolstudio\NolStudioData.jar

set G2_HOST=%1
if "%G2_HOST%" == "" set G2_HOST="localhost"

set G2_PORT=%2
if "%G2_PORT%" == "" set G2_PORT=1111

set INTERFACE_CLASS=%3
if "%INTERFACE_CLASS%" == "" set INTERFACE_CLASS="NOLS-GATEWAY"

set INTERFACE_NAME=%4
if "%INTERFACE_NAME%" == "" set INTERFACE_NAME="nols-interface"

set LISTENER_PORT=%5
if "%LISTENER_PORT%" == "" set LISTENER_PORT=22044

java -Xmx240m com.gensym.nols.deploy.NolG2Gateway -g2host %G2_HOST% -g2port %G2_PORT% -interfaceclass %INTERFACE_CLASS% -interfacename %INTERFACE_NAME% -listenerport %LISTENER_PORT%

goto result%ERRORLEVEL%
:result1
echo An Error has Occurred!
pause
:result0
REM else nothing has gone wrong, exit and do nothing...
