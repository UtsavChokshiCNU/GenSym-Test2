@echo off

rem copied from nolstudio/nolonline.bat, this batch file is used to start
rem nolonline in test environment

TITLE NeurOn-Line Studio
REM ------------------------------------------------------
REM This file should only be edited to change the following
REM paths to define PATH, CLASSPATH
REM updated November 12, 2005 by Gang Chen
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
set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%NOLSTUDIO_HOME%\NolStudioMath.jar;%NOLSTUDIO_HOME%\NolStudioDeploy.jar;%NOLSTUDIO_HOME%\NolStudioData.jar;%NOLSTUDIO_HOME%\NolStudioGUI.jar

REM -- run NOL Studio --

if "%1" == "" goto arg0
if "%2" == "" goto arg1
if "%3" == "" goto arg2
if "%4" == "" goto arg3
if "%5" == "" goto arg4
if "%6" == "" goto arg5
goto arg6

:arg0
java -Xmx990m com.gensym.nols.main.NeurOnLine -root "%NOLSTUDIO_HOME%"
goto done

:arg1
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -root "%NOLSTUDIO_HOME%"
goto done

:arg2
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -root "%NOLSTUDIO_HOME%"
goto done

:arg3
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -interfaceclass %3 -root "%NOLSTUDIO_HOME%"
goto done

:arg4
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -interfaceclass %3 -interfacename %4 -root "%NOLSTUDIO_HOME%"
goto done

:arg5
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -interfaceclass %3 -interfacename %4 -listenerport %5 -root "%NOLSTUDIO_HOME%"
goto done

goto result%ERRORLEVEL%
:result1
echo An Error has Occurred!
pause
:problem
echo The installation home is not set!
:result0
REM else nothing has gone wrong, exit and do nothing...
:done
