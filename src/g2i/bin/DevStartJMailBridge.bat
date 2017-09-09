@echo off
setlocal

echo JMail Bridge

rem
rem	This batch file launches the JMail Bridge
rem	You may supply up to one argument
rem	   - the port number the bridge is listening for G2 connections
rem


set HM=%G2I_HOME%
set G2=%G2_HOME%
set JVM=%JAVA_HOME%


set PATH=%HM%\bin;%JVM%\bin;%G2%\javalink\bin;%G2%\tw2\bin;%G2%\gsi;%PATH%
set CLASSPATH=%HM%\java;%HM%\java\classes\mail.jar;%HM%\java\classes\activation.jar;%G2%\javalink\classes\core.jar;%G2%\javalink\classes\classtools.jar;%G2%\javalink\classes\javalink.jar;%G2%\javalink\classes;%G2%\tw2\classes;%CLASSPATH%


cd %HM%\java

if "%1" == "" goto defaultPort

echo Starting JMailBridge at Port %1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jmail.JMailBridge -port %1 -debug 6

goto end

:defaultPort
echo Starting JMailBridge at Default Port 22080 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jmail.JMailBridge -port 22080 -debug 6

:end
