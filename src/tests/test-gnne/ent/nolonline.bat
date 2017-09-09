@echo off

rem copied from nolstudio/nolonline.bat, this batch file is used to start
rem nolonline in test environment

TITLE NeurOn-Line Deployment
REM ------------------------------------------------------
REM updated February 09, 2002 by Gang Chen
REM ------------------------------------------------------

rem First setup environment variables for on line environment.

set TEST_FOLDER=%~dp0

rem Set up JAVA_HOME
call %TEST_FOLDER%\..\set-up-java.bat
set JAVA_HOME=%ENT_JAVA_HOME%

set SRCBOX=%TEST_FOLDER%\..\..\..
set DSTBOX=%SRCBOX%\..\dst

mkdir %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo
mkdir %DSTBOX%\javalink\classes\com\gensym\classes\modules\javalink

xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.java %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.class %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\*.ser %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\jgidemo\generate-classes.bat %DSTBOX%\javalink\classes\com\gensym\classes\modules\jgidemo\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\javalink\*.java %DSTBOX%\javalink\classes\com\gensym\classes\modules\javalink\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\classes\modules\javalink\*.class %DSTBOX%\javalink\classes\com\gensym\classes\modules\javalink\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\demos\jgi\*.java %DSTBOX%\javalink\classes\com\gensym\demos\jgi\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\demos\jgi\*.class %DSTBOX%\javalink\classes\com\gensym\demos\jgi\ /R /Y /Q
xcopy %SRCBOX%\java\com\gensym\demos\jgi\DownloadJgiDemoClasses.bat %DSTBOX%\javalink\classes\com\gensym\demos\jgi\ /R /Y /Q

set JAVALINK_HOME=%DSTBOX%\javalink
set NOLSTUDIO_HOME=%SRCBOX%\nolstudio\out\Jar

set PATH=%JAVALINK_HOME%\lib\x64;%JAVA_HOME%\bin;%PATH%
set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%NOLSTUDIO_HOME%\NolStudioMath.jar;%NOLSTUDIO_HOME%\NolStudioDeploy.jar;%NOLSTUDIO_HOME%\NolStudioData.jar

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
