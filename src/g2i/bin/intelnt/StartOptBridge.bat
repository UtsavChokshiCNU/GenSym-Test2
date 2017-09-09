@echo off
setlocal

echo Gensym Optimization Engine Bridge

rem
rem	This batch file launches the Optimization Bridge
rem	You may supply up to one argument
rem	   - the port number the bridge is listening for G2 connections
rem


set HM=%ROOTDIR%
set JVM=%HM%\jre

set PATH=%HM%\g2i\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\g2i\classes\G2JGope.jar;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar



cd %HM%\g2i\java

if "%1" == "" goto defaultPort

echo Starting Optimization Engine at Port %1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jgope.deploy.JGopeG2Gateway  -port %*

goto end

:defaultPort
echo Starting Optimization Engine at Port 22090 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jgope.deploy.JGopeG2Gateway  -port 22090

:end
