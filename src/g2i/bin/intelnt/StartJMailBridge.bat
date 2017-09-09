@echo off
setlocal

echo JMail Bridge

rem
rem	This batch file launches the JMail Bridge
rem	You may supply up to one argument
rem	   - the port number the bridge is listening for G2 connections
rem


set HM=%ROOTDIR%
set JVM=%HM%\jre

set PATH=%HM%\jmail\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\jmail\classes\G2JMail.jar;%HM%\jmail\classes\mail.jar;%HM%\jmail\classes\activation.jar;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


cd %HM%\jmail\classes

if "%1" == "" goto defaultPort

echo Starting JMail Bridge at Port %1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jmail.JMailBridge -port %*

goto end

:defaultPort
echo Starting JMail Bridge at Default Port 22080 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jmail.JMailBridge -port 22080 -debug 6

:end
