@echo off
setlocal

echo G2 Optimization Engine Bridge

rem
rem	This batch file launches the Optimization Bridge
rem	You may supply up to one argument
rem	   - the port number the bridge is listening for G2 connections
rem


set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%

set PATH="%HM%\bin";"%G2%\javalink\bin";"%G2%\tw2\bin";"%G2%\gsi";%PATH%
set CLASSPATH=%HM%\java;%CLASSPATH%


rem
rem temp solution
rem
set CLASSPATH=%CLASSPATH%;%G2%\javalink\classes;%G2%\tw2\classes


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting Optimization Engine at Port %1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jgope.deploy.JGopeG2Gateway  -port %1

goto end

:defaultPort
echo Starting Optimization Engine at Port 22090 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jgope.deploy.JGopeG2Gateway  -port 22090

:end
