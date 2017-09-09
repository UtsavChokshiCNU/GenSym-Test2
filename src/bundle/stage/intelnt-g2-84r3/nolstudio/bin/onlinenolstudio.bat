@echo off
TITLE NeurOn-Line Studio
REM ------------------------------------------------------
REM This file should only be edited to change the following
REM paths to define PATH, CLASSPATH
REM updated November 12, 2005 by Gang Chen
REM ------------------------------------------------------
SET NOL_INSTALL_HOME=%ROOTDIR%

if "%NOL_INSTALL_HOME%" == "" goto problem
if "%JAVA_HOME%" == "" set JAVA_HOME=%NOL_INSTALL_HOME%\jre

set JAVALINK_HOME=%NOL_INSTALL_HOME%\javalink
set NOLSTUDIO_HOME=%NOL_INSTALL_HOME%
set PATH=%JAVALINK_HOME%\bin;%PATH%;%JAVA_HOME%\bin;%NOLSTUDIO_HOME%\nolstudio\bin
set CLASSPATH=%JAVALINK_HOME%\classes;%JAVALINK_HOME%\classes\core.jar;%JAVALINK_HOME%\classes\classtools.jar;%JAVALINK_HOME%\classes\javalink.jar;%JAVALINK_HOME%\classes\beanbuilder.jar;%NOLSTUDIO_HOME%\nolstudio\NolStudioMath.jar;%NOLSTUDIO_HOME%\nolstudio\NolStudioDeploy.jar;%NOLSTUDIO_HOME%\nolstudio\NolStudioData.jar;%NOLSTUDIO_HOME%\nolstudio\NolStudioGUI.jar

REM -- run NOL Studio --

if "%1" == "" goto arg0
if "%2" == "" goto arg1
if "%3" == "" goto arg2
if "%4" == "" goto arg3
if "%5" == "" goto arg4
if "%6" == "" goto arg5
goto arg6

:arg0
java -Xmx990m com.gensym.nols.main.NeurOnLine -root "%NOLSTUDIO_HOME%\nolstudio"								   
goto done

:arg1
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -root "%NOLSTUDIO_HOME%\nolstudio"								   
goto done

:arg2
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -root "%NOLSTUDIO_HOME%\nolstudio" 								   
goto done

:arg3
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -interfaceclass %3 -root "%NOLSTUDIO_HOME%\nolstudio"							   
goto done

:arg4
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -interfaceclass %3 -interfacename %4 -root "%NOLSTUDIO_HOME%\nolstudio"							   
goto done

:arg5
java -Xmx990m com.gensym.nols.main.NeurOnLine -g2host %1 -g2port %2 -interfaceclass %3 -interfacename %4 -listenerport %5 -root "%NOLSTUDIO_HOME%\nolstudio"								   
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
