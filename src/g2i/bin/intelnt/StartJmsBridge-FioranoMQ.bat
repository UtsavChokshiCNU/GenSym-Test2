@echo off
setlocal

rem
rem	This batch file launches the JMSlink Bridge
rem	You may supply up to one argument
rem	   - the port number the bridge is listening for G2 connections
rem        - default port number: 22070
rem


set HM=%ROOTDIR%
set JVM=%HM%\jre

SET FMQ_DIR=C:\Program Files\Fiorano\FioranoMQ7.0
set FMQ_LIB=%FMQ_DIR%\lib\common.zip;%FMQ_DIR%\lib\fmprtl.zip

set PATH=%HM%\jms\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\jms\classes\G2Jms.jar;%FMQ_LIB%;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for Fiorano MQ Version 7.0
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %*

goto end

:defaultPort
echo Starting G2-JMS Bridge for Fiorano MQ Version 7.0
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22070

:end