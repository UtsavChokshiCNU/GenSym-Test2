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

if "%ActiveMQ_HOME%" == "" set ActiveMQ_HOME=C:\Program Files (x86)\apache-activemq-5.13.2
set ActiveMQ_LIB=%ActiveMQ_HOME%\activemq-all-5.13.2.jar;%ActiveMQ_HOME%\lib\jndi.properties

set PATH=%HM%\jms\bin;%ActiveMQ_HOME%\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\jms\classes\G2Jms.jar;%ActiveMQ_LIB%;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for for ActiveMQ V5.13.2 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -? -debug -port %*

goto end

:defaultPort
echo Starting G2-JMS Bridge for ActiveMQ V5.13.2 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -? -debug -port 22070

:end
