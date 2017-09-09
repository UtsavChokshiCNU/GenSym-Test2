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

set JBOSS_HM=c:\jboss-3.0.6

if "%JBOSS_HOME%" == "" goto defaultJBOSS
set JBOSS_HM=%JBOSS_HOME%
:defaultJBOSS

set JBOSS_CLIENT=%JBOSS_HM%\client

set PATH=%HM%\jms\bin;%JBOSS_HM%\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\jms\classes\G2Jms.jar;%JBOSS_CLIENT%;%JBOSS_CLIENT%\jbossall-client.jar;%JBOSS_CLIENT%\client\jbossmq-client.jar;%JBOSS_CLIENT%\jnet.jar;%JBOSS_CLIENT%\jnp-client.jar;%JBOSS_CLIENT%\log4j.jar;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for JBoss V3.0.6 Application Server...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %*

goto end

:defaultPort
echo Starting G2-JMS Bridge for JBoss V3.0.6 Application Server...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22070

:end