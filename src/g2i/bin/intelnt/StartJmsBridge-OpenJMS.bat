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

if "%OPENJMS_HOME%" == "" set OPENJMS_HOME=C:\openjms-0.7.6.1
set POLICY_FILE=%OPENJMS_HOME%\config\openjms.policy
set OPENJMS_LIB=%OPENJMS_HOME%\lib\openjms-client-0.7.6.1.jar;%OPENJMS_HOME%\lib\jta-1.0.1.jar

set PATH=%HM%\jms\bin;%OPENJMS_HOME%\bin;%JVM%\bin;%HM%\javalink\bin;%HM%\tw2\bin;%HM%\gsi;%PATH%
set CLASSPATH=%HM%\jms\classes\G2Jms.jar;%OPENJMS_LIB%;%HM%\javalink\classes\core.jar;%HM%\javalink\classes\classtools.jar;%HM%\javalink\classes\javalink.jar


if "%1" == "" goto defaultPort

echo Starting G2-JMS Bridge for for OpenJMS V7.6.1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port %*

goto end

:defaultPort
echo Starting G2-JMS Bridge for OpenJMS V7.6.1 ...
"%JVM%\bin\java" -cp "%CLASSPATH%" com.gensym.jms.G2Jms -port 22070

:end