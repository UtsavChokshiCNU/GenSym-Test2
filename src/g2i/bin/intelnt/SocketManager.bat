@echo off
setlocal

echo Java Socket Manager Bridge

rem
rem	This batch file launches the Java Socket Manager Bridge
rem	You may supply up to one argument
rem	   - the port number the bridge is listening for G2 connections
rem


set HM=%ROOTDIR%
set JVM=%HM%\jre

set PATH=%HM%\sockman\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\sockman\classes;%HM%\sockman\classes\SocketManager.jar;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


cd %HM%\sockman\classes

if "%1" == "" goto defaultPort

echo Starting Java Socket Manager Bridge at Port %1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.SocketManager.JavaG2SocketManager -port %*

goto end

:defaultPort
echo Starting Java Socket Manager Bridge at Default Port 22044 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.SocketManager.JavaG2SocketManager -port 22044 -debug 6

:end
