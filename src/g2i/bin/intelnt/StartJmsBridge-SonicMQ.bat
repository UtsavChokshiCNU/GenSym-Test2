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

set SONICMQ_HOME=C:\Program Files\SonicSoftware\SonicMQ
set SONICMQ_LIB=%SONICMQ_HOME%\lib

set SONIC_LIB=%SONICMQ_LIB%;%SONICMQ_LIB%\sonic_Client.jar;%SONICMQ_LIB%\broker.jar;%SONICMQ_LIB%\jndi.jar;%SONICMQ_LIB%\mfcontext.jar

set PATH=%HM%\jms\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\jms\classes\G2Jms.jar;%SONIC_LIB%;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for Sonic MQ Version 5.0.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %*

goto end

:defaultPort
echo Starting G2-JMS Bridge for Sonic MQ Version 5.0.1
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22070

:end